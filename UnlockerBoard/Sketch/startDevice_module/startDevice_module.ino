#include <TFT_eSPI.h>
#include "icon.h"

TFT_eSPI tft = TFT_eSPI();

void setup(){
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setSwapBytes(true);
  tft.pushImage(68,9,120,120,icon);
}

void loop(){
}
