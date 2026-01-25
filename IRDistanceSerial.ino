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
 * 
 * FUNCTION:
 *  Reads the analog voltage.
 *  Maps the reading to an approximate distance in cm.
 *  
 *  Outputs a single float value to Serial per second.
 */

const int SENSOR_PIN = A0;
const long BAUD_RATE = 9600;

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  
  // Simple conversion for SHARP GP2Y0A21YK0F (10-80cm)
  // Formula: Distance (cm) ~= 29.988 * (Voltage)^-1.173
  // Since reading (0-1023) maps to voltage, we use an approx formula:
  // distance = 4800 / (sensorValue - 20)
  // Note: This is an approximation. Adjust based on your specific sensor.
  
  float distance = 0;
  
  if (sensorValue > 20) {
    distance = 4800.0 / (sensorValue - 20.0);
  } else {
    distance = 100.0; // Out of range / Far
  }
  
  // Constrain to realistic values (e.g., 10cm to 100cm)
  if (distance > 100) distance = 100.0;
  if (distance < 10) distance = 10.0;

  Serial.println(distance);
  
  // Requirement: Send exactly one value per second
  delay(1000);
}
