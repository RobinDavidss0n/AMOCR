#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "SdCardStorage.h"

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

class ErrorHandler{

private:
    String m_errorDescription;
    String m_error;
    String m_errorFileName;

    bool saveErrorToSdCard();

public:

    ErrorHandler();
    ~ErrorHandler();

    
    bool handleError(String errorDesc, esp_err_t error, String errorFileName);

};

#endif