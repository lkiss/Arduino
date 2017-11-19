#include <Arduino.h>

#include "./services/services.h"

ConfigService configService;
WifiService wifiService;
DataService dataService(configService);

void setup()
{
    wifiService.begin();

    Serial.begin(9600);
    Serial.print("WIFI_START");

    while (Serial.available() == 0)
    {
    }

    String testJson = Serial.readString();
    dataService.sendSensorReadings(testJson);
    Serial.print("WIFI_END");
    Serial.end();
    ESP.deepSleep(10e6, WAKE_RF_DEFAULT);
}

void loop()
{
}