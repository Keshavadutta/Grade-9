# Grade 9 Code Repository

Welcome to the Grade 9 Code Repository! This repository contains various IoT and electronics activities involving ESP32, Arduino, and other components, along with the necessary library files in the **Library Zip Files** folder.

## Activities

The following activities are included:

- **IoT_Smart_Lock**: Build an IoT smart lock using RFID and a servo motor.
- **Servo_IoT_Password**: Control a servo motor with a password through the cloud.
- **RFID_Servo**: Control a servo motor with an RFID reader.
- **Read_RFID**: Basic RFID reader functionality.
- **LED_Touch**: Turn an LED on/off using a touch sensor.
- **ESP_Servo**: Control a servo motor using the ESP32.
- **LED**: Simple LED control.

Each activity covers a different concept related to IoT and automation using sensors, actuators, and cloud-based control.

## Library Zip Files

All the libraries required for these activities are available in the **Library Zip Files** folder. Make sure to install the appropriate libraries before running the code.

## How to Install Libraries in Arduino IDE

1. Download the necessary `.zip` library files from the **Library Zip Files** folder.
2. Open the Arduino IDE.
3. Go to **Sketch > Include Library > Add .ZIP Library...**
4. Navigate to the location where you downloaded the `.zip` file, select it, and click **Open**.
5. The library will now be installed and available for use in your Arduino projects.

### Required Libraries:
- **Adafruit IO Library**: For communication with Adafruit IO.
- **ESP32 Servo Library**: For controlling servo motors.
- **MFRC522 Library**: For RFID functionality.
- **WiFi Library**: For ESP32 Wi-Fi connection.

---

## How to Use

### 1. **Adafruit IO Setup**:

For all IoT projects, you need an **Adafruit IO** account to interact with the cloud. To set up the projects:

1. **Create an account on Adafruit IO**: Go to [Adafruit IO](https://io.adafruit.com/) and sign up for a free account.
2. **Create Feeds**: For each project, create a feed in Adafruit IO to store or send data like RFID readings, servo control commands, etc.
   - For example, for the **Servo_IoT_Password** project, create a feed named `servo_control`.

### 2. **WiFi and Adafruit IO Credentials**:

Replace the placeholders `"your_username"`, `"your_aio_key"`, `"your_wifi_ssid"`, and `"your_wifi_password"` in the project code files with your actual Adafruit IO and Wi-Fi credentials.

- **IO Username**: The username you created on Adafruit IO.
- **IO Key**: This is your Adafruit IO key, which can be found in your Adafruit IO dashboard under **My Profile**.
- **Wi-Fi SSID**: Your Wi-Fi network name.
- **Wi-Fi Password**: Your Wi-Fi password.

Example:

```cpp
#define IO_USERNAME  "Sujaykumar"      // Replace with your Adafruit IO username
#define IO_KEY       "aio_TdoX96ijmCNO03WYWj5nmU5zQgzG"       // Replace with your Adafruit IO key
#define WIFI_SSID    "Sujaykmr"     // Replace with your Wi-Fi SSID
#define WIFI_PASS    "P@ssw0rd"     // Replace with your Wi-Fi password
```

---
