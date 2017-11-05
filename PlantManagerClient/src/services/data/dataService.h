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
  Configuration configuration;
  JsonService jsonService;

public:
  int sendSensorReadings(SensorReading reading);
  void getConfigurationFromServer();
};

#endif