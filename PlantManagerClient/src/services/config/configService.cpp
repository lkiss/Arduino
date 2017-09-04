#include "configService.h"

ConfigService::ConfigService()
{
  this->config.measuringInterval = 60000 * 30;
  this->config.wateringTime = 2000;
  this->config.smtpPort = 465;
  this->config.smtpServer = "smtp.gmail.com";
  this->config.base64UserId = "a2lzc2xhYzg4QGdtYWlsLmNvbQ==";
  this->config.base64Password = "NTExMzExMV9Db25z";
  this->config.emailTo = "kisslac1988@hotmail.com";
  this->config.emailFrom = "kisslac88@gmail.com";
  this->config.emailSubject = "Water tank empty!";
  this->config.emailBody = "Refill water tank!";
}

String ConfigService::getConfiguration()
{
  // String fileContent;

  // fileContent = fileService.readConfigurationFromFile();

  // if (fileContent == "")
  // {
  //   return jsonService.convertConfigToJson(this->config);
  // }
  // else
  // {
  //   return fileContent;
  // }

  return jsonService.convertConfigToJson(this->config);
}

void ConfigService::setConfiguration(String config)
{
  //fileService.writeConfigurationFile(config);
  this->config = jsonService.convertJsonToConfig(config);
}