#include "p04_breathing_led.h"
#include <Arduino.h>

constexpr int LED_PIN = 2;
constexpr int PWM_CHANNEL = 0;
constexpr int PWM_FREQ = 10000;
constexpr int PWM_BITS = 8;
constexpr int FADE_STEP_MS = 8;

void p04_setup() {
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_BITS);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
}

void p04_loop() {
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(PWM_CHANNEL, duty);
    delay(FADE_STEP_MS);
  }
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(PWM_CHANNEL, duty);
    delay(FADE_STEP_MS);
  }
}
