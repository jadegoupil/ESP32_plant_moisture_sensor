#pragma once

// Pin map
#define SOIL_PIN 36       // VP / GPIO36 -> soil AOUT (ADC1)
#define I2C_SDA_PIN 21    // IO21 -> oled SDA
#define I2C_SCL_PIN 22    // IO22 -> oled SCL
#define OLED_I2C_ADDRESS 0x3C

// Serial
#define SERIAL_BAUDRATE 9600

// Read/update interval
#define READ_INTERVAL_MS 5000

// Calibration (raw ADC values based on wet soil and air readings)
#define DRY_VALUE 2870
#define WET_VALUE 1400

// Status thresholds in % (0=dry, 100=wet)
#define STATUS_DRY_MAX 34
#define STATUS_MOIST_MAX 69
