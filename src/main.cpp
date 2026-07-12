#include <Arduino.h>

#include "projects/p01_blink.h"
#include "projects/p02_led_resistor.h"
#include "projects/p03_button_led.h"
#include "projects/p04_breathing_led.h"
#include "projects/p04b_pir_alarm.h"
#include "projects/p04c_lm393_obstacle.h"
#include "projects/p05_pot_led.h"
#include "projects/p06_ldr_light.h"
#include "projects/p07_servo_pot.h"
#include "projects/p07b_two_servos.h"
#include "projects/p08_web_server.h"
#include "projects/p09_oled_sensor.h"
#include "projects/p10_buzzer.h"
#include "projects/p14_relay.h"

// Chọn project: bỏ comment đúng 1 cặp setup/loop, comment các cặp còn lại.

void setup() {
  // p01_setup();
  // p02_setup();
  // p03_setup();
  // p04_setup();
  // p04b_setup();
  // p04c_setup();
  // p05_setup();
  // p06_setup();
  // p07_setup();
  // p07b_setup();
  // p08_setup();
  // p09_setup();
  // p10_setup();
  p14_setup();
}

void loop() {
  // p01_loop();
  // p02_loop();
  // p03_loop();
  // p04_loop();
  // p04b_loop();
  // p04c_loop();
  // p05_loop();
  // p06_loop();
  // p07_loop();
  // p07b_loop();
  // p08_loop();
  // p09_loop();
  // p10_loop();
  p14_loop();
}
