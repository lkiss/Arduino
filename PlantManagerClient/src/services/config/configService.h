#include <Arduino.h>

struct Configuration
{
  int measuringInterval;
  int wateringTime;
  int smptPort;
  String smtpServer;
  String base64UserId;
  String base64Password;
  String emailTo;
  String emailFrom;
  String emailSubject;
  String emailBody;
};

class ConfigService
{
private:
  Configuration config;

public:
  ConfigService();
  Configuration getConfiguration();
  void setConfiguration(Configuration config);
};