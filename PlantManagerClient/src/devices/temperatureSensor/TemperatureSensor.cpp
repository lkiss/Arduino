#include <SimpleDHT.h>
#include "TemperatureSensor.h"

SimpleDHT11 dht11;

TemperatureSensor::TemperatureSensor() {}

TemperatureSensor::TemperatureSensor(int *DHT11Pin)
{
  this->DHT11Pin = *DHT11Pin;
}

TemperatureReading TemperatureSensor::read()
{
  byte temperature = 0;
  byte humidity = 0;
  TemperatureReading reading;
  
  reading.dht11ErrorCode = dht11.read(this->DHT11Pin, &temperature, &humidity, NULL);
  reading.temperatureInCelsius = (int)temperature;
  reading.humidity = (int)humidity;

  return reading;
}