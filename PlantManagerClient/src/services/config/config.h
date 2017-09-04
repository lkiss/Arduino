#ifndef CONFIGURATION
#define CONFIGURATION

struct Configuration
{
  int measuringInterval;
  int wateringTime;
  int smtpPort;
  String smtpServer;
  String base64UserId;
  String base64Password;
  String emailTo;
  String emailFrom;
  String emailSubject;
  String emailBody;
};

#endif