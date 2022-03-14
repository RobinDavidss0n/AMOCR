#include "SdCardStorage.h"



SdCardStorage::SdCardStorage(){

    if (!SD_MMC.begin())
    {
        Serial.println("SdCardStorage -> SD Card Mount Failed");
    }
    else
    {
        uint8_t cardType = SD_MMC.cardType();
        if (cardType == CARD_NONE)
        {
            Serial.println("SdCardStorage -> No SD Card attached");
        }
    }
}

SdCardStorage::~SdCardStorage(){

}


bool SdCardStorage::writeTxtFile(String path, String text){
    File file = m_fileStream.open(path, FILE_WRITE);

    if(!file){
        Serial.println("writeTxtFile -> Failed to open file in writing mode");
        file.close();
        return false;
    } 
    else {
        
        if(!file.print(text)){
            Serial.println("writeTxtFile -> Saved file with path: " + path);
            file.close();
            return true;
        } else {
            file.close();
            return false;
        }
    }
}

bool SdCardStorage::writeImageFile(String path, const uint8_t* buffer, size_t length){

    File file = m_fileStream.open(path.c_str(), FILE_WRITE);
    if (!file)
    {
        Serial.println("writeImageFile ->Failed to open file in writing mode");
        file.close();
        return false;
    }
    else
    {
        file.write(buffer, length); // payload (image), payload length
        Serial.println("writeImageFile -> Saved image with path: " + path);
        file.close();
        return true;
    }
}
