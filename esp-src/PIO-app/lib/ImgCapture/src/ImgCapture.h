#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include "CameraConfig.h"
#include "InternalStorage.h"
#include "ErrorHandler.h"
#include "SdCardStorage.h"
#include "bitmap.h"

#ifndef IMGCAPTURE_H
#define IMGCAPTURE_H

class ImgCapture {

private:
    String m_imgPath;
    
    CameraConfig* camConfig = nullptr;
    camera_config_t config;
    camera_fb_t* fb;
    int m_brightness = 0;
    int m_contrast = 0;

    bool initCamera();
    bool saveImage();
    bool saveAsBitmap();
    bool saveAsRawPixelData();

public:
    
    ImgCapture(pixformat_t pixFormat, framesize_t frameSize, String fileFormat, int brightness = 0, int contrast = 0, int jpgQuality = 0, size_t fbCount = 1);
    ~ImgCapture();

    String captureImage(bool initCam);
};

#endif // IMGCAPTURE_H