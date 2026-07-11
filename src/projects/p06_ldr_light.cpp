#include "p06_ldr_light.h"
#include <Arduino.h>

constexpr int LDR_AO_PIN = 34;  // GPIO34 = D34 @ j13, ADC input-only

void p06_setup() {
  Serial.begin(115200);
  Serial.println("P6 LDR — che/mo cam bien, xem ADC tren Serial (115200).");
}

void p06_loop() {
  int adc = analogRead(LDR_AO_PIN);

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    Serial.printf("light ADC=%d\n", adc);
    lastPrint = millis();
  }

  delay(10);
}
