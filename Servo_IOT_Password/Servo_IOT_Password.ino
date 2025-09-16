#include <AdafruitIO_WiFi.h> // Library to connect Adafruit IO with WiFi
#include <WiFi.h> // ESP32 WiFi library
#include <ESP32Servo.h> //ESP32 Servo library
/******** Adafruit IO Config ***********/
#define IO_USERNAME "Akhlk12"    // Replace with your Adafruit IO username
#define IO_KEY "aio_rKXa802KBUssrj4ExEnlNH4" // Replace with your Adafruit IO key


/******** WiFi Config **************/
#define WIFI_SSID "Abcd"          // Your WiFi SSID
#define WIFI_PASS "a#@12Aa"     // Your Password


Servo myservo;
/******** Adafruit IO Setup ************/
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
// Set up the Adafruit IO feed for LED control
AdafruitIO_Feed *control_servo_feed = io.feed("Servo");
void setup() {
 // Start the serial connection
 Serial.begin(115200);
 myservo.attach(12); // Attach servo to pin 12

 // Connect to Adafruit IO
 Serial.print("Connecting to Adafruit IO");
 io.connect();
 // Set up a message handler for when feed data is received
 control_servo_feed->onMessage(handleMessage);
 // Wait for a connection to Adafruit IO
 while(io.status() < AIO_CONNECTED) {
 Serial.print(".");
 delay(500);
 }
 // We’re connected!
 Serial.println();
 Serial.println("Connected to Adafruit IO!");
}

void loop() {
 // io.run() is required to process Adafruit IO messages
 io.run();
}
// Function to handle received feed data
void handleMessage(AdafruitIO_Data *data) {
 // Print the received value (on/off) to the Serial Monitor
 Serial.print("Received: ");
 Serial.println(data->value());
 int angle = constrain(data->toInt(), 0, 180); // Ensure the angle is between 0 and 180
 myservo.write(angle); // Set servo position
} 

