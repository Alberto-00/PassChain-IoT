
void callback(){}

void wakeup_deepSleep(){
  touchAttachInterrupt(DEEP_SLEEP, callback, Threshold);
  esp_sleep_enable_touchpad_wakeup();
}

void deepSleep(){
  if(isInactive_device(DEEPSLEEP_TIME+BLOCKSCREEN_TIME)){
     esp_deep_sleep_start();
     restart_time(); 
  }
}
