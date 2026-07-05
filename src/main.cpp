#include <Arduino.h>

#include "projects/p01_blink.h"
#include "projects/p02_led_resistor.h"
#include "projects/p03_button_led.h"

// Chọn project: bỏ comment đúng 1 cặp setup/loop, comment các cặp còn lại.

void setup() {
  // p01_setup();
  // p02_setup();
  p03_setup();
}

void loop() {
  // p01_loop();
  // p02_loop();
  p03_loop();
}
