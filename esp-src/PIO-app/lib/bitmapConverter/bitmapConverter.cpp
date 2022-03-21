#include "bitmapConverter.h"

BitmapConverter::BitmapConverter(){
    
}

BitmapConverter::~BitmapConverter(){
    
}


unsigned char BitmapConverter::createBitMap(const uint8_t* buf, size_t len, size_t width, size_t height, int bytesPerPixel){

    const int paddingAmount = ((4 - (width * bytesPerPixel) % 4) % 4);

    unsigned char bmpPad[3] = {0,0,0};
    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    
    const int fileSize = fileHeaderSize + informationHeaderSize + width * height * bytesPerPixel + paddingAmount * height;

    
    unsigned char fileHeader[fileHeaderSize];

    //File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    //File size 
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    //Reserved 1 (not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    //Reserved 1 (not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];
    
    //Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;    
    informationHeader[2] = 0;    
    informationHeader[3] = 0;
    //Image width
    informationHeader[4] = width;    
    informationHeader[5] = width >> 8;
    informationHeader[6] = width >> 16;
    informationHeader[7] = width >> 24;
    //Image hieght
    informationHeader[4] = height;    
    informationHeader[5] = height >> 8;
    informationHeader[6] = height >> 16;
    informationHeader[7] = height >> 24;
    //Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    //Bits per pixel
    informationHeader[14] = bytesPerPixel;
    informationHeader[15] = 0;
    //Compression (no compreession)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;
    //Image size (no compreession)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;
    //X pixels per meter
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;
    //X pixels per meter
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;
    //Total colors
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    //Important colors
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;
    



}