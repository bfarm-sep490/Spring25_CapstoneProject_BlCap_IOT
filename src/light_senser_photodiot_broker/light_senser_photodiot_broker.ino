#include <PicoMQTT.h>

#if __has_include("config.h")
#include "config.h"
#endif

#ifndef WIFI_SSID
#define WIFI_SSID "TAN TIEN HOME"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "@999999999"
#endif

#define PHOTO_PIN A0 

PicoMQTT::Client mqtt("broker.hivemq.com");
unsigned long last_publish_time = 0;

void setup() {
    Serial.begin(9600);

    pinMode(PHOTO_PIN, INPUT);

    Serial.printf("Connecting to WiFi %s\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");

    mqtt.subscribe("blcap-sep400/device", [](const char *topic, const char *payload) {
        Serial.print("Message received on topic: ");
        Serial.println(topic);

        Serial.print("Payload: ");
        Serial.println(payload);
    });

    mqtt.begin();
}

void loop() {
    mqtt.loop();

    if (millis() - last_publish_time >= 10000) {
        int lightLevel = analogRead(PHOTO_PIN);

        float lightPercentage = (lightLevel / 1023.0) * 100;

        if (lightLevel < 0) {
            Serial.println("Failed to read from photodiode!");
            return;
        }

        Serial.println("Publishing light intensity...");

        String lightPayload = "Light Intensity: " + String(lightPercentage, 1) + "%";
        bool lightResult = mqtt.publish("blcap-sep400/device/light", lightPayload.c_str());
        if (lightResult) {
            Serial.println("Light intensity published successfully!");
        } else {
            Serial.println("Failed to publish light intensity!");
        }

        last_publish_time = millis();
        Serial.println("Finished publishing.");
    }
}
