# PS5 Controller Robot Tank 

## Project Description
This robot tank is controlled wirelessly using a **PS5 DualSense Controller**.  
It uses an **ESP32-WROOM** for Bluetooth communication and an **Arduino Uno R3** for motor control. Real-time RPM is displayed on an LCD screen.

---

## 📁 Files in this Folder

| File Name                    | Purpose |
|-----------------------------|--------|
| **esp32-wroom code.cpp**    | Main code for ESP32 (PS5 controller + RPM display + Serial commands) |
| **Arduino Uno Code.cpp**    | Main code for Arduino Uno (Motor control: Drivetrain, Turret, Puncher) |
| arduino_serial_test.ino     | serial communication test |
| esp32_serial_test.ino       | serial communication test |
| README.MD                   | This file |

---

## Required Setup

### 1. ESP32 Board & Library
- **Board**: `ESP32 Dev Module (Bluepad32)`
- **Additional Board URL**:
