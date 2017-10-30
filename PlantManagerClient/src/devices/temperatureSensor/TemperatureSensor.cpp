#include <SimpleDHT.h>
#include "TemperatureSensor.h"

SimpleDHT11 dht11;

TemperatureSensor::TemperatureSensor(){}

TemperatureSensor::TemperatureSensor(int *DHT11Pin)
{
  this->DHT11Pin = *DHT11Pin;
}

int *TemperatureSensor::read(int *result)
{
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(this->DHT11Pin, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    result[0] = err;
    result[1] = err;
    return result;
  }

  result[0] = (int)temperature;
  result[1] = (int)humidity;
  return result;
}