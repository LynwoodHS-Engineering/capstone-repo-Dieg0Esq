// ESP32-WROOM - PS5 Tank Controller
// Reads PS5 left joystick and sends commands to Arduino
// Library: ps5Controller by rodneyBakiskan
// Wiring: ESP32 GPIO17 (TX2) -> Arduino Pin 0 (RX)
//         ESP32 GPIO16 (RX2) -> Arduino Pin 1 (TX)
//         ESP32 GND          -> Arduino GND
// Controls: Left stick up=Forward, down=Backward
//           Left stick left=Left, right=Right

#include <ps5Controller.h>

#define TX_PIN 17
#define RX_PIN 16
#define ENCODER_A 34
#define ENCODER_B 35

const int DEAD_ZONE = 30;
const char* PS5_MAC = "58:10:31:21:65:D7";

char lastCmd = 'S';
volatile long pulseCount = 0;
unsigned long lastTime = 0;
float speed = 0;

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  ps5.begin(PS5_MAC);
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), countPulse, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B), countPulse, RISING);
  Serial.println("Tank Controller Started");
  Serial.println("--------------------");
}

void sendCmd(char cmd) {
  if (cmd != lastCmd) {
    Serial2.write(cmd);
    lastCmd = cmd;
  }
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= 1000) {
    speed = pulseCount / 90.0 * 60.0;
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" RPM");
    Serial.println("--------------------");
    pulseCount = 0;
    lastTime = currentTime;
  }

  if (!ps5.isConnected()) {
    sendCmd('S');
    delay(100);
    return;
  }

  int leftX = ps5.LStickX();
  int r2    = ps5.R2Value();
  int l2    = ps5.L2Value();

  bool movingForward  = r2 > 10;
  bool movingBackward = l2 > 10;
  bool turningRight   = leftX >  DEAD_ZONE;
  bool turningLeft    = leftX < -DEAD_ZONE;

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

  delay(50);
}
