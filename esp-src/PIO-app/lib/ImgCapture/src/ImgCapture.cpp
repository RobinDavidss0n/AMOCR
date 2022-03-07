#include "ImgCapture.h"

ImgCapture::ImgCapture(pixformat_t pixFormat, framesize_t frameSize, int jpgQuality, size_t fbCount) {

    fb = NULL;
    camConfig = CameraConfig(pixFormat, frameSize, jpgQuality, fbCount);

    if (!psramFound()) {
        frameSize = FRAMESIZE_SVGA;
        jpgQuality = 12;
        fbCount = 1;
    }

    config = camConfig.getCamConfig();
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
    String fileFormat = camConfig.getImgFormat();
    m_imgPath = "/picture" + String(m_pictureNumber) + fileFormat;

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