#include "dataService.h"

DataService::DataService(ConfigService configService)
{
    this->configurationService = configService;
}

int DataService::sendSensorReadings(String sensorReadingsJson)
{
    Configuration config = this->configurationService.getConfiguration();

    httpClient.begin(config.appServer);
    httpClient.addHeader("Content-Type", "application/json");

    int httpStatusCode = httpClient.POST(sensorReadingsJson);
    httpClient.end();

    return httpStatusCode;
}

void DataService::getConfigurationFromServer()
{
}