#include "./waterTank.h"
#include "math.h"

WaterTank::WaterTank() {}

WaterTank::WaterTank(WaterTankType tankType, DimensionsInCentimeters dimensions)
{
    this->waterTankType = tankType;
    this->dimensions = dimensions;

    CalculateCapacityCC();
}

WaterTank::WaterTank(WaterTankType tankType, double lengthCM, double widthCM, double heightCM, double radiusCM)
{
    DimensionsInCentimeters dimensions;
    dimensions.length = lengthCM;
    dimensions.width = widthCM;
    dimensions.height = heightCM;
    dimensions.radius = radiusCM;

    this->waterTankType = tankType;
    this->dimensions = dimensions;

    CalculateCapacityCC();
}

double WaterTank::CalculateVolume(double height)
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

    return volume;
}

void WaterTank::CalculateCapacityCC()
{
    double volume = this->CalculateVolume(this->dimensions.height);

    this->waterTankVolumeCC = volume;
}

double WaterTank::GetRemainingInPercentage(double height)
{
    double waterHeight = this->dimensions.height - height;
    double waterVolume = this->CalculateVolume(waterHeight);

    return (this->waterTankVolumeCC / waterVolume) * 100;
}

bool WaterTank::isWaterLevelSufficient(double height){
    return this->minimumWaterThresholdPercentage <= this->GetRemainingInPercentage(height) ? false : true;
}