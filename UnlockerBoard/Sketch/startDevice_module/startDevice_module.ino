#include <TFT_eSPI.h>
#include "icon.h"

TFT_eSPI tft = TFT_eSPI();

void setup(){
  tft.init();
  tft.fillScreen(TFT_BLACK);

  tft.setSwapBytes(true);
  tft.pushImage(9,68,120,120,icon);
}

void loop(){
}
