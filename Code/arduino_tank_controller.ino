#include <Servo.h>

const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 5;
const int IN4 = 4;
const int ENB = 3;

const int TURRET_ENA = 6;
const int TURRET_IN1 = 10;
const int TURRET_IN2 = 11;

const int RIGHT_SPEED = 255;
const int LEFT_SPEED  = 220;
const int TURRET_SPEED = 80;

Servo turretServo;
int servoPos = 90;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TURRET_ENA, OUTPUT);
  pinMode(TURRET_IN1, OUTPUT);
  pinMode(TURRET_IN2, OUTPUT);
  turretServo.attach(2);
  turretServo.write(servoPos);
  stopTank();
  stopTurret();
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

void turretLeft() {
  digitalWrite(TURRET_IN1, HIGH);
  digitalWrite(TURRET_IN2, LOW);
  analogWrite(TURRET_ENA, TURRET_SPEED);
}

void turretRight() {
  digitalWrite(TURRET_IN1, LOW);
  digitalWrite(TURRET_IN2, HIGH);
  analogWrite(TURRET_ENA, TURRET_SPEED);
}

void stopTurret() {
  digitalWrite(TURRET_IN1, LOW);
  digitalWrite(TURRET_IN2, LOW);
  analogWrite(TURRET_ENA, 0);
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
      case 'X': turretLeft();             break;
      case 'Y': turretRight();            break;
      case 'Z': stopTurret();             break;
      case 'U':
        servoPos = min(180, servoPos + 5);
        turretServo.write(servoPos);
        break;
      case 'D':
        servoPos = max(0, servoPos - 5);
        turretServo.write(servoPos);
        break;
      default: break;
    }
  }
}
