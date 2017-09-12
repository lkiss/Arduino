#include "../../lib/gsender/Gsender.h"

class EmailService
{
private:
  Gsender *gsender;

public:
  EmailService();
  void SendEmail(char *subject, char *emailTo, char *body);
  void UpdateSmtpSettings(const char *smtpServer, const char *base64SmtpUserName, const char *base64SmtpPassword, const char *emailFrom);
};
