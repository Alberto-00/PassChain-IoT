int mainMenu(){
  int pos = 0;

  tft.fillRect(0,25,240,110,TFT_BLACK);
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

      uint8_t id = fingerprint_match();
      if((id > 0 && id < 7) || id > 12){
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
      connection_status = false;
      check_inactivity_device();
    
      if(!connection_status){
        if(!check_connection()){
          restart_time();
          connection_status = true;
          return;
        }
      }
    } 
    else{
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

          // decrypt credential
          char username_dec_arr[256] = {0};
          char password_dec_arr[256]= {0};

          int user_len = credentials[select].getUsername().length() + 1; 
          int passw_len = credentials[select].getPassword().length() + 1;
          int iv_user_len = credentials[select].getIVUser().length() + 1;
          int iv_pasw_len = credentials[select].getIVPassword().length() + 1;

          char buf_user[user_len];
          char buf_pasw[passw_len];
          char buf_iv_user[iv_user_len];
          char buf_iv_pasw[iv_pasw_len];
          
          credentials[select].getUsername().toCharArray(buf_user, user_len);
          credentials[select].getPassword().toCharArray(buf_pasw, passw_len);
          credentials[select].getIVUser().toCharArray(buf_iv_user, iv_user_len);
          credentials[select].getIVPassword().toCharArray(buf_iv_pasw, iv_pasw_len);
          
          decrypt(buf_user, username_dec_arr, buf_iv_user);
          decrypt(buf_pasw, password_dec_arr, buf_iv_pasw);

          String username_dec = String(username_dec_arr);
          String password_dec = String(password_dec_arr);
          // end decryption
      
          tft_bold.setCursor(5, 47);
          tft_bold.print("> Username:");
          tft.setCursor(26, 73);
          tft.print("************");
      
          tft_bold.setCursor(5, 104);
          tft_bold.print("> Password:");
          tft.setCursor(26, 132);
          tft.print("************");

          uint8_t id = fingerprint_match();
          if((id > 0 && id < 7) || id > 12){
            exit = true;
            tft.fillRect(0,25,235,110,TFT_BLACK);
          
            while(!username || !password){
              int flag = verify_Ble_FingerPrint(&exit);
              
              if(flag == -1)
                break;
                
              else if(flag == -2){
                connection_status = false;
                return;
              }
              
              buttonState1 = digitalRead(BUTTON1PIN);
              buttonState2 = digitalRead(BUTTON2PIN);
                 
              tft_bold.setCursor(5, 47);
              tft_bold.print("> Username:");
              tft_lightText.setCursor(26, 73);

              if(username_dec.length() > 21){
                scrollUser = true;
                tft_lightText.print(username_dec.substring(0,20));
              }
              else
                 tft_lightText.print(username_dec);
      
              tft_bold.setCursor(5, 104);
              tft_bold.print("> Password:");
              tft_lightText.setCursor(26, 128);

              if(password_dec.length() > 21){
                scrollPasw = true;
                tft_lightText.print(password_dec.substring(0,20));
              }
              else 
                tft_lightText.print(password_dec);

              if(username_dec.length() > 21 || password_dec.length() > 21){
                state = scrollText(username_dec, password_dec, scrollUser, scrollPasw, &exit);

                if(state == -1)
                  break;
                  
                else if(state == -2){
                  connection_status = false;
                  return;
                }
              }
                
              if(buttonState2 == LOW || state == 2)
                sendPassword(&password, password_dec);
              
              if(buttonState1 == LOW || state == 1)
                sendUsername(&username, username_dec);
              
              
              if(username && password){
                doubleDigitBug = true;
                break; 
              }
            }
            delay(200);
          }
          
          if(id > 6 && id < 13){
            connection_status = false;
            return;
          }
          
          if(doubleDigitBug)
            break;
            
          if(buttonState2 == LOW)
            sendPassword(&password, password_dec);
              
          if(buttonState1 == LOW)
            sendUsername(&username, username_dec);
        }
      }
      /******************************
      *   credentials_module END   *
      ******************************/

      else if(select == -1){
        connection_status = false;
        return;
      }
      
      connection_status = false;
    }
  }
}

void sendUsername(bool *username, String username_dec){
  write_button("username", username_dec);
  restart_time();
  *username = true;
}

void sendPassword(bool *password, String password_dec){
  write_button("password", password_dec);
  restart_time();
  *password = true;
}

int scrollText(String username_dec, String password_dec, bool scrollUser, bool scrollPasw, bool *exit){
  while(true){
    bool goOut = false;
           
    /* Username Text */
    if(username_dec.length() > 21 || scrollUser){
      tft_lightText.fillRect(26,60,235,18, TFT_BLACK);
      tft_lightText.setCursor(26, 73);
      
      while(true){
        for(int i = 0; i < username_dec.length(); i++){
          if(i == 0){
            tft_lightText.print(username_dec.substring(i, 20 + i));
            delay(800);
          } else
              tft_lightText.print(username_dec.substring(i, 20 + i));
              
          int verify = verify_Ble_FingerPrint(exit);
          if(verify == -1)
            return -1;
            
          else if(verify == -2)
            return -2;
            
          buttonState1 = digitalRead(BUTTON1PIN);
          buttonState2 = digitalRead(BUTTON2PIN);   
            
          if(buttonState2 == LOW){
            scrollPasw = true;
            scrollUser = false;
            goOut = true;

            tft_lightText.fillRect(26,60,235,18, TFT_BLACK);
            tft_lightText.setCursor(26, 73);
            tft_lightText.print(username_dec.substring(0,20));
            
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
      
    if(password_dec.length() > 21 || scrollPasw){
      tft_lightText.fillRect(26,115,235,18, TFT_BLACK);
      tft_lightText.setCursor(26, 128);
        
      while(true){
        for(int i = 0; i < password_dec.length(); i++){
          if(i == 0){
            tft_lightText.print(password_dec.substring(i, 20 + i));
            delay(800);
          } else
              tft_lightText.print(password_dec.substring(i, 20 + i));
              
          int verify = verify_Ble_FingerPrint(exit);
          if(verify == -1)
            return -1;
            
          else if(verify == -2)
            return -2;
            
          buttonState1 = digitalRead(BUTTON1PIN);
          buttonState2 = digitalRead(BUTTON2PIN);
          
          if(buttonState1 == LOW){
            scrollPasw = false;
            scrollUser = true;
            goOut = true;

            tft_lightText.fillRect(26,115,235,18, TFT_BLACK);
            tft_lightText.setCursor(26, 128);
            tft_lightText.print(password_dec.substring(0,20));
            
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

  uint8_t id = fingerprint_match();
  if((id > 0 && id < 7) || id > 12){
    *exit = false;
    tft.fillRect(0,25,235,110,TFT_BLACK);
    return -1;
  }
  else if(id > 6 && id < 13){
    return -2;
  }
  
  return 0;
}
