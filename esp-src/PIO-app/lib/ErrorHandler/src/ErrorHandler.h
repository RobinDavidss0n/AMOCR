#include <EEPROM.h>            // read and write from flash memory
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include <iostream>            // For making text file
#include <fstream>             // For making text file

class ErrorHandler{

private:
    String error;
    String errorFileName;

    bool saveErrorToSdCard();

public:

    ErrorHandler(/* args */);
    ~ErrorHandler();

    
    bool handleError(String error);

};



