#include <SoftwareSerial.h>
#include <TinyGPS.h>
// Pin Definitions
const int pin = 9; // Button pin
int state = 0; // To track SMS sending state
float gpslat, gpslon; // Variables to store GPS coordinates
TinyGPS gps;
SoftwareSerial sgps(8, 9); // GPS module RX, TX
SoftwareSerial sgsm(2, 3); // GSM module RX, TX
void setup() {
pinMode(pin, INPUT); // Button input
sgsm.begin(9600); // Start GSM communication
sgps.begin(9600); // Start GPS communication
Serial.begin(9600); // Debugging on Serial Monitor
Serial.println("System Initialized. Waiting for GPS fix...");
}
void loop() {
sgps.listen(); // Ensure GPS module is active
while (sgps.available()) {
char c = sgps.read(); // Read data from GPS
if (gps.encode(c)) { // Parse GPS data
gps.f_get_position(&gpslat, &gpslon); // Get latitude and longitude
}
}
// Debugging: Print GPS data to the Serial Monitor
if (gpslat != TinyGPS::GPS_INVALID_F_ANGLE && gpslon !=
TinyGPS::GPS_INVALID_F_ANGLE) {
Serial.print("Latitude: "); Serial.println(gpslat, 6);
Serial.print("Longitude: "); Serial.println(gpslon, 6);
} else {
Serial.println("No valid GPS data yet.");
}
// Check if button is pressed and SMS hasn't been sent
if (digitalRead(pin) == HIGH && state == 0) {
sgsm.listen(); // Ensure GSM module is active
// Send SMS
sendSMS();
state = 1; // Update state to prevent multiple SMS
33
}
// Reset state when button is released
if (digitalRead(pin) == LOW) {
state = 0;
}
delay(100); // Small delay for debounce
}
// Function to send SMS with GPS location
void sendSMS() {
sgsm.print("\r"); // Wake GSM module
delay(1000);
sgsm.print("AT+CMGF=1\r"); // Set SMS mode
delay(1000);
// Replace XXXXXXXXXX with a valid phone number
sgsm.print("AT+CMGS=\"+91XXXXXXXXXX\"\r");
delay(1000);
// The SMS content with Google Maps link
sgsm.print("https://www.google.com/maps/?q=");
sgsm.print(gpslat, 6);
sgsm.print(",");
sgsm.print(gpslon, 6);
delay(1000);
sgsm.write(0x1A); // End SMS with Ctrl+Z
delay(3000);
Serial.println("SMS Sent!");
