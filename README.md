# 🔥 IoT Gas & Flame Detection & Alert System (ESP32 + Blynk IoT)

[![Made with ESP32](https://img.shields.io/badge/Microcontroller-ESP32-blue.svg)](#)
[![IoT Project](https://img.shields.io/badge/Category-IoT-orange.svg)](#)
[![Blynk IoT](https://img.shields.io/badge/Cloud-Blynk-green.svg)](#)
[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](#)
[![Status](https://img.shields.io/badge/Status-Active-success.svg)](#)

A real-time IoT-based **Gas & Flame Detection and Alert System** built using **ESP32**, **MQ Gas Sensor**, **Flame Sensor**, **Blynk IoT Cloud**, and a **local buzzer alarm**.  
The system monitors gas leakage and fire hazards, triggers an immediate audible alarm, and sends **instant mobile notifications** via the Blynk IoT platform.

---

## ⭐ Features

- 🔹 Real-time gas leakage detection  
- 🔹 Instant flame/fire detection  
- 🔹 Buzzer alarm for immediate awareness  
- 🔹 Cloud notifications via Blynk Events  
- 🔹 Live sensor values on Blynk Dashboard  
- 🔹 Adjustable gas sensitivity threshold  
- 🔹 Manual alarm reset using mobile app  
- 🔹 Fault-tolerant readings & smooth updates  

---

## 🛠️ Hardware Components

| Component            | Description |
|----------------------|-------------|
| ESP32 Dev Board      | Main microcontroller & WiFi module |
| MQ Gas Sensor        | Detects flammable gas concentration |
| Flame Sensor Module  | Detects fire/infrared flame presence |
| Active Buzzer        | Local audible alarm |
| Breadboard & Wires   | Circuit assembly |
| USB Cable            | Power + programming |

---

## 🔌 Circuit Connections

| Sensor/Module | ESP32 Pin |
|---------------|-----------|
| Gas Sensor A0 | GPIO 34   |
| Flame Sensor D0 | GPIO 27 |
| Buzzer (+)    | GPIO 25   |
| Buzzer (–)    | GND       |
| Sensor VCC    | 3.3V / 5V |
| Sensor GND    | GND       |

---

## 📲 Blynk IoT Setup

### Configure these virtual pins:

| Function | Virtual Pin |
|----------|-------------|
| Gas Value Display | V0 |
| Flame Status (1/0) | V1 |
| Alarm Indicator | V2 |
| Gas Threshold Slider | V3 |
| Reset Button | V4 |

### Create Event for Notifications:

- **Event Name:** `alert`  
- **Type:** Critical / High Priority  
- **Push Notifications:** ON  

---

## 📡 Working Principle

1. ESP32 reads gas & flame sensors every 300ms  
2. Threshold logic checks for dangerous levels  
3. If hazard detected:  
   - Buzzer = ON  
   - Alarm State = Active  
   - Cloud Event Trigger → Mobile Notification  
4. User may reset alarm from the app  
5. Normal readings update live on Blynk Dashboard  

---

## 🧠 Code

Full ESP32 firmware is located here:  
👉 [`/Code/main.ino`](Code/main.ino)

---

## 📄 Documentation (Visual Proof Included)

The complete minor project report containing:

- Circuit diagrams  
- Flowcharts  
- DFD levels  
- ER diagrams  
- Hardware photos  
- System testing screenshots  
- Explanation & analysis  

is available here:

👉 **[Download Project Report (PDF)](Documentation/Minor_Project_Report.pdf)**  
*(Rename this link once your actual filename is uploaded.)*

---

## 👥 Team Members

- **Swapnil Thakur**  
- **Satyam Saurav**

---

## 🧰 Skills Demonstrated

- Internet of Things (IoT)  
- Embedded Systems  
- Microcontroller Programming (ESP32)  
- Cloud Integration (Blynk IoT)  
- Sensor Interfacing (MQ/Flame)  
- Real-Time Monitoring  
- Event-Driven I/O  
- Hardware Debugging  
- C/C++ (Arduino Framework)  

---

## 📜 License

This project is released under the **MIT License** — free to use and modify with attribution.

---

## ⭐ Support & Contributions

Feel free to fork, improve, or open issues.  
Pull requests are welcome!

