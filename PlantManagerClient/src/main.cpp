#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include <Timer.h>

#include "./devices/devices.h"
#include "./services/services.h"

int DHT11Pin = 14;
int soilMoisturePin01 = 4;
int soilMoisturePin02 = 5;
int waterPumpPin01 = 12;
int waterPumpPin02 = 13;
int waterSensorPin = 16;
long measuringInterval = 60000 * 30; //30 minutes
int measureIntervalTimerId = -1;

Timer timer;
ESP8266WebServer webServer(80);

TemperatureSensor TemperatureSensor(&DHT11Pin);
SoilMoistureSensor SoilMoistureSensor01(&soilMoisturePin01);
SoilMoistureSensor SoilMoistureSensor02(&soilMoisturePin02);
WaterPump WaterPump01(&waterPumpPin01, &waterSensorPin);
WaterPump WaterPump02(&waterPumpPin02, &waterSensorPin);
EmailService emailService;
WifiService wifiService;
JsonService jsonService;
ConfigService configService;

String getSensorReadingsAsJson()
{
  int soilMoistureReadings[2];
  int dht11Readings[2];

  soilMoistureReadings[0] = SoilMoistureSensor01.read();
  soilMoistureReadings[1] = SoilMoistureSensor02.read();
  TemperatureSensor.read(dht11Readings);

  return jsonService.convertSensorReadingsToJson(soilMoistureReadings, dht11Readings);
}

void water()
{
  bool result = false;
  
  result = WaterPump01.activateWaterPump();
  result = WaterPump02.activateWaterPump();

  if (result == false)
  {
    emailService.SendEmail("Water tank empty!", "kisslac1988@hotmail.com", "Please refill water tank!");
  }
}

void handleSensorRequest()
{
  Serial.print("Handling Sensor Request");
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

void handleGetConfigRequest()
{
  String jsonMessage;
  jsonMessage = configService.getConfigurationJson();
  webServer.send(200, "application/json", jsonMessage);
}

void updateMeasureTimerInterval(int measuringInterval){
  if(measureIntervalTimerId != -1){
    timer.stop(measureIntervalTimerId);
  }
  measureIntervalTimerId = timer.every(measuringInterval, water);
}

void setupFromConfig(){
  Configuration config = configService.getConfiguration();

  updateMeasureTimerInterval(config.measuringInterval);
}

void handlePutConfigRequest()
{
  if (webServer.hasArg("plain") == false)
  {
    webServer.send(200, "text/plain", "Body not received");
    return;
  }

  configService.setConfigurationJson(webServer.arg("plain"));

  setupFromConfig();

  webServer.send(200);
}

void routingSetup()
{
  webServer.on("/sensor", HTTP_GET, handleSensorRequest);
  webServer.on("/waterpump", HTTP_GET, handleWaterPumpRequest);
  webServer.on("/config", HTTP_GET, handleGetConfigRequest);
  webServer.on("/config", HTTP_PUT, handlePutConfigRequest);
  webServer.on("/info", HTTP_GET, handleInfoRequest);
}


void setup(void)
{
  Serial.begin(115200);  
  wifiService.begin();
  webServer.begin();
  routingSetup();

  Configuration config = configService.getConfiguration();

  updateMeasureTimerInterval(config.measuringInterval);
}

void loop(void)
{
  webServer.handleClient();
  timer.update();
}