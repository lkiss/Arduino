#include "configService.h"

  // this->config["measuringInterval"] = "60000";
  // this->config["wateringTime"] = "2000";
  // this->config["smptServer"] = "smtp.gmail.com";
  // this->config["base64UserId"] = "a2lzc2xhYzg4QGdtYWlsLmNvbQ==";
  // this->config["base64Password"] = "NTExMzExMV9Db25z";
  // this->config["smptPort"] = "465";
  // this->config["emailTo"] = "kisslac1988@hotmail.com";
  // this->config["emailFrom"] = "kisslac88@gmail.com";
  // this->config["emailSubject"] = "Water tank empty!";
  // this->config["emailBody"] = "Refill water tank!";

  ConfigService::ConfigService(){
    this->config.measuringInterval = 60000 * 30;
    this->config.wateringTime = 2000;
    this->config.smptPort = 465;
    this->config.smtpServer = "smtp.gmail.com";
    this->config.base64UserId = "a2lzc2xhYzg4QGdtYWlsLmNvbQ==";
    this->config.base64Password = "NTExMzExMV9Db25z";
    this->config.emailTo = "kisslac1988@hotmail.com";
    this->config.emailFrom = "kisslac88@gmail.com";
    this->config.emailSubject = "Water tank empty!";
    this->config.emailBody = "Refill water tank!";
  }

  Configuration ConfigService::getConfiguration(){
    return this->config;
  }

  void ConfigService::setConfiguration(Configuration config){
    this->config = config;
  }