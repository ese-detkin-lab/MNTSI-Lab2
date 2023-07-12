// Setup Blynk and WiFi in secrets.h
// include the library code:
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

const int trigPin = 3;
const int echoPin = 2;

long duration;
int distance;

void setup() {
 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("starting");
  Blynk.virtualWrite(V0, "hello");
}

void loop() {
 Blynk.run();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance to Blynk
  Blynk.virtualWrite(V0, distance);
  delayMicroseconds(5000);  
}
