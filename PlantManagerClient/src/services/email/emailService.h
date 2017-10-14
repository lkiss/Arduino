#include "../../lib/gsender/Gsender.h"

class EmailService
{
private:
  Gsender *gsender;

public:
  EmailService();
  bool SendEmail(char *subject, char *emailTo, char *body);
  void UpdateSmtpSettings(const char *smtpServer, int port, const char *base64SmtpUserName, const char *base64SmtpPassword, const char *emailFrom);
};
