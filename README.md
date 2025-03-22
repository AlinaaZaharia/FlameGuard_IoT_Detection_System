# FlameGuard – IoT Flame Detection System (ESP32 + Google Sheets + WhatsApp)

A Wi-Fi enabled flame detection system using ESP32, an IR flame sensor, and buzzer alerts. The system logs fire detection events to Google Sheets and sends real-time WhatsApp notifications via IFTTT.

## 📌 Description

**FlameGuard** is a compact, IoT-based fire alert system designed for real-time flame monitoring in small indoor environments. It uses an IR flame sensor connected to an ESP32 microcontroller, which activates a buzzer locally and triggers two forms of remote alerts:
- Sends the event with timestamp to a **Google Sheet**
- Triggers an **IFTTT** WhatsApp notification

The system resets automatically once the flame is no longer detected and returns to monitoring mode.

## 🧠 Features

- Detects flames using an infrared (IR) flame sensor
- Activates a buzzer on detection
- Logs alert events with timestamps to Google Sheets via Google Sheets API
- Sends real-time WhatsApp alerts using IFTTT webhooks
- Automatically resets buzzer when flame is no longer detected
- Lightweight and affordable hardware implementation

## 🔧 Technologies Used

- **ESP32** – Wi-Fi-enabled microcontroller
- **Arduino IDE**
- **Google Sheets API (via `ESP_Google_Sheet_Client`)**
- **IFTTT Webhooks**
- **NTP Server** – time synchronization
- **WiFi.h**, **time.h**, **FirebaseJson**

## 🏗️ Project Structure

- `setup()` – Initializes Wi-Fi, pins, time, and Google Sheets connection
- `loop()` – Monitors flame sensor, triggers alerts, and logs data
- `getFormattedTime()` – Formats and returns current time (UTC+2)
- `tokenStatusCallback()` – Handles token errors for Google Sheets API

## 🖥️ Hardware Configuration

- **ESP32**
  - GPIO 34: IR Flame Sensor input
  - GPIO 15: Buzzer output
- **Power Supply**: USB or battery (future improvement)
- **Optional**: Speaker icons or LED indicators for better UX

## 🧪 Testing & Validation

- Flame sensor tested in various lighting conditions
- Issues with low buzzer volume resolved using higher frequency tone (NOTE_A5)
- Verified connection to Google Sheets with accurate timestamps
- WhatsApp notification reliability confirmed via IFTTT

## 📈 Future Improvements

- Add battery backup (rechargeable Li-ion)
- Integrate GSM module for alerts without Wi-Fi
- Add complementary smoke or temperature sensor
- Improve flame detection accuracy under direct sunlight
- Web dashboard for real-time remote monitoring

## 📸 Sample Log Output (Google Sheets)
| Time      | Event           |
|-----------|------------------|
| 14:52:03  | flame detected   |
| 14:58:19  | flame detected   |
