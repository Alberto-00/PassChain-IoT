
//minimo 3.5V
void battery_setup() {
  tft_battery.begin();
  tft_battery.setRotation(1);
  tft_battery.setTextColor(TFT_WHITE,TFT_BLACK); 
  tft_battery.fillScreen(TFT_BLACK);
  tft_battery.setSwapBytes(true);
  tft_battery.setTextFont(2);

  tft_logo.begin();
  tft_logo.setRotation(1);
  tft_logo.setTextColor(tft_logo.color565(3, 211, 216), TFT_BLACK);
  tft_logo.setSwapBytes(true);
  tft_logo.setTextFont(2);
    
  pinoutInit();
  xTaskCreate(battery_info, "battery_info", 2048, NULL, 1, &TaskHandle_2);
}

void pinoutInit(){
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}

void battery_info(void *arg){
  while (true) {
    tft_logo.pushImage(5, 3, 33, 23, home);
    tft_logo.setCursor(43,5);
    tft_logo.print("PassChain");
    
    if(BL.getBatteryVolts() >= MIN_USB_VOL){
      for(int i = 0; i < ARRAY_SIZE; i++){
       drawingBatteryIcon(batteryImages[i]);
       drawingText("Chrg");
       vTaskDelay(500);
      }
    }

    else if(BL.getBatteryVolts() <= 3.5){
     tft.fillScreen(TFT_BLACK);
     tft.setCursor(35, 32);
     tft.setFreeFont(&FreeSansBold12pt7b);
     tft.setTextColor(TFT_WHITE, TFT_BLACK);
     tft.print("LOW BATTERY");
     tft.pushImage(20, 50, 199, 76, battery_low);
      
     delay(3000);
     esp_deep_sleep_start();
   }

    else{
       tft_battery.fillRect(153,3,35,17,TFT_BLACK);
       int imgNum = 0;
       int batteryLevel = getBatteryLevel();

       if(batteryLevel >= 80){
         imgNum = 3;
       }else if(batteryLevel < 80 && batteryLevel >= 50){
         imgNum = 2;
       }else if(batteryLevel < 50 && batteryLevel >= 20){
         imgNum = 1;
       }else if(batteryLevel < 20 ){
         imgNum = 0;
       }  
    
       drawingBatteryIcon(batteryImages[imgNum]); 
       drawingText(String(batteryLevel) + "%");
       vTaskDelay(1000);
    }
  }
}

void drawingBatteryIcon(char* filePath){  
  if(strcmp("battery/battery_01", filePath) == 0){
    tft_battery.pushImage(190, 0, 45, 23, battery_01);
  } 
  
  else if(strcmp("battery/battery_02", filePath) == 0){
    tft_battery.pushImage(190, 0, 45, 23, battery_02);
  }
   
  else if(strcmp("battery/battery_03", filePath) == 0){
    tft_battery.pushImage(190, 0, 45, 23, battery_03);
  }
  
  else if(strcmp("battery/battery_04", filePath) == 0){
    tft_battery.pushImage(190, 0, 45, 23, battery_04);
  }
  
  else if(strcmp("battery/battery_05", filePath) == 0){
    tft_battery.pushImage(190, 0, 45, 23, battery_05);
  }
}

void drawingText(String text){
  tft_battery.setCursor(155, 3);
  tft_battery.print(text);
}

int getBatteryLevel(){
  double battery = BL.getBatteryVolts();

  for(int i = 0; i < 100 - 1; i++){
    if(battery >= _vs[i] && battery <= _vs[i+1]){
      double min = _vs[i];
      double max = _vs[i+1];

      if((battery - min) < (max - battery))
        return i + 1;
      else
        return i + 2;
    }
  }
}
