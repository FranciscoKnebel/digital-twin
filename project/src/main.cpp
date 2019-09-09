#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <Network.h>




// #if defined(DEVICE_ESP01)
//     device = ""
// #endif

#define DHT_PIN 16
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    int counter = 0;

    #if defined(DEVICE_ESP01) || defined(DEVICE_ESP02)
        esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
        esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
        esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
        esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
        esp_wifi_sta_wpa2_ent_enable(&config);
        WiFi.begin(ssid);
    #endif

    #if defined(DEVICE_ESP03)
        struct station_config *config;
        wifi_station_set_config(config);
        wifi_station_set_wpa2_enterprise_auth(1);
        wifi_station_set_enterprise_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
        wifi_station_set_enterprise_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
        wifi_station_connect();
    #endif

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        counter++;
        
        if(counter >= 60) {
            ESP.restart();
        }
    }

    dht.begin();

    Serial.println("Setup done");
}

void loop()
{
    Serial.println("");

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C ");
    
    delay(2000);
}