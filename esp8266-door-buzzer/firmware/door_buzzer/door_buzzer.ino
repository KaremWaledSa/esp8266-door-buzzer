// Blynk template credentials — copy from your Blynk dashboard
#define BLYNK_TEMPLATE_ID   "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial

#define APP_DEBUG

#include "BlynkEdgent.h"

// GPIO pin for the buzzer/LED (D4 = GPIO2 on Wemos D1 Mini / NodeMCU)
#define BUZZER_PIN D4

// V0: Blynk virtual button — triggers a short pulse on the buzzer/LED
BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(BUZZER_PIN, value);
  delay(100);
  digitalWrite(BUZZER_PIN, !value);
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
}

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // BlynkEdgent handles Wi-Fi provisioning automatically.
  // On first run: connect your phone to the "Blynk ..." AP
  // and configure credentials through the Blynk app.
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
