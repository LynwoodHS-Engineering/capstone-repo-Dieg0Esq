#include <LiquidCrystal.h>

// LCD PINS
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

// ENCODER PINS
const int encoderA = 34;
const int encoderB = 35;

// VARIABLES
volatile int pulses = 0;

int lastA;

unsigned long lastTime = 0;

float rpm = 0;

// CHANGE THIS TO MATCH YOUR ENCODER
const int pulsesPerRevolution = 20;

void setup() {

  Serial.begin(115200);

  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);

  lcd.begin(16, 2);

  lastA = digitalRead(encoderA);

  // INITIAL DISPLAY
  lcd.setCursor(0, 0);
  lcd.print("RPM: 0.00");
}

void loop() {

  int currentA = digitalRead(encoderA);

  // COUNT PULSES
  if (currentA != lastA) {

    pulses++;
  }

  lastA = currentA;

  // UPDATE EVERY 1 SECOND
  if (millis() - lastTime >= 1000) {

    // RPM CALCULATION
    rpm = (pulses * 60.0) / pulsesPerRevolution;

    // DISPLAY RPM
    lcd.setCursor(0, 0);

    lcd.print("RPM: ");
    lcd.print(rpm, 2);
    lcd.print("     ");

    // SERIAL MONITOR
    Serial.print("RPM: ");
    Serial.println(rpm);

    // RESET PULSES
    pulses = 0;

    // RESET TIMER
    lastTime = millis();
  }
}
