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

WifiService wifiService;
JsonService jsonService;
ConfigService configService;
DataService dataService(configService, jsonService);
SensorService sensorService(waterLevelSensor, waterPump, soilMoistureSensor);

void setup(void)
{
  wifiService.begin();
}

void loop(void)
{
  Configuration config = configService.getConfiguration();

  SensorReading reading;
  reading.humidity = 100;
  reading.soilMoisture = 920;
  reading.temperature = 25;
  reading.waterLevel = 40;
  reading.temperatureUnit = "C";
  reading.waterLevelUnit = "%";
  dataService.sendSensorReadings(reading);
  // ESP.deepSleep(5 * 1000000);

  delay(10000);
}