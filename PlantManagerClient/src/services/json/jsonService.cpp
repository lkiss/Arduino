#include "./jsonService.h"

String JsonService::convertSensorReadingsToJson(int soilMoistureReadings[2], int *dht11Readings)
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

    JsonObject &temperatureReading = buffer.createObject();
    temperatureReading["sensor"] = "TEMPERATURE";
    temperatureReading["value"] = dht11Readings[0];
    temperatureReading["sensorIndex"] = 1;
    temperatureReading["unit"] = "C";
    jsonArray.add(temperatureReading);

    JsonObject &humidityReading = buffer.createObject();
    humidityReading["sensor"] = "HUMIDITY";
    humidityReading["value"] = dht11Readings[1];
    humidityReading["sensorIndex"] = 1;
    humidityReading["unit"] = "%";
    jsonArray.add(humidityReading);

    jsonArray.printTo(jsonMessage);
    return jsonMessage;
}

String JsonService::convertConfigToJson(
    int measuringInterval,
    int wateringTime,
    int smtpPort,
    String smptServer,
    String base64UserId,
    String base64Password,
    String emailTo,
    String emailFrom,
    String emailSubject,
    String emailBody)
{
    String jsonMessage;
    DynamicJsonBuffer buffer(200);

    JsonObject &config = buffer.createObject();
    config["measuringInterval"] = measuringInterval;
    config["wateringTime"] = wateringTime;
    config["smtpPort"] = smtpPort;
    config["smptServer"] = smptServer;
    // config["base64UserId"] = base64UserId;
    // config["base64Password"] = base64Password;
    config["emailTo"] = emailTo;
    config["emailFrom"] = emailFrom;
    config["emailSubject"] = emailSubject;
    config["emailBody"] = emailBody;

    config.printTo(jsonMessage);

    return jsonMessage;
}