#include "../../lib/gsender/Gsender.h"
#include "./emailService.h"

void EmailService::sendEmail(String subject, String emailTo, String body)
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