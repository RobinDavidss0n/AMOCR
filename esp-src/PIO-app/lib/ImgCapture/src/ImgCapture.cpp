#include "ImgCapture.h"
#include <string>
#include <sstream>

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

bool ImgCapture::configSensor() {
    sensor_t * s = esp_camera_sensor_get();
    s->set_brightness(s, -1);     // -2 to 2
    s->set_contrast(s, 1);       // -2 to 2
    s->set_saturation(s, 0);     // -2 to 2
    s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)
    s->set_whitebal(s, 1);       // 0 = disable , 1 = enable
    s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
    s->set_wb_mode(s, 0);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
    s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
    s->set_aec2(s, 0);           // 0 = disable , 1 = enable
    s->set_ae_level(s, 0);       // -2 to 2
    s->set_aec_value(s, 300);    // 0 to 1200
    s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
    s->set_agc_gain(s, 0);       // 0 to 30
    s->set_gainceiling(s, (gainceiling_t)0);  // 0 to 6
    s->set_bpc(s, 0);            // 0 = disable , 1 = enable
    s->set_wpc(s, 1);            // 0 = disable , 1 = enable
    s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
    s->set_lenc(s, 1);           // 0 = disable , 1 = enable
    s->set_hmirror(s, 1);        // 0 = disable , 1 = enable
    s->set_vflip(s, 0);          // 0 = disable , 1 = enable
    s->set_dcw(s, 1);            // 0 = disable , 1 = enable
    s->set_colorbar(s, 0);       // 0 = disable , 1 = enable
}

String ImgCapture::captureImage()
{

    ErrorHandler errorHandler;
    InternalStorage internalStorage;

    if (initCamera())
    {   
        configSensor();
        pinMode(4, OUTPUT);    // Set the pin as output
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
    }
    else
    {
        errorHandler.handleError("Camera init failed", NULL, "ErrorFile_" + internalStorage.getImageNumber());
        internalStorage.updateImageNumber();
    }

    return m_imgPath;
}

bool ImgCapture::saveImage()
{
    // Path where new picture will be saved in SD Card
    String fileFormat = camConfig->getImgFormat();

    if (fileFormat == ".bmp")
    {
        saveAsBitmap();
        //saveAsRawPixelData();
    }
    else if (fileFormat == ".txt")
    {
        saveAsRawPixelData();
    }
    else
    {
        InternalStorage internalStorage;
        m_imgPath = "/picture" + String(internalStorage.getImageNumber()) + fileFormat;

        internalStorage.updateImageNumber();

        Serial.println("Picture file name: " + m_imgPath);

        SdCardStorage sdStorage;
        sdStorage.writeImageFile(m_imgPath, fb->buf, fb->len);
    }
}

bool ImgCapture::saveAsRawPixelData()
{
    InternalStorage internalStorage;
    m_imgPath = "/picture" + String(internalStorage.getImageNumber()) + camConfig->getImgFormat();

    internalStorage.updateImageNumber();

    Serial.println("Picture file name: " + m_imgPath);
    Serial.println("fb->width: "+String(fb->width) +"\nfb->height: " + String(fb->height));

    //Bitmap bitmap(fb->width, fb->height, fb->len, camConfig->bytesPerPixel, fb->buf);

    SdCardStorage sdStorage;
    sdStorage.writeRawPixelDataToBinFile(m_imgPath, fb->buf, fb->len);
}


//**********************************    NOT USED    **********************************

bool ImgCapture::saveAsBitmap()
{
    InternalStorage internalStorage;
    m_imgPath = "/picture" + String(internalStorage.getImageNumber()) + ".bmp";

    internalStorage.updateImageNumber();

    Serial.println("Picture file name: " + m_imgPath);

    Bitmap bitmap(fb->width, fb->height, fb->len, camConfig->bytesPerPixel, fb->buf);

    Serial.println("fb->width"+String(fb->width) +"fb->height: " + String(fb->height));

    SdCardStorage sdStorage;

    for (int i = 0; i < bitmap.m_length; i++)
    {
        Serial.println("HeaderData[" + String(i) + "]: " + bitmap.m_bitmapHeaderPointer[i]);
        sleep(0.1);
    }

    sdStorage.writeBitmapFile(m_imgPath, bitmap.m_bitmapHeaderPointer, bitmap.m_length, fb->buf, fb->len);
}