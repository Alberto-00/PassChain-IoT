bool load_R_WiFiConfigFile(){
  if(!SPIFFS.begin(true)){
    return false;
  }
  
  WiFiFile = SPIFFS.open("/accessPoint.json");
  if(!WiFiFile){
    return false;
  }
  return true;
}

bool close_WiFiFile(){
  if(WiFiFile){
    WiFiFile.close();
    return true;
  }
  return false;
}

void read_WiFiFile(){
  if(WiFiFile){
    DeserializationError error = deserializeJson(wifi_config, WiFiFile);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
  }
}

void accessPoint_start(){
   WiFi.softAP(wifi_config["SSID"], wifi_config["password"]);
   IPAddress IP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(IP);
    server.begin();
}

/*int scanWiFi(){

    int i = 0, j = 0, pos = 0, current = i;
    boolean title = false;
  
    tft_bold.setCursor(45, 45);
    tft_bold.println("WiFi Networks");
    int total_WiFi = WiFi.scanNetworks();       // WiFi.scanNetworks will return the number of networks found
  
    while(true){
      unsigned int time_start = millis();
        
      if(total_WiFi == 0){
        tft.setCursor(5, 47);
        tft.fillRect(0,25,235,110,TFT_BLACK);
        tft.print("No WiFi found.");
        tft.setCursor(5, 73);
        tft.print("Connect it with USB.");
      } else{
          
        if(title){
          title = false;
          tft_bold.setCursor(45, 45);
          tft_bold.println("WiFi Networks");
        }
      
        buttonState1 = digitalRead(BUTTON1PIN);
        buttonState2 = digitalRead(BUTTON2PIN);
        int shift = 45;
      
        tft.fillRect(0,50,235,85,TFT_BLACK);
      
        if(pos > 2){
          pos = 0;
          i+=3;
        }
  
        if(pos < 0 && i >= 3){
          pos = 2;
          i -= 3;
        } 
        if(pos < 0 && i == 0){
          if(total_WiFi % 3 == 0){
            pos = 2;
            i = total_WiFi - 3;
          } else if(total_WiFi % 3 == 1){
            pos = 0;
            i = total_WiFi - 1;
          } else{
            pos = 1;          
            i = total_WiFi - 2;
          }
        }
           
        switch(pos){
          case 0: {
            if(i < total_WiFi){
              tft_lightText.setCursor(5, shift += 28);
              tft_lightText.print("> " + WiFi.SSID(i));
              current = i;
            } else break;
      
            for(j = i+1; j < i+3; j++){
              if(j < total_WiFi){
                tft_lightText.setCursor(26, shift += 28);
                tft_lightText.print(WiFi.SSID(j));     
              } else break;
            }
            break;
          }
            
          case 1:{
            if(i < total_WiFi){
              tft_lightText.setCursor(26, shift += 28);
              tft_lightText.println(WiFi.SSID(i));
            } else break;
      
            for(j = i+1; j < i+3; j++){
              if(j < total_WiFi){
                if(j == i+1){
                  tft_lightText.setCursor(5, shift += 28);
                  tft_lightText.print("> " + WiFi.SSID(j));
                  current = j; 
                } else{
                  tft_lightText.setCursor(26, shift += 28);
                  tft_lightText.print(WiFi.SSID(j)); 
                }    
              } else break;
            }
            break;
          }
            
          case 2:{
            if(i < total_WiFi){
              tft_lightText.setCursor(26, shift += 28);
              tft_lightText.println(WiFi.SSID(i));
            } else break;
              
            for(j = i+1; j < i+3; j++){
              if(j < total_WiFi){
                if(j == i+2){
                  tft_lightText.setCursor(5, shift += 28);
                  tft_lightText.print("> " + WiFi.SSID(j)); 
                  current = j;
                } else{
                  tft_lightText.setCursor(26, shift += 28);
                  tft_lightText.print(WiFi.SSID(j)); 
                }    
              } else break;
            }
            break;  
          }
          default:
            break;
        }
          
        while(buttonState1 == digitalRead(BUTTON1PIN) && buttonState2 == digitalRead(BUTTON2PIN)){
          
          if(check_inactivity_device()){
            title = true;
            break;
          }
          
          unsigned int time_end = millis();
          if((time_end - time_start) > WiFiScan_TIME){
            total_WiFi = WiFi.scanNetworks();
            pos = 0; i = 0;
            break;
          }
            
          if(buttonState1 == LOW){
            pos--;
            delay(200);
          }
          else if(buttonState2 == LOW){
            if(pos == 2){
              if(i+3 < total_WiFi){
                pos++;
                delay(200);
              } else{
                pos = 0;
                i = 0;
                delay(200);
              }
            } 
            else if(pos == 0){
               if(i+1 < total_WiFi){
                pos++;
                delay(200);
              } else{
                pos = 0;
                i = 0;
                delay(200);
              }
            } 
            else if(pos == 1){
              if(i+2 < total_WiFi){
                pos++;
                delay(200);
              } else{
                pos = 0;
                i = 0;
                delay(200);
              }
            }
          }
            
          if(fingerprint_match()){ 
              return current;
          }
        }
      }
    }
}*/
