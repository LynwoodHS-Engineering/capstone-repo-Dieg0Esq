// Arduino Uno - Serial Communication Test
// Tests communication between Arduino and ESP32

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Ready - Waiting for ESP32...");
}

void loop() {
  if (Serial.available() > 0) {
    String incoming = Serial.readStringUntil('\n');
    incoming.trim();
    if (incoming.length() > 0) {
      Serial.println("RECEIVED → " + incoming);
    }
  }
}
