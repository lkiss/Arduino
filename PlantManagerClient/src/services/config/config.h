#ifndef CONFIGURATION
#define CONFIGURATION

struct Configuration
{
  int measuringInterval;
  int wateringTime;
  int smtpPort;
  String smtpServer;
  const char * base64UserId;
  const char * base64Password;
  const char * emailTo;
  const char * emailFrom;
  const char * emailSubject;
  const char * emailBody;
};

#endif