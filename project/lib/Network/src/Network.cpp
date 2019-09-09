#include <Arduino.h>

#include <Network.h>

void scanNetworks() {
    Serial.print("scan starting on board");
    // Serial.println(CURRENT_DEVICE);

    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            printNetwork(i);
            delay(10);
        }
    }
}

void printNetwork(int i) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.print(")");
    Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
}