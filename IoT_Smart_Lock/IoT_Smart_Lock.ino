#include <AdafruitIO_WiFi.h> // Library to connect Adafruit IO with WiFi
#include <WiFi.h> // ESP32 WiFi library
#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 27
#define SS_PIN 5

/******** Adafruit IO Config ***********/
#define IO_USERNAME "Akhilk12"    // Replace with your Adafruit IO username
#define IO_KEY "aio_kmcT63S4IDnIK5dPBHrHHMLLyd9c" // Replace with your Adafruit IO key

/******** WiFi Config **************/
#define WIFI_SSID "Abcd"          // Your WiFi SSID
#define WIFI_PASS "a#@7812Aa"  

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up the Adafruit IO feed for servo control
AdafruitIO_Feed *control_servo_feed = io.feed("smart_door");
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
Servo myservo;

int lock_status = LOW; // Door lock status: LOW = locked, HIGH = unlocked
const String AUTHORIZED_UID = "30 9B BB 5D"; // Authorized UID

// Function to lock the door
void lockDoor() {
  myservo.write(0); // Servo to locked position
  lock_status = LOW;
  Serial.println("Door Locked.");
}

// Function to unlock the door
void unlockDoor() {
  myservo.write(90); // Servo to unlocked position
  lock_status = HIGH;
  Serial.println("Door Unlocked.");
}

void setup() {
  Serial.begin(9600); // Start the serial connection
  delay(2000);
  Serial.println();

  //-----------------------------------------------------
  SPI.begin(); // Initiate SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  myservo.attach(12); // Attach servo to pin 12
  lockDoor(); // Ensure the door starts in the locked position

  //------------------------------------------------------
  control_servo_feed->onMessage(handleMessage);

  // Wait for a connection to Adafruit IO
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected to Adafruit IO!");
}

void loop() {
  io.run();

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  Serial.print("UID tag : ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    content += String(mfrc522.uid.uidByte[i], HEX);
  }
  content.trim(); // Remove extra spaces
  content.toUpperCase(); // Ensure consistency
  Serial.println(content);

  // Check if the scanned UID matches the authorized UID
  if (content == AUTHORIZED_UID) {
    Serial.println("Access Granted.");
    if (lock_status == LOW) {
      unlockDoor();
      delay(5000); // Keep the door unlocked for 5 seconds
      lockDoor();
    } else {
      Serial.println("Door is already unlocked.");
    }
  } else {
    Serial.println("Access Denied. Unauthorized card.");
  }

  // Halt PICC to stop reading
  mfrc522.PICC_HaltA();
}

// Function to handle received feed data
void handleMessage(AdafruitIO_Data *data) {
  // Print the received value (on/off) to the Serial Monitor
  Serial.print("Received: ");
  Serial.println(data->value());

  if (data->toInt() == 1) { 
    // If the IoT dashboard sends a HIGH signal (switch ON)
    myservo.write(90); // Set the servo to 90 degrees
  } else { 
    // If the IoT dashboard sends a LOW signal (switch OFF)
    myservo.write(0); // Set the servo to 0 degrees
  }
}
