#include <ArduinoJson.h>

#include "./jsonBuilderService.h"

String JsonBuilderService::getSensorReadingsAsJson(int *soilMoistureReadings, int* dht11Reading)
{
    DynamicJsonBuffer buffer(200);
    //Log debug
    String jsonMessage;

    JsonArray &jsonArray = buffer.createArray();

    JsonObject &soilMoistureReading01 = buffer.createObject();
    soilMoistureReading01["sensor"] = "SOIL_MOISTURE";
    soilMoistureReading01["value"] = soilMoistureReadings[0];
    soilMoistureReading01["sensorIndex"] = 1;
    soilMoistureReading01["unit"] = "%";
    jsonArray.add(soilMoistureReading01);

    JsonObject &soildMoistureReading02 = buffer.createObject();
    soildMoistureReading02["sensor"] = "SOIL_MOISTURE";
    soildMoistureReading02["value"] = soilMoistureReadings[1];
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