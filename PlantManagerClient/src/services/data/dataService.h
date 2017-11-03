#ifndef DATA_SERVICE
#define DATA_SERVICE

#include "../sensor/sensorReading.h"

class DataService
{
public:
  int sendSensorReadings(SensorReading reading);
  void getConfigurationFromServer();
};

#endif