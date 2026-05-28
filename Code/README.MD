# PS5 Controller Robot Tank

A remote-controlled robot tank using a PS5 DualSense controller, ESP32-WROOM, and Arduino Uno R3.

## 📋 Project Overview

This project allows full wireless control of a robot tank using a PS5 controller:
- **R2** → Forward
- **L2** → Backward
- **Right Joystick** → Turn Left / Right
- **Left Joystick** → Turret Left / Right
- **Circle Button** → Punch / Fire mechanism

Real-time RPM display on LCD screen.

---

## 🛠 Hardware Used

- **ESP32-WROOM** (Main Bluetooth + Controller)
- **Arduino Uno R3** (Motor Control)
- **PS5 DualSense Controller** (MAC: `58:10:31:21:65:D7`)
- **L298N Motor Driver** (×2)
- **16x2 LCD Display**
- **Rotary Encoder** (for RPM feedback)
- Power supply for motors (recommended separate from logic)

---

## 📦 Required Libraries & Boards

### 1. ESP32 Board
- **Board Package**: ESP32 by Espressif Systems (latest)
- **Bluepad32 Board**: ESP32 + Bluepad32 by Ricardo Quesada

**Additional Board URL:**
