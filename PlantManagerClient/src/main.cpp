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
#include "./services/email/emailService.h"

int DHT11Pin = 14;
int soilMoisturePin01 = 4;
int soilMoisturePin02 = 5;
int waterPumpPin01 = 12;
int waterPumpPin02 = 13;
int waterSensorPin = 16;
long timeBetweenMeasuring = 60000 * 30; //30 minutes

Timer timer;
ESP8266WebServer webServer(80);

DHT11Service dht11Service(&DHT11Pin);
SoilMoistureService soilMoistureService01(&soilMoisturePin01);
SoilMoistureService soilMoistureService02(&soilMoisturePin02);
WaterPumpService waterPumpService01(&waterPumpPin01, &waterSensorPin);
WaterPumpService waterPumpService02(&waterPumpPin02, &waterSensorPin);
EmailService emailService;
WifiService wifiService;
JsonBuilderService jsonBuilderService;

String getSensorReadingsAsJson()
{
  int soilMoistureReadings[2];
  int dht11Readings[2];

  soilMoistureReadings[0] = soilMoistureService01.read();
  soilMoistureReadings[1] = soilMoistureService02.read();
  dht11Service.read(dht11Readings);

  return jsonBuilderService.convertSensorReadingsToJson(soilMoistureReadings, dht11Readings);
}

void water()
{
  bool result = false;
  result = waterPumpService01.activateWaterPump();
  result = waterPumpService02.activateWaterPump();

  if (result == false)
  {
    emailService.sendEmail("Water tank empty!", "kisslac1988@hotmail.com", "Please refill water tank!");
  }
}

void handleSensorRequest()
{
  webServer.send(200, "application/json", getSensorReadingsAsJson());
}

void handleWaterPumpRequest()
{
  water();
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
  routingSetup();

  timer.every(timeBetweenMeasuring, water);
}

void loop(void)
{
  webServer.handleClient();
  timer.update();
}