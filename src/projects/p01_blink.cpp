#include "p01_blink.h"
#include <Arduino.h>

constexpr int LED_PIN = 2;

void p01_setup() {
  pinMode(LED_PIN, OUTPUT);
}

void p01_loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  delay(2000);
}
