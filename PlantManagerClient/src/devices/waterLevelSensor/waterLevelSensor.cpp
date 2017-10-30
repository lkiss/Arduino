#include "./waterLevelSensor.h"
#include <Arduino.h>

WaterLevelSensor::WaterLevelSensor(){}

WaterLevelSensor::WaterLevelSensor(int *triggerPin, int *echoPin)
{
    pinMode(*triggerPin, INPUT_PULLUP);
    pinMode(*echoPin, OUTPUT);

    this->triggerPin = *triggerPin;
    this->echoPin = *echoPin;
}

int WaterLevelSensor::getWaterLevelInMillimeters()
{
    return 100;
}

bool WaterLevelSensor::isWaterLevelSufficient()
{
    return true;
}