#include <ESP32Servo.h>
#include "AdafruitIO_WiFi.h"

// Adafruit IO credentials
#define IO_USERNAME  "your_username"   // Replace with your Adafruit IO username
#define IO_KEY       "your_aio_key"    // Replace with your Adafruit IO Key

// Wi-Fi credentials
#define WIFI_SSID    "your_wifi_ssid"  // Replace with your Wi-Fi SSID
#define WIFI_PASS    "your_wifi_password" // Replace with your Wi-Fi password

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Create a feed called "servo-password"
AdafruitIO_Feed *servo_password = io.feed("servo-password");

Servo myservo;
int pos = 0;
String correct_password = "1234";  // Set the correct password

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  io.connect();
  
  // Wait for the connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected to Adafruit IO!");

  // Attach the servo to pin 12
  myservo.attach(12);
  myservo.write(0);   // Initialize servo to 0 degrees (locked)

  // Set up a callback for the "servo-password" feed
  servo_password->onMessage(handlePasswordInput);
}

void loop() {
  // Keep the connection to Adafruit IO alive
  io.run();
}

// Function to handle password input from Adafruit IO
void handlePasswordInput(AdafruitIO_Data *data) {
  String received_password = data->toString();

  // Print received password for debugging
  Serial.print("Received Password: ");
  Serial.println(received_password);

  // Check if the received password matches the correct password
  if(received_password == correct_password) {
    Serial.println("Correct password. Servo unlocking...");
    myservo.write(90);   // Move servo to 90 degrees (open)
    delay(3000);         // Wait for 3 seconds
    myservo.write(0);    // Move servo back to 0 degrees (locked)
  } else {
    Serial.println("Incorrect password. Access denied.");
  }
}
