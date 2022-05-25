int mainMenu(){
  int pos = 0;
  
  tft_bold.setCursor(55, 47);
  tft_bold.println("PassChain");
  tft.drawLine(0, 54, 235, 54, tft.color565(3, 211, 216));
  tft.drawLine(0, 130, 235, 130, tft.color565(3, 211, 216));

  while(true){
    buttonState1 = digitalRead(BUTTON1PIN);
    buttonState2 = digitalRead(BUTTON2PIN);
    int shift = 82;
    
    tft_menu.fillRect(0,56,235,71,TFT_BLACK);
    
    if(pos < 0)
      pos = 3;

    if(pos > 3)
      pos = 0;
     
    switch(pos){
      case 0: {
        tft_menu.fillRoundRect(2, 61, 229, 27, 4, tft.color565(3, 211, 216));
        tft_menu.setCursor(5, shift);
        tft_menu.print("> Credentials List");

        tft.setCursor(28, shift += 31);
        tft.print("Bluetooth Devices");
        break;
      }
      
      case 1:{
        tft.setCursor(26, shift);
        tft.print("Credentials List");
        
        tft_menu.fillRoundRect(2, 92, 232, 27, 4, tft.color565(3, 211, 216));
        tft_menu.setCursor(2, shift += 31);
        tft_menu.print("> Bluetooth Devices");
        break;
      }
      
      case 2:{
        tft.setCursor(26, shift);
        tft.print("Bluetooth Devices");
        
        tft_menu.fillRoundRect(2, 92, 229, 27, 4, tft.color565(3, 211, 216));
        tft_menu.setCursor(5, shift += 31);
        tft_menu.print("> WiFi List");
        break;  
      }

      case 3:{
        tft.setCursor(26, shift);
        tft.print("WiFi List");
        
        tft_menu.fillRoundRect(2, 92, 229, 27, 4, tft.color565(3, 211, 216));
        tft_menu.setCursor(5, shift += 31);
        tft_menu.print("> Settings");
        break;  
      }
    }
    
    while(buttonState1 == digitalRead(BUTTON1PIN) && buttonState2 == digitalRead(BUTTON2PIN)){
      if(check_inactivity_device()){
        break;
      }
      
      if(buttonState1 == LOW){
        pos--;
        delay(200);
      }
      else if(buttonState2 == LOW){
        pos++;
        delay(200);
      }
      
      if(fingerprint_match()){
        return pos;
      }
    }
  }
  return pos;
}


int credentialMenu(){
  while(true){
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
          check_inactivity_device();

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
              check_inactivity_device();

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
}
