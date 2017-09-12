#include "./emailService.h"

EmailService::EmailService()
{
  this->gsender = Gsender::Instance();
}

void EmailService::SendEmail(char *subject, char *emailTo, char *body)
{
  if (this->gsender->Subject(subject)->Send(emailTo, body))
  {
    Serial.println("Message send.");
  }
  else
  {
    Serial.print("Error sending message: ");
    Serial.println(this->gsender->getError());
  }
}

void EmailService::UpdateSmtpSettings(const char *smtpServer, const char *base64SmtpUserName, const char *base64SmtpPassword, const char *emailFrom)
{
  this->gsender->UpdateSmptSettings(smtpServer, base64SmtpUserName, base64SmtpPassword, emailFrom);
}