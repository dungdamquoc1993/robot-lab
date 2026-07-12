#include "p07_servo_pot.h"
#include <Arduino.h>

constexpr int SERVO_PIN = 18;  // GPIO18 = D18 @ b10/a10, servo signal
constexpr int POT_PIN = 34;    // GPIO34 = D34 @ j13, ADC input-only

constexpr int SERVO_PWM_CHANNEL = 1;
constexpr int SERVO_PWM_FREQ = 50;  // SG90 expects a 20ms frame
constexpr int SERVO_PWM_BITS = 16;
constexpr int SERVO_MIN_US = 500;
constexpr int SERVO_MAX_US = 2500;
constexpr int SERVO_PERIOD_US = 1000000 / SERVO_PWM_FREQ;

uint32_t servoDutyFromMicros(int pulseUs) {
  const uint32_t maxDuty = (1UL << SERVO_PWM_BITS) - 1;
  return (static_cast<uint32_t>(pulseUs) * maxDuty) / SERVO_PERIOD_US;
}

void writeServoAngle(int angle) {
  angle = constrain(angle, 0, 180);
  const int pulseUs = map(angle, 0, 180, SERVO_MIN_US, SERVO_MAX_US);
  ledcWrite(SERVO_PWM_CHANNEL, servoDutyFromMicros(pulseUs));
}

void p07_setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  ledcSetup(SERVO_PWM_CHANNEL, SERVO_PWM_FREQ, SERVO_PWM_BITS);
  ledcAttachPin(SERVO_PIN, SERVO_PWM_CHANNEL);
  writeServoAngle(90);

  Serial.println("P7 Servo + bien tro — xoay bien tro de dieu khien SG90.");
}

void p07_loop() {
  const int adc = analogRead(POT_PIN);
  const int angle = map(adc, 0, 4095, 0, 180);
  const int pulseUs = map(angle, 0, 180, SERVO_MIN_US, SERVO_MAX_US);

  writeServoAngle(angle);

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    Serial.printf("pot ADC=%d angle=%d pulse=%dus\n", adc, angle, pulseUs);
    lastPrint = millis();
  }

  delay(20);
}
