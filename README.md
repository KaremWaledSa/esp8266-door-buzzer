# ESP8266 Door Buzzer

> A Blynk-connected IoT device that triggers a buzzer or LED pulse from anywhere — remotely via the Blynk mobile app, using Blynk Edgent for zero-touch Wi-Fi provisioning and OTA firmware updates.

![Platform](https://img.shields.io/badge/Platform-ESP8266%20%2F%20Wemos%20D1%20Mini-blue)
![Language](https://img.shields.io/badge/Language-Arduino%20C%2B%2B-lightgrey)
![Cloud](https://img.shields.io/badge/Cloud-Blynk%20Edgent-purple)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

## Overview

This project turns an ESP8266 into a remotely-triggered buzzer. A single button in the Blynk app sends a command to virtual pin V0, which fires a brief pulse on the output pin — activating a buzzer, LED, or relay.

The project uses **Blynk Edgent**, which handles Wi-Fi provisioning via a captive portal, OTA firmware updates, and automatic reconnection — all without hardcoding credentials.

---

## Features

| Feature | Implementation |
|---|---|
| Remote trigger | Blynk virtual pin V0 → pulse on D4 |
| Wi-Fi provisioning | Blynk Edgent captive portal (no hardcoded SSID) |
| OTA updates | Built-in via Blynk Edgent |
| Status indication | On-board LED reflects connection state |
| Config reset | Hold GPIO0 button for 10 seconds |

---

## Hardware

| Component | Notes |
|---|---|
| ESP8266 board | Wemos D1 Mini or NodeMCU |
| Buzzer or LED | Connected to D4 (GPIO2) via appropriate resistor/driver |
| Optional: reset button | GPIO0 — usually the FLASH button on D1 Mini |

**Wiring:**

```
D4 (GPIO2) ──► 100Ω resistor ──► LED ──► GND
           or
D4 (GPIO2) ──► Transistor base ──► Buzzer ──► GND
```

---

## How It Works

```
Blynk app (phone)
      │
      │  V0 button press
      ▼
Blynk cloud (blynk.cloud)
      │
      │  MQTT/TLS
      ▼
ESP8266 (BlynkEdgent)
      │
      └──► BLYNK_WRITE(V0): pulse D4 HIGH → delay → LOW
```

**Provisioning flow (first run):**

```
1. Power on the ESP8266
2. It creates a Wi-Fi AP: "Blynk <device-name>"
3. Open the Blynk app → Add Device → find the AP
4. Enter your Wi-Fi credentials in the app
5. Device connects to your router and to Blynk cloud
6. Credentials are saved to EEPROM — no re-provisioning needed
```

---

## Repository Structure

```
esp8266-door-buzzer/
├── firmware/
│   └── door_buzzer/
│       ├── door_buzzer.ino      # Main sketch — edit template ID here
│       ├── secrets.example.h    # Credential placeholders
│       ├── BlynkEdgent.h        # Edgent framework entry point
│       ├── BlynkState.h         # Connection state machine
│       ├── ConfigMode.h         # Captive portal + provisioning
│       ├── ConfigStore.h        # EEPROM credential storage
│       ├── Console.h            # Serial debug console
│       ├── Indicator.h          # LED status indication
│       ├── OTA.h                # Over-the-air update handler
│       ├── ResetButton.h        # 10-second factory reset
│       └── Settings.h           # Board pin definitions and timeouts
├── docs/
│   └── SETUP.md
├── .gitignore
├── LICENSE
└── README.md
```

---

## Getting Started

### Prerequisites

- Arduino IDE 2.x with ESP8266 board package
- Blynk library ≥ 1.3.0 (new Blynk, not legacy)
- A Blynk account at [blynk.cloud](https://blynk.cloud)

### Create a Blynk Template

```
1. Log in to https://blynk.cloud
2. Developer Zone → New Template
3. Add Datastream: Virtual Pin V0, Integer, 0–1
4. Add Widget in the mobile app: Button → V0, Switch mode
5. Copy BLYNK_TEMPLATE_ID and BLYNK_TEMPLATE_NAME
```

### Configure & Flash

```
1. Open: firmware/door_buzzer/door_buzzer.ino
2. Replace the two defines at the top:
      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Your Template Name"
3. Flash to the board
4. Open Serial Monitor at 115200 baud
```

### Provision the Device

```
1. Power on — the board creates a Wi-Fi AP: "Blynk <name>"
2. Open the Blynk app → Add Device → scan for the AP
3. Follow the in-app setup to enter your Wi-Fi credentials
4. Device connects and appears online in Blynk dashboard
```

### Reset to Factory

Hold the GPIO0 button (FLASH button on D1 Mini) for **10 seconds**. The device clears its stored credentials and returns to provisioning mode.

---

## Security

Credentials are provisioned at runtime via the Blynk app and stored in EEPROM. Never hardcode Wi-Fi credentials or Blynk tokens in source files. The `secrets.example.h` file shows the expected format for documentation purposes only.

---

## License

MIT — see [LICENSE](LICENSE).
