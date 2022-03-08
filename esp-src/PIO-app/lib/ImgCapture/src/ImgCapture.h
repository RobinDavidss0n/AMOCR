#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <EEPROM.h>            // read and write from flash memory
#include "CameraConfig.h"

#ifndef IMGCAPTURE_H
#define IMGCAPTURE_H

class ImgCapture {

private:
    String m_imgPath;
    int m_pictureNumber;
    
    CameraConfig* camConfig = nullptr;
    camera_config_t config;
    camera_fb_t* fb;

    bool initCamera();
    bool initSdCard();
    bool saveImage();

public:
    ImgCapture(pixformat_t pixFormat, framesize_t frameSize, int jpgQuality = 10, size_t fbCount = 2);
    ~ImgCapture();

    String captureImage();
};

#endif // IMGCAPTURE_H