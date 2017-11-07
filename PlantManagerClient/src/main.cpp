#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

#include "./devices/devices.h"
#include "./services/services.h"

int DHT11Pin = 5;
int powerPin = 14;
int waterPumpPin = 4;
int waterSensorEchoPin = 12;
int waterSensorTriggerPin = 13;

TemperatureSensor temperatureSensor(&DHT11Pin);
SoilMoistureSensor soilMoistureSensor;
WaterPump waterPump(&waterPumpPin);
WaterLevelSensor waterLevelSensor(&waterSensorTriggerPin, &waterSensorEchoPin);

WifiService wifiService;
JsonService jsonService;
ConfigService configService;
DataService dataService(configService, jsonService);
SensorService sensorService(waterLevelSensor, waterPump, soilMoistureSensor, temperatureSensor);

void setup(void)
{
  wifiService.begin();
  
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  delay(2000);

  Configuration config = configService.getConfiguration();

  SensorReading readings = sensorService.getSensorReadings();

  dataService.sendSensorReadings(readings);

  digitalWrite(powerPin, LOW);

  ESP.deepSleep(10e6, WAKE_RF_DEFAULT);
}

void loop(void)
{
}