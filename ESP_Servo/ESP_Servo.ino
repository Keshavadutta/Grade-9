#include <ESP32Servo.h> // Include the ESP32Servo library

Servo myServo;          // Create a servo object to control the servo motor
int servoPin = 15;      // Define the GPIO pin where the servo is connected
int angle = 0;          // Variable to store the servo angle

void setup() {
  myServo.attach(servoPin);  // Attach the servo to the defined GPIO pin
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (angle = 0; angle <= 180; angle++) {
    myServo.write(angle);   // Move the servo to the specified angle
    delay(15);              // Wait for 15ms to allow the servo to reach the position
  }

  // Sweep the servo back from 180 to 0 degrees
  for (angle = 180; angle >= 0; angle--) {
    myServo.write(angle);   // Move the servo back to the specified angle
    delay(15);              // Wait for 15ms to allow the servo to reach the position
  }
}
