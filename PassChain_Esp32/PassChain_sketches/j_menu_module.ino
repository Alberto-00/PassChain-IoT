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
    tft_bold.setCursor(55, 47);
    tft_bold.println("PassChain");
    tft.drawLine(0, 54, 235, 54, tft.color565(3, 211, 216));
    tft.drawLine(0, 130, 235, 130, tft.color565(3, 211, 216));
    
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

      default:
        break;
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


void credentialsMenu(){
  
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
      int select = subMenuCredentials();
      delay(200);
    
      if(select != -1){
        bool username = false, password = false;
        bool scrollUser = false, scrollPasw = false;
        bool exit = false;
        bool doubleDigitBug = false;
        int state = 0;
      
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
              if(verify_Ble_FingerPrint(&exit) == -1)
                break;
              
              buttonState1 = digitalRead(BUTTON1PIN);
              buttonState2 = digitalRead(BUTTON2PIN);
                 
              tft_bold.setCursor(5, 47);
              tft_bold.print("> Username:");
              tft_lightText.setCursor(26, 73);

              if(credentials[select].getUsername().length() > 21)
                tft_lightText.print(credentials[select].getUsername().substring(0,20));
              else
                tft_lightText.print(credentials[select].getUsername());
      
              tft_bold.setCursor(5, 104);
              tft_bold.print("> Password:");
              tft_lightText.setCursor(26, 128);
              
              if(credentials[select].getPassword().length() > 21)
                tft_lightText.print(credentials[select].getPassword().substring(0,20));
              else
                tft_lightText.print(credentials[select].getPassword());

              if(credentials[select].getUsername().length() > 21 || credentials[select].getPassword().length() > 21){
                scrollUser = true;
                state = scrollText(select, scrollUser, scrollPasw, &exit);
              }

              if(state == -1)
                break;

              if(buttonState2 == LOW || state == 2)
                sendPassword(&password, select);
              
              if(buttonState1 == LOW || state == 1)
                sendUsername(&username, select);
              
              
              if(username && password){
                doubleDigitBug = true;
                break; 
              }
            }
            delay(200);
          }
          if(doubleDigitBug)
            break;
            
          if(buttonState2 == LOW)
            sendPassword(&password, select);
              
          if(buttonState1 == LOW)
            sendUsername(&username, select);
        }
      }
      /******************************
      *   credentials_module END   *
      ******************************/
    
      connection_status = false;
    }
  }
}

void sendUsername(bool *username, int select){
  write_button("username", credentials[select].getUsername());
  restart_time();
  *username = true;
}

void sendPassword(bool *password, int select){
  write_button("password", credentials[select].getPassword());
  restart_time();
  *password = true;
}

int scrollText(int select, bool scrollUser, bool scrollPasw, bool *exit){
  while(true){
    bool goOut = false;
           
    /* Username Text */
    if(credentials[select].getUsername().length() > 21 && scrollUser){
      tft_lightText.fillRect(26,60,235,18, TFT_BLACK);
      tft_lightText.setCursor(26, 73);
      
      while(true){
        for(int i = 0; i < credentials[select].getUsername().length(); i++){
          if(i == 0){
            tft_lightText.print(credentials[select].getUsername().substring(i, 20 + i));
            delay(800);
          } else
              tft_lightText.print(credentials[select].getUsername().substring(i, 20 + i));
          
          if(verify_Ble_FingerPrint(exit) == -1)
            return -1;
            
          buttonState1 = digitalRead(BUTTON1PIN);
          buttonState2 = digitalRead(BUTTON2PIN);   
            
          if(buttonState2 == LOW){
            scrollPasw = true;
            scrollUser = false;
            goOut = true;

            tft_lightText.fillRect(26,60,235,18, TFT_BLACK);
            tft_lightText.setCursor(26, 73);
            tft_lightText.print(credentials[select].getUsername().substring(0,20));
            
            delay(100);
            break;
          }

          if(buttonState1 == LOW)
            return 1;

          delay(100);
          tft_lightText.fillRect(26,60,235,18, TFT_BLACK);
          tft_lightText.setCursor(26, 73);
        }
        
        if(goOut)
          break;
      } 
    }
    
    /*Password Text */
    goOut = false;
      
    if(credentials[select].getPassword().length() > 21 && scrollPasw){
      tft_lightText.fillRect(26,115,235,18, TFT_BLACK);
      tft_lightText.setCursor(26, 128);
        
      while(true){
        for(int i = 0; i < credentials[select].getPassword().length(); i++){
          if(i == 0){
            tft_lightText.print(credentials[select].getPassword().substring(i, 20 + i));
            delay(800);
          } else
              tft_lightText.print(credentials[select].getPassword().substring(i, 20 + i));
              
          if(verify_Ble_FingerPrint(exit) == -1)
            return -1;
            
          buttonState1 = digitalRead(BUTTON1PIN);
          buttonState2 = digitalRead(BUTTON2PIN);
          
          if(buttonState1 == LOW){
            scrollPasw = false;
            scrollUser = true;
            goOut = true;

            tft_lightText.fillRect(26,115,235,18, TFT_BLACK);
            tft_lightText.setCursor(26, 128);
            tft_lightText.print(credentials[select].getPassword().substring(0,20));
            
            delay(100);
            break;
          }

          if(buttonState2 == LOW)
            return 2;

          delay(100);
          tft_lightText.fillRect(26,115,235,18, TFT_BLACK);
          tft_lightText.setCursor(26, 128);
        }
        
        if(goOut)
          break;
      } 
    }
  }
    
  if(buttonState2 == LOW)
    return 2;
      
  if(buttonState1 == LOW)
    return 1;
}

int verify_Ble_FingerPrint(bool *exit){
  check_inactivity_device();

  if(!bleKeyboard.isConnected())
    return -1;

  if(fingerprint_match()){
    *exit = false;
    tft.fillRect(0,25,235,110,TFT_BLACK);
    return -1;
  }
}

/*
void WiFiMenu(){
  int SSID = scanWiFi();
}*/