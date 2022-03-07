#include "Arduino.h"
#include "ImgCapture.h"

void setup() {

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
 
  Serial.begin(115200);

  ImgCapture imgCapture(PIXFORMAT_RAW, FRAMESIZE_UXGA);
  String filePath = imgCapture.captureImage();

  Serial.println(filePath);

  delay(2000);
  Serial.println("Going to sleep now");
  delay(2000);
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}

void loop() {
  
}
