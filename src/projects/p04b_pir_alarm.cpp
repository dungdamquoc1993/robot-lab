#include "p04b_pir_alarm.h"
#include <Arduino.h>

constexpr int PIR_PIN = 19;   // D19 @ b11
constexpr int LED_PIN = 2;    // D2 @ b5 — LED breadboard tùy chọn

void p04b_setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("P4b PIR — warm-up ~30s, đứng yên trước cảm biến...");
}

void p04b_loop() {
  int motion = digitalRead(PIR_PIN);
  digitalWrite(LED_PIN, motion == HIGH ? HIGH : LOW);

  static int last = -1;
  if (motion != last) {
    Serial.println(motion ? "MOTION" : "clear");
    last = motion;
  }

  delay(50);
}
