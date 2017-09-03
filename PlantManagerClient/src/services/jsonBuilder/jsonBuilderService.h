#include <ArduinoJson.h>
#include <list>

class JsonBuilderService
{
public:
  String convertSensorReadingsToJson(int soilMoistureReadings[2], int *dht11Readings);
};