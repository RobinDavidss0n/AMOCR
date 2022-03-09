#include "ErrorHandler.h"


ErrorHandler::ErrorHandler(){

}

ErrorHandler::~ErrorHandler() {

}

bool ErrorHandler::saveErrorToSdCard() {

    // Path where error will be saved in SD Card
    char* m_errorPath = ("/errors/%s.txt", m_errorFileName);

    fs::FS &fs = SD_MMC;

    File file = fs.open(m_errorPath, FILE_WRITE);

    if(!file){
        Serial.println("Failed to open file in writing mode");
        file.close();
        return false;
    } 
    else {

        if(!file.print("Error description: "+m_errorDescription+"\nError: "+m_error)){
            Serial.printf("Saved error to path: %s\n", m_errorPath);
            file.close();
            return true;
        } else {
            file.close();
            return false;
        }
    }
}

bool ErrorHandler::handleError(String errorDesc, esp_err_t error, char* errorFileName) {
    m_errorDescription = errorDesc;
    m_error = esp_err_to_name(error);
    m_errorFileName = errorFileName;

    if(saveErrorToSdCard()){
        Serial.printf("Error saved to SD card:)");
    } else {
        Serial.printf("Error not saved to SD card :(");
    }
}