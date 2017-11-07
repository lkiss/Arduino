#include "./sensorService.h"

SensorService::SensorService(){}

SensorReading SensorService::getSensorReadings(){
    SensorReading reading;
    TemperatureReading temperatureReading;
    
    temperatureReading = this->temperatureSensor.read();
    
    reading.soilMoisture = this->soilMoistureSensor.read();
    reading.waterLevel = this->waterLevelSensor.getWaterLevelInMillimeters();
    reading.waterLevelUnit = "ml";
    reading.humidity = temperatureReading.humidity;
    reading.temperature = temperatureReading.temperatureInCelsius;
    reading.dht11ErrorCode = temperatureReading.dht11ErrorCode;

    return reading;
}

SensorService::SensorService(const WaterLevelSensor& waterLevelSensor, const WaterPump& waterPump, const SoilMoistureSensor& soilMoistureSensor, const TemperatureSensor& temperatureSensor)
{
    this->waterLevelSensor = waterLevelSensor;
    this->waterPump = waterPump;
    this->soilMoistureSensor = soilMoistureSensor;
    this->temperatureSensor = temperatureSensor;
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