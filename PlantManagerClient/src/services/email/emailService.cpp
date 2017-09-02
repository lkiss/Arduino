#include "../../lib/gsender/Gsender.h"
#include "./emailService.h"

void EmailService::sendEmail(char *subject, char *emailTo, char *body)
{
  Gsender *gsender = Gsender::Instance();
  if (gsender->Subject(subject)->Send(emailTo, body))
  {
    Serial.println("Message send.");
  }
  else
  {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }
}