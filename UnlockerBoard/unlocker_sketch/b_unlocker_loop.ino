
void loop(){
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);

 /*************************
  * bluetooth_module loop *
  *************************/
  if(!bleKeyboard.isConnected()){
    check_inactivity_device();
    deepSleep();
    
    if(!connection_status){
      check_connection();
      restart_time();
      connection_status = true;
    }
  } else{
    check_inactivity_device();
    
    if(connection_status){
      check_connection();
      restart_time();
    }

  /******************************
   *   credentials_module loop  *
   ******************************/
    menuList();
  /******************************
   *   credentials_module END   *
   ******************************/

    tft.setCursor(0, 30);
    tft.fillScreen(TFT_BLACK);
    tft.print("Select the place where to write\r\nand press the\r\nbottom button.");
    
    if(buttonState2 == LOW){
      write_button();
      restart_time();
    }
    connection_status = false;
  }
}
