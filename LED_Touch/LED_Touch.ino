#define LED_PIN 2        // LED connected to GPIO 2
#define TOUCH_PIN 4      // Touch input connected to GPIO 4

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
  Serial.begin(115200);     // Start serial communication for debugging
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);  // Read touch input on GPIO 4

  if (touchValue <= 20) {  // If the touch sensor is triggered
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off the LED
  }

  delay(1000);  // Short delay to avoid constantly reading the sensor
}
