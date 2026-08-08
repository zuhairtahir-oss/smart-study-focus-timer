Smart Study Focus Timer

Touchless Arduino + Python smart study timer with automatic focus/break tracking, session logging, and visualization.

The system uses an infrared sensor to detect whether someone is present at their desk, streams that reading over serial to a Python/Tkinter desktop app, and automatically tracks focus vs. break time — no buttons, no manual start/stop. A custom enclosure was designed in SolidWorks to house the electronics and keep wiring tidy.

How It Works
An IR sensor mounted on the enclosure detects whether a person is present in front of it.
The Arduino sketch reads the sensor and streams one distance value (in cm) over Serial every second — a "near" reading (≈50 cm) means present, a "far" reading (≈100 cm) means away.
The Python desktop app (smart_timer_app.py) reads the serial stream and runs a simple state machine:
FOCUS state accumulates time while the sensor reports "present."
BREAK state accumulates time as soon as the person is detected as away.
When the person returns after a break, the session is closed, logged, and a new session begins.
Every session (start time, focus minutes, break minutes, status) is saved to session_log.json, so history persists across runs and can be turned into focus analytics.
Hardware
Arduino Uno (or compatible, e.g. ELEGOO UNO R3)
IR sensor — the repo includes firmware for two sensor types:
Analog distance sensor (e.g. Sharp GP2Y0A21YK0F) → Analog pin A0
Digital IR obstacle sensor (e.g. KY-032) → Digital pin 2
Breadboard + jumper wires
USB cable (Arduino ↔ computer)
Custom SolidWorks-designed enclosure for internal sensor mounting and cable routing
Wiring

Analog sensor (IRDistanceSerial.ino)

Sensor Pin	Arduino Pin
VCC	5V
GND	GND
OUT	A0

Digital sensor (arduino/sensor_digital.ino, arduino/SensorSerialLED.ino)

Sensor Pin	Arduino Pin
VCC	5V
GND	GND
OUT	Digital Pin 2
Repository Structure
smart-study-focus-timer/
├── IRDistanceSerial.ino          # Analog IR sensor firmware — real distance (cm) over Serial
└── arduino/
    ├── sensor_digital.ino        # Digital IR sensor firmware — simulated near/far distance over Serial
    ├── SensorSerialLED.ino       # Digital sensor + status LED, listens for 'N'/'F' serial commands
    ├── sensor_log.json           # Sample/example session log data
    └── python/
        └── smart_timer_app.py    # Tkinter desktop app: reads Serial, tracks focus/break, logs sessions
Getting Started
1. Flash the Arduino

Pick the sketch matching your sensor:

IRDistanceSerial.ino for an analog distance sensor
arduino/sensor_digital.ino for a digital obstacle sensor
arduino/SensorSerialLED.ino for a digital sensor with an onboard status LED
Open the sketch in the Arduino IDE.
Wire the sensor as described above.
Select your board and port, then upload.
Open the Serial Monitor at 9600 baud to confirm you're seeing one value printed per second (50.0 when present, 100.0 when away).
2. Run the Python app
Install the dependency:
bash
   pip install pyserial
Open arduino/python/smart_timer_app.py and update SERIAL_PORT (currently set to "COM7") to match your Arduino's port — e.g. COM3 on Windows, or /dev/ttyUSB0 / /dev/tty.usbmodem* on Mac/Linux.
Run it:
bash
   python arduino/python/smart_timer_app.py
Click Start Session in the window that opens. The app will track FOCUS/BREAK time live and write each completed session to session_log.json.
Enclosure

The desktop enclosure was designed in SolidWorks to:

Mount the IR sensor with a clear, unobstructed line of sight to the desk area
Route the sensor and USB cables internally for a clean desktop footprint
House the Arduino and breadboard/sensor circuit securely
Tech Stack
Arduino (C++) — sensor firmware and serial data streaming
Python (Tkinter, pyserial) — serial communication, focus/break state machine, session logging, and analytics
SolidWorks — enclosure design and cable/sensor mounting
Roadmap / Ideas
 Add a focus-analytics/visualization script to chart session_log.json (daily/weekly focus totals, trends)
 Add SolidWorks/STL files for the enclosure to the repo
 Make session thresholds (e.g. the "20 minutes = success" target) configurable
 Add CSV export of session logs
 Auto-detect the Arduino's serial port instead of hardcoding it
License

Add a license of your choice (e.g. MIT) if you plan to share or open this project up for contributions.
