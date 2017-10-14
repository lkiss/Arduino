class TemperatureSensor
{
private:
  int DHT11Pin;

public:
  TemperatureSensor(int *DHT11Pin);
  int *read(int *result);
};