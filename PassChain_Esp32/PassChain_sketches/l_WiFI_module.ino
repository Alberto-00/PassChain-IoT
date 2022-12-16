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
  if(WiFi.status() != WL_CONNECTED){ 
    bleKeyboard.end();

    String ssid = wifi_config["SSID"];
    String password = wifi_config["password"];
    
    WiFi.begin(ssid.c_str(), password.c_str());

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

      String credentialsJsonString = doc["credentials"];
      client.println("Hello World!");
      client.println(cipher->getKey());
      startCommunicationToServer(credentialsJsonString);
    }
  }
}
