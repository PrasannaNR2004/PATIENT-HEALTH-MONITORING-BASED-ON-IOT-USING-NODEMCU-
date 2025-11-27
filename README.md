# PATIENT-HEALTH-MONITORING-BASED-ON-IOT-USING-NODEMCU-
IoT-based patient health monitoring system using NodeMCU ESP8266. Tracks real-time pulse rate, body temperature, and humidity via MAX30102, LM35, and DHT11 sensors. Data is displayed on an OLED and transmitted to the ThingSpeak cloud for remote monitoring and analysis.

IoT-Based Patient Health Monitoring System using NodeMCU (ESP8266)

This project implements a real-time IoT-based patient health monitoring system using NodeMCU ESP8266, capable of continuously measuring:

💓 Heart Rate

🩸 SpO2 (Blood Oxygen Level)

🌡️ Body Temperature

💧 Humidity

🖥️ Local OLED Display

☁️ Cloud Upload to ThingSpeak

The goal is to provide remote monitoring, allowing healthcare professionals or family members to view vital health data from anywhere.

📌 Project Overview

The system integrates the following components for monitoring health parameters:

Parameter	Sensor
Heart Rate & SpO2	MAX30102
Body Temperature	LM35
Humidity & Temperature	DHT11
Display	1.3-inch OLED (I2C)
Microcontroller	NodeMCU ESP8266

All sensor data is displayed locally via OLED and uploaded to ThingSpeak IoT cloud.

🖼️ Block Diagram


<img width="341" height="242" alt="image" src="https://github.com/user-attachments/assets/21b2e97f-059d-418c-be91-f42294d1925f" />


🌐 ThingSpeak Dashboard


![thingspeak](https://github.com/user-attachments/assets/d18ffeb7-d4a8-42cf-a0e5-41ac461cc2b9)

🖥️ Serial Monitor Output


![serail1](https://github.com/user-attachments/assets/b6f0d9dc-a763-417a-80bf-7e73d3d0e50c)

🔧 Working Model
Prototype – Sensor & NodeMCU Setup
![serial_monitor](https://github.com/user-attachments/assets/0d2fda1b-8fb0-4c4b-afdc-616d16901487)

Final Assembled Device
![final](https://github.com/user-attachments/assets/8e6b8669-be69-4cf2-b5df-c7a5d5df94eb)

⚙️ Hardware Components

NodeMCU ESP8266

MAX30102 Pulse Oximeter Sensor

LM35 Temperature Sensor

DHT11 Humidity Sensor

1.3" OLED I2C Display

USB Cable

PCB / Breadboard

Jumper Wires

📡 System Architecture

Sensors measure real-time SpO2, heart rate, temperature, humidity.

NodeMCU collects and processes the data.

OLED displays live parameter readings.

Data is transmitted to ThingSpeak Cloud via Wi-Fi.

Users monitor the data through dashboards and graphs.

🧠 Key Features

✔️ Real-time sensing

✔️ Cloud-based monitoring

✔️ OLED display visualization

✔️ Low-power and cost-efficient

✔️ Portable PCB design

✔️ Expandable architecture for future sensors

🛠️ Software Requirements

Arduino IDE

ESP8266 Board Manager

Required Libraries:

ESP8266WiFi.h

Wire.h

Adafruit_GFX.h

Adafruit_SSD1306.h

DHT.h

MAX30102 library

📝 Future Enhancements

Add blood pressure or ECG sensor support

Integrate mobile app for instant alerts

AI/ML-based predictive health analytics

SMS/E-mail emergency alert system

Battery-powered portable version
