#include <Arduino.h>
#include <Network.h>

void setup()
{
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}

void loop()
{
    scanNetworks();
    Serial.println("");
    
    delay(5000);
}