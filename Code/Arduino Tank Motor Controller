// Arduino Uno - Tank Motor Controller
// Receives commands from ESP32 via Hardware Serial
// L298N Pin Map:
//   ENA (pin 9)  -> Left  motor speed (PWM)
//   IN1 (pin 8)  -> Left  motor dir A
//   IN2 (pin 7)  -> Left  motor dir B
//   IN3 (pin 5)  -> Right motor dir A
//   IN4 (pin 4)  -> Right motor dir B
//   ENB (pin 3)  -> Right motor speed (PWM)
// Commands: F=Forward, B=Backward, L=Left, R=Right, S=Stop

const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 5;
const int IN4 = 4;
const int ENB = 3;

const int RIGHT_SPEED = 255;
const int LEFT_SPEED  = 220;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopTank();
}

void tankForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, RIGHT_SPEED); analogWrite(ENB, LEFT_SPEED);
}

void tankBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, RIGHT_SPEED); analogWrite(ENB, LEFT_SPEED);
}

void tankLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255); analogWrite(ENB, 255);
}

void tankRight() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 255); analogWrite(ENB, 255);
}

void stopTank() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = (char)Serial.read();
    switch (cmd) {
      case 'F': case 'f': tankForward();  break;
      case 'B': case 'b': tankBackward(); break;
      case 'L': case 'l': tankLeft();     break;
      case 'R': case 'r': tankRight();    break;
      case 'S': case 's': stopTank();     break;
      default: break;
    }
  }
}
