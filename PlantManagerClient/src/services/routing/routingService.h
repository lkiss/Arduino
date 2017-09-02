#include <ESP8266WebServer.h>

class RoutingService
{
private:
  ESP8266WebServer webServer;

  void handleSensorRequest();
  void handleWaterPumpRequest();
  void handleInfoRequest();

public:
  RoutingService(ESP8266WebServer webServer);
  void begin(void (*sensorHandler) (void));
};