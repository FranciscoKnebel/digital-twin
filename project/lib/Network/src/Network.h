#ifdef ESP8266
    #include "ESP8266WiFi.h"
    #include <user_interface.h>

    #define WIFI_AUTH_OPEN ENC_TYPE_NONE
#endif

#ifdef ESP32
    #include "WiFi.h"
    #include "esp_wpa2.h"
#endif


void scanNetworks();
void printNetwork(int i);

