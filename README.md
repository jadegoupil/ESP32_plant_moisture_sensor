# Plant Moisture Monitor (ESP32)

An autonomous plant moisture monitoring system powered by an **ESP32**, a **capacitive soil moisture sensor** (TLC555), and an **OLED display** for real-time data visualization.

---

## Project Overview

This project helps monitor a plant's health by accurately measuring soil moisture without the corrosion issues typical of traditional resistive sensors. Data is read continuously by the ESP32 and displayed both numerically and graphically on the OLED screen. The sensor is manually calibrated based on dry and wet values.

---

## How capacitance works with water

* **What is Capacitance?** 
  Capacitance is the ability of a system to store electrical charge. A capacitive sensor uses two conductive plates separated by an insulating material. In this setup, the surrounding soil (wet or dry) acts as that insulator (known as the *dielectric*).
* **How Water Changes It:** 
  Water has a much higher dielectric constant ($\approx 80$) compared to dry air ($\approx 1$) and dry soil ($\approx 3-5$). When moisture increases in the soil, the dielectric constant goes up, which **increases the capacitance**. The TLC555 timer circuit detects this shift in capacitance and translates it into a varying voltage output that the ESP32's ADC pin can easily measure.

source : [https://www.nde-ed.org/Physics/Electricity/capacitance.xhtml](https://www.sciencedirect.com/topics/materials-science/capacitance)

---

## Hardware Components

| Component | Role / Description |
| :--- | :--- |
| **ESP32 WROOM** | Microcontroller (Integrated Wi-Fi / Bluetooth) |
| **Capacitive Moisture Sensor (TLC555 timer)** | Measures capacitance |
| **128x64 I2C OLED display** | I2C display for data (moisture percentage, graphs) |

---

## Wiring Diagram

| Component | Component Pin | Corresponding ESP32 Pin |
| :--- | :--- | :--- |
| **Moisture Sensor** | VCC | 3.3V or 5V |
| | GND | GND |
| | OUT (Signal) | GPIO (e.g. `GPIO 34` - ADC) |
| **OLED Display** | VCC | 3.3V |
| | GND | GND |
| | SCL | GPIO 22 (Default SCL) |
| | SDA | GPIO 21 (Default SDA) |

---

## Prerequisites & Dependencies (Arduino IDE)

1. **ESP32 Board Support** (via the Board Manager).
2. The following libraries (available via the Library Manager):
   - `Adafruit SSD1306`
   - `Adafruit GFX Library`

---
