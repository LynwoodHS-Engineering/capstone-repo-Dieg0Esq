# 🛡️ EDD-Capstone - PS5 Robot Tank

**Members:** Diego Esquivel, Ulices Ayala, Aldo Torres  
May 28th, 2026


<img width="900" height="800" alt="20260527_184037" src="https://github.com/user-attachments/assets/271c7a8d-e547-482c-8a06-6f9c6da4eebe" />


## 🚀 Project Overview
This project is a remote-controlled robot tank controlled wirelessly using a **PS5 DualSense Controller**. The tank features a functional drivetrain, a rotating turret, and a puncher mechanism. It also displays real-time RPM feedback on an LCD screen.

The main goal was to create a responsive, smooth, and fun-to-control tank using modern wireless technology.

## 🛠️ Requirements & How We Met Them

For this project, we had to include at least one element from five specific categories. Here is how we implemented each one:

- **Logic, Processing & Control**: Used an **ESP32-WROOM** and **Arduino Uno R3** working together. The ESP32 handles Bluetooth communication and logic, while the Arduino controls all motors.
  
- **Manual User Input**: **PS5 DualSense Controller** — full wireless control using triggers, joysticks, and buttons.

- **Actuators & Hardware**: Two **L298N Motor Drivers** powering multiple DC motors for the drivetrain, turret rotation, and puncher mechanism.

- **Automatic Sensors**: **Rotary Encoder** used to measure and display real-time **RPM** of the drivetrain on the LCD screen.

- **Output Display**: **16x2 LCD Screen** shows live RPM feedback to the user.

## 🏗️ How It Works
The **ESP32-WROOM** connects to the PS5 controller via Bluetooth using the Bluepad32 library. It reads all controller inputs and sends simple serial commands to the **Arduino Uno**. The Arduino then controls the motors through the L298N drivers. An encoder on the ESP32 calculates the RPM and displays it on the LCD.

## Key Features
- **Wireless PS5 Control**: Smooth driving with R2/L2 triggers and joysticks
- **Functional Turret**: Rotates left and right using the left joystick
- **Puncher Mechanism**: Activated by the Circle button
- **Real-time RPM Display**: Live feedback on LCD screen
- **Strong Turning**: Full power differential drive for realistic tank movement

## 📦 Main Components
- ESP32-WROOM
- Arduino Uno R3
- PS5 DualSense Controller
- VEX 7.2 Battery
- 2x L298N Motor Driver Modules
- 16x2 LCD Display
- VEX Rotary Encoder
- Tank chassis with (2) VEX 2-Wire Motors 393
- Puncher mechanism with a VEx 2-Wire Motor 393

<img width="1000" height="1726" alt="20260527_184121 (1)" src="https://github.com/user-attachments/assets/f111799b-381b-4ecd-aa77-98f18946e4c5" />

---

## Lessons Learned 🤔

1. **PS5 Controller Pairing**  
   Problem: Initial pairing was very unstable.  
   Solution: Switched from `ps5-esp32` library to **Bluepad32** — much more reliable.

2. **Turret Stopping**  
   Problem: Turret kept moving even when joystick was centered.  
   Solution: Added explicit stop command (`'T'`) and timing logic.

3. **Turning Power**  
   Problem: Tank turned too slowly and struggled.  
   Solution: Used full PWM (255) during turns with proper differential drive.

**Recommendation:** Always test motor power separately from logic power.

---

## Instructions ❗ (How to Build & Run)

1. Install ESP32 + Bluepad32 boards in Arduino IDE (see detailed README).
2. Upload `esp32-wroom code.cpp` to the ESP32 (select Bluepad32 board).
3. Upload `Arduino Uno Code.cpp` to the Arduino Uno.
4. Connect ESP32 and Arduino via Serial (GPIO17→Pin0, GPIO16→Pin1).
5. Connect LCD and Encoder to ESP32 as defined in code.
6. Wire both L298N drivers to Arduino according to pin definitions.
7. Power motors with separate battery (7.4V–12V recommended).
8. Hold **PS + Create** on PS5 controller to connect.
9. Test controls:
   - R2 = Forward
   - L2 = Backward
   - Right Joystick = Turn
   - Left Joystick = Turret
   - Circle = Punch

---
