#define BLYNK_TEMPLATE_ID "TMPL2p9wJ0rmO"
#define BLYNK_TEMPLATE_NAME "LCD MKR 1010"
#define BLYNK_AUTH_TOKEN "3io2qrjoiVVBVE4cF2IGg324jB1GPWPB"


#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char ssid[] = "Zimmer 2017";
char pass[] = "";

#define SS_PIN 6
#define RST_PIN 7

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myservo;

const int greenLed = 3;
const int redLed = 4;
const int servoPin = 5;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  Serial.println("Setting up");
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  // attaches the servo on pin 8 to the servo and latter
  // two arguments will give us a full 180-degree servo range
  myservo.attach(servoPin, 544, 2400);



  Serial.println();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.virtualWrite(V0, "RFID");
}

void loop() {
  
  Serial.println("Bring your card close to the reader");
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
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

  if (content.substring(1) == "00 00 00 00") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    digitalWrite(greenLed, HIGH);
    myservo.write(95);
    delay(3000);
    myservo.write(0);
    digitalWrite(greenLed, LOW);
  }
  else {
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
