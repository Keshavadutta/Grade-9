#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5   // SDA
#define RST_PIN 22 // Reset
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.println("Approximate your card to the reader...");
}

void loop() {
  // Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print card UID (even if not MIFARE Classic)
  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Halt PICC (stop reading the card)
  mfrc522.PICC_HaltA();
}
