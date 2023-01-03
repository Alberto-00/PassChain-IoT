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

bool load_W_hotSpotFile(){
  if(!SPIFFS.begin(true)){
    return false;
  }
  
  WiFiFile = SPIFFS.open("/accessPoint.json", "w");
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
      ESP.restart();
      return;
    }
  }
}

bool update_hotSpot(char* ssid, char* password, char* iv_ssid, char *iv_password){
  if(load_W_hotSpotFile()){
    
    if(ssid != NULL && strcmp(ssid, "NULL") != 0){
      wifi_config["SSID"] = ssid;
      wifi_config["iv_SSID"] = iv_ssid;
    }

    if(password != NULL && strcmp(password, "NULL") != 0){
      wifi_config["password"] = password;
      wifi_config["iv_password"] = iv_password;
    }
    
    serializeJsonPretty(wifi_config, WiFiFile);
    close_WiFiFile();
    return true;
  }
  return false;
}

void accessPoint_start(){
  if(WiFi.status() != WL_CONNECTED){ 
    
    char ssid_dec[256] = {0};
    char password_dec[256]= {0};

    String buf_ssid = wifi_config["SSID"];
    String buf_passw = wifi_config["password"];
    String buf_iv_SSID = wifi_config["iv_SSID"];
    String buf_iv_password = wifi_config["iv_password"];

    int len_ssid = buf_ssid.length() + 1;
    int len_passw = buf_passw.length() + 1;
    int len_iv_ssid = buf_iv_SSID.length() + 1;
    int len_iv_password = buf_iv_password.length() + 1;

    char buf_ssid_char[len_ssid];
    char buf_passw_char[len_passw];
    char buf_iv_ssid_char[len_iv_ssid];
    char buf_iv_password_char[len_iv_password];

    buf_ssid.toCharArray(buf_ssid_char, len_ssid);
    buf_passw.toCharArray(buf_passw_char, len_passw);
    buf_iv_SSID.toCharArray(buf_iv_ssid_char, len_iv_ssid);
    buf_iv_password.toCharArray(buf_iv_password_char, len_iv_password);
    
    decrypt(buf_ssid_char, ssid_dec, buf_iv_ssid_char);
    decrypt(buf_passw_char, password_dec, buf_iv_password_char);
  
    WiFi.begin(ssid_dec, password_dec);
    
    String ssid = String(ssid_dec);
    String password = String(password_dec);

    // attempt to connect to Wifi network:
    unsigned long start_time_connection = millis();
    do {
      tft.setCursor(5, 47);
      tft.print("Connecting to");
      tft.setCursor(5, 74);
      tft.print(ssid);
      
      delay(400); tft.print(".");
      delay(400); tft.print(".");
      delay(400); tft.print(".");
      delay(400);
      tft.fillRect(0,25,235,110,TFT_BLACK);
      
      if((millis() - start_time_connection) > 15000){
        tft.setCursor(5, 47);
        tft.print("HotSpot not");
        tft.setCursor(5, 74);
        tft.print("found.");
        
        WiFi.disconnect(true);  // Disconnect from the network
        WiFi.mode(WIFI_OFF); //Switch WiFi off
        
        delay(3000);
        tft.fillRect(0,25,235,110,TFT_BLACK);
        return;
      }
    } while (WiFi.status() != WL_CONNECTED);
    
    tft.setCursor(5, 47);
    tft.fillRect(0,25,235,110,TFT_BLACK);
    tft.print("Connected to");
    tft.setCursor(5, 74);
    tft.print('"' + ssid + '"' + "."); 
    tft_logo.pushImage(90, 84, 60, 48, wifi);
    delay(3000);
    
    if(connectionToServer()){
      tft.fillRect(0,25,235,110,TFT_BLACK);
      tft.setCursor(5, 47);
      tft.print("Esp32 connected to");
      tft.setCursor(5, 74);
      tft.print("server !!");
      
      client.println("Hello World!");
      
      finger.getTemplateCount();
      client.println(finger.templateCount);
      client.println(ssid + "Æ" + password);

      String credentialsJsonString = doc["credentials"];
      startCommunicationToServer(credentialsJsonString);
    }
  }
}
