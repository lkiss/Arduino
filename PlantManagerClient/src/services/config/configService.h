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
  String getConfigurationJson();
  void setConfigurationJson(String config);

  Configuration getConfiguration();
  void setConfiguration(Configuration config);
};