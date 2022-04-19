#include "CameraConfig.h"

CameraConfig::CameraConfig(pixformat_t pixFormat, framesize_t frameSize, int jpgQuality, size_t fbCount)
{

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

CameraConfig::~CameraConfig()
{
}

camera_config_t CameraConfig::getCamConfig()
{
    return config;
}

void CameraConfig::setFileFormat(String fileFormat)
{
    //Serial.println("setFileFormat -> fileformat: " + fileFormat);

    m_fileFormat = fileFormat;

    switch (config.pixel_format)
    {
    case PIXFORMAT_RGB888:
        m_bytesPerPixel = 3;
        break;

    case PIXFORMAT_GRAYSCALE:
        m_bytesPerPixel = 1;
        break;
    }
}

String CameraConfig::getImgFormat()
{
    return m_fileFormat;
}


// ONLY DO AFTER CAMERA INIT, brightness & contrast: -2 to 2 
bool CameraConfig::configSensor(int brightness, int contrast) {
    sensor_t * s = esp_camera_sensor_get();
    s->set_brightness(s, brightness);     // -2 to 2
    s->set_contrast(s, contrast);       // -2 to 2
    s->set_saturation(s, 0);     // -2 to 2
    s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)
    s->set_whitebal(s, 0);       // 0 = disable , 1 = enable
    s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
    s->set_wb_mode(s, 1);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
    s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
    s->set_aec2(s, 1);           // 0 = disable , 1 = enable
    s->set_ae_level(s, 2);       // -2 to 2
    s->set_aec_value(s, 1200);    // 0 to 1200
    s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
    s->set_agc_gain(s, 0);       // 0 to 30
    s->set_gainceiling(s, (gainceiling_t)6);  // 0 to 6
    s->set_bpc(s, 0);            // 0 = disable , 1 = enable
    s->set_wpc(s, 1);            // 0 = disable , 1 = enable
    s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable -------->SHOULD BE 1
    s->set_lenc(s, 1);           // 0 = disable , 1 = enable
    s->set_hmirror(s, 0);        // 0 = disable , 1 = enable
    s->set_vflip(s, 1);          // 0 = disable , 1 = enable
    s->set_dcw(s, 1);            // 0 = disable , 1 = enable
    s->set_colorbar(s, 0);       // 0 = disable , 1 = enable
}