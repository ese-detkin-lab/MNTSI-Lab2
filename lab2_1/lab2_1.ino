#define BLYNK_TEMPLATE_ID "TMPL2p9wJ0rmO"
#define BLYNK_TEMPLATE_NAME "LCD MKR 1010"
#define BLYNK_AUTH_TOKEN "3io2qrjoiVVBVE4cF2IGg324jB1GPWPB"

// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String incomingByte; // for incoming serial data


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Zimmer 2017";
char pass[] = "";

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 Blynk.run();
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.readString();
    Serial.print(incomingByte);

    // say what you got:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(incomingByte);
    Blynk.virtualWrite(V0, incomingByte);
  }
  
}
