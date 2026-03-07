// ESP32-WROOM - Serial Communication Test
// Tests communication between ESP32 and Arduino
// Wiring: ESP32 GPIO17 (TX2) -> Arduino Pin 0 (RX)
//         ESP32 GPIO16 (RX2) -> Arduino Pin 1 (TX)
//         ESP32 GND          -> Arduino GND

#define TX_PIN 17
#define RX_PIN 16

int counter = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  Serial.println("ESP32 Serial Test Started");
}

void loop() {
  String msg = "HELLO:" + String(counter);
  Serial2.println(msg);
  Serial.println("SENT → " + msg);
  counter++;
  delay(1000);
}
