#include "dataService.h"

int DataService::sendSensorReadings(SensorReading reading)
{
    String jsonMessage = this->jsonService.convertSensorReadingsToJson(reading);

    httpClient.begin(this->configuration.appServer);
    httpClient.addHeader("Content-Type", "application/json");

    int httpStatusCode = httpClient.POST(jsonMessage);
    httpClient.end();

    return httpStatusCode;
}

void DataService::getConfigurationFromServer(){

}