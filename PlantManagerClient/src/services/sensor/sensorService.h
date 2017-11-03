#include "../../devices/devices.h"
#include "../../constants.h"

class SensorService
{
  private:
    WaterLevelSensor waterLevelSensor;
    WaterPump waterPump;
    SoilMoistureSensor soilMoistureSensor;

  public:
    SensorService();
    SensorService(const WaterLevelSensor& waterLevelSensor, const WaterPump& waterPump, const SoilMoistureSensor& soilMoistureSensor);
    bool water();
    
};