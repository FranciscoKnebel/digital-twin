#ifdef ESP8266
    #include "ESP8266WiFi.h"

    #define WIFI_AUTH_OPEN ENC_TYPE_NONE
#endif

#ifdef ESP32
    #include "WiFi.h"
#endif

void scanNetworks();
void printNetwork(int i);