#include "ImgCapture.h"

ImgCapture::ImgCapture() {

    fb = NULL;

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
    config.pixel_format = PIXFORMAT_JPEG; 

    if(psramFound()){
        config.frame_size = FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
        config.jpeg_quality = 10;
        config.fb_count = 2;
    } else {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }
}

ImgCapture::~ImgCapture() {

}

bool ImgCapture::initCamera() {
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return false;
    }
    return true;
}

bool ImgCapture::initSdCard() {
    //Serial.println("Starting SD Card");
    if(!SD_MMC.begin()){
        Serial.println("SD Card Mount Failed");
        return false;
    }

    uint8_t cardType = SD_MMC.cardType();
    if(cardType == CARD_NONE){
        Serial.println("No SD Card attached");
        return false;
    }

    return true;
}

bool ImgCapture::saveImage() {
    // initialize EEPROM with predefined size
    EEPROM.begin(EEPROM_SIZE);
    m_pictureNumber = EEPROM.read(0) + 1;

    // Path where new picture will be saved in SD Card
    m_imgPath = "/picture" + String(m_pictureNumber) +".jpg";

    fs::FS &fs = SD_MMC; 
    Serial.printf("Picture file name: %s\n", m_imgPath.c_str());

    File file = fs.open(m_imgPath.c_str(), FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file in writing mode");
        file.close();
        return false;
    } 
    else {
        file.write(fb->buf, fb->len); // payload (image), payload length
        Serial.printf("Saved file to path: %s\n", m_imgPath.c_str());
        EEPROM.write(0, m_pictureNumber);
        EEPROM.commit();
        file.close();
        return true;
    }
}

String ImgCapture::captureImage() {
    
    //TODO: Ta hand om false-returer från dessa två:
    initCamera();
    initSdCard();

    // Take Picture with Camera
    fb = esp_camera_fb_get();  
    
    if(!fb) {
        Serial.println("Camera capture failed");
        return String("");
    }

    saveImage();

    // Turns off the ESP32-CAM white on-board LED (flash) connected to GPIO 4
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    rtc_gpio_hold_en(GPIO_NUM_4);

    return m_imgPath;

}