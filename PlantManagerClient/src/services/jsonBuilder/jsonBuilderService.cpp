#include "./jsonBuilderService.h"

String JsonBuilderService::getSensorReadingsAsJson(int *soilMoistureReading, int *dht11Reading, int soilMoistureReadings[2], int dht11Readings[1][2])
{
    String jsonMessage;
    DynamicJsonBuffer buffer(200);
    JsonArray &jsonArray = buffer.createArray();

    for (int i = 0; i < 2; i++)
    {
        JsonObject &soilMoistureReading = buffer.createObject();
        soilMoistureReading["sensor"] = "SOIL_MOISTURE";
        soilMoistureReading["value"] = soilMoistureReadings[i];
        soilMoistureReading["sensorIndex"] = i;
        soilMoistureReading["unit"] = "%";
        jsonArray.add(soilMoistureReading);
    }

    for (int i = 0; i < 1; i++)
    {
        JsonObject &temperatureReading = buffer.createObject();
        temperatureReading["sensor"] = "TEMPERATURE";
        temperatureReading["value"] = dht11Readings[i][0];
        temperatureReading["sensorIndex"] = i;
        temperatureReading["unit"] = "C";
        jsonArray.add(temperatureReading);
    
        JsonObject &humidityReading = buffer.createObject();
        humidityReading["sensor"] = "HUMIDITY";
        humidityReading["value"] = dht11Readings[i][1];
        humidityReading["sensorIndex"] = i;
        humidityReading["unit"] = "%";
        jsonArray.add(humidityReading);
    }

    JsonObject &soilMoistureReading01 = buffer.createObject();
    soilMoistureReading01["sensor"] = "SOIL_MOISTURE";
    soilMoistureReading01["value"] = soilMoistureReading[0];
    soilMoistureReading01["sensorIndex"] = 1;
    soilMoistureReading01["unit"] = "%";
    jsonArray.add(soilMoistureReading01);

    JsonObject &soildMoistureReading02 = buffer.createObject();
    soildMoistureReading02["sensor"] = "SOIL_MOISTURE";
    soildMoistureReading02["value"] = soilMoistureReading[1];
    soildMoistureReading02["sensorIndex"] = 2;
    soildMoistureReading02["unit"] = "%";
    jsonArray.add(soildMoistureReading02);

    JsonObject &temperatureReading01 = buffer.createObject();
    temperatureReading01["sensor"] = "TEMPERATURE";
    temperatureReading01["value"] = dht11Reading[0];
    temperatureReading01["sensorIndex"] = 1;
    temperatureReading01["unit"] = "C";
    jsonArray.add(temperatureReading01);

    JsonObject &humidityReading01 = buffer.createObject();
    humidityReading01["sensor"] = "HUMIDITY";
    humidityReading01["value"] = dht11Reading[1];
    humidityReading01["sensorIndex"] = 1;
    humidityReading01["unit"] = "%";
    jsonArray.add(humidityReading01);

    jsonArray.printTo(jsonMessage);
    return jsonMessage;
}