#ifndef SOIL_MOISTURE_SENSOR
#define SOIL_MOISTURE_SENSOR

class SoilMoistureSensor
{
private:
  int soilMoistureDryTreshold = 920;
  int soilMoistureWetTreshold = 850;
  int soilMoisturePin = 0;

  bool isValidMoistureTreshold(int moistureTreshold);

public:
  SoilMoistureSensor();
  SoilMoistureSensor(int *soilMoisturePin);
  void updateTresholdValues(int newDryTreshold, int newWetTreshold);
  bool isDry();
  int read();
};
#endif