#include "p07b_two_servos.h"
#include <Arduino.h>

constexpr int SERVO_1_PIN = 18;  // Servo 1 signal
constexpr int SERVO_2_PIN = 19;  // Servo 2 signal

constexpr int SERVO_1_CHANNEL = 1;
constexpr int SERVO_2_CHANNEL = 2;
constexpr int SERVO_PWM_FREQ = 50;
constexpr int SERVO_PWM_BITS = 16;
constexpr int SERVO_MIN_US = 700;   // Conservative range to avoid hard end stops.
constexpr int SERVO_MAX_US = 2300;
constexpr int SERVO_PERIOD_US = 1000000 / SERVO_PWM_FREQ;

uint32_t p07bDutyFromMicros(int pulseUs) {
  const uint32_t maxDuty = (1UL << SERVO_PWM_BITS) - 1;
  return (static_cast<uint32_t>(pulseUs) * maxDuty) / SERVO_PERIOD_US;
}

void p07bWriteServoAngle(int channel, int angle) {
  angle = constrain(angle, 0, 180);
  const int pulseUs = map(angle, 0, 180, SERVO_MIN_US, SERVO_MAX_US);
  ledcWrite(channel, p07bDutyFromMicros(pulseUs));
}

void p07b_setup() {
  Serial.begin(115200);

  ledcSetup(SERVO_1_CHANNEL, SERVO_PWM_FREQ, SERVO_PWM_BITS);
  ledcSetup(SERVO_2_CHANNEL, SERVO_PWM_FREQ, SERVO_PWM_BITS);
  ledcAttachPin(SERVO_1_PIN, SERVO_1_CHANNEL);
  ledcAttachPin(SERVO_2_PIN, SERVO_2_CHANNEL);

  p07bWriteServoAngle(SERVO_1_CHANNEL, 90);
  p07bWriteServoAngle(SERVO_2_CHANNEL, 90);

  Serial.println("P7b Hai servo — pha A: phat 2 signal D18/D19, chua cap 5V servo.");
}

void p07b_loop() {
  static int angle = 60;
  static int step = 2;
  static unsigned long lastMove = 0;

  if (millis() - lastMove < 400) return;
  lastMove = millis();

  angle += step; 
  if (angle >= 120 || angle <= 60) {
    step = -step;
    angle += step;
  }

  const int servo1Angle = angle;
  const int servo2Angle = 180 - angle;
  const int servo1Pulse = map(servo1Angle, 0, 180, SERVO_MIN_US, SERVO_MAX_US);
  const int servo2Pulse = map(servo2Angle, 0, 180, SERVO_MIN_US, SERVO_MAX_US);

  p07bWriteServoAngle(SERVO_1_CHANNEL, servo1Angle);
  p07bWriteServoAngle(SERVO_2_CHANNEL, servo2Angle);

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 400) {
    Serial.printf(
      "servo1 D18 angle=%d pulse=%dus | servo2 D19 angle=%d pulse=%dus\n",
      servo1Angle,
      servo1Pulse,
      servo2Angle,
      servo2Pulse
    );
    lastPrint = millis();
  }
}
