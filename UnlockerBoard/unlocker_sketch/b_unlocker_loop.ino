
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
    delay(200);
    
    if(select != -1){
      bool username = false;
      bool password = false;
      bool exit = false;
      
      tft.fillRect(0,25,235,110,TFT_BLACK);
    
      while((!username || !password) && !exit){
        if(!bleKeyboard.isConnected())
          break;
          
        buttonState1 = digitalRead(BUTTON1PIN);
        buttonState2 = digitalRead(BUTTON2PIN);
      
        tft_bold.setCursor(5, 47);
        tft_bold.print("> Username:");
        tft.setCursor(26, 73);
        tft.print("************");
      
        tft_bold.setCursor(5, 104);
        tft_bold.print("> Password:");
        tft.setCursor(26, 132);
        tft.print("************");

        if(fingerprint_match()){
          exit = true;
          tft.fillRect(0,25,235,110,TFT_BLACK);
          
          while(!username || !password){
            if(!bleKeyboard.isConnected())
              break;

            if(fingerprint_match()){
              exit = false;
              tft.fillRect(0,25,235,110,TFT_BLACK);
              break;
            }
              
            buttonState1 = digitalRead(BUTTON1PIN);
            buttonState2 = digitalRead(BUTTON2PIN);
      
            tft_bold.setCursor(5, 47);
            tft_bold.print("> Username:");
            tft.setCursor(26, 73);
            tft.print(credentials[select].getUsername());
      
            tft_bold.setCursor(5, 104);
            tft_bold.print("> Password:");
            tft.setCursor(26, 128);
            tft.print(credentials[select].getPassword());

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
          delay(200);
        }
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
