#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "./wifiService.h"

void WifiService::begin(){
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
  
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      WiFi.begin(ssid, password);
    }
}