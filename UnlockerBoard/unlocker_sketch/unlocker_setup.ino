void setup(){
 /****************************
  * startDevice_module setup *
  ****************************/
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setSwapBytes(true);
  tft.pushImage(68,9,120,120,icon);
  
  bleKeyboard.begin();
  delay(3500);


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
  tft.setTextSize(1); //la dimensione va da 1 a 5, di default usa 1


  /******************************
   * function to send the board *
   *    in deep_sleep mode      *
   ******************************/
  /*  NOT WORKING 'A SIGNOR ME NE' MANNAT'   ->   attualmente la scheda mostra il logo e poi va in deep_sleep, da capire perchè
  //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);  //Function that wake-up the board after the setted time (is based on the variable TIME_TO_SLEEP that is defined in unlocker_sketch)
  if(TIME_TO_SLEEP * uS_TO_S_FACTOR > 30)
    esp_deep_sleep_start(); //The function that actually trigger the deep_sleep mode
  */
}
