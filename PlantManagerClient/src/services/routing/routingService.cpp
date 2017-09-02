#include "routingService.h"

RoutingService::RoutingService(ESP8266WebServer webServer)
{
    this->webServer = webServer;
}

void RoutingService::handleSensorRequest()
{
    // httpServer.send(200, "application/json", getSensorReadingsAsJson());
}
void RoutingService::handleWaterPumpRequest()
{
    // waterPumpService01.activateWaterPump();
    // waterPumpService02.activateWaterPump();
    // httpServer.send(200);
}
void RoutingService::handleInfoRequest() {}

void RoutingService::begin(void (*sensorHandler) (void))
{
    this->webServer.on("/sensor", [sensorHandler]() { sensorHandler(); });
    this->webServer.on("/waterPump", [this]() { handleWaterPumpRequest(); });
    this->webServer.on("/info", [this]() { handleInfoRequest(); });

    webServer.begin();
}
