#include "./emailService.h"

EmailService::EmailService()
{
  this->gsender = Gsender::Instance();
}

bool EmailService::SendEmail(char *subject, char *emailTo, char *body)
{
  if (this->gsender->Subject(subject)->Send(emailTo, body))
  {
    Serial.println("Message sent.");
    return true;
  }
  else
  {
    Serial.print("Error sending message: ");
    Serial.println(this->gsender->getError());
    return false;
  }
}

void EmailService::UpdateSmtpSettings(const char *smtpServer, int port, const char *base64SmtpUserName, const char *base64SmtpPassword, const char *emailFrom)
{
  this->gsender->UpdateSmptSettings(smtpServer, port, base64SmtpUserName, base64SmtpPassword, emailFrom);
}