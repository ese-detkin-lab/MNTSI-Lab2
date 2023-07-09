#define BLYNK_TEMPLATE_ID "TMPL29ZktT9jQ"
#define BLYNK_TEMPLATE_NAME "sht40"
#define BLYNK_AUTH_TOKEN "iIx6-N_hqg0vbiXWAolU8ZoHcewb8soj"

// include the library code:
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HP Setup 1";//"Halo i bims der FritZ";
char pass[] = "detkin101";//"Keine#Hose!Wlan42";

#include "Adafruit_SHT4x.h"

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

double h = 0, t = 0;

void setup() {
  Serial.begin(9600);
  
  // Setup the SHT40
  if (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    while (1) delay(1);
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);
  
  // You can have 3 different precisions, higher precision takes longer
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  // You can have 6 different heater settings
  // higher heat and longer times uses more power
  // and reads will take longer too! This will skew
  // the temperature, so let's not use the heater.
  sht4.setHeater(SHT4X_NO_HEATER);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  
  Serial.println("starting");
  Blynk.virtualWrite(V0, "temp");
  Blynk.virtualWrite(V1, "humidity");
}


void loop() {
  Blynk.run();
  // Wait a couple seconds between measurements.
  delay(2000);
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

  Serial.print("Temperature: ");
  Serial.println(temp.temperature);
  Blynk.virtualWrite(V0, temp.temperature);
  

  delay(100);
  
  Serial.print("Humidity: ");
  Serial.println(humidity.relative_humidity);
  Blynk.virtualWrite(V1, humidity.relative_humidity);
  
}
