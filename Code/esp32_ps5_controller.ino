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

const int DEAD_ZONE = 30;
const char* PS5_MAC = "58:10:31:21:65:D7";

char lastCmd = 'S';

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  ps5.begin(PS5_MAC);
  Serial.println("Waiting for PS5 controller...");
}

void sendCmd(char cmd) {
  if (cmd != lastCmd) {
    Serial2.write(cmd);
    lastCmd = cmd;
    Serial.print("CMD sent: ");
    Serial.println(cmd);
  }
}

void loop() {
  if (!ps5.isConnected()) {
    sendCmd('S');
    delay(100);
    return;
  }

  int leftY = ps5.LStickY();
  int leftX = ps5.LStickX();

  bool movingForward  = leftY >  DEAD_ZONE;
  bool movingBackward = leftY < -DEAD_ZONE;
  bool turningRight   = leftX >  DEAD_ZONE;
  bool turningLeft    = leftX < -DEAD_ZONE;

  if (movingForward && !turningLeft && !turningRight) {
    sendCmd('F');
  } else if (movingBackward && !turningLeft && !turningRight) {
    sendCmd('B');
  } else if (turningRight) {
    sendCmd('R');
  } else if (turningLeft) {
    sendCmd('L');
  } else {
    sendCmd('S');
  }

  delay(50);
}
