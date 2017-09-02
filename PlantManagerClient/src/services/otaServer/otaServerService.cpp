#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#include "./otaServerService.h"

void OtaServerService::begin(char* host, ESP8266WebServer* httpServer, ESP8266HTTPUpdateServer* httpUpdater)
{
    MDNS.begin(host);

    httpUpdater->setup(httpServer);

    MDNS.addService("http", "tcp", 80);
}