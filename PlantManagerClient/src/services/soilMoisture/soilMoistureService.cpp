#include <Arduino.h>

#include "soilMoistureService.h"

SoilMoistureService::SoilMoistureService(int *soilMoisturePin)
{
  pinMode(*soilMoisturePin, OUTPUT);
  digitalWrite(*soilMoisturePin, LOW);
  this->soilMoisturePin = *soilMoisturePin;
}

bool SoilMoistureService::isValidMoistureTreshold(int moistureTreshold){
  if(moistureTreshold > 1024 || moistureTreshold < 0){
    return false;
  }
  return true;
}

int SoilMoistureService::read()
{
  //Log debug
  int result = 0;
  digitalWrite(this->soilMoisturePin, HIGH);
  delay(50);
  result = analogRead(A0);
  digitalWrite(this->soilMoisturePin, LOW);
  delay(50);
  return result;
}

void SoilMoistureService::updateMoistureTresholds(int newDryTreshold, int newMiddleTreshold, int newWetTreshold){
  if(this->isValidMoistureTreshold(dryTreshold) && this->isValidMoistureTreshold(middleTreshold) && this->isValidMoistureTreshold(wetTreshold)){
    this->soilMoistureDryTreshold = dryTreshold;
    this->soilMoistureWetTreshold = wetTreshold;
    this->soilMoistureMiddleTreshold = middleTreshold;
  }
}

bool SoilMoistureService::isWateringNeeded()
{
  //Log debug
  int soilMoistureTreshold = this->read();
  if (soilMoistureTreshold >= soilMoistureDryTreshold)
  {
    return true;
  }
  else if (soilMoistureTreshold >= soilMoistureMiddleTreshold)
  {
    return true;
  }
  else
  {
    return false;
  }
}
