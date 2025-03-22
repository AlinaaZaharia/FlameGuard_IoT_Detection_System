#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>
#include "pitches.h"
#include "secrets.h"


unsigned long lastTime = 0;  
unsigned long timerDelay = 3000;

const char* ntpServer = "pool.ntp.org";

const int flamePin = 34;
const int buzzerPin = 15;

String getFormattedTime() {
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    timeinfo.tm_hour += 2;

    if (timeinfo.tm_hour >= 24) {
      timeinfo.tm_hour -= 24;
    }

    char timeStr[10];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
    return String(timeStr);
  } else {
    return "00:00:00";
  }
}

void tokenStatusCallback(TokenInfo info) {
  if (info.status == token_status_error) {
    GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  configTime(0, 0, ntpServer);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
  GSheet.setTokenCallback(tokenStatusCallback);
}

void loop() {
  int flameDetected = digitalRead(flamePin) == LOW ? 1 : 0;

  if (flameDetected) {
    tone(buzzerPin, NOTE_A5, 500);

    unsigned long currentMillis = millis();
    if (GSheet.ready() && currentMillis - lastTime > timerDelay) {
      lastTime = currentMillis;

      String currentTime = getFormattedTime();
      String flameMessage = "flame detected";
  
      FirebaseJson valueRange;
      valueRange.add("majorDimension", "COLUMNS");
      valueRange.set("values/[0]/[0]", currentTime);
      valueRange.set("values/[1]/[0]", flameMessage);

      FirebaseJson response;
      if (GSheet.values.append(&response, spreadsheetId, "Foaie1!A1", &valueRange)) {
        valueRange.clear();
        Serial.println("Data sent to Google Sheets.");
      }
    }
  }
 else {
    noTone(buzzerPin);
  }
}
