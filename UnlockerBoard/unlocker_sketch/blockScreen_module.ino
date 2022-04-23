
bool isInactive_device(unsigned long inactivity_time){ 
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);
  
  stop_time = millis();

  if(buttonState1 != HIGH || buttonState2 != HIGH){
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
  buttonState2 = digitalRead(BUTTON2PIN);
  
  while(buttonState2 == HIGH){
    digitalRainAnim.loop();
    buttonState2 = digitalRead(BUTTON2PIN);
  }
  
  if(!bleKeyboard.isConnected())
    connection_status = false;

  tft.fillScreen(TFT_BLACK);
  
  while(buttonState2 == LOW){
     buttonState2 = digitalRead(BUTTON2PIN);
  }
}

void check_inactivity_device(){
  if(isInactive_device(BLOCKSCREEN_TIME)){
    blockScreen();
    restart_time();
  }
}

void restart_time(){
  start_time = millis();
  stop_time = millis();
}
