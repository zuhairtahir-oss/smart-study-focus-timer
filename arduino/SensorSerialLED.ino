const int SENSOR_PIN = 2;
const int LED_PIN = 13;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 1. Send Sensor Status
  int val = digitalRead(SENSOR_PIN);
  if (val == 0) Serial.println("0"); // User Present
  else Serial.println("1");          // User Gone

  // 2. Listen for LED Commands
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'N') digitalWrite(LED_PIN, HIGH); // ON
    else if (command == 'F') digitalWrite(LED_PIN, LOW);  // OFF
  }
  
  delay(100);
}
