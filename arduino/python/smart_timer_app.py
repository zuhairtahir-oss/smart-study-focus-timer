import tkinter as tk
from tkinter import ttk, messagebox
import time
import serial
import json
import os
from datetime import datetime

# ---------------- CONFIG ----------------
SERIAL_PORT = "COM7"     # Change if needed
BAUD_RATE = 9600
DATA_FILE = "session_log.json"

# ---------------- DATA MANAGER ----------------
class SessionManager:
    def __init__(self):
        self.filename = DATA_FILE
        self.sessions = self.load()

        if not self.sessions or self.sessions[-1]["closed"]:
            self.new_session()

    def load(self):
        if not os.path.exists(self.filename):
            return []
        with open(self.filename, "r") as f:
            return json.load(f)

    def save(self):
        with open(self.filename, "w") as f:
            json.dump(self.sessions, f, indent=4)

    def new_session(self):
        session = {
            "id": len(self.sessions) + 1,
            "time": datetime.now().strftime("%H:%M"),
            "focus": 0,
            "break": 0,
            "status": "In Progress",
            "closed": False
        }
        self.sessions.append(session)
        self.save()

    def update(self, focus, break_time):
        s = self.sessions[-1]
        s["focus"] = round(focus, 1)
        s["break"] = round(break_time, 1)

        if focus >= 20:
            s["status"] = "SUCCESS"

        self.save()

    def close(self):
        self.sessions[-1]["closed"] = True
        self.save()
        self.new_session()

# ---------------- TIMER ----------------
class FocusTimer:
    def __init__(self, manager):
        self.manager = manager
        self.state = "IDLE"
        self.focus = 0
        self.break_time = 0

        try:
            self.arduino = serial.Serial(SERIAL_PORT, BAUD_RATE)
            time.sleep(2)
            print("Arduino connected")
        except:
            self.arduino = None
            print("Arduino not connected")

    def update(self):
        present = False

        if self.arduino and self.arduino.in_waiting:
            val = self.arduino.readline().decode().strip()
            if val == "50.0":
                present = True

        if self.state == "FOCUS":
            if present:
                self.focus += 0.1
            else:
                self.state = "BREAK"

        elif self.state == "BREAK":
            if not present:
                self.break_time += 0.1
            else:
                self.manager.close()
                self.focus = 0
                self.break_time = 0
                self.state = "FOCUS"

        self.manager.update(self.focus, self.break_time)

# ---------------- GUI ----------------
class App:
    def __init__(self, root):
        self.root = root
        self.root.title("Smart Study Timer")

        self.manager = SessionManager()
        self.timer = FocusTimer(self.manager)

        ttk.Button(root, text="Start Session", command=self.start).pack(pady=10)

        self.lbl_state = ttk.Label(root, text="IDLE", font=("Arial", 24))
        self.lbl_state.pack()

        self.lbl_focus = ttk.Label(root, text="Focus: 0.0")
        self.lbl_focus.pack()

        self.lbl_break = ttk.Label(root, text="Break: 0.0")
        self.lbl_break.pack()

        self.loop()

    def start(self):
        self.timer.state = "FOCUS"

    def loop(self):
        self
