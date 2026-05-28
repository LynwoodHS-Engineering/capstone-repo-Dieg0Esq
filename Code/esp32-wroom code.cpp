#include <Bluepad32.h>
#include <LiquidCrystal.h>

// ==================== LCD ====================
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

// ==================== ENCODER ====================
const int encoderA = 32;
const int encoderB = 33;
volatile int pulses = 0;
int lastA;
unsigned long lastTime = 0;
float rpm = 0;
const int pulsesPerRevolution = 20;

// ==================== CONTROLLER ====================
ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  
  // LCD Setup - Only RPM
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM: 0.00");
  
  // Encoder Setup
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  lastA = digitalRead(encoderA);
  
  Serial.println("=== PS5 Robot Tank - RPM Only ===");
  
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
}

void loop() {
  BP32.update();

  // ==================== RPM CALCULATION ====================
  int currentA = digitalRead(encoderA);
  if (lastA == LOW && currentA == HIGH) {
    pulses++;
  }
  lastA = currentA;

  if (millis() - lastTime >= 1000) {
    rpm = (pulses * 60.0) / pulsesPerRevolution;
    if (rpm < 1.0) rpm = 0.0;

    // Update LCD - ONLY RPM
    lcd.setCursor(0, 0);
    lcd.print("RPM: ");
    lcd.print(rpm, 2);
    lcd.print("    ");   // Clear extra characters

    Serial.print("RPM: ");
    Serial.println(rpm);

    pulses = 0;
    lastTime = millis();
  }

  // ==================== CONTROLLER CONTROL ====================
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    ControllerPtr ctl = myControllers[i];
    
    if (ctl && ctl->isConnected()) {
      
      int R2 = ctl->throttle();
      int L2 = ctl->brake();
      int rightX = ctl->axisRX();
      int leftX = ctl->axisX();

      // Drivetrain
      if (R2 > 150)       Serial2.print('F');
      else if (L2 > 150)  Serial2.print('B');
      else if (rightX < -180) Serial2.print('L');
      else if (rightX > 180)  Serial2.print('R');
      else                Serial2.print('S');

      // Turret 
      if (leftX < -180)       Serial2.print('Q');
      else if (leftX > 180)   Serial2.print('E');
      else                    Serial2.print('T');

      // Punch
      if (ctl->b()) {
        Serial2.print('P');
        delay(600);
      }

      delay(45);
    }
  }
  delay(10);
}

// ====================== CALLBACKS ======================
void onConnectedController(ControllerPtr ctl) {
  Serial.println("✅ PS5 Controller CONNECTED!");
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (!myControllers[i]) { myControllers[i] = ctl; break; }
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  Serial.println("❌ PS5 Controller Disconnected");
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) { myControllers[i] = nullptr; break; }
  }
}
