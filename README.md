## 🛡️ EDD-Capstone - PS5 Robot Tank
**Members:** Diego Esquivel, Ulices Ayala, Aldo Torres  
** May 28th, 2026 **

<img width="900" height="813" alt="20260527_184037" src="https://github.com/user-attachments/assets/271c7a8d-e547-482c-8a06-6f9c6da4eebe" />


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
- 2x L298N Motor Driver Modules
- 16x2 LCD Display
- Rotary Encoder
- Tank chassis with DC motors
- Puncher mechanism

---

**Project Complete**  
Diego Esquivel - May 28th, 2026
