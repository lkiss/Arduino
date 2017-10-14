#include "./waterTank.h"
#include "math.h"

WaterTank::WaterTank(WaterTankType tankType, DimensionsInMillimeters dimensions)
{
    this->waterTankType = tankType;
    this->dimensions = dimensions;

    CalculateCapacityInLiters();
}

void WaterTank::CalculateCapacityInLiters()
{
    double volume = 0;

    switch (this->waterTankType)
    {
        case WaterTankType::CYLINDER:
        {
            volume = pow(this->dimensions.radius, 2) * PI * this->dimensions.height;
            break;
        }

        case WaterTankType::CUBE:
        {
            volume = pow(this->dimensions.width, 3);
            break;
        }

        case WaterTankType::PRISM:
        {
            volume = this->dimensions.width * this->dimensions.length * this->dimensions.height;
            break;
        }
    }

    this->CapacityInLiters = volume / pow(10, 6);
}

double WaterTank::GetCapacityInLiters()
{
    return this->CapacityInLiters;
}