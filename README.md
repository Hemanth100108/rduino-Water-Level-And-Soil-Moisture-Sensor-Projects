# Arduino Water Level and Soil Moisture Monitoring Projects

## Objective

To develop and implement a collection of Arduino-based water management and irrigation projects that demonstrate water level monitoring, soil moisture sensing, automatic irrigation, pump control, tank filling automation, interactive dashboards, and real-time sensor data visualization.

This repository contains a collection of Arduino projects developed using Water Level and Soil Moisture Sensors.

---

## Projects Included

1. Water Level Monitor
2. Water Pump Control
3. Auto Tank Filling System
4. Automatic Plant Watering System
5. Interactive Irrigation Dashboard

---

## Components Used

### Hardware

* Arduino Uno
* Water Level Sensor
* Soil Moisture Sensor
* SSD1306 OLED Display (128×64)
* Relay Module
* Water Pump
* Push Button
* Buzzer
* Breadboard
* Jumper Wires
* USB Cable

### Software

* Arduino IDE
* Wire Library
* Adafruit GFX Library
* Adafruit SSD1306 Library

---

## Circuit Diagram

### OLED Connections

| OLED Pin | Arduino Uno |
| -------- | ----------- |
| VCC      | 5V          |
| GND      | GND         |
| SDA      | A4          |
| SCL      | A5          |

### Water Level Sensor Connections

| Water Level Sensor Pin | Arduino Uno |
| ---------------------- | ----------- |
| VCC                    | 5V          |
| GND                    | GND         |
| AO                     | A0          |

### Soil Moisture Sensor Connections

| Soil Moisture Sensor Pin | Arduino Uno |
| ------------------------ | ----------- |
| VCC                      | 5V          |
| GND                      | GND         |
| AO                       | A1          |

### Relay Module Connections

| Relay Pin | Arduino Uno |
| --------- | ----------- |
| VCC       | 5V          |
| GND       | GND         |
| IN        | D8          |

### Push Button Connections

| Push Button Pin | Arduino Uno |
| --------------- | ----------- |
| Pin 1           | D2          |
| Pin 2           | GND         |

### Buzzer Connections

| Buzzer Pin | Arduino Uno |
| ---------- | ----------- |
| Positive   | D7          |
| Negative   | GND         |

---

## Code Explanation

### Project 1 – Water Level Monitor

* Reads water level using the Water Level Sensor.
* Converts sensor readings into percentage values.
* Displays water level and tank status on the OLED display.
* Provides real-time tank monitoring.

### Project 2 – Water Pump Control

* Controls a water pump using a relay module.
* Uses a push button to switch the pump ON and OFF.
* Displays pump status on the OLED display.
* Includes pump runtime monitoring.

### Project 3 – Auto Tank Filling System

* Automatically monitors water tank levels.
* Turns the pump ON when the water level falls below the threshold.
* Turns the pump OFF when the tank reaches the full level.
* Displays tank percentage and system status.
* Implements smooth percentage transitions for improved visualization.

### Project 4 – Automatic Plant Watering System

* Uses the Soil Moisture Sensor to detect dry soil conditions.
* Uses the Water Level Sensor to verify water availability.
* Activates irrigation only when soil is dry and sufficient water is available.
* Displays soil moisture percentage, water level percentage, and pump status.

### Project 5 – Interactive Irrigation Dashboard

* Implements a multi-page OLED interface.
* Displays water tank information on Page 1.
* Displays soil moisture information on Page 2.
* Displays a combined irrigation dashboard on Page 3.
* Uses a push button for page navigation.
* Includes moving-average filtering and gradual percentage updates for smooth sensor visualization.

---

## Output Images

### Water Level Monitor

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 05 PM" src="https://github.com/user-attachments/assets/01803064-9bc7-48d8-b4d9-1e226091dc01" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 05 PM (1)" src="https://github.com/user-attachments/assets/9dc87e00-5c88-4bcd-b229-931b31d21c44" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 06 PM" src="https://github.com/user-attachments/assets/c4808118-8223-4f3a-8d5e-fb392b096f6a" />


### Water Pump Control

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 06 PM (1)" src="https://github.com/user-attachments/assets/681d712e-ec4f-42f0-9d5a-e00fe2f84be7" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 06 PM" src="https://github.com/user-attachments/assets/e5dc82ed-2db2-46ba-8969-79b225a05e4a" />


### Auto Tank Filling System

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 07 PM (1)" src="https://github.com/user-attachments/assets/4fae5883-265c-4a17-b093-f7b5d6e538bb" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 07 PM" src="https://github.com/user-attachments/assets/64a722fd-5350-44fc-a900-706fff9c8935" />


### Automatic Plant Watering System

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 08 PM (2)" src="https://github.com/user-attachments/assets/3c00ecad-11cc-44cb-a8f8-2e87f71b9e01" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 08 PM (1)" src="https://github.com/user-attachments/assets/6fa11df6-328a-4bec-b031-65ba18f423fe" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 08 PM" src="https://github.com/user-attachments/assets/bfe00870-e95b-40e4-8270-48684e338bbc" />


### Interactive Irrigation Dashboard
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 10 PM" src="https://github.com/user-attachments/assets/cad4c24a-f061-40ea-bc7e-7a9b4d6d1ae6" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 09 PM (1)" src="https://github.com/user-attachments/assets/763b83e9-650b-4b37-b8a7-678af6b45b99" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-16 at 8 11 09 PM" src="https://github.com/user-attachments/assets/a3d7fbd6-2883-4f7b-ab03-88cb2a2bf4a6" />


---

## Learning Outcome

Through these projects, the following concepts were learned:

* Arduino Programming Fundamentals
* Analog Sensor Interfacing
* Water Level Monitoring Techniques
* Soil Moisture Measurement
* Relay and Pump Control
* Automatic Irrigation System Design
* Water Tank Automation
* OLED Display Interfacing
* I2C Communication Protocol
* Real-Time Data Acquisition
* Dashboard Development
* Multi-Page User Interface Design
* Sensor Data Filtering and Smoothing
* Embedded Systems Programming
* Hardware and Software Integration
* Problem Solving using Arduino

---

Hemanth A S
