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

String JsonService::convertConfigToJson(Configuration configuration)
{
    String jsonMessage;
    DynamicJsonBuffer buffer(200);

    JsonObject &config = buffer.createObject();
    config["measuringInterval"] = configuration.measuringInterval;
    config["wateringTime"] = configuration.wateringTime;
    config["smtpPort"] = configuration.smtpPort;
    config["smtpServer"] = configuration.smtpServer;
    config["emailTo"] = configuration.emailTo;
    config["emailFrom"] = configuration.emailFrom;
    config["emailSubject"] = configuration.emailSubject;
    config["emailBody"] = configuration.emailBody;

    config.printTo(jsonMessage);

    return jsonMessage;
}

Configuration JsonService::convertJsonToConfig(String configJson)
{
    Configuration configuration = Configuration();
    String jsonMessage;
    DynamicJsonBuffer buffer(200);

    JsonObject &config = buffer.parseObject(configJson);

    configuration.measuringInterval = config["measuringInterval"];
    configuration.wateringTime = config["wateringTime"];
    configuration.smtpPort = config["smtpPort"];
    configuration.smtpServer = config["smtpServer"].as<String>();
    configuration.base64UserId = config["base64UserId"];
    configuration.base64Password = config["base64Password"];
    configuration.emailTo = config["emailTo"];
    configuration.emailFrom = config["emailFrom"];
    configuration.emailSubject = config["emailSubject"];
    configuration.emailBody = config["emailBody"];

    return configuration;
}