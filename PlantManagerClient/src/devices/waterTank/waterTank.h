#include "../../constants.h"
#ifndef WATER_TANK
#define WATER_TANK
class WaterTank
{
private:
  double CapacityInLiters;
  WaterTankType waterTankType;
  DimensionsInMillimeters dimensions;
  void CalculateCapacityInLiters();

public:
  WaterTank();
  WaterTank(WaterTankType tankType, DimensionsInMillimeters dimensions);
  double GetCapacityInLiters();
};
#endif