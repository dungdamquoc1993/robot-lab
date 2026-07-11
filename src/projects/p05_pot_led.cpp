#include "p05_pot_led.h"
#include <Arduino.h>

constexpr int LED_PIN = 2;
constexpr int POT_PIN = 34;  // GPIO34 = D34 @ j13, ADC input-only
constexpr int PWM_CHANNEL = 0;
constexpr int PWM_FREQ = 5000;
constexpr int PWM_BITS = 8;

void p05_setup() {
  Serial.begin(115200);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_BITS);
  ledcAttachPin(LED_PIN, PWM_CHANNEL);
}

void p05_loop() {
  int adc = analogRead(POT_PIN);
  int duty = map(adc, 0, 4095, 0, 255);
  ledcWrite(PWM_CHANNEL, duty);

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    Serial.printf("ADC=%d  duty=%d\n", adc, duty);
    lastPrint = millis();
  }

  delay(10);
}
