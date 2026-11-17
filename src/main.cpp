#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include "config.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE, I2C_SCL_PIN, I2C_SDA_PIN);

// Calculate moisture percentage based on raw ADC value
// The formula is: percent = (raw - DRY_VALUE) * 100 / (WET_VALUE - DRY_VALUE)
// 
static int calculateMoisturePercent(int raw) {
  // Avoid division by zero if DRY_VALUE equals WET_VALUE, and constrain the result to 0-100%
  if (WET_VALUE == DRY_VALUE) {
    return 0;
  }
  int percent = lroundf((float)(raw - DRY_VALUE) * 100.0f / (float)(WET_VALUE - DRY_VALUE));
  return constrain(percent, 0, 100);
}

// Determine moisture status based on percentage thresholds (with fun messages :D)
static const char* moistureStatus(int percent) {
  if (percent <= STATUS_DRY_MAX) {
    return "J'ai soif!";
  }
  if (percent <= STATUS_MOIST_MAX) {
    return "Ca va!";
  }
  return "Parfait!";
}

// This will draw the moisture percentage and status on the OLED display  
static void drawDisplay(int percent, const char* status) {
  char pctStr[5];
  snprintf(pctStr, sizeof(pctStr), "%d", percent);

  oled.clearBuffer();

  // Moisture % 
  oled.setFont(u8g2_font_logisoso24_tn);
  oled.drawStr(4, 44, pctStr);

  oled.setFont(u8g2_font_helvB14_tf);
  oled.drawStr(64, 42, "%");

  // Status below the % area
  oled.setFont(u8g2_font_9x15B_tf);
  oled.drawStr(2, 58, status);

  oled.sendBuffer();
}

// Setup function initializes Serial, ADC, I2C, and OLED display
// It also scans for I2C devices and prints their addresses to Serial, for debugging purposes.
void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  delay(200);

  pinMode(SOIL_PIN, INPUT);
  analogReadResolution(12);
  analogSetPinAttenuation(SOIL_PIN, ADC_11db);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  Serial.println("Scanning I2C...");
  // This loop scans for I2C devices on the bus and prints their addresses to Serial. Normally, you would only see the OLED's address (0x3C) if it's connected properly.
for (uint8_t addr = 1; addr < 127; addr++) {
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    Serial.print("Found device at 0x");
    Serial.println(addr, HEX);
  } else {
    Serial.print("No device at 0x");
    Serial.println(addr, HEX);
  }
}
  // Initialize the OLED display, set the I2C address, and show a startup message
  oled.setI2CAddress(OLED_I2C_ADDRESS << 1); // U8g2 uses 8-bit I2C address
  oled.begin();

  oled.clearBuffer();
  oled.setFont(u8g2_font_6x13_tf);
  oled.drawStr(0, 16, "ESP32 Moisture Monitor");
  oled.drawStr(0, 32, "Init complete...");
  oled.sendBuffer();
}

// Main loop reads the soil moisture, calculates the percentage, determines the status, and updates the OLED display every READ_INTERVAL_MS milliseconds.
void loop() {
  const int raw = analogRead(SOIL_PIN);
  const int percent = calculateMoisturePercent(raw);
  const char* status = moistureStatus(percent);

  // Raw ADC only on Serial (for debugging)
  Serial.print("Raw ADC: ");
  Serial.print(raw);
  Serial.print(" | Moisture: ");
  Serial.print(percent);
  Serial.print("% | Status: ");
  Serial.println(status);

  drawDisplay(percent, status);

  // Delay defined in config.h, e.g., 1000ms = 1 second
  delay(READ_INTERVAL_MS);
}
