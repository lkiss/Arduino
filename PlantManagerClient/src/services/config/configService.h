#include <Arduino.h>
#include "config.h"
#include "../file/fileService.h"
#include "../json/jsonService.h"

class ConfigService
{
private:
  FileService fileService;
  JsonService jsonService;
  Configuration config;

public:
  ConfigService();
  String getConfiguration();
  void setConfiguration(String config);
};