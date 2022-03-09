#include "ErrorHandler.h"


ErrorHandler::ErrorHandler(){

}

ErrorHandler::~ErrorHandler() {

}

bool ErrorHandler::saveErrorToSdCard() {

    // Path where error will be saved in SD Card
    String m_errorPath = "/picture" + errorFileName + ".txt";

    fs::FS &fs = SD_MMC; 
    Serial.printf("Error file name: %s\n", m_errorPath.c_str());

    File file = fs.open(m_errorPath.c_str(), FILE_WRITE);

    if(!file){
        Serial.println("Failed to open file in writing mode");
        file.close();
        return false;
    } 
    else {

        size_t errorLength = error.length();
        const uint8_t* errorStringBuffer = reinterpret_cast<const uint8_t*>(&error[0]);
        
        file.write(errorStringBuffer, errorLength); // payload (image), payload length
        Serial.printf("Saved error to path: %s\n", m_errorPath.c_str());
        file.close();
        return true;
    }

}

bool ErrorHandler::handleError(String _error) {
    error =_error;

    if(saveErrorToSdCard()){
        Serial.printf("Error saved to SD card:)");
    } else {
        Serial.printf("Error not saved to SD card :(");
    }
}