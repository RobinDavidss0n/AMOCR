#include "FS.h"                // SD Card ESP32
//#include "SD_MMC.h"            // SD Card ESP32


#ifndef BITMAPCONVERTER_H
#define BITMAPCONVERTER_H

class BitmapConverter{

private:

    
public:
    BitmapConverter();
    ~BitmapConverter();

    unsigned char createBitMap(const uint8_t* buf, size_t len,
     size_t width, size_t height, int bytesPerPixel);

};

#endif