/*
 * Smart Study Timer - Analog IR Sensor Firmware
 * 
 * HARDWARE:
 *  - Arduino Uno/Nano
 *  - Analog IR Distance Sensor (e.g., Sharp GP2Y0A21YK0F)
 * 
 * WIRING:
 *  - Sensor VCC -> Arduino 5V
 *  - Sensor GND -> Arduino GND
 *  - Sensor OUT -> Arduino Analog Pin A0
 */

const int SENSOR_PIN = A0;
const long BAUD_RATE = 9600;

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);

  float distance;

  if (sensorValue > 20) {
    distance = 4800.0 / (sensorValue - 20.0);
  } else {
    distance = 100.0;
  }

  if (distance > 100) distance = 100;
  if (distance < 10) distance = 10;

  Serial.println(distance);
  delay(1000);
}
