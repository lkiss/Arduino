#include <ArduinoJson.h>

class JsonService
{
public:
  String convertSensorReadingsToJson(int soilMoistureReadings[2], int *dht11Readings);
};