

class WaterLevelSensor
{
  public:
    WaterLevelSensor(int triggerPin, int echoPin);
    int getWaterLevelInMillimeters();
};