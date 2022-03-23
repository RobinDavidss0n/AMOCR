#include "Arduino.h"
#include "ImgCapture.h"

void setup()
{

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

    Serial.begin(115200);

    //InternalStorage internalStorage;
    //internalStorage.resetImageNumber();

    ImgCapture imgCapture(PIXFORMAT_GRAYSCALE, FRAMESIZE_UXGA);
    imgCapture.captureImage();

    Serial.println("Going to sleep now");
    rtc_gpio_hold_en(GPIO_NUM_4);
    
    esp_deep_sleep_start();
}

void loop()
{
}