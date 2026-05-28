// ======================================
// PS5 ROBOT TANK - FINAL CODE (Arduino Uno)
// ======================================

// L298N #1 DRIVETRAIN
const int ENA1 = 9;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 5;
const int IN4 = 4;
const int ENB1 = 3;

// L298N #2 TURRET + PUNCHER
const int ENA2 = 10;
const int IN5 = 11;
const int IN6 = 12;
const int IN7 = 13;
const int IN8 = A0;
const int ENB2 = A1;

// ======================================
void setup() {
  Serial.begin(9600);
  
  // Drivetrain
  pinMode(ENA1, OUTPUT); pinMode(ENB1, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  
  // Turret + Puncher
  pinMode(ENA2, OUTPUT); pinMode(ENB2, OUTPUT);
  pinMode(IN5, OUTPUT); pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT); pinMode(IN8, OUTPUT);
  
  stopAll();
  Serial.println("=== ROBOT READY - Strong Turning ===");
}

// ======================================
void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    
    Serial.print("Received: ");
    Serial.println(cmd);

    // ==================== DRIVETRAIN ====================
    if (cmd == 'F' || cmd == 'f') {
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      analogWrite(ENA1, 230);
      analogWrite(ENB1, 230);
    }
    else if (cmd == 'B' || cmd == 'b') {
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
      analogWrite(ENA1, 230);
      analogWrite(ENB1, 230);
    }
    else if (cmd == 'L' || cmd == 'l') {
      Serial.println("LEFT TURN - Strong");
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // Left motor forward
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // Right motor backward
      analogWrite(ENA1, 255);   // ← Full power for turning
      analogWrite(ENB1, 255);
    }
    else if (cmd == 'R' || cmd == 'r') {
      Serial.println("RIGHT TURN - Strong");
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left motor backward
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right motor forward
      analogWrite(ENA1, 255);   // ← Full power for turning
      analogWrite(ENB1, 255);
    }
    else if (cmd == 'S' || cmd == 's') {
      stopDrivetrain();
    }

    // ==================== TURRET ====================
    else if (cmd == 'Q' || cmd == 'q') {
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, HIGH);
      analogWrite(ENA2, 170);
    }
    else if (cmd == 'E' || cmd == 'e') {
      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);
      analogWrite(ENA2, 170);
    }
    else if (cmd == 'T' || cmd == 't') {
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, LOW);
      analogWrite(ENA2, 0);
    }

    // ==================== PUNCHER ====================
    else if (cmd == 'P' || cmd == 'p') {
      Serial.println("PUNCH!");
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, HIGH);
      analogWrite(ENB2, 255);
      delay(80);
      analogWrite(ENB2, 200);
      delay(630);
      stopPuncher();
    }
    else if (cmd == 'O' || cmd == 'o') {
      stopPuncher();
    }
  }
}

// ======================================
void stopDrivetrain() {
  analogWrite(ENA1, 0); analogWrite(ENB1, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void stopPuncher() {
  analogWrite(ENB2, 0);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);
}

void stopAll() {
  stopDrivetrain();
  analogWrite(ENA2, 0);
  analogWrite(ENB2, 0);
  digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
}
