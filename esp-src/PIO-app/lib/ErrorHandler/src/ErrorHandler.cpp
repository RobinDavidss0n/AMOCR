#include "ErrorHandler.h"


ErrorHandler::ErrorHandler()
{
}

ErrorHandler::~ErrorHandler()
{
}

bool ErrorHandler::saveErrorToSdCard()
{

    Serial.println("ErrorHandler -> Got error: " + m_errorDescription);

    // Path where error will be saved in SD Card
    String errorPath = "/" + m_errorFileName + ".txt";

    if (m_error == NULL)
    {
        m_error = " ";
    }

    SdCardStorage sdStorage;

    return sdStorage.writeTxtFile(errorPath, "Error description: " + m_errorDescription + "\nError: " + m_error);
}

bool ErrorHandler::handleError(String errorDesc, esp_err_t error, String errorFileName)
{
    m_errorDescription = errorDesc;
    m_error = esp_err_to_name(error);
    m_errorFileName = errorFileName;

    if (saveErrorToSdCard())
    {
        Serial.printf("Error saved to SD card :)\n");
    }
    else
    {
        Serial.printf("Error not saved to SD card :(\n");
    }
}