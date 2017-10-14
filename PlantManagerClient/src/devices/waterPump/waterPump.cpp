#include <Arduino.h>

#include "WaterPump.h"

WaterPump::WaterPump(int *waterPumpPin, int *waterSensorPin)
{
    pinMode(*waterSensorPin, INPUT);
    pinMode(*waterPumpPin, OUTPUT);
    digitalWrite(*waterPumpPin, LOW);
    this->waterSensorPin = *waterSensorPin;
    this->waterPumpPin = *waterPumpPin;
}

bool WaterPump::canActivateWaterPump()
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

bool WaterPump::activateWaterPump()
{
    if (this->canActivateWaterPump())
    {
        //Log debug
        digitalWrite(this->waterPumpPin, HIGH);
        delay(wateringTime);
        digitalWrite(this->waterPumpPin, LOW);
        return true;
    }
    else
    {
        //Log warning
        return false;
    }
}

void WaterPump::updateWateringTime(int newWateringTime){
    this->wateringTime = newWateringTime;
}