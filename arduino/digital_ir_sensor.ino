/*
 * Smart Study Timer - Digital IR Sensor Firmware
 *
 * HARDWARE:
 *  - Arduino Uno/Nano
 *  - Digital IR Obstacle Sensor (KY-032 or similar)
 *
 * WIRING:
 *  - Sensor VCC -> 5V
 *  - Sensor GND -> GND
 *  - Sensor OUT -> Digital Pin 2
 *  - LED -> Pin 13
 */

const int SENSOR_PIN = 2;
const int LED_PIN = 13;
const long BAUD_RATE = 9600;

// Simulated distances in cm
const float DIST_NEAR = 50.0;   // Sitting
const float DIST_FAR  = 100.0;  // Away

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  int sensorState = digitalRead(SENSOR_PIN);

  if (sensorState == LOW) {      // Obstacle detected
    Serial.println(DIST_NEAR);
  } else {
    Serial.println(DIST_FAR);
  }

  // Listen for LED command from Python
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'N') digitalWrite(LED_PIN, HIGH);
    if (command == 'F') digitalWrite(LED_PIN, LOW);
  }

  delay(1000);   // Send once per second
}
