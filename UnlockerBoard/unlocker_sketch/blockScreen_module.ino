
bool isInactive_device(){
  unsigned long start_time = millis();
  unsigned long stop_time = millis();
  Serial.println('time: %d', start_time);
  while((stop_time - start_time) < 30000){
    if(buttonState1 == LOW || buttonState2 == LOW){
      return false; 
    }
    stop_time = millis();
      Serial.println(stop_time - start_time);

  } 
  return true;
}

void blockScreen(){
  digitalRainAnim.loop();

  while(buttonState2 == HIGH){
    return;
  }
  digitalRainAnim.pause();
  tft.fillScreen(TFT_BLACK);
}
