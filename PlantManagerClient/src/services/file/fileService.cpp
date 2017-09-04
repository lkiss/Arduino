#include "fileService.h"

#define ConfigurationFilePath "/configuration.json"

String FileService::readConfigurationFromFile()
{
    String configurationString;
    if (SPIFFS.begin() == true)
    {
        if (SPIFFS.exists(ConfigurationFilePath) == false)
        {
            return "";
        }

        File configurationFile = SPIFFS.open(ConfigurationFilePath, "r+");
        if (!configurationFile)
        {
            //Log file open failed
        }

        while (configurationFile.available())
        {
            configurationString += char(configurationFile.read());
        }

        configurationFile.close();
    }
    else
    {
    }

    SPIFFS.end();

    return configurationString;
}

void FileService::writeConfigurationFile(String config)
{
    if (SPIFFS.begin() == true)
    {
        if (SPIFFS.format() == false)
        {
            return;
        }
        if (SPIFFS.exists(ConfigurationFilePath) == false)
        {
            return;
        }

        File configurationFile = SPIFFS.open(ConfigurationFilePath, "w+");
        if (!configurationFile)
        {
            //Log file open failed
        }

        configurationFile.print(config);

        configurationFile.close();
        SPIFFS.end();
    }
    else
    {
    }
}