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

#define SOIL_MOISTURE_PIN A0 

PicoMQTT::Client mqtt("broker.hivemq.com");
unsigned long last_publish_time = 0;

void setup() {
    Serial.begin(9600);

    pinMode(SOIL_MOISTURE_PIN, INPUT);

    // Connect to WiFi
    Serial.printf("Connecting to WiFi %s\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");

    // Subscribe to topic
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
        int moistureLevel = analogRead(SOIL_MOISTURE_PIN);

        float moisturePercentage = ((1023 - moistureLevel) / 1023.0) * 100;

        if (moistureLevel < 0) {
            Serial.println("Failed to read from soil moisture sensor!");
            return;
        }

        Serial.println("Publishing soil moisture level...");

        String moisturePayload = "Soil Moisture: " + String(moisturePercentage, 1) + "%";
        bool moistureResult = mqtt.publish("blcap-sep400/device/soil_moisture", moisturePayload.c_str());
        if (moistureResult) {
            Serial.println("Soil moisture level published successfully!");
        } else {
            Serial.println("Failed to publish soil moisture level!");
        }

        last_publish_time = millis();
        Serial.println("Finished publishing.");
    }
}
