#ifndef TEMPERATURE_SENSOR
#define TEMPERATURE_SENSOR

#include "./temperatureReading.h"

class TemperatureSensor
{
private:
  int DHT11Pin;

public:
  TemperatureSensor();
  TemperatureSensor(int *DHT11Pin);
  TemperatureReading read();
};
#endif