#include <TFT_eSPI.h>
#include <DigitalRainAnim.h>

TFT_eSPI tft = TFT_eSPI();
DigitalRainAnim digitalRainAnim = DigitalRainAnim(); 

void setup(){
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  digitalRainAnim.init(&tft);
  digitalRainAnim.setTextColor(4, 188, 200);
  digitalRainAnim.setHeadCharColor(4, 254, 253);
}

void loop(){
  digitalRainAnim.loop();
}
