#include "./waterLevelSensor.h"

WaterLevelSensor::WaterLevelSensor(int triggerPin, int echoPin)
{
    pinMode(triggerPin, INPUT_PULLUP);
    pinMode(echoPin, OUTPUT);
}

int WaterLevelSensor::getWaterLevel()
{
    return 100;
}