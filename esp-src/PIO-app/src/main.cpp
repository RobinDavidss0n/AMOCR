#include "Arduino.h"
#include "ImgCapture.h"

void setup()
{

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

    Serial.begin(115200);

    InternalStorage internalStorage;
    internalStorage.resetImageNumber();

    int brightness = -2;
    int contrast = 2;

    // ImgCapture imgCapture1(PIXFORMAT_GRAYSCALE, FRAMESIZE_UXGA);
    // imgCapture.captureImage();

    int counter = 0;
    bool init = false;

    while (counter < 5)
    {
        ImgCapture imgCapture(PIXFORMAT_RGB888, FRAMESIZE_SVGA, ".bin", brightness, contrast);
        imgCapture.captureImage(init);

        counter += 1;
        init = true;
        Serial.println("counter:");
        Serial.println(counter);
    }

    Serial.println("Going to sleep now");
    rtc_gpio_hold_en(GPIO_NUM_4);

    esp_deep_sleep_start();
}

void loop()
{
}