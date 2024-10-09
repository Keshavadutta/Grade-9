#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22
#define SS_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
Servo myservo;

int pos = 0;
int lock_status = LOW;
String authorizedUID = "10 18 C9 1A"; // Replace this with your authorized UID (in HEX)

void setup() {
  Serial.begin(9600); // Start the serial connection
  delay(2000);
  SPI.begin(); // Initiate SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  myservo.attach(12); // Attach servo to pin 12
  myservo.write(0);   // Set servo initial position to 0 degrees
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  Serial.print("UID tag: ");
  String content = "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  
  // Compare the UID with the authorizedUID
  if (content.substring(1) == authorizedUID) {
    Serial.println("Authorized access");
    myservo.write(90);   // Move servo to 90 degrees (open)
    delay(3000);         // Wait for 3 seconds
    myservo.write(0);    // Move servo back to 0 degrees (close)
  } else {
    Serial.println("Unauthorized access");
    myservo.write(0);    // Keep the servo at 0 degrees (locked)
  }

  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}
