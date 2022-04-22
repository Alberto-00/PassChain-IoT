
bool isInactive_device(){
  unsigned long start_time = millis();
  unsigned long stop_time = millis();
  Serial.print("Start_time: ");
  Serial.println(start_time);
  while(start_time < 30000){
    if(buttonState1 == LOW || buttonState2 == LOW){
      Serial.println(buttonState1);
      return false; 
    }
  } 
  return true;
}

void blockScreen(){
  //tft.fillScreen(TFT_BLACK);
  digitalRainAnim.loop();

  while(buttonState2 == HIGH){
    return;
  }
  digitalRainAnim.pause();
  tft.fillScreen(TFT_BLACK);
}
