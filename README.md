# Arduino GPS Tracker with SIM800L

A simple GPS tracker using Arduino UNO, SIM800L GSM module, and Neo-6M GPS. Sends Google Maps location via SMS every 10 minutes.

**No WhatsApp, no server, no Twilio. Pure GSM SMS.**

## 🧰 Hardware Requirements

- Arduino UNO
- SIM800L GSM Module (with proper 4.0–4.2V power supply ⚠️ very important)
- Neo-6M GPS Module
- External power supply for SIM800L (2A peak capability)

## 📦 Required Libraries

Install from Arduino Library Manager:
- **TinyGPS++**

## 🔌 Pin Connections

### GPS (Neo-6M → Arduino)
| GPS | Arduino |
|-----|---------|
| TX  | D4      |
| RX  | D3      |
| VCC | 5V      |
| GND | GND     |

### SIM800L → Arduino
| SIM800L | Arduino          |
|---------|------------------|
| TX      | D7               |
| RX      | D8               |
| GND     | GND              |
| VCC     | External 4V supply |

> ⚠️ **Do NOT power SIM800L from Arduino 5V** - It requires 4.0-4.2V with 2A peak current capability. Use a buck converter or Li-ion battery.

## 📱 SMS Output Example

```
Live Location:
https://maps.google.com/?q=15.391234,73.877654
```

Click the link → Opens directly in Google Maps 🗺️

## ⚠️ Important Notes

1. **SIM800L Power**: Must get enough current (2A peak). Use a buck converter or Li-ion battery.
2. **GPS Fix**: First fix can take 1–2 minutes outdoors with clear sky view.
3. **Phone Format**: Use international phone format (e.g., +91XXXXXXXXXX).
4. **SIM Card**: Ensure SIM has SMS capability and sufficient balance.

## 🚀 Getting Started

1. Install the TinyGPS++ library from Arduino Library Manager
2. Connect hardware according to pin connections above
3. Open `gps_tracker.ino` in Arduino IDE
4. Replace `+91XXXXXXXXXX` with your phone number
5. Upload to Arduino UNO
6. Wait for GPS fix (LED on GPS module may blink)
7. Receive SMS every 10 minutes with location

## 🧠 Possible Upgrades

- SMS only when location changes
- Add LOW POWER SLEEP mode
- Send location on missed call
- Add geo-fencing alerts
- Store last location in EEPROM
- Battery voltage monitoring

## 📄 License

MIT License - Feel free to use and modify!

## 🤝 Contributing

Pull requests are welcome. For major changes, please open an issue first.
