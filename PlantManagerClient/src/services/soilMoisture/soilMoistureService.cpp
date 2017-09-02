#include <Arduino.h>

#include "soilMoistureService.h"

SoilMoistureService::SoilMoistureService(int soilMoisturePin){
  pinMode(soilMoisturePin, OUTPUT);
  digitalWrite(soilMoisturePin, LOW);
  this->soilMoisturePin = soilMoisturePin;
}

int SoilMoistureService::read()
{
  //Log debug
  int result = 0;
  digitalWrite(soilMoisturePin, HIGH);
  delay(50);
  result = analogRead(A0);
  digitalWrite(soilMoisturePin, LOW);
  delay(50);
  return result;
}

bool SoilMoistureService::isWateringNeeded()
{
  //Log debug
  int soilMoistureValue = this->read();
  if (soilMoistureValue >= soilMoistureDryValue)
  {
    return true;
  }
  else if (soilMoistureValue >= soilMoistureMiddleValue)
  {
    return true;
  }
  else
  {
    return false;
  }
}
