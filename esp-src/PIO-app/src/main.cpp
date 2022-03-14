#include "Arduino.h"
#include "ImgCapture.h"
#include "ErrorHandler.h"

void setup()
{

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

    Serial.begin(115200);

    pinMode(4, OUTPUT); // Set the pin as output

    digitalWrite(4, LOW); // Turn on flash

    ErrorHandler errorHandler;

    if (!SD_MMC.begin())
    {
        errorHandler.handleError("SD Card Mount Failed", NULL, "Setup error");
    }
    else
    {
        uint8_t cardType = SD_MMC.cardType();
        if (cardType == CARD_NONE)
        {
            errorHandler.handleError("No SD Card attached", NULL, "Setup error");
        }
    }

    // ImgCapture imgCapture(PIXFORMAT_GRAYSCALE, FRAMESIZE_UXGA);
    // String filePath = imgCapture.captureImage();

    // Serial.println(filePath);

    digitalWrite(4, HIGH); // Turn off flash

    Serial.println("Going to sleep now");
    rtc_gpio_hold_en(GPIO_NUM_4);
    
    esp_deep_sleep_start();
}

void loop()
{
}