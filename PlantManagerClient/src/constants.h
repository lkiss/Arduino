#define PI 3.14159265358979323846

enum WaterTankType
{
    CYLINDER = 0,
    PRISM = 1,
    CUBE = 2
};

struct DimensionsInMillimeters
{
    double length;
    double width;
    double height;
    double radius;
};