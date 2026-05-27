# Serial Monitor for all mechanisms


// ======================================
// FINAL ROBOT TANK CONTROL CODE
// ======================================

// ------------------------------
// L298N #1 DRIVETRAIN
// ------------------------------
const int ENA1 = 9;
const int IN1  = 8;
const int IN2  = 7;
const int IN3  = 5;
const int IN4  = 4;
const int ENB1 = 3;

// ------------------------------
// L298N #2 TURRET + PUNCHER
// ------------------------------
const int ENA2 = 10;
const int IN5  = 11;
const int IN6  = 12;

const int IN7  = 13;
const int IN8  = A0;
const int ENB2 = A1;

// ======================================
// SETUP
// ======================================
void setup() {

  Serial.begin(9600);

  // Drivetrain
  pinMode(ENA1, OUTPUT);
  pinMode(ENB1, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Turret + Puncher
  pinMode(ENA2, OUTPUT);
  pinMode(ENB2, OUTPUT);

  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);

  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  stopAll();

  Serial.println("=== ROBOT READY ===");
}

// ======================================
// MAIN LOOP
// ======================================
void loop() {

  if (Serial.available()) {

    char cmd = Serial.read();

    // ======================================
    // DRIVETRAIN
    // ======================================

    // FORWARD
    if (cmd == 'F' || cmd == 'f') {

      Serial.println("FORWARD");

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      analogWrite(ENA1, 220);
      analogWrite(ENB1, 220);
    }

    // BACKWARD
    else if (cmd == 'B' || cmd == 'b') {

      Serial.println("BACKWARD");

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      analogWrite(ENA1, 220);
      analogWrite(ENB1, 220);
    }

    // LEFT
    else if (cmd == 'L' || cmd == 'l') {

      Serial.println("LEFT");

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      analogWrite(ENA1, 220);
      analogWrite(ENB1, 220);
    }

    // RIGHT
    else if (cmd == 'R' || cmd == 'r') {

      Serial.println("RIGHT");

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      analogWrite(ENA1, 220);
      analogWrite(ENB1, 220);
    }

    // STOP DRIVETRAIN
    else if (cmd == 'S' || cmd == 's') {

      Serial.println("STOP");

      stopDrivetrain();
    }

    // ======================================
    // TURRET
    // ======================================

    // LEFT
    else if (cmd == 'Q' || cmd == 'q') {

      Serial.println("TURRET LEFT");

      digitalWrite(IN5, LOW);
      digitalWrite(IN6, HIGH);

      analogWrite(ENA2, 255);
    }

    // RIGHT
    else if (cmd == 'E' || cmd == 'e') {

      Serial.println("TURRET RIGHT");

      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);

      analogWrite(ENA2, 255);
    }

    // STOP TURRET
    else if (cmd == 'T' || cmd == 't') {

      Serial.println("TURRET STOP");

      digitalWrite(IN5, LOW);
      digitalWrite(IN6, LOW);

      analogWrite(ENA2, 0);
    }

    // ======================================
    // PUNCHER
    // ======================================

    else if (cmd == 'P' || cmd == 'p') {

      Serial.println("PUNCH!");

      // FORWARD DIRECTION
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, HIGH);

      // KICK START
      analogWrite(ENB2, 255);
      delay(80);

      // NORMAL RUN SPEED
      analogWrite(ENB2, 200);

      // FULL ROTATION
      delay(630);

      // STOP
      stopPuncher();

      Serial.println("FULL ROTATION COMPLETE");
    }

    // MANUAL PUNCHER STOP
    else if (cmd == 'O' || cmd == 'o') {

      Serial.println("PUNCHER STOP");

      stopPuncher();
    }
  }
}

// ======================================
// FUNCTIONS
// ======================================

// STOP DRIVETRAIN
void stopDrivetrain() {

  analogWrite(ENA1, 0);
  analogWrite(ENB1, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// STOP PUNCHER
void stopPuncher() {

  analogWrite(ENB2, 0);

  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);
}

// STOP EVERYTHING
void stopAll() {

  stopDrivetrain();

  analogWrite(ENA2, 0);
  analogWrite(ENB2, 0);

  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);

  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);
}
