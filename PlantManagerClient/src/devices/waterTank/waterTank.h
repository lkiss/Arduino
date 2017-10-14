#include "../../constants.h"

class WaterTank
{
private:
  double CapacityInLiters;
  WaterTankType waterTankType;
  DimensionsInMillimeters dimensions;
  void CalculateCapacityInLiters();

public:
  WaterTank(WaterTankType tankType, DimensionsInMillimeters dimensions);
  double GetCapacityInLiters();
};