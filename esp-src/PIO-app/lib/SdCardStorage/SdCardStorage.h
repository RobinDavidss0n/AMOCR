#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32

#ifndef SDCARDSTORAGE_H
#define SDCARDSTORAGE_H

class SdCardStorage{

private:
    fs::FS& m_fileStream = SD_MMC;
    
    
public:
    SdCardStorage();
    ~SdCardStorage();

    bool writeTxtFile(String path, String text);
    bool writeImageFile(String path, const uint8_t* buffer, size_t length);
    bool writeBitmapFile(String path, const uint8_t* headerData, size_t headerDataLength, const uint8_t* pixelDatat, size_t pixelDatatLength);

};

#endif