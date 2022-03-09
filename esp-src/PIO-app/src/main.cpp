#include "Arduino.h"
#include "ImgCapture.h"
#include "ErrorHandler.h"

void setup()
{

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector

    Serial.begin(115200);

    pinMode(4, OUTPUT); // Set the pin as output

    digitalWrite(4, LOW);  // Turn on flash

    if(!SD_MMC.begin()){
        Serial.println("SD Card Mount Failed");
    }

    uint8_t cardType = SD_MMC.cardType();
    if(cardType == CARD_NONE){
        Serial.println("No SD Card attached");
    }

    ErrorHandler errorHandler;

    esp_err_t error = ESP_ERR_NOT_SUPPORTED;

    errorHandler.handleError("testar :)", error, "Error file name");

    //ImgCapture imgCapture(PIXFORMAT_GRAYSCALE, FRAMESIZE_UXGA);
    //String filePath = imgCapture.captureImage();

    //Serial.println(filePath);

    digitalWrite(4, HIGH); // Turn off flash

    delay(2000);
    Serial.println("Going to sleep now");
    delay(2000);
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}

void loop()
{
}