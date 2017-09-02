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
#include "./services/routing/routingService.h"

int pinDHT11 = 14;
int pinSoilMoisture01 = 4;
int pinSoilMoisture02 = 5;
int pinWaterPump01 = 12;
int pinWaterPump02 = 13;
int waterSensorPin = 16;
long timeBetweenWatering = 60000 * 30;

Timer timer;
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient http;

RoutingService routingService(httpServer);
DHT11Service dht11Service(pinDHT11);
SoilMoistureService soilMoistureService01(pinSoilMoisture01);
SoilMoistureService soilMoistureService02(pinSoilMoisture02);
WaterPumpService waterPumpService01(pinWaterPump01, waterSensorPin);
WaterPumpService waterPumpService02(pinWaterPump02, waterSensorPin);

WifiService wifiService;
OtaServerService otaServerService;

JsonBuilderService jsonBuilderService;

void handleSensorRequest()
{
  int soilMoistureReadings[2];
  soilMoistureReadings[0] = soilMoistureService01.read();
  soilMoistureReadings[1] = soilMoistureService02.read();

  int dht11Readings[2];
  dht11Service.read(dht11Readings);
  
  httpServer.send(200, "application/json", jsonBuilderService.getSensorReadingsAsJson(soilMoistureReadings, soilMoistureReadings));
}

void handleWaterPumpRequest()
{
  httpServer.send(200);
}

void water()
{
  //Log debug
  bool isWateringNeeded01 = soilMoistureService01.isWateringNeeded();
  bool isWateringNeeded02 = soilMoistureService02.isWateringNeeded();

  if (isWateringNeeded01 == true)
  {
    waterPumpService01.activateWaterPump();
  }

  if (isWateringNeeded02 == true)
  {
    waterPumpService02.activateWaterPump();
  }
}

void postSensorReadings()
{
  http.addHeader("Content-Type", "application/json");
  // http.POST(getSensorReadingsAsJson());

  http.end();
}

void plantManagerServerSetup()
{
  http.begin("http://192.168.1.100:3000/sensor");
}

void setup(void)
{
  wifiService.begin();
  otaServerService.begin("Test", &httpServer, &httpUpdater);
  routingService.begin(handleSensorRequest);

  timer.every(timeBetweenWatering, water);
}

void loop(void)
{
  httpServer.handleClient();
  timer.update();
}