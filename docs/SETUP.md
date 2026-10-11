# Setup Guide

## Requirements

| Tool | Version | Notes |
|---|---|---|
| Arduino IDE | 2.x | https://www.arduino.cc/en/software |
| ESP8266 board package | Latest | Add board manager URL (see below) |
| Blynk library | ≥ 1.3.0 | Install via Library Manager: search "Blynk" |

Board manager URL:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

> ⚠️ Install only the **new Blynk library** (v1.x). The legacy library (v0.6.x) is incompatible with Blynk Edgent.

## Board Settings

| Setting | Value |
|---|---|
| Board | LOLIN(WEMOS) D1 R2 & mini |
| Upload Speed | 115200 |
| Flash Size | 4MB (FS:2MB OTA:~1019KB) |

## Template Setup (Blynk Cloud)

```
1. Go to https://blynk.cloud → Developer Zone → Templates
2. Click "+ New Template"
3. Name: e.g. "Door Buzzer", Hardware: ESP8266, Connection: WiFi
4. Datastreams tab → "+ New Datastream" → Virtual Pin
   - Name: Trigger
   - Pin: V0
   - Data Type: Integer
   - Min: 0, Max: 1
5. Dashboard tab → add a Button widget → assign V0 → Switch mode
6. Copy BLYNK_TEMPLATE_ID and BLYNK_TEMPLATE_NAME from the template info
```

## Flash

```
1. Open firmware/door_buzzer/door_buzzer.ino
2. Replace:
      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Your Name"
3. Upload to board
```

## Provision (First Run)

```
1. Power on
2. Board broadcasts Wi-Fi AP: "Blynk <device-name>"
3. Blynk mobile app → Add Device → connect to the AP
4. Enter your home Wi-Fi SSID and password
5. Device saves credentials to EEPROM and connects
```

## Verify

Open Serial Monitor (115200 baud). You should see:
```
Connecting to WiFi...
Using Dynamic IP: 192.168.x.x
Blynk connected
```

## Reset

Hold the FLASH button (GPIO0) for 10 seconds to erase stored credentials and return to provisioning mode.
