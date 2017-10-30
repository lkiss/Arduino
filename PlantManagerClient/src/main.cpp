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
SensorService sensorService(waterLevelSensor, waterPump, soilMoistureSensor);

void setup(void)
{
  Configuration config = configService.getConfiguration();
  
  wifiService.begin();

  ESP.deepSleep(config.measuringInterval);
}

void loop(void)
{
}