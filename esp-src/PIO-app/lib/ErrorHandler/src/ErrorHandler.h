#include <EEPROM.h>            // read and write from flash memory
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include <iostream>            // For making text file
#include <fstream>             // For making text file

class ErrorHandler{

private:
    String m_errorDescription;
    esp_err_t m_error;
    String m_errorFileName;

    bool saveErrorToSdCard();

public:

    ErrorHandler(/* args */);
    ~ErrorHandler();

    
    bool handleError(String errorDesc, esp_err_t error);

};



