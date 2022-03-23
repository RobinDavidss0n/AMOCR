#include "bitmap.h"

Bitmap::Bitmap(size_t width, size_t height, size_t pixelDataLength, int bytesPerPixel, const uint8_t *rawPixelData)
{

    const int paddingAmount = ((4 - (width * bytesPerPixel) % 4) % 4);
    // unsigned char bmpPad[3] = {0,0,0};

    createBitmapHeader(width, height, pixelDataLength, bytesPerPixel, paddingAmount);

    // if (paddingAmount > 0)
    // {
    //     Serial.println("Bitmap-> Padding needed, ammount: " + paddingAmount);
    //     insertPadding(rawPixelData, pixelDataLength, bytesPerPixel, paddingAmount, width, height);
    // }else
    // {
    //     Serial.println("Bitmap-> Padding NOT needed.");
    // }
    
}

void Bitmap::insertPadding(const uint8_t *rawPixelData, size_t pixelDataLength, int bytesPerPixel, size_t paddingAmount, size_t width, size_t height)
{

    // for (size_t index = 0; index < pixelDataLength; index++)
    // {
    //     if ((index+1) % width != 0)
    //     {
    //         m_pixelDataWithPadding[index] = rawPixelData[index];
    //     }
    //     else
    //     {
    //         Serial.println("Bitmap->insertPadding-> On end of width with index:"+index);

    //         m_pixelDataWithPadding[index] = rawPixelData[index];

    //         for (size_t i = 0; i < paddingAmount; i++)
    //         {
    //             Serial.println("Bitmap->insertPadding-> Adding padding on index:"+(index + 1 + i));
    //             m_pixelDataWithPadding[index + 1 + i] = 0;
    //         }
    //         index += paddingAmount;
    //     }
    // }
}

void Bitmap::createBitmapHeader(size_t width, size_t height, size_t pixelDataLength, int bytesPerPixel, int paddingAmount)
{

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    const int fileSize = fileHeaderSize + informationHeaderSize + width * height * bytesPerPixel + pixelDataLength + paddingAmount * height;

    //m_pixelDataWithPadding[fileSize];

    uint8_t fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 66; // B
    fileHeader[1] = 77; // M
    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Reserved 1 (not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // Reserved 1 (not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    uint8_t informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    // Image width
    informationHeader[4] = width;
    informationHeader[5] = width >> 8;
    informationHeader[6] = width >> 16;
    informationHeader[7] = width >> 24;
    // Image hieght
    informationHeader[4] = height;
    informationHeader[5] = height >> 8;
    informationHeader[6] = height >> 16;
    informationHeader[7] = height >> 24;
    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    // Bits per pixel
    informationHeader[14] = bytesPerPixel;
    informationHeader[15] = 0;
    // Compression (no compreession)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;
    // Image size (no compreession)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;
    // X pixels per meter
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;
    // X pixels per meter
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;
    // Total colors
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    // Important colors
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    // const int fileHeaderSize = 14;
    // const int informationHeaderSize = 40;

    // const int fileSize = fileHeaderSize + informationHeaderSize + width * height * bytesPerPixel/* + paddingAmount * height*/;

    // unsigned char fileHeader[fileHeaderSize];

    // const uint8_t* buf, size_t len, size_t width, size_t height, int bytesPerPixel

    // for (int i = 0; i < fileHeaderSize; i++)
    // {
    //     Serial.println("HeaderData[" + String(i) + "]: " + fileHeader[i]);
    //     sleep(0.1);
    // }

    // for (int i = 0; i < informationHeaderSize; i++)
    // {
    //     Serial.println("HeaderData[" + String(i) + "]: " + informationHeader[i]);
    //     sleep(0.1);
    // }

    m_bitmapHeader[fileHeaderSize + informationHeaderSize];

    int index = 0;

    for (size_t i = 0; i < fileHeaderSize; i++)
    {
        m_bitmapHeader[index] = fileHeader[i];
        index += 1;
    }

    for (size_t i = 0; i < informationHeaderSize; i++)
    {
        m_bitmapHeader[index] = informationHeader[i];
        index += 1;
    }

    m_bitmapHeaderPointer = &m_bitmapHeader[0];

    size_t length = fileHeaderSize + informationHeaderSize;

    // for (int i = 0; i < length; i++)
    // {
    //     Serial.println("bitmapHeaderPointer[" + String(i) + "]: " + bitmapHeaderPointer[i]);
    //     sleep(0.1);
    // }
}

Bitmap::~Bitmap()
{
    //delete m_pixelDataWithPadding;
}
