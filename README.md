# ESP32 Temperature Alert System

## Overview

An IoT-based temperature monitoring and alert system developed using ESP32 and a DHT22 temperature sensor. The system continuously monitors ambient temperature and sends real-time readings to the Blynk IoT dashboard.

When the temperature reaches or exceeds the predefined threshold of 40°C, the system triggers an alert through the Blynk dashboard and activates a buzzer for audible notification. The buzzer can also be remotely enabled or disabled through the Blynk application, providing flexible alert control.

## Features

- **Real-Time Temperature Monitoring:** Measures ambient temperature using the DHT22 sensor.
- **IoT Dashboard Integration:** Sends temperature readings to the Blynk Cloud platform.
- **High-Temperature Alert:** Detects temperatures at or above 40°C.
- **Remote Notifications:** Generates Blynk event notifications when the temperature threshold is exceeded.
- **LED Indicator:** Controls a dashboard LED widget to indicate high-temperature conditions.
- **Audible Alert:** Activates a buzzer when high temperature is detected.
- **Remote Buzzer Control:** Enables or disables the buzzer through a Blynk switch.
- **Automatic Buzzer Timeout:** Limits each buzzer activation to one second.
- **Offline Handling:** Includes Wi-Fi connection timeout handling and offline operation when Wi-Fi is unavailable.

## Hardware Components

- ESP32 Development Board
- DHT22 Temperature and Humidity Sensor
- Passive Buzzer
- Connecting Wires
- Power Supply

## Pin Configuration

| Component | ESP32 Pin |
|---|---|
| DHT22 Data Pin | GPIO 14 |
| Passive Buzzer | GPIO 26 |

## Software and Technologies

- C/C++
- Arduino IDE
- ESP32
- DHT22 Sensor
- Blynk IoT Platform
- Wi-Fi Communication

## System Workflow

1. **Initialization:** The ESP32 initializes the DHT22 sensor, buzzer, and Wi-Fi connection.
2. **Cloud Connection:** Connects to the Blynk Cloud platform for remote monitoring and control.
3. **Temperature Reading:** Reads the ambient temperature every 3 seconds.
4. **Data Transmission:** Sends temperature readings to the Blynk dashboard.
5. **Threshold Monitoring:** Compares the measured temperature against the predefined 40°C threshold.
6. **Alert Generation:** If the threshold is exceeded, the system generates a Blynk event notification and activates the dashboard LED indicator.
7. **Buzzer Activation:** Activates the buzzer for one second when the high-temperature condition is detected, provided the buzzer is enabled.
8. **Remote Control:** Allows the buzzer to be enabled or disabled remotely through the Blynk dashboard.

## Blynk Dashboard Configuration

The project uses the following virtual pins:

| Virtual Pin | Function |
|---|---|
| V1 | Displays temperature readings |
| V2 | High-temperature LED indicator |
| V3 | Remote buzzer control switch |

The Blynk event configured in the program is:

- `temp_alert` – Triggered when the temperature reaches or exceeds the threshold.

## How to Set Up

### 1. Install Arduino IDE

Install the Arduino IDE and configure it for ESP32 development.

### 2. Install Required Libraries

Install the following libraries through the Arduino IDE Library Manager:

- Blynk
- DHT sensor library

### 3. Configure Blynk

Create a Blynk template and configure the dashboard with the following virtual pins:

- V1 – Temperature display
- V2 – LED indicator
- V3 – Switch

Configure the `temp_alert` event in the Blynk template for notifications.

### 4. Configure Credentials

Update the following values in the source code with your own credentials:

- Blynk Template ID
- Blynk Template Name
- Blynk Authentication Token
- Wi-Fi SSID
- Wi-Fi Password

### 5. Connect the Hardware

Connect the DHT22 data pin to GPIO 14 and the passive buzzer to GPIO 26 of the ESP32.

### 6. Upload the Code

Upload the program to the ESP32 using Arduino IDE.

### 7. Monitor the System

Open the Serial Monitor at **115200 baud** to view temperature readings, connection status, and alert messages.

Monitor and control the system through the Blynk dashboard.

## Temperature Alert Logic

| Temperature Condition | System Response |
|---|---|
| Temperature below 40°C | LED indicator OFF and buzzer stopped |
| Temperature at or above 40°C | Blynk event triggered, LED indicator ON, buzzer activated if enabled |
| Buzzer disabled remotely | Buzzer activation suppressed |
| Temperature reading failure | Error message printed to Serial Monitor |

## Applications

- Room temperature monitoring
- Server room temperature alerts
- IoT-based environmental monitoring
- Laboratory temperature monitoring
- Smart home monitoring systems

## Learning Outcomes

- Interfacing DHT22 sensors with ESP32.
- Implementing IoT-based monitoring using Blynk.
- Configuring virtual pins for dashboard communication.
- Implementing threshold-based alert systems.
- Controlling hardware remotely through IoT.
- Using timers and `millis()` for non-blocking timing logic.

## Author

Developed as an IoT-based temperature monitoring and alert system using ESP32.
