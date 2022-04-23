
bool isInactive_device(){ 
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);
  
  stop_time = millis();

  if(buttonState1 != HIGH || buttonState2 != HIGH){
    restart_time();
    return false;
  } else if((stop_time - start_time) > 8000){
      restart_time();
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
  isInactive = true;
}

void check_inactivity_device(){
  if(isInactive_device())
    blockScreen();
}

void restart_time(){
  start_time = millis();
  stop_time = millis();
}
