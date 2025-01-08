#include <PicoMQTT.h>
#include <DHT.h>

#if __has_include("config.h")
#include "config.h"
#endif

#ifndef WIFI_SSID
#define WIFI_SSID "TAN TIEN HOME" 
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "@999999999" 
#endif

#define DHTPIN 4 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);
PicoMQTT::Client mqtt("broker.hivemq.com");
unsigned long last_publish_time = 0;

void setup() {
    Serial.begin(9600);

    dht.begin();

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
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }

        Serial.println("Publishing temperature and humidity...");

        String tempPayload = "Temperature: " + String(temperature) + "°C";
        bool tempResult = mqtt.publish("blcap-sep400/device", tempPayload.c_str());
        if (tempResult) {
            Serial.println("Temperature published successfully!");
        } else {
            Serial.println("Failed to publish temperature!");
        }

        String humidityPayload = "Humidity: " + String(humidity) + "%";
        bool humidityResult = mqtt.publish("blcap-sep400/device/humidity", humidityPayload.c_str());
        if (humidityResult) {
            Serial.println("Humidity published successfully!");
        } else {
            Serial.println("Failed to publish humidity!");
        }

        last_publish_time = millis();
        Serial.println("Finished publishing.");
    }
}
