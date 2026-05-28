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
https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json

- **Library**: Bluepad32 by Ricardo Quesada

### 2. Arduino Uno
- No extra libraries needed.

---

## Controls

- **R2 Trigger** → Forward
- **L2 Trigger** → Backward
- **Right Joystick** → Turn Left / Right
- **Left Joystick** → Turret Left / Right
- **Circle Button** → Punch

---

## How to Upload

1. **ESP32**:
 - Open `esp32-wroom code.cpp`
 - Select board: **ESP32 Dev Module (Bluepad32)**
 - Upload

2. **Arduino Uno**:
 - Open `Arduino Uno Code.cpp`
 - Upload

3. **Connect Controller**:
 - Hold **PS + Create** button on PS5 controller until the light flashes rapidly.

---

## Notes

- Serial communication between ESP32 (GPIO16/GPIO17) and Arduino Uno (Pin 0/1)
- LCD and Encoder are connected to the ESP32
- Adjust motor speeds in the Arduino code if needed
- Use separate power supply for the motors

---

**Project by Diego Esquivel**  
**Completed:** May 2026

---

---

**How to save it:**

1. Copy all the text above.
2. Open your existing `README.MD` file.
3. Replace everything with the text above.
4. Save it.

Would you like me to make any changes to this README?
