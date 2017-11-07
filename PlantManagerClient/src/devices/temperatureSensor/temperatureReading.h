#ifndef TEMPERATURE_READING
#define TEMPERATURE_READING

struct TemperatureReading {
    int humidity;
    int temperatureInCelsius;
    int dht11ErrorCode;
};

#endif