#include <Arduino.h>

class WaterPumpService
{
  private:
    long wateringTime = 2000;
    int waterSensorPin = 0;
    int waterPumpPin = 0;

  public:
    WaterPumpService(int waterPumpPin, int waterSensorPin);
    bool canActivateWaterPump();
    void activateWaterPump();
};