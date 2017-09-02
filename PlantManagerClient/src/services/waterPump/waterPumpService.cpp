#include <Arduino.h>

#include "waterPumpService.h"
#include "../email/emailService.h"

EmailService emailService;

WaterPumpService::WaterPumpService(int waterPumpPin, int waterSensorPin)
{
    pinMode(waterSensorPin, INPUT);
    pinMode(waterPumpPin, OUTPUT);
    this->waterSensorPin = waterSensorPin;
    this->waterPumpPin = waterPumpPin;
}

bool WaterPumpService::canActivateWaterPump()
{
    int isWateringAllowed = digitalRead(waterSensorPin);

    if (isWateringAllowed == 1)
    {
        //Log debug
        return true;
    }
    else
    {
        emailService.sendEmail("Water tank empty!", "kisslac1988@hotmail.com", "Please refill water tank!");
        //Log warning
        return false;
    }
}

void WaterPumpService::activateWaterPump()
{
    if (this->canActivateWaterPump())
    {
        //Log debug
        digitalWrite(waterPumpPin, LOW);
        delay(wateringTime);
        digitalWrite(waterPumpPin, HIGH);
    }
    else
    {
        //Log warning
    }
}