#include <Arduino.h>

#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(){}

SoilMoistureSensor::SoilMoistureSensor(int *soilMoisturePin)
{
  pinMode(*soilMoisturePin, OUTPUT);
  digitalWrite(*soilMoisturePin, LOW);
  this->soilMoisturePin = *soilMoisturePin;
}

bool SoilMoistureSensor::isDry()
{
  int sensorReading = this->read();

  if (sensorReading >= this->soilMoistureDryTreshold)
  {
    return true;
  }
  return false;
}

bool SoilMoistureSensor::isValidMoistureTreshold(int moistureTreshold)
{
  if (moistureTreshold > 1024 || moistureTreshold < 0)
  {
    return false;
  }
  return true;
}

int SoilMoistureSensor::read()
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

void SoilMoistureSensor::updateTresholdValues(int newDryTreshold, int newWetTreshold)
{
  if (this->isValidMoistureTreshold(newDryTreshold) && this->isValidMoistureTreshold(newWetTreshold))
  {
    this->soilMoistureDryTreshold = newDryTreshold;
    this->soilMoistureWetTreshold = newWetTreshold;
  }
}