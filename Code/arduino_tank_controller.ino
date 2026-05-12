#include <Servo.h>

// --------------------
// TANK DRIVER (L298N #1)
// --------------------
const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 5;
const int IN4 = 4;
const int ENB = 3;

// --------------------
// TURRET DRIVER (L298N #2)
// --------------------
const int TURRET_ENA = 6;
const int TURRET_IN1 = 10;
const int TURRET_IN2 = 11;

// --------------------
// SHOOTER MOTOR (L298N #2)
// --------------------
const int SHOOT_ENB = A0;
const int SHOOT_IN3 = 12;
const int SHOOT_IN4 = 13;

// --------------------
// SPEED SETTINGS
// --------------------
const int RIGHT_SPEED   = 255;
const int LEFT_SPEED    = 220;
const int TURRET_SPEED  = 180;

// --------------------
// SERVO
// --------------------
Servo turretServo;
int servoPos = 90;

// =====================================================
// SETUP
// =====================================================
void setup() {

  Serial.begin(9600);

  // Tank Driver
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Turret Driver
  pinMode(TURRET_ENA, OUTPUT);
  pinMode(TURRET_IN1, OUTPUT);
  pinMode(TURRET_IN2, OUTPUT);

  // Shooter Driver
  pinMode(SHOOT_ENB, OUTPUT);
  pinMode(SHOOT_IN3, OUTPUT);
  pinMode(SHOOT_IN4, OUTPUT);

  // Servo
  turretServo.attach(2);
  turretServo.write(servoPos);

  stopTank();
  stopTurret();
  shooterStop();
}

// =====================================================
// TANK MOVEMENT
// =====================================================

void tankForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, RIGHT_SPEED);
  analogWrite(ENB, LEFT_SPEED);
}

void tankBackward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, RIGHT_SPEED);
  analogWrite(ENB, LEFT_SPEED);
}

void tankLeft() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void tankRight() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void stopTank() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// =====================================================
// TURRET ROTATION
// =====================================================

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

// =====================================================
// SHOOTER MOTOR
// =====================================================

void shooterFire() {

  digitalWrite(SHOOT_ENB, HIGH);

  digitalWrite(SHOOT_IN3, HIGH);
  digitalWrite(SHOOT_IN4, LOW);
}

void shooterStop() {

  digitalWrite(SHOOT_ENB, LOW);

  digitalWrite(SHOOT_IN3, LOW);
  digitalWrite(SHOOT_IN4, LOW);
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  if (Serial.available() > 0) {

    char cmd = (char)Serial.read();

    switch (cmd) {

      // Tank
      case 'F':
      case 'f':
        tankForward();
        break;

      case 'B':
      case 'b':
        tankBackward();
        break;

      case 'L':
      case 'l':
        tankLeft();
        break;

      case 'R':
      case 'r':
        tankRight();
        break;

      case 'S':
      case 's':
        stopTank();
        break;

      // Turret Rotation
      case 'X':
        turretLeft();
        break;

      case 'Y':
        turretRight();
        break;

      case 'Z':
        stopTurret();
        break;

      // Servo Up
      case 'U':
        servoPos = min(180, servoPos + 5);
        turretServo.write(servoPos);
        break;

      // Servo Down
      case 'D':
        servoPos = max(0, servoPos - 5);
        turretServo.write(servoPos);
        break;

      // Shooter
      case 'P':
        shooterFire();
        break;

      case 'O':
        shooterStop();
        break;

      default:
        break;
    }
  }
}
