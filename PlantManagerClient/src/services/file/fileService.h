#ifndef FILE_SERVICE
#define FILE_SERVICE

#include "FS.h"
#include "../config/config.h"

class FileService{
public: 
    String readConfigurationFromFile();
    void writeConfigurationFile(String config);
};

#endif