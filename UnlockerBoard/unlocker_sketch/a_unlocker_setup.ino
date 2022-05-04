
void setup(){
  Serial.begin(115200);
  
 /****************************
  * startDevice_module setup *
  ****************************/
  tft_bold.begin();   
  tft_bold.setRotation(1);
  tft_bold.setSwapBytes(true);
  tft_bold.setTextColor(tft.color565(3, 211, 216), TFT_BLACK);
  tft_bold.setFreeFont(&FreeSansBold12pt7b);
  
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.setTextColor(tft.color565(3, 211, 216), TFT_BLACK);
  tft.setFreeFont(&FreeSans12pt7b);
  tft.pushImage(56, 18, 140, 99, logo);

  
  /***************************
  * fingerprint_module setup *
  ****************************/
  fingerprint_setup();

  
  /****************************
  * blockScreen_module setup *
  *****************************/
  digitalRainAnim.init(&tft);
  digitalRainAnim.setTextColor(4, 188, 200);
  digitalRainAnim.setHeadCharColor(4, 254, 253);
  restart_time();
  

  /*************************
  * bluetooth_module setup *
  **************************/
  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT);
  
  bleKeyboard.begin();
  wakeup_deepSleep();


  /***************************
  * credentials_module setup *
  ****************************/
  if(load_R_credentialsFile()){
    read_credentialsFile();
    close_credentialsFile();
  }
  
  delay(1500);
  tft.fillScreen(TFT_BLACK);
  
  start_time = millis();
 
  
  /***************************
  *   battery_module setup   *
  ****************************/
  battery_setup();
}
