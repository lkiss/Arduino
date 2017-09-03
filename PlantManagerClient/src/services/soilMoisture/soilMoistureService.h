class SoilMoistureService
{
private:
  int soilMoistureDryValue = 850;
  int soilMoistureWetValue = 600;
  int soilMoistureMiddleValue = 725;
  int soilMoisturePin = 0;

public:
  SoilMoistureService(int *soilMoisturePin);
  int read();
  bool isWateringNeeded();
};