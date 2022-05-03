
void loop(){
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);

 /*************************
  * bluetooth_module loop *
  *************************/
  if(!bleKeyboard.isConnected()){
    check_inactivity_device();
    
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
    int select = menuList();

    if(select != -1){
      bool username = false;
      bool password = false;
      tft.fillScreen(TFT_BLACK);
    
      while(!username || !password){
        buttonState1 = digitalRead(BUTTON1PIN);
        buttonState2 = digitalRead(BUTTON2PIN);
      
        tft.setCursor(0, 30);
        tft.println("Username:");
        tft.println("*********");
      
        tft.setCursor(0, 90);
        tft.println("Password:");
        tft.println("*********");
    
        if(buttonState2 == LOW){
          write_button("password", credentials[select].getPassword());
          restart_time();
          password = true;
        }
      
        if(buttonState1 == LOW){
          write_button("username", credentials[select].getUsername());
          restart_time();
          username = true;
        } 
      }
      
      username = false;
      password = false;
    }
   /******************************
    *   credentials_module END   *
    ******************************/
    
    connection_status = false;
  }
}
