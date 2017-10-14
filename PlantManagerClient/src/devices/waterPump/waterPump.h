#include <Arduino.h>

class WaterPump
{
  private:
    long wateringTime = 2000;
    int waterSensorPin = 0;
    int waterPumpPin = 0;

  public:
    WaterPump(int *waterPumpPin, int *waterSensorPin);
    bool canActivateWaterPump();
    bool activateWaterPump();
    void updateWateringTime(int newWateringTime);
};