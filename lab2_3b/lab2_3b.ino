// Paste the Blynk tokens and the WiFi info in secrets.h
#include "secrets.h"
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// #define statements are substituded out literally during a compile
// They can be useful for specifying hardcoded strings or alternate names, etc.

//Set this to the UID of the card that you want to allow access for
#define ALLOWED_UID "00 00 00 00"

const int greenLed = 3;
const int redLed = 4;
const int servoPin = 5;
const int RST_PIN=6;
const int SS_PIN=7;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myservo; // Create variable for Servo instance

bool successful_scan = true;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication

  // Pause for 5 seconds to allow serial to detect on computer
  delay(5000);

  Serial.println("Setting up");
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  // attaches the servo on pin 8 to the servo and latter
  // two arguments will give us a full 180-degree servo range
  myservo.attach(servoPin, 544, 2400);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);


  Serial.println();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.virtualWrite(V0, "RFID");
}

void loop() {
  // Only print the first time through, and after a good scan occurs
  // Prevents spamming the serial monitor
  if(successful_scan){
    Serial.println("Bring your card close to the reader");
    successful_scan = false;
  }

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  successful_scan = true;
  //Show UID on serial monitor
  Serial.print("UID tag :");

  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  Blynk.virtualWrite(V0, content);

  if (content.substring(1).equals(ALLOWED_UID)) {
    Serial.println("Authorized access");
    digitalWrite(greenLed, HIGH);
    myservo.write(95);
    delay(3000);
    myservo.write(0);
    digitalWrite(greenLed, LOW);
  } else {
    Serial.println("Access denied");
    for(int i = 0; i<3; i++){
      digitalWrite(redLed, HIGH);
      delay(500); // delay in milliseconds (you can adjust the time)
      digitalWrite(redLed, LOW);
      delay(500); // delay in milliseconds (you can adjust the time)
    }
    delay(3000); // delay in milliseconds (you can adjust the time)
  }
}
