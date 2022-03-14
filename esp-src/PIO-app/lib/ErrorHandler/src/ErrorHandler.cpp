#include "ErrorHandler.h"


ErrorHandler::ErrorHandler(){

}

ErrorHandler::~ErrorHandler() {

}

bool ErrorHandler::saveErrorToSdCard() {

    Serial.printf("ErrorHandler -> Got error: %s\n", m_errorDescription);

    fs::FS &fs = SD_MMC;

    // Path where error will be saved in SD Card
    String errorPath = "/" + m_errorFileName + ".txt";

    File file = fs.open(errorPath, FILE_WRITE);

    if(!file){
        Serial.println("Failed to open file in writing mode");
        file.close();
        return false;
    } 
    else {

        if (m_error == NULL)
        {
            m_error= " ";
        }
        
        if(!file.print("Error description: "+m_errorDescription+"\nError: "+m_error)){
            Serial.printf("Saved error to path: %s\n", errorPath);
            file.close();
            return true;
        } else {
            file.close();
            return false;
        }
    }
}

bool ErrorHandler::handleError(String errorDesc, esp_err_t error, String errorFileName) {
    m_errorDescription = errorDesc;
    m_error = esp_err_to_name(error);
    m_errorFileName = errorFileName;

    if(saveErrorToSdCard()){
        Serial.printf("Error saved to SD card :)\n");
    } else {
        Serial.printf("Error not saved to SD card :(\n");
    }
}