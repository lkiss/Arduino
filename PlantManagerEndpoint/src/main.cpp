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
int sleepAmount = 1;

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
  if (sleepCount != sleepAmount)
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

  Serial.println("Sensor readings");
  Serial.println("Temperature in celsius");
  Serial.println(reading.temperature);
  Serial.println("Humidity in %");
  Serial.println(reading.humidity);
  Serial.println("Soil moisture value");
  Serial.println(reading.soilMoisture);
  Serial.println("WaterLevel in %");
  Serial.println(reading.waterLevel);
  Serial.println("DHT11 error code");
  Serial.println(reading.dht11ErrorCode);

  sensorService.water(reading);

  digitalWrite(powerPin, LOW);
  Serial.end();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
