#include <ESP32Servo.h>
Servo myservo;
int pos = 0; // store servo angle

void setup() {
  Serial.begin(9600);
  myservo.attach(12); // Servo connected to GPIO 12
  Serial.println("Start Servo");
  Serial.print("Angle = 90 deg");
  myservo.write(90); // Move to center position
  Serial.println("Fix small gear");
  delay(3000);
}

void loop() {
  for (pos = 0; pos <= 180; pos++) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos--) {
    myservo.write(pos);
    delay(15);
  }
}
