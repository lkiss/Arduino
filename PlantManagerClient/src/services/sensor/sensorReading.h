#ifndef SENSOR_READING
#define SENSOR_READING

struct SensorReading
{
    int temperature;
    int humidity;
    int soilMoisture;
    int waterLevel;
};

#endif