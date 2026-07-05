#include "p04c_lm393_obstacle.h"
#include <Arduino.h>

constexpr int SENSOR_PIN = 19;  // D19 @ b11
constexpr int LED_PIN = 2;
// Nhiều module LM393 IR: OUT = LOW khi có vật. Đổi false nếu ngược.
constexpr bool OBSTACLE_ACTIVE_LOW = true;

void p04c_setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("P4c LM393 — đưa vật gần sensor, xoay biến trở module nếu cần.");
}

void p04c_loop() {
  int raw = digitalRead(SENSOR_PIN);
  bool obstacle = OBSTACLE_ACTIVE_LOW ? (raw == LOW) : (raw == HIGH);
  digitalWrite(LED_PIN, obstacle ? HIGH : LOW);

  static bool last = false;
  if (obstacle != last) {
    Serial.printf("OUT=%d  %s\n", raw, obstacle ? "OBSTACLE" : "clear");
    last = obstacle;
  }

  delay(50);
}
