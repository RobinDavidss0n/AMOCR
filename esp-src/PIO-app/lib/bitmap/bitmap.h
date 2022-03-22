#include "FS.h"                // SD Card ESP32
#include <tuple>


#ifndef BITMAP_H
#define BITMAP_H

class Bitmap{

private:

    void createBitmapHeader(size_t width, size_t height, size_t pixelDataLength, int bytesPerPixel, int paddingAmount);
    void insertPadding(const uint8_t* rawPixelData, size_t pixelDataLength, int bytesPerPixel, size_t paddingAmount, size_t width, size_t height);
    
public:
    Bitmap(size_t width, size_t height, size_t pixelDataLength, int bytesPerPixel, const uint8_t* rawPixelData);
    ~Bitmap();

    size_t m_length = 54;
    uint8_t m_bitmapHeader[54];
    uint8_t* m_bitmapHeaderPointer;
    uint8_t m_pixelDataWithPadding[];

};

#endif