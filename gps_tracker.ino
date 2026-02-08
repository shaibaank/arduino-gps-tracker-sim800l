/*
 * Arduino GPS Tracker with SIM800L
 * 
 * Sends Google Maps location via SMS every 10 minutes
 * 
 * Hardware:
 * - Arduino UNO
 * - SIM800L GSM Module (4.0-4.2V external power!)
 * - Neo-6M GPS Module
 * 
 * Connections:
 * GPS TX  -> D4
 * GPS RX  -> D3
 * SIM TX  -> D7
 * SIM RX  -> D8
 */

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// GPS serial (RX, TX)
SoftwareSerial gpsSerial(4, 3);

// SIM800L serial (RX, TX)
SoftwareSerial sim800l(7, 8);

TinyGPSPlus gps;

String phoneNumber = "+91XXXXXXXXXX"; // Replace with your phone number

unsigned long lastSMSTime = 0;
const unsigned long interval = 600000; // 10 minutes in milliseconds

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  sim800l.begin(9600);

  delay(3000);

  Serial.println("Initializing SIM800L...");
  sim800l.println("AT");
  delay(1000);
  sim800l.println("AT+CMGF=1");  // Set SMS to text mode
  delay(1000);
  
  Serial.println("GPS Tracker Started");
  Serial.println("Waiting for GPS fix...");
}

void loop() {
  // Read GPS data
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    if (millis() - lastSMSTime > interval) {
      sendLocationSMS();
      lastSMSTime = millis();
    }
  }
}

void sendLocationSMS() {
  double lat = gps.location.lat();
  double lng = gps.location.lng();

  String mapsLink = "https://maps.google.com/?q=";
  mapsLink += String(lat, 6);
  mapsLink += ",";
  mapsLink += String(lng, 6);

  String message = "Live Location:\n" + mapsLink;

  Serial.println("Sending SMS...");
  Serial.println(message);

  sim800l.println("AT+CMGS=\"" + phoneNumber + "\"");
  delay(1000);
  sim800l.print(message);
  delay(500);
  sim800l.write(26); // CTRL+Z to send
  delay(5000);

  Serial.println("SMS Sent!");
}
