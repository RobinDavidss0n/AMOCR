#include "SdCardStorage.h"

SdCardStorage::SdCardStorage()
{

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

SdCardStorage::~SdCardStorage()
{
}

bool SdCardStorage::writeTxtFile(String path, String text)
{
    File file = m_fileStream.open(path, FILE_WRITE);

    if (!file)
    {
        Serial.println("writeTxtFile -> Failed to open file in writing mode");
        file.close();
        return false;
    }
    else
    {

        if (!file.print(text))
        {
            Serial.println("writeTxtFile -> Saved file with path: " + path);
            file.close();
            return true;
        }
        else
        {
            Serial.println("writeTxtFile -> Failed to saved file");
            file.close();
            return false;
        }
    }
}

bool SdCardStorage::writeRawPixelDataToBinFile(String path, const uint8_t *rawPixelData, size_t rpdLength)
{

    Serial.println("writeRawPixelDataToBinFile -> rpdLength: "+ String(rpdLength));

    File file = m_fileStream.open(path, FILE_WRITE);

    if (!file)
    {
        Serial.println("writeRawPixelDataToBinFile -> Failed to open file in writing mode");
        file.close();
        return false;
    }
    else
    {

        if (file.write(rawPixelData, rpdLength))
        {
            file.close();
            Serial.println("writeRawPixelDataToBinFile -> Saved pixel data to textfile with path: " + path);
            return true;
        }
        else
        {
            file.close();
            Serial.println("writeRawPixelDataToBinFile -> Failed to print rawPixel data.");
            return false;
        }
    }
}



//**********************************    NOT USED    **********************************

bool SdCardStorage::writeImageFile(String path, const uint8_t *buffer, size_t length)
{

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
        file.close();
        Serial.println("writeImageFile -> Saved image with path: " + path);
        return true;
    }
}

bool SdCardStorage::writeBitmapFile(String path, const uint8_t *headerData, size_t headerDataLength, const uint8_t *pixelDatat, size_t pixelDatatLength)
{
    File file = m_fileStream.open(path.c_str(), FILE_WRITE);
    if (!file)
    {
        Serial.println("writeBitmapFile ->Failed to open file in writing mode");
        file.close();
        return false;
    }
    else
    {
        Serial.println("writeBitmapFile -> headerDataLength: "+ String(headerDataLength));
        Serial.println("writeBitmapFile -> headerDataLength: "+ String(pixelDatatLength));
        file.write(headerData, headerDataLength);
        file.write(pixelDatat, pixelDatatLength);
        file.close();
        Serial.println("writeBitmapFile -> Saved bitmap with path: " + path);
        return true;
    }
}
