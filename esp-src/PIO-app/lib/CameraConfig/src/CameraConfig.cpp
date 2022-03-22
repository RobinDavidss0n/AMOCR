#include "CameraConfig.h"

CameraConfig::CameraConfig(pixformat_t pixFormat, framesize_t frameSize, int jpgQuality, size_t fbCount) {
    
    // Standard configuration:
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;

    // Customizable configuration:
    config.pixel_format = pixFormat;
    config.frame_size = frameSize;
    config.jpeg_quality = jpgQuality;
    config.fb_count = fbCount;
}

CameraConfig::~CameraConfig() {

}

camera_config_t CameraConfig::getCamConfig() { 
    return config; 
}

String CameraConfig::getImgFormat() {
       
    switch (config.pixel_format) {
        case PIXFORMAT_RGB888:
            bytesPerPixel = 3;
            return ".bmp";
        
        case PIXFORMAT_JPEG:
            return ".jpg";

        case PIXFORMAT_GRAYSCALE:
            bytesPerPixel = 1;
            return ".bmp";

        default:
            return ".error";
    }
}