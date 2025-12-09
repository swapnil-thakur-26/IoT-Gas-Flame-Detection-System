/********************************************************
  ESP32 IoT Gas & Flame Detection System (stable)
  - MQ analog on GPIO34 (ADC 0..4095)
  - Flame digital on GPIO27 (INPUT_PULLUP, LOW = flame)
  - Buzzer on GPIO25 (active buzzer)
  - Blynk New: uses BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN
  - Use Blynk.logEvent("alert", msg) for notifications (New Blynk)
*********************************************************/

// --------------------- BLYNK REQUIRED (fill these) -------------------

#define BLYNK_TEMPLATE_ID "TMPL35xHdqldT"
#define BLYNK_TEMPLATE_NAME "IOT BASED GAS AND FIRE DETECTION"
#define BLYNK_AUTH_TOKEN    "eXHb-rAxWDrR5dOjn4RtEe5dSLnHBwTI"
// --------------------- LIBRARIES ------------------------
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// --------------------- WIFI / BLYNK ---------------------
char ssid[] = "I";
char pass[] = "11111111";
char auth[] = "eXHb-rAxWDrR5dOjn4RtEe5dSLnHBwTI";

// --------------------- PINS -----------------------------
const int MQ_PIN     = 34;   // ADC input (AO -> GPIO34)
const int FLAME_PIN  = 27;   // digital input (DO -> GPIO27)
const int BUZZER_PIN = 25;   // buzzer -> GPIO25

// --------------------- PARAMETERS -----------------------
int GAS_THRESHOLD = 2500;        // default (tune this after calibration)
const int GAS_HYSTERESIS = 120; // avoid chatter
const int GAS_SAMPLES = 8;      // samples to average
const int FLAME_CONFIRM = 3;    // consecutive readings to confirm flame
const unsigned long ALERT_INTERVAL = 12000UL; // min interval between alerts (ms)

// --------------------- STATE ----------------------------
bool alarmState = false;
unsigned long lastAlertTime = 0;
int flameCounter = 0;
BlynkTimer timer;

// --------------------- HELPERS --------------------------
int readGasAvg() {
  long sum = 0;
  for (int i = 0; i < GAS_SAMPLES; ++i) {
    sum += analogRead(MQ_PIN);
    delay(8);
  }
  return (int)(sum / GAS_SAMPLES);
}

bool rawFlame() {
  // Most flame modules pull DO LOW when flame is detected.
  // We enable INPUT_PULLUP and treat LOW as flame.
  return (digitalRead(FLAME_PIN) == LOW);
}

void buzzerOn()  { digitalWrite(BUZZER_PIN, HIGH); }
void buzzerOff() { digitalWrite(BUZZER_PIN, LOW); }

void sendAlert(String message) {
  unsigned long now = millis();
  if (now - lastAlertTime >= ALERT_INTERVAL) {
    Blynk.logEvent("temp_high", message);
    lastAlertTime = now;
  }
}

// --------------------- MAIN CHECK -----------------------
void checkSensors() {
  int gasVal = readGasAvg();   // 0..4095
  bool flameRaw = rawFlame();

  // Flame debounce (confirm multiple consecutive readings)
  if (flameRaw) {
    if (flameCounter < FLAME_CONFIRM) flameCounter++;
  } else {
    if (flameCounter > 0) flameCounter--;
  }
  bool flameConfirmed = (flameCounter >= FLAME_CONFIRM);

  // Gas hazard with hysteresis logic
  static bool gasPreviouslyHazard = false;
  bool gasHazard;
  if (gasPreviouslyHazard) {
    gasHazard = (gasVal >= (GAS_THRESHOLD - GAS_HYSTERESIS));
  } else {
    gasHazard = (gasVal >= GAS_THRESHOLD);
  }
  gasPreviouslyHazard = gasHazard;

  bool hazard = flameConfirmed || gasHazard;

  // Alarm handling
  if (hazard) {
    buzzerOn();
    if (!alarmState) {
      String msg = "";
      if (gasHazard) msg += "⚠ GAS LEAK! Level: " + String(gasVal) + ". ";
      if (flameConfirmed) msg += "🔥 FLAME DETECTED!";
      sendAlert(msg);
    }
    alarmState = true;
  } else {
    buzzerOff();
    alarmState = false;
  }

  // Update Blynk and Serial
  Blynk.virtualWrite(V0, gasVal);                 // gas value
  Blynk.virtualWrite(V1, flameConfirmed ? 1 : 0); // flame boolean
  Blynk.virtualWrite(V2, alarmState ? 1 : 0);     // alarm state

  // Serial debug
  Serial.print("Gas:");
  Serial.print(gasVal);
  Serial.print(" | FlameRaw:");
  Serial.print(flameRaw ? "LOW" : "HIGH");
  Serial.print(" | FlameCnt:");
  Serial.print(flameCounter);
  Serial.print(" | Confirmed:");
  Serial.print(flameConfirmed ? "YES" : "NO");
  Serial.print(" | Alarm:");
  Serial.println(alarmState ? "ON" : "OFF");
}

// --------------------- BLYNK WIDGET HANDLERS -------------
BLYNK_WRITE(V3) { // slider sets threshold remotely (0..4095)
  int val = param.asInt();
  if (val >= 0 && val <= 4095) {
    GAS_THRESHOLD = val;
    Serial.print("GAS_THRESHOLD updated via Blynk: ");
    Serial.println(GAS_THRESHOLD);
  }
}

BLYNK_WRITE(V4) { // reset alarm
  int v = param.asInt();
  if (v == 1) {
    buzzerOff();
    alarmState = false;
    flameCounter = 0;
    Serial.println("Alarm reset by user (Blynk)");
  }
}

// --------------------- SETUP & LOOP ----------------------
void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(FLAME_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  buzzerOff();

  // Connect Wi-Fi first (this may block until connected)
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
    if (millis() - start > 20000) break; // 20s timeout
  }
  if (WiFi.status() == WL_CONNECTED) Serial.println("\nWiFi connected.");
  else Serial.println("\nWiFi not connected (timeout). Blynk will try.");

  Blynk.begin(auth, ssid, pass); // starts Blynk (will reconnect if necessary)

  timer.setInterval(1500L, checkSensors); // check sensors every 1.5s
  Serial.println("System started. Let MQ warm up (30s+).");
  Serial.print("Initial GAS_THRESHOLD: ");
  Serial.println(GAS_THRESHOLD);
}

void loop() {
  Blynk.run();
  timer.run();
}
