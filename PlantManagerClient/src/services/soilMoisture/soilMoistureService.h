class SoilMoistureService
{
private:
  int soilMoistureDryTreshold = 920;
  int soilMoistureWetTreshold = 850;
  int soilMoistureMiddleTreshold = 885;
  int soilMoisturePin = 0;

  bool isValidMoistureTreshold(int moistureTreshold);

public:
  SoilMoistureService(int *soilMoisturePin);
  void updateMoistureTreshold(int newDryTreshold, int newMiddleTreshold, int newWetTreshold);
  int read();
  bool isWateringNeeded();
};