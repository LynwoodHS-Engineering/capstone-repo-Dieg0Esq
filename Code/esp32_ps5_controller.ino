#include <ps5Controller.h>
#include <LiquidCrystal.h>

// =======================================
// UART TO ARDUINO
// =======================================
#define TX_PIN 17
#define RX_PIN 16

// =======================================
// ENCODER
// =======================================
#define ENCODER_A 32
#define ENCODER_B 33

// =======================================
// LCD
// RS, E, D4, D5, D6, D7
// =======================================
LiquidCrystal lcd(19, 18, 4, 5, 2, 21);

// =======================================
// SETTINGS
// =======================================
const int DEAD_ZONE = 30;

// YOUR PS5 CONTROLLER MAC
const char* PS5_MAC = "58:10:31:21:65:D7";

// =======================================
// VARIABLES
// =======================================
char lastCmd = 'S';
char lastTurret = 'Z';

volatile long pulseCount = 0;

unsigned long lastTime = 0;

float speed = 0;

bool wasConnected = false;

// =======================================
// ENCODER INTERRUPT
// =======================================
void IRAM_ATTR countPulse() {
  pulseCount++;
}

// =======================================
// SETUP
// =======================================
void setup() {

  Serial.begin(115200);

  // UART to Arduino
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  // PS5
  ps5.begin(PS5_MAC);

  // Encoder
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(ENCODER_A),
    countPulse,
    FALLING
  );

  attachInterrupt(
    digitalPinToInterrupt(ENCODER_B),
    countPulse,
    FALLING
  );

  // LCD
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("PS5: Waiting");

  lcd.setCursor(0, 1);
  lcd.print("RPM: 0");

  Serial.println("Tank Controller Started");
}

// =======================================
// SEND COMMANDS
// =======================================
void sendCmd(char cmd) {

  if (cmd != lastCmd) {

    Serial2.write(cmd);

    lastCmd = cmd;
  }
}

void sendTurret(char cmd) {

  if (cmd != lastTurret) {

    Serial2.write(cmd);

    lastTurret = cmd;
  }
}

// =======================================
// LOOP
// =======================================
void loop() {

  unsigned long currentTime = millis();

  // ---------------------------
  // RPM CALCULATION
  // ---------------------------
  if (currentTime - lastTime >= 1000) {

    speed = pulseCount / 90.0 * 60.0;

    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" RPM");

    lcd.setCursor(0, 1);
    lcd.print("RPM: ");
    lcd.print(speed);
    lcd.print("     ");

    pulseCount = 0;

    lastTime = currentTime;
  }

  // ---------------------------
  // CONTROLLER DISCONNECTED
  // ---------------------------
  if (!ps5.isConnected()) {

    if (wasConnected) {

      lcd.setCursor(0, 0);
      lcd.print("PS5: Disconnected");
      wasConnected = false;
    }

    sendCmd('S');
    sendTurret('Z');

    Serial2.write('O');

    delay(100);

    return;
  }

  // ---------------------------
  // CONTROLLER CONNECTED
  // ---------------------------
  if (!wasConnected) {

    lcd.setCursor(0, 0);
    lcd.print("PS5: Connected   ");

    wasConnected = true;
  }

  // ==================================
  // CONTROLLER INPUTS
  // ==================================
  int leftX  = ps5.LStickX();

  int rightX = ps5.RStickX();
  int rightY = ps5.RStickY();

  int r2 = ps5.R2Value();
  int l2 = ps5.L2Value();

  bool movingForward  = r2 > 10;
  bool movingBackward = l2 > 10;

  bool turningRight = leftX > DEAD_ZONE;
  bool turningLeft  = leftX < -DEAD_ZONE;

  bool turretRight = rightX > DEAD_ZONE;
  bool turretLeft  = rightX < -DEAD_ZONE;

  bool turretUp   = rightY > DEAD_ZONE;
  bool turretDown = rightY < -DEAD_ZONE;

  bool shoot = ps5.Cross();

  // ==================================
  // TANK CONTROL
  // ==================================
  if (turningRight) {

    sendCmd('R');

  } else if (turningLeft) {

    sendCmd('L');

  } else if (movingForward) {

    sendCmd('F');

  } else if (movingBackward) {

    sendCmd('B');

  } else {

    sendCmd('S');
  }

  // ==================================
  // TURRET CONTROL
  // ==================================
  if (turretRight) {

    sendTurret('Y');

  } else if (turretLeft) {

    sendTurret('X');

  } else if (turretUp) {

    sendTurret('U');

  } else if (turretDown) {

    sendTurret('D');

  } else {

    sendTurret('Z');
  }

  // ==================================
  // SHOOTER CONTROL
  // ==================================
  if (shoot) {

    Serial2.write('P');

  } else {

    Serial2.write('O');
  }

  delay(50);
}
