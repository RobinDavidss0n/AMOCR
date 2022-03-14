#include "ImgCapture.h"

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
        ErrorHandler errorHandler;
        InternalStorage internalStorage;
        errorHandler.handleError("Camera init failed", err, "ErrorFile_" + internalStorage.getImageNumber());
        internalStorage.updateImageNumber();
        return false;
    }
    return true;
}

bool ImgCapture::saveImage()
{
    // Path where new picture will be saved in SD Card
    String fileFormat = camConfig->getImgFormat();
    InternalStorage internalStorage;
    m_imgPath = "/picture" + String(internalStorage.getImageNumber()) + fileFormat;

    internalStorage.updateImageNumber();

    Serial.println("Picture file name: " + m_imgPath);

    SdCardStorage sdStorage;

    sdStorage.writeImageFile(m_imgPath, fb->buf, fb->len);
}

String ImgCapture::captureImage()
{

    ErrorHandler errorHandler;
    InternalStorage internalStorage;

    if (initCamera())
    {
        pinMode(4, OUTPUT); // Set the pin as output
        digitalWrite(4, HIGH); // Turn on flash

        // Take Picture with Camera
        fb = esp_camera_fb_get();

        if (!fb)
        {
            errorHandler.handleError("Camera capture failed", NULL, "ErrorFile_" + internalStorage.getImageNumber());
            internalStorage.updateImageNumber();
            return String("");
        }

        digitalWrite(4, LOW); // Turn off flash
        
        saveImage();

    }else
    {
        errorHandler.handleError("Camera init failed", NULL, "ErrorFile_" + internalStorage.getImageNumber());
        internalStorage.updateImageNumber();
    }

    // Turns off the ESP32-CAM white on-board LED (flash) connected to GPIO 4
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);

    return m_imgPath;
}