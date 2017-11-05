#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

#include "./devices/devices.h"
#include "./services/services.h"

int DHT11Pin = 14;
int soilMoisturePin = 5;
int waterPumpPin = 4;
int waterSensorEchoPin = 12;
int waterSensorTriggerPin = 13;

TemperatureSensor temperatureSensor(&DHT11Pin);
SoilMoistureSensor soilMoistureSensor(&soilMoisturePin);
WaterPump waterPump(&waterPumpPin);
WaterLevelSensor waterLevelSensor(&waterSensorTriggerPin, &waterSensorEchoPin);

EmailService emailService;
WifiService wifiService;
JsonService jsonService;
ConfigService configService;
DataService dataService;
SensorService sensorService(waterLevelSensor, waterPump, soilMoistureSensor);

HTTPClient httpClient;

void setup(void)
{
  Configuration config = configService.getConfiguration();
  //sensorService.water();
  //waterPump.activateWaterPump();
  wifiService.begin();

  SensorReading reading;
  reading.humidity = 100;
  reading.soilMoisture = 920;
  reading.temperature = 25;
  reading.waterLevel = 40;

  // dataService.sendSensorReadings(reading);

  // String jsonMessage = jsonService.convertSensorReadingsToJson(reading);

  // httpClient.begin("192.168.1.100/szilahome/sensor");
  // httpClient.addHeader("Content-Type", "application/json");

  // int httpStatusCode = httpClient.POST(jsonMessage);
  // httpClient.end();

  // delay(10000);

  //ESP.deepSleep(config.measuringInterval);
}

void loop(void)
{
}