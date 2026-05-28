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
| arduino_serial_test.ino     | Serial communication test |
| esp32_serial_test.ino       | Serial communication test |
| README.MD                   | This file |

---

## 🔧 Arduino IDE Settings

### **For ESP32-WROOM**

1. Go to **Tools → Board → Boards Manager**
2. Install:
   - `esp32` by Espressif Systems (latest)
   - `ESP32 + Bluepad32` by Ricardo Quesada (latest)

3. **Board Settings** (Important):
   - **Board**: `ESP32 Dev Module (Bluepad32)`
   - **USB CDC On Boot**: Disabled
   - **CPU Frequency**: 240MHz (WiFi/BT)
   - **Flash Mode**: QIO
   - **Flash Frequency**: 80MHz
   - **Partition Scheme**: Default 4MB with spiffs
   - **Upload Speed**: 921600 (or 115200 if issues)

### **For Arduino Uno**

- **Board**: `Arduino Uno`
- **Port**: Select the correct COM port
- No other special settings needed

---

## Required Board URL (Add in Preferences)

Go to **File → Preferences** and add this in **Additional Boards Manager URLs**:
https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json



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
   - Select **ESP32 Dev Module (Bluepad32)**
   - Upload (hold BOOT button if it fails)

2. **Arduino Uno**:
   - Open `Arduino Uno Code.cpp`
   - Upload

3. **Connect Controller**:
   - Hold **PS + Create** button on PS5 controller until the light flashes rapidly.

---

## Notes

- Serial communication: ESP32 GPIO17 (TX) → Arduino Pin 0 (RX)
- Serial communication: ESP32 GPIO16 (RX) → Arduino Pin 1 (TX)
- Use separate power supply for motors
- Adjust motor speeds in Arduino code if needed

---

**Project by Diego Esquivel, Ulices Ayala, Aldo Torres**  
**Completed:** May 2026
