#include <Arduino.h>
#include <Network.h>

#define EAP_IDENTITY ""
#define EAP_PASSWORD ""
const char* ssid = "INF";

const char* device;

#if defined(DEVICE_ESP01)
    device = ""
#endif

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

    Serial.println("Setup done");
}

void loop()
{
    scanNetworks();
    Serial.println("");
    
    delay(5000);
}