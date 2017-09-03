#include <ArduinoJson.h>

class JsonService
{
public:
  String convertSensorReadingsToJson(int soilMoistureReadings[2], int *dht11Readings);
  String convertConfigToJson(int measuringInterval,
                             int wateringTime,
                             int smtpPort,
                             String smptServer,
                             String base64UserId,
                             String base64Password,
                             String emailTo,
                             String emailFrom,
                             String emailSubject,
                             String emailBody);
};