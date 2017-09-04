#ifndef JSON_SERVICE
#define JSON_SERVICE

#include <ArduinoJson.h>
#include "../config/config.h"

class JsonService
{
public:
  String convertSensorReadingsToJson(int soilMoistureReadings[2], int *dht11Readings);
  String convertConfigToJson(Configuration config);
  Configuration convertJsonToConfig(String configJson);
};

#endif