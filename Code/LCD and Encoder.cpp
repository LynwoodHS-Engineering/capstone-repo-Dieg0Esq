#include <LiquidCrystal.h>

// LCD PINS
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

// ENCODER PINS
const int encoderA = 32;
const int encoderB = 33;

// VARIABLES
volatile int pulses = 0;

int lastA;

unsigned long lastTime = 0;

float rpm = 0;

// CHANGE IF NEEDED
const int pulsesPerRevolution = 20;

void setup() {

  Serial.begin(115200);

  // ENABLE INTERNAL PULLUPS
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("RPM: 0.00");

  lastA = digitalRead(encoderA);
}

void loop() {

  int currentA = digitalRead(encoderA);

  // COUNT ONLY CLEAN RISING EDGES
  if (lastA == LOW && currentA == HIGH) {

    pulses++;

    delayMicroseconds(500);
  }

  lastA = currentA;

  // UPDATE RPM EVERY SECOND
  if (millis() - lastTime >= 1000) {

    rpm = (pulses * 60.0) / pulsesPerRevolution;

    // REMOVE FALSE SMALL VALUES
    if (rpm < 1.0) {
      rpm = 0.0;
    }

    lcd.setCursor(0, 0);

    lcd.print("RPM: ");
    lcd.print(rpm, 2);
    lcd.print("     ");

    Serial.print("RPM: ");
    Serial.println(rpm);

    // RESET COUNTER
    pulses = 0;

    lastTime = millis();
  }
}
