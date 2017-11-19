#ifndef DATA_SERVICE
#define DATA_SERVICE

#include "../config/configService.h"

#include <ESP8266HTTPClient.h>

class DataService
{
private:
  HTTPClient httpClient;
  ConfigService configurationService;

public:
  DataService(ConfigService configService);
  int sendSensorReadings(String sensorReadingsJson);
  void getConfigurationFromServer();
};

#endif