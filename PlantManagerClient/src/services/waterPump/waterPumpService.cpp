#include <Arduino.h>

#include "waterPumpService.h"

WaterPumpService::WaterPumpService(int *waterPumpPin, int *waterSensorPin)
{
    pinMode(*waterSensorPin, INPUT);
    pinMode(*waterPumpPin, OUTPUT);
    digitalWrite(*waterPumpPin, HIGH);
    this->waterSensorPin = *waterSensorPin;
    this->waterPumpPin = *waterPumpPin;
}

bool WaterPumpService::canActivateWaterPump()
{
    int isWateringAllowed = digitalRead(this->waterSensorPin);

    if (isWateringAllowed == 1)
    {
        //Log debug
        return true;
    }
    else
    {
        //Log warning
        return false;
    }
}

bool WaterPumpService::activateWaterPump()
{
    if (this->canActivateWaterPump())
    {
        //Log debug
        digitalWrite(this->waterPumpPin, LOW);
        delay(wateringTime);
        digitalWrite(this->waterPumpPin, HIGH);
        return true;
    }
    else
    {
        //Log warning
        return false;
    }
}