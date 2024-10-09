#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include "AdafruitIO_WiFi.h"

// RFID Pins
#define SS_PIN 5
#define RST_PIN 22

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Servo setup
Servo myservo;

// Adafruit IO credentials
#define IO_USERNAME  "your_username"    // Replace with your Adafruit IO username
#define IO_KEY       "your_aio_key"     // Replace with your Adafruit IO Key

// Wi-Fi credentials
#define WIFI_SSID    "your_wifi_ssid"   // Replace with your Wi-Fi SSID
#define WIFI_PASS    "your_wifi_password" // Replace with your Wi-Fi password

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Create a feed called "servo-password" in Adafruit IO
AdafruitIO_Feed *servo_password = io.feed("servo-password");

// Correct password and authorized RFID UID
String correct_password = "1234";               // Replace with correct password
String authorizedUID = "10 18 C9 1A";           // Replace with the authorized RFID tag (UID in HEX)

// Function declarations
void handlePasswordInput(AdafruitIO_Data *data);
void checkRFID();

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

  // Initialize SPI bus and MFRC522
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("Present your RFID card or enter password from the cloud...");

  // Attach the servo to pin 12 and set to initial position
  myservo.attach(12);
  myservo.write(0);   // Initialize servo to 0 degrees (locked)

  // Set up a callback for the "servo-password" feed
  servo_password->onMessage(handlePasswordInput);
}

void loop() {
  // Keep the connection to Adafruit IO alive
  io.run();
  
  // Check for RFID tags
  checkRFID();
}

// Handle password input from Adafruit IO
void handlePasswordInput(AdafruitIO_Data *data) {
  String received_password = data->toString();

  Serial.print("Received Password: ");
  Serial.println(received_password);

  // If the received password matches the correct password
  if(received_password == correct_password) {
    Serial.println("Correct password. Unlocking servo...");
    unlockServo();
  } else {
    Serial.println("Incorrect password. Access denied.");
  }
}

// Check for RFID tags and match against authorized UID
void checkRFID() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  String rfidTag = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    rfidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  rfidTag.toUpperCase();
  
  Serial.print("UID tag: ");
  Serial.println(rfidTag);

  // Compare the read RFID UID with the authorized UID
  if (rfidTag.substring(1) == authorizedUID) {
    Serial.println("Authorized RFID. Unlocking servo...");
    unlockServo();
  } else {
    Serial.println("Unauthorized RFID.");
  }

  // Halt the PICC and stop encryption on PCD
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// Function to unlock the servo
void unlockServo() {
  myservo.write(90);   // Move servo to 90 degrees (open)
  delay(3000);         // Wait for 3 seconds
  myservo.write(0);    // Move servo back to 0 degrees (locked)
}
