# ESP32 Wi-Fi and MQTT LED Control with Optional DHT11 Sensor

This project demonstrates how to connect an ESP32 microcontroller to a Wi-Fi network and an MQTT broker, and control an LED via MQTT messages. The code is designed to work with a DHT11 sensor (though currently commented out), which could be used for reading temperature and humidity data.

### Features:
- Connects ESP32 to a Wi-Fi network.
- Communicates with an MQTT broker for receiving control messages.
- Controls an onboard LED via MQTT messages (`ON`/`OFF`).
- (Optional) Reads temperature and humidity data from a DHT11 sensor.

### Required Hardware:
- **ESP32 Development Board**
- **DHT11 Sensor** (Optional, currently commented out)
- **LED** (Onboard or external)

### Libraries Used:
- `WiFi.h`: For Wi-Fi connectivity.
- `PubSubClient.h`: For MQTT communication.
- `Arduino.h`: For basic Arduino functions.
- `esp_system.h`: For random number generation.

### Setup:

1. **Install the required libraries:**
   - `WiFi.h` and `PubSubClient.h` can be installed via the Arduino Library Manager.

2. **Configure your Wi-Fi credentials:**
   - Open the code and replace the following with your network's details:
     - `ssid`: Your Wi-Fi network name.
     - `password`: Your Wi-Fi password.
     - `mqtt_server`: The IP address of your MQTT broker.

   ```cpp
   const char* ssid = "YOUR_SSID";
   const char* password = "YOUR_PASSWORD";
   const char* mqtt_server = "YOUR_MQTT_BROKER_IP";
