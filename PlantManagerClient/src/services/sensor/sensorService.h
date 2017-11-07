#ifndef SENSOR_SERVICE
#define SENSOR_SERVICE

#include "../../devices/devices.h"
#include "./sensorReading.h"
#include "../../constants.h"

class SensorService
{
  private:
    WaterLevelSensor waterLevelSensor;
    WaterPump waterPump;
    SoilMoistureSensor soilMoistureSensor;
    TemperatureSensor temperatureSensor;

  public:
    SensorService();
    SensorService(const WaterLevelSensor& waterLevelSensor, const WaterPump& waterPump, const SoilMoistureSensor& soilMoistureSensor, const TemperatureSensor& temperatureSensor);
    SensorReading getSensorReadings();
    bool water();
    
};

#endif