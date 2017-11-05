#ifndef DATA_SERVICE
#define DATA_SERVICE

#include "../sensor/sensorReading.h"
#include "../config/configService.h"
#include "../json/JsonService.h"

#include <ESP8266HTTPClient.h>

class DataService
{
private:
  HTTPClient httpClient;
  ConfigService configurationService;
  JsonService jsonService;

public:
  DataService(ConfigService configService, JsonService jsonService);
  int sendSensorReadings(SensorReading reading);
  void getConfigurationFromServer();
};

#endif