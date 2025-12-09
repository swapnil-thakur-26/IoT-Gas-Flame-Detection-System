# 🔥 IoT Gas & Flame Detection & Alert System (ESP32 + Blynk IoT)

This project is a real-time IoT-based safety monitoring system designed to detect **gas leakage** and **flame hazards** using an ESP32 microcontroller.  
The system triggers a **buzzer alarm**, displays **live sensor data**, and sends **instant push notifications** to the user via **Blynk IoT**.

---

## 🚀 Features

- 🔹 Gas leakage detection (MQ-series gas sensor)
- 🔹 Flame/fire detection (IR flame sensor)
- 🔹 Instant mobile alerts using Blynk Events
- 🔹 Real-time monitoring on Blynk Dashboard
- 🔹 Adjustable gas threshold (via mobile slider)
- 🔹 Local buzzer alarm for immediate awareness
- 🔹 Manual alarm reset from the app
- 🔹 WiFi-enabled IoT connectivity with ESP32

---

## 🛠️ Hardware Components

- ESP32 Dev Module (NodeMCU-32S)
- MQ Gas Sensor (MQ-2 / MQ-5 / MQ-135)
- IR Flame Sensor Module
- Active/Passive Buzzer
- Jumper Wires
- Breadboard
- USB Cable (Data Cable)

---

## 🔌 Circuit Connections (ESP32)

| Component         | ESP32 Pin |
|------------------|-----------|
| Gas Sensor A0    | GPIO 34   |
| Flame Sensor D0  | GPIO 27   |
| Buzzer +         | GPIO 25   |
| Buzzer -         | GND       |
| Sensors VCC      | 3.3V / 5V |
| Sensors GND      | GND       |

---

## 📲 Blynk IoT Setup

### 1️⃣ Create a Template  
- Add device → Select **ESP32**  
- Copy these values:
  - `BLYNK_TEMPLATE_ID`
  - `BLYNK_TEMPLATE_NAME`
  - `DEVICE_AUTH_TOKEN`

### 2️⃣ Create Datastreams  
| Datastream | Type | Pin |
|------------|-------|-----|
| Gas Value  | Integer | V0 |
| Flame State | Integer | V1 |
| Alarm State | Integer | V2 |
| Threshold Slider | Integer | V3 |
| Reset Button | Integer | V4 |

### 3️⃣ Create Event for Alerts  
- Event Name: **alert**  
- Priority: High  
- Push Notifications: **Enabled**

---

## 📟 Working Principle

1. ESP32 reads the gas and flame sensor values.
2. If levels cross the threshold or flame is detected:
   - Buzzer turns ON  
   - Blynk event triggers a mobile push notification  
3. Dashboard displays live values.
4. User can reset the alarm using a virtual button.

---

## 📄 Source Code

The full ESP32 code is available inside the [`/Code`](./Code) folder.  
It includes:

- WiFi setup  
- Blynk IoT template integration  
- Gas + Flame sensor logic  
- Alarm system  
- Cloud notifications  

---

## 🖼️ Project Images

(Add your images here in the `/Images` folder)

- Circuit Diagram  
- Hardware Setup  
- Blynk Dashboard  
- Output Results  

---

## 👥 Team Members

- **Your Name**  
- **Your Teammate’s Name**

---

## 📚 Skills Demonstrated

- Internet of Things (IoT)
- Embedded Systems
- ESP32 Development
- Sensor Integration
- Cloud IoT (Blynk)
- Real-Time Monitoring Systems
- Circuit Debugging
- C/C++ (Arduino)

---

## 📜 License

This project is licensed under the **MIT License**.

---

## ⭐ Want to Contribute?

Feel free to fork this repository and submit pull requests. Any improvements are welcome!

