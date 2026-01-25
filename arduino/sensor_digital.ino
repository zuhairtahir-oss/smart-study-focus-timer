/*
 * Smart Study Timer - Digital IR Sensor Firmware
 * 
 * HARDWARE:
 *  - Arduino Uno/Nano
 *  - Digital IR Obstacle Sensor (e.g., KY-032 or similar)
 * 
 * WIRING:
 *  - Sensor VCC -> Arduino 5V
 *  - Sensor GND -> Arduino GND
 *  - Sensor OUT -> Arduino Digital Pin 2
 * 
 * FUNCTION:
 *  Reads the digital pin. 
 *  - LOW usually means obstacle detected (Close)
 *  - HIGH usually means no obstacle (Far)
 *  
 *  Outputs a simulated distance in cm to Serial for Python processing.
 */

const int SENSOR_PIN = 2;
const long BAUD_RATE = 9600;

// Simulated distances in cm
const float DIST_NEAR = 50.0; // "Sitting" distance
const float DIST_FAR = 100.0; // "Away" distance

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  int sensorState = digitalRead(SENSOR_PIN);
  
  // Note: Most IR modules are Active LOW (LOW when obstacle detected)
  if (sensorState == LOW) {
    Serial.println(DIST_NEAR);
  } else {
    Serial.println(DIST_FAR);
  }
  
  // Requirement: Send exactly one value per second
  delay(1000);
}
