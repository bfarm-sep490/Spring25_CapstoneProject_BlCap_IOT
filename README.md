# IoT Documents

This document is intended for study and research purposes. BlCap IOT Document is a project to monitor processes of planing.

---

## Technologies

### Programming Language
- **C/C++**

### IDE
- [Arduino IDE](https://arduino.vn/)
- [PlatformIO](https://platformio.org/)

### Cloud
- [HiveMQ](https://www.hivemq.com/)

### Libraries
- [PicoMQTT](https://github.com/mlesniew/PicoMQTT)
- [DHT22](https://docs.arduino.cc/libraries/dht-sensor-library/)

---

## Modules

### Kit Wifi BLE ESP32 NodeMCU-32S CH340 Ai-Thinker

![ESP32 NodeMCU](https://github.com/bfarm-sep490/Spring25_CapstoneProject_BlCap_IOT/blob/main/benmark/NodeMCU-32S_WiFi_Bluetooth_BLE.jpg)

- **Specifications**:
  - Manufacturer: Ai-Thinker
  - Central Module: Ai-Thinker ESP32-S
  - SPI Flash: 32Mbits
  - Frequency Range: 2400~2483.5MHz
  - Bluetooth: BLE 4.2 BR/EDR
  - WiFi: 802.11 b/g/n/e/i
  - Interfaces: UART/SPI/SDIO/I2C/PWM/I2S/IR/ADC/DAC
  - Power Supply: 5VDC (Micro USB)
  - Features: Integrated UART CH340, LED Status, Boot Button, Full GPIO pins
  - Dimensions: 25.4 x 48.3mm

- **Price**: 9 USD

---

### Soil Moisture Sensor

![Soil Moisture Sensor](https://github.com/bfarm-sep490/Spring25_CapstoneProject_BlCap_IOT/blob/main/benmark/soil_moisture_sensor.jpeg)

- **Specifications**:
  - Operating Voltage: 3.3~5VDC
  - Output Signals:
    - **Analog**: Corresponding to supply voltage.
    - **Digital**: High/Low, adjustable via LM393 comparator.
  - Dimensions: 3 x 1.6cm

- **Price**: 1 USD

---

### Photodiode Light Sensor

![Photodiode Light Sensor](https://raw.githubusercontent.com/bfarm-sep490/Spring25_CapstoneProject_BlCap_IOT/refs/heads/main/benmark/photodiode.webp)

- **Specifications**:
  - Operating Voltage: 3.3~5VDC
  - Sensor Type: Photodiode for high accuracy
  - Outputs:
    - **Digital**: Adjustable via onboard potentiometer.
    - **Analog**: Easy to use.
  - Dimensions: 30 x 16mm

- **Price**: 1 USD

---

### DHT22 Sensor

![DHT22 Sensor](https://github.com/bfarm-sep490/Spring25_CapstoneProject_BlCap_IOT/blob/main/benmark/dht22.png)

- **Specifications**:
  - Operating Voltage: 3~5VDC
  - Current: Max 2.5mA (during data transmission)
  - Humidity Range: 0-100%RH, Accuracy: ±2-5%
  - Temperature Range: -40 to 80°C, Accuracy: ±0.5°C
  - Sampling Rate: Max 0.5Hz (1 sample every 2 seconds)
  - Dimensions: 27mm x 59mm x 13.5mm
  - Pins: 4-pin interface, 0.1'' spacing

- **Price**: 4 USD

---

## Design Flows

### Flow 1: Broker-Based Communication

The modules send data to the broker (HiveMQ Cloud). The server's background services are responsible for processing the data.

![Flow 1](https://github.com/bfarm-sep490/Spring25_CapstoneProject_BlCap_IOT/blob/main/benmark/design_flow_1.png)

---

### Flow 2: Direct API Communication

The modules send data directly to the server through APIs.

![Flow 2](https://github.com/bfarm-sep490/Spring25_CapstoneProject_BlCap_IOT/blob/main/benmark/design_flow_2.png)
