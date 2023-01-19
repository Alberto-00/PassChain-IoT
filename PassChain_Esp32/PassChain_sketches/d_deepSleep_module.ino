
void callback(){}

void wakeup_deepSleep(){
  touchAttachInterrupt(DEEP_SLEEP, callback, Threshold);
  esp_sleep_enable_touchpad_wakeup();
}

void deepSleep(){
  if(isInactive_device_deep_sleep(DEEPSLEEP_TIME + BLOCKSCREEN_TIME))
     esp_deep_sleep_start();
}
