#include "p03_button_led.h"
#include <Arduino.h>

constexpr int LED_PIN = 2;
constexpr int BUTTON_PIN = 18;
constexpr unsigned long DEBOUNCE_MS = 40;

bool ledOn = false;
int buttonState = HIGH;
int lastReading = HIGH;
unsigned long lastDebounceTime = 0;

void p03_setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
}

void p03_loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        ledOn = !ledOn;
        digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
      }
    }
  }

  lastReading = reading;
}

