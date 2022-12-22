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
      return;
    }
  }
}

bool update_hotSpot(String ssid, String password){
  if(load_W_hotSpotFile()){
    
    if(ssid != NULL && !ssid.isEmpty())
      wifi_config["SSID"] = ssid;

    if(password != NULL && !password.isEmpty())
      wifi_config["password"] = password;

    serializeJsonPretty(wifi_config, WiFiFile);
    close_WiFiFile();
    return true;
  }
  return false;
}

void accessPoint_start(){
  if(WiFi.status() != WL_CONNECTED){ 
    bleKeyboard.end();
    
    String ssid = wifi_config["SSID"];
    String password = wifi_config["password"];

    String ssi_dec = cipher->decryptString(ssid);
    String password_dec = cipher->decryptString(password);

    WiFi.begin(ssi_dec.c_str(), password_dec.c_str());

    // attempt to connect to Wifi network:
    unsigned long start_time_connection = millis();
    do {
      tft.setCursor(5, 47);
      tft.print("Connecting to");
      tft.setCursor(5, 74);
      tft.print(ssi_dec);
      
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
    tft.print('"' + ssi_dec + '"' + "."); 
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
      client.println(ssi_dec + "Æ" + password_dec);

      String credentialsJsonString = doc["credentials"];
      startCommunicationToServer(credentialsJsonString);
    }
  }
}
