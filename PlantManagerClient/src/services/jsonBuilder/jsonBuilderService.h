#include <ArduinoJson.h>
#include <list>

class JsonBuilderService
{
public:
  String getSensorReadingsAsJson(int *soilMoistureReading, int *dht11Reading, int soilMoistureReadings[2], int dht11Readings[1][2]);
};