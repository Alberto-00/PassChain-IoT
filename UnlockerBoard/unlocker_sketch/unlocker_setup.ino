
void setup(){
  Serial.begin(115200);
 /****************************
  * startDevice_module setup *
  ****************************/
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.pushImage(56,18,140,99,logo);
  delay(4000);
  

  /****************************
  * standbyImage_module setup *
  *****************************/
  digitalRainAnim.init(&tft);
  digitalRainAnim.setTextColor(4, 188, 200);
  digitalRainAnim.setHeadCharColor(4, 254, 253);


  /*************************
  * bluetooth_module setup *
  **************************/
  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(tft.color565(3, 211, 216), TFT_BLACK);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.setTextSize(0);
  
  bleKeyboard.begin();
}
