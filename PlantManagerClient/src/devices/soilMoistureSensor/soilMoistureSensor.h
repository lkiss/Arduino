class SoilMoistureSensor
{
private:
  int soilMoistureDryTreshold = 920;
  int soilMoistureWetTreshold = 850;
  int soilMoisturePin = 0;

  bool isValidMoistureTreshold(int moistureTreshold);

public:
  SoilMoistureSensor(int *soilMoisturePin);
  void updateTresholdValues(int newDryTreshold, int newWetTreshold);
  int read();
  bool isDry();
};