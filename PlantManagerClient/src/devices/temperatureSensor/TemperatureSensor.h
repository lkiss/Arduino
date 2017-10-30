#ifndef TEMPERATURE_SENSOR
#define TEMPERATURE_SENSOR

class TemperatureSensor
{
private:
  int DHT11Pin;

public:
  TemperatureSensor();
  TemperatureSensor(int *DHT11Pin);
  int *read(int *result);
};
#endif