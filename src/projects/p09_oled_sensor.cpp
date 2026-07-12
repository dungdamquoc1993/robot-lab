#include "p09_oled_sensor.h"

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

constexpr int I2C_SDA_PIN = 21;
constexpr int I2C_SCL_PIN = 22;
constexpr int LDR_AO_PIN = 34;

constexpr int OLED_WIDTH = 128;
constexpr int OLED_HEIGHT = 64;
constexpr int OLED_RESET_PIN = -1;
constexpr uint32_t I2C_CLOCK_HZ = 100000;

Adafruit_SSD1306 p09Display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

bool p09OledReady = false;
uint8_t p09OledAddress = 0;

bool p09I2cAddressResponds(uint8_t address) {
  Wire.beginTransmission(address);
  return Wire.endTransmission() == 0;
}

uint8_t p09FindOledAddress() {
  if (p09I2cAddressResponds(0x3C)) return 0x3C;
  if (p09I2cAddressResponds(0x3D)) return 0x3D;
  return 0;
}

void p09PrintI2cScan() {
  Serial.println("P9 I2C scan:");

  int found = 0;
  for (uint8_t address = 1; address < 127; address++) {
    if (p09I2cAddressResponds(address)) {
      Serial.printf("  found 0x%02X\n", address);
      found++;
    }
  }

  if (found == 0) {
    Serial.println("  no I2C device found; check VCC/GND/SDA/SCL.");
  }
}

void p09DrawReading(int adc, int percent) {
  if (!p09OledReady) return;

  p09Display.clearDisplay();
  p09Display.setTextColor(SSD1306_WHITE);

  p09Display.setTextSize(1);
  p09Display.setCursor(0, 0);
  p09Display.println("P9 OLED + LDR");

  p09Display.setCursor(0, 16);
  p09Display.print("I2C: 0x");
  p09Display.println(p09OledAddress, HEX);

  p09Display.setCursor(0, 30);
  p09Display.print("ADC: ");
  p09Display.println(adc);

  p09Display.setTextSize(2);
  p09Display.setCursor(0, 46);
  p09Display.print(percent);
  p09Display.println("%");

  p09Display.display();
}

void p09_setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println();
  Serial.println("P9 OLED + LDR — I2C OLED on D21/D22, LDR AO on D34.");

  analogReadResolution(12);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(I2C_CLOCK_HZ);

  p09PrintI2cScan();
  p09OledAddress = p09FindOledAddress();

  if (p09OledAddress == 0) {
    Serial.println("OLED not found at 0x3C/0x3D. Serial logging will continue.");
    return;
  }

  p09OledReady = p09Display.begin(SSD1306_SWITCHCAPVCC, p09OledAddress);
  if (!p09OledReady) {
    Serial.println("SSD1306 init failed. Serial logging will continue.");
    return;
  }

  p09Display.clearDisplay();
  p09Display.setTextSize(1);
  p09Display.setTextColor(SSD1306_WHITE);
  p09Display.setCursor(0, 0);
  p09Display.println("P9 ready");
  p09Display.println("Cover LDR sensor");
  p09Display.display();

  Serial.printf("OLED ready at 0x%02X.\n", p09OledAddress);
}

void p09_loop() {
  const int adc = analogRead(LDR_AO_PIN);
  const int percent = constrain(map(adc, 0, 4095, 0, 100), 0, 100);

  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 500) {
    Serial.printf("light ADC=%d approx=%d%% oled=%s\n", adc, percent, p09OledReady ? "ok" : "missing");
    p09DrawReading(adc, percent);
    lastUpdate = millis();
  }
}
