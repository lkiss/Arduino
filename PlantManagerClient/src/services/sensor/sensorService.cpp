#include "./sensorService.h"

SensorService::SensorService(){}

SensorService::SensorService(const WaterLevelSensor& waterLevelSensor, const WaterPump& waterPump, const SoilMoistureSensor& soilMoistureSensor)
{
    this->waterLevelSensor = waterLevelSensor;
    this->waterPump = waterPump;
    this->soilMoistureSensor = soilMoistureSensor;
}

bool SensorService::water()
{
    if (this->waterLevelSensor.isWaterLevelSufficient())
    {
        if (this->soilMoistureSensor.isDry())
        {
            this->waterPump.activateWaterPump();
        }
    }
    else
    {
        return false;
    }

    this->waterPump.activateWaterPump();
}