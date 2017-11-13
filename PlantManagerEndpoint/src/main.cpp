#include "LowPower.h"
#include "./devices/devices.h"
#include "./services/services.h"
#include "./constants.h"

int DHT11Pin = 5;
int waterPumpPin = 6;
int waterSensorEchoPin = 7;
int waterSensorTriggerPin = 8;
int powerPin = 4;
int soilMoisturePin = 14;
int sleepCount = 0;
int sleepAmount = 225;

Dht11Sensor dht11Sensor(&DHT11Pin);
SoilMoistureSensor soilMoistureSensor(soilMoisturePin);
WaterPump waterPump(&waterPumpPin);
WaterLevelSensor waterLevelSensor(waterSensorTriggerPin, waterSensorEchoPin);
WaterTank waterTank(PRISM, 16, 6.5, 12);

JsonService jsonService;
ConfigService configService;
DataService dataService(configService, jsonService);
SensorService sensorService(waterTank, waterLevelSensor, waterPump, soilMoistureSensor, dht11Sensor);

void setup()
{
}

void loop()
{
  if (sleepCount != 0 && sleepCount != sleepAmount)
  {
    sleepCount++;
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    return;
  }

  sleepCount = 0;

  Serial.begin(9600);
  pinMode(powerPin, OUTPUT);

  digitalWrite(powerPin, HIGH);
  SensorReading reading = sensorService.getSensorReadings();
  sensorService.water(reading);

  digitalWrite(powerPin, LOW);
  Serial.end();

  sleepCount++;
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
