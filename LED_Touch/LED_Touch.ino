// Program to test the touch feature of the ESP32
// ESP32 Touch Test - touch pin - Touch0 is T0 which is on GPIO 4
int onboard_led = 2;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("ESP32 Touch Test");
  pinMode(onboard_led, OUTPUT);
}

void loop() {
  Serial.println(touchRead(T0)); // get value using T0
  if (touchRead(T0) <= 20) {
    digitalWrite(onboard_led, HIGH);
    Serial.println("LED is activated as Touch is detected");
  }
  else {
    digitalWrite(onboard_led, LOW);
  }
  delay(1000); // check for touch value after every 1 second
}
