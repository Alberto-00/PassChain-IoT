
bool isInactive_device(unsigned long inactivity_time){ 
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);

  stop_time = millis();

  if(buttonState1 == LOW || buttonState2 == LOW || fingerprint_match() != 0){
    restart_time();
    return false;
  } else if((stop_time - start_time) > inactivity_time){
      return true;
  } else {
    return false;
  }
}

bool isInactive_device_deep_sleep(unsigned long inactivity_time){ 
  stop_time = millis();

  if(fingerprint_match() != 0){
    restart_time();
    return false;
  } else if((stop_time - start_time) > inactivity_time){
      return true;
  } else {
    return false;
  }
}

void blockScreen(){
  tft.fillScreen(TFT_BLACK);
  
  while(true){
    digitalRainAnim.loop();
    
    if(fingerprint_match() != 0){
      delay(100);
      break;
    }
    deepSleep();
  }
  
  if(!bleKeyboard.isConnected())
    connection_status = false;

  tft.fillScreen(TFT_BLACK);
}

bool check_inactivity_device(){
  if(isInactive_device(BLOCKSCREEN_TIME)){
    vTaskDelete(TaskHandle_2);
    blockScreen();
    restart_time();
    battery_setup();
    return true;
  }
  return false;
}

void restart_time(){
  start_time = millis();
  stop_time = millis();
}
