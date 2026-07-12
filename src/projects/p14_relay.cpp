#include "p14_relay.h"

#include <Arduino.h>

constexpr int RELAY1_PIN = 26;
constexpr int RELAY2_PIN = 27;

struct RelayStep {
  bool relay1On;
  bool relay2On;
  uint16_t durationMs;
  const char* label;
};

constexpr RelayStep PATTERN[] = {
  {false, false, 1000, "both off"},
  {true, false, 700, "relay 1 on"},
  {false, false, 500, "both off"},
  {false, true, 700, "relay 2 on"},
  {false, false, 1500, "both off"},
};

void p14SetRelay(int pin, bool on) {
  if (on) {
    digitalWrite(pin, LOW);
    pinMode(pin, OUTPUT);
  } else {
    pinMode(pin, INPUT);
  }
}

void p14ApplyStep(const RelayStep& step) {
  p14SetRelay(RELAY1_PIN, step.relay1On);
  p14SetRelay(RELAY2_PIN, step.relay2On);
  Serial.printf("P14 %s: K1=%s K2=%s\n", step.label, step.relay1On ? "ON" : "OFF",
                step.relay2On ? "ON" : "OFF");
}

void p14_setup() {
  Serial.begin(115200);
  delay(300);

  p14SetRelay(RELAY1_PIN, false);
  p14SetRelay(RELAY2_PIN, false);

  Serial.println();
  Serial.println("P14 Relay — VIN/5V to relay VCC, GND common, D26->IN1, D27->IN2.");
  Serial.println("Active-LOW relay control: OFF = GPIO INPUT, ON = GPIO sinks LOW.");
}

void p14_loop() {
  static size_t stepIndex = 0;
  static unsigned long stepStartedAt = 0;
  static bool stepApplied = false;

  const unsigned long now = millis();
  const RelayStep& step = PATTERN[stepIndex];

  if (!stepApplied) {
    p14ApplyStep(step);
    stepStartedAt = now;
    stepApplied = true;
  }

  if (now - stepStartedAt >= step.durationMs) {
    stepIndex = (stepIndex + 1) % (sizeof(PATTERN) / sizeof(PATTERN[0]));
    stepApplied = false;
  }
}
