#include "p10_buzzer.h"

#include <Arduino.h>

constexpr int BUZZER_PIN = 25;
constexpr int BUZZER_PWM_CHANNEL = 2;
constexpr int BUZZER_PWM_BITS = 10;
constexpr int BUZZER_DUTY = 1 << (BUZZER_PWM_BITS - 1);

struct ToneStep {
  uint16_t frequencyHz;
  uint16_t durationMs;
};

constexpr ToneStep PATTERN[] = {
  {440, 180},
  {0, 100},
  {660, 180},
  {0, 100},
  {880, 250},
  {0, 1500},
};

void p10WriteTone(uint16_t frequencyHz) {
  if (frequencyHz == 0) {
    ledcWrite(BUZZER_PWM_CHANNEL, 0);
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }

  ledcSetup(BUZZER_PWM_CHANNEL, frequencyHz, BUZZER_PWM_BITS);
  ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHANNEL);
  ledcWrite(BUZZER_PWM_CHANNEL, BUZZER_DUTY);
}

void p10_setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  ledcSetup(BUZZER_PWM_CHANNEL, 440, BUZZER_PWM_BITS);
  ledcAttachPin(BUZZER_PIN, BUZZER_PWM_CHANNEL);
  p10WriteTone(0);

  Serial.println();
  Serial.println("P10 Buzzer — GPIO25 -> 220R -> buzzer +, buzzer - -> GND.");
  Serial.println("Passive buzzer: frequency changes pitch. Active buzzer: it will mostly beep on/off.");
}

void p10_loop() {
  static size_t stepIndex = 0;
  static unsigned long stepStartedAt = 0;
  static bool stepApplied = false;

  const unsigned long now = millis();
  const ToneStep& step = PATTERN[stepIndex];

  if (!stepApplied) {
    p10WriteTone(step.frequencyHz);
    if (step.frequencyHz == 0) {
      Serial.println("buzzer off");
    } else {
      Serial.printf("tone %u Hz\n", step.frequencyHz);
    }
    stepStartedAt = now;
    stepApplied = true;
  }

  if (now - stepStartedAt >= step.durationMs) {
    stepIndex = (stepIndex + 1) % (sizeof(PATTERN) / sizeof(PATTERN[0]));
    stepApplied = false;
  }
}
