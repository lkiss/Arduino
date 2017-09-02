#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Timer.h>
#include "./services/dht11/DHT11Service.h"
#include "./services/soilMoisture/soilMoistureService.h"
#include "./services/waterPump/waterPumpService.h"
#include "./services/wifi/wifiService.h"
#include "./services/otaServer/otaServerService.h"
#include "./services/jsonBuilder/jsonBuilderService.h"

int pinDHT11 = 14;
int pinSoilMoisture01 = 4;
int pinSoilMoisture02 = 5;
int pinWaterPump01 = 12;
int pinWaterPump02 = 13;
int waterSensorPin = 16;
long timeBetweenWatering = 60000 * 30;

// Timer timer;
ESP8266WebServer webServer(80);
// ESP8266HTTPUpdateServer httpUpdater;
// HTTPClient http;
// DHT11Service dht11Service(&pinDHT11);
// SoilMoistureService soilMoistureService01(pinSoilMoisture01);
// SoilMoistureService soilMoistureService02(pinSoilMoisture02);
// WaterPumpService waterPumpService01(pinWaterPump01, waterSensorPin);
// WaterPumpService waterPumpService02(pinWaterPump02, waterSensorPin);

WifiService wifiService;
// OtaServerService otaServerService;
// JsonBuilderService jsonBuilderService;

void handleSensorRequest()
{
  webServer.send(200);
}

void handleWaterPumpRequest()
{
  webServer.send(200);
}
void handleInfoRequest()
{
  webServer.send(200);
}

void routingSetup()
{
  webServer.on("/sensor", handleSensorRequest);
  webServer.on("/waterpump", handleWaterPumpRequest);
  webServer.on("/info", handleInfoRequest);
}

void setup(void)
{
  wifiService.begin();
  webServer.begin();
  routingSetup()
}

void loop(void)
{
  webServer.handleClient();
  // timer.update();
}