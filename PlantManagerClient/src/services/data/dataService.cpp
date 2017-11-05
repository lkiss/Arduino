#include "dataService.h"

DataService::DataService(ConfigService configService, JsonService jsonService)
{
    this->configurationService = configService;
    this->jsonService = jsonService;
}

int DataService::sendSensorReadings(SensorReading reading)
{
    Configuration config = this->configurationService.getConfiguration();
    String jsonMessage = this->jsonService.convertSensorReadingsToJson(reading);

    httpClient.begin(config.appServer);
    httpClient.addHeader("Content-Type", "application/json");

    int httpStatusCode = httpClient.POST(jsonMessage);
    httpClient.end();

    return httpStatusCode;
}

void DataService::getConfigurationFromServer()
{
}