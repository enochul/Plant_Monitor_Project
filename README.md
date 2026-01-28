<p align="center">
  <img src="images/plant.png" width="200">
</p>

# Plant Monitor: A Self-Watering Plant Device

![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![Sensors](https://img.shields.io/badge/sensors-DHT11%20%7C%20Moisture%20%7C%20LDR-yellow)
![Power](https://img.shields.io/badge/power-18650-red)
![Status](https://img.shields.io/badge/status-active-brightgreen)
![Made With](https://img.shields.io/badge/made%20with-PlatformIO-orange)

## ✨ Features
- Automated soil moisture monitoring
- Automatic watering via pump
- Temperature and humidity tracking
- Light level detection
- LCD display for real-time readings
- Battery-powered operation
---

## 🌱 About
Plant Monitor is a compact, IoT‑ready device designed to keep your plants healthy and thriving. Four environmental sensors continuously monitor soil moisture, temperature, humidity, and light levels to maintain ideal growing conditions.
---

## 🔧 Hardware List
### **Sensors / Active Parts**
- **ESP32 WROOM 32E**
 Dual-core 32-bit microcontroller with Wi-Fi and Bluetooth. Runs up to 240 MHz. Ideal for low-power IoT applications such as this.
- **DHT11 Humiture Sensor**
 Measures both temperature (0-50 Celcius) and relative humidity using a capacitive humidity sensor. Outputs data over a single wire digital interface.
- **Capacitive Soil Moisture Module**
 Measures soil water content by sensing changes in soil capacitance. The soil acts as a dialectric between two conductors. Long-lasting, corrosion-resistant, and outputs an analog signal.
- **Centrifugal Pump**
 Small DC motor pump (.36 ~ 0.91 W). Fluid is accelerated by the impeller and flows out of an attached tube.
- **Photoresistor**
 Light-dependent resistor (LDR) that uses semiconductor material and varying resistance to measure ambient light intensity.
- **I2C LCD1602**
 16x2 character LCD with a two-wire I2C backpack used to display sensor readings.
---
### **Supporting Components**
- **ESP32 Battery xtension Board**
 Provides battery power, an on/off switch, USB-C charging (allowing device to be used anywhere), and easier pin access.
- **18650 battery**
 A 3.6V rechargeable lithium-ion cell battery. 
- **L293D Dual Motor Driver**
 Dual H bridge driver supporting PWM output. Handles 600mA per channel and a peak current of 1.2A.
- **Breadboard**
 Used for prototyping the circuit.
- **Jumper Wires**
 Used for connecting sensors and modules
- **Resistor**
 10k ohm resistor used for pull-up or signal conditioning.
---

## 🧩 Wiring Diagram
*Coming Soon - ESP32 pinout, sensor connections, pump driver wiring*
---

## 📸 Photos
*Coming soon — hardware setup, wiring, and enclosure.*
---

## 🗺️ Roadmap
- [ ] Add full wiring diagram  
- [ ] Implement sensor calibration  
- [ ] Add OLED/LCD UI  
- [ ] Add pump control logic  
- [ ] Add enclosure design  
- [ ] Add cloud logging or Wi‑Fi dashboard  

## 📄 License
This project is licensed under the MIT License.