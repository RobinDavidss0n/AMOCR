#include "ImgCapture.h"
#include "ErrorHandler.h"

ErrorHandler errorHandler;

ImgCapture::ImgCapture(pixformat_t pixFormat, framesize_t frameSize, int jpgQuality, size_t fbCount)
{

    fb = NULL;
    camConfig = new CameraConfig(pixFormat, frameSize, jpgQuality, fbCount);

    if (!psramFound())
    {
        frameSize = FRAMESIZE_SVGA;
        jpgQuality = 12;
        fbCount = 1;
    }

    config = camConfig->getCamConfig();
}

ImgCapture::~ImgCapture()
{
    delete camConfig;
}

bool ImgCapture::initCamera()
{
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        errorHandler.handleError("Camera init failed", err, "Error file name");

        return false;
    }
    return true;
}

bool ImgCapture::saveImage()
{
    // initialize EEPROM with predefined size
    EEPROM.begin(EEPROM_SIZE);
    m_pictureNumber = EEPROM.read(0) + 1;

    // Path where new picture will be saved in SD Card
    String fileFormat = camConfig->getImgFormat();
    m_imgPath = "/picture" + String(m_pictureNumber) + fileFormat;

    fs::FS &fs = SD_MMC;
    Serial.printf("Picture file name: %s\n", m_imgPath.c_str());

    File file = fs.open(m_imgPath.c_str(), FILE_WRITE);
    if (!file)
    {
        errorHandler.handleError("Failed to open file in writing mode", NULL, "Error file name");
        file.close();
        return false;
    }
    else
    {
        file.write(fb->buf, fb->len); // payload (image), payload length
        Serial.printf("Saved file to path: %s\n", m_imgPath.c_str());
        EEPROM.write(0, m_pictureNumber);
        EEPROM.commit();
        file.close();
        return true;
    }
}

String ImgCapture::captureImage()
{

    if (initCamera())
    {
        // Take Picture with Camera
        fb = esp_camera_fb_get();

        if (!fb)
        {
            errorHandler.handleError("Camera capture failed", NULL, "Error file name");
            return String("");
        }
        saveImage();

    }else
    {
        errorHandler.handleError("Camera init failed", NULL, "Error file name");
    }

    // Turns off the ESP32-CAM white on-board LED (flash) connected to GPIO 4
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);

    return m_imgPath;
}