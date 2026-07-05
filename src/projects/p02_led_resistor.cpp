#include "p02_led_resistor.h"
#include <Arduino.h>

constexpr int LED_PIN = 2;

void p02_setup() {
  pinMode(LED_PIN, OUTPUT);
}

void p02_loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
