
bool load_credentialsFile(){
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }
  
  authFile = SPIFFS.open("/credentials.json");
  if(!authFile){
    Serial.println("Failed to open file for reading");
    return false;
  }
  return true;
}

bool close_credentialsFile(){
  if(authFile){
    authFile.close();
    return true;
  }
  return false;
}

void read_credentialsFile(){
  StaticJsonDocument<256> doc;
  
  if(authFile){
    DeserializationError error = deserializeJson(doc, authFile);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    unsigned int sizeJson = doc["credentials"].size();
    
    for(int i = 0; i < sizeJson; i++){
      if(doc["credentials"][i].containsKey("name") && doc["credentials"][i]["name"] != NULL)
        credentials[i].setName(doc["credentials"][i]["name"]);
        
      if(doc["credentials"][i].containsKey("username") && doc["credentials"][i]["username"] != NULL)
         credentials[i].setUsername(doc["credentials"][i]["username"]);

      if(doc["credentials"][i].containsKey("password") && doc["credentials"][i]["password"] != NULL)
         credentials[i].setPassword(doc["credentials"][i]["password"]);

      if(doc["credentials"][i].containsKey("pinCode") && doc["credentials"][i]["pinCode"] != NULL)
         credentials[i].setPinCode(doc["credentials"][i]["pinCode"]);
    }
  } else
    Serial.println("Can't open file.");
}

bool write_credentialsFile(){
  
}

void menuList(){
  int i = 0, j = 0;
  
  while(true){
   //check_inactivity_device();
   buttonState1 = digitalRead(BUTTON1PIN);
   buttonState2 = digitalRead(BUTTON2PIN);

   
   if(buttonState1 == LOW && i - 1 >= 0){
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 30);
    tft.println("Authentication ?");
    tft.setCursor(0, 60);
    tft.print("> " + credentials[i--].getName());
     tft.setCursor(0, 70);
    tft.print("> " + credentials[i].getName());
   } 
   else if(buttonState2 == LOW && credentials[i + 1].getName() != NULL){
     tft.fillScreen(TFT_BLACK);
     tft.setCursor(0, 30);
     tft.println("Authentication ?");
     tft.print(credentials[i++].getName());
   }
 }
}
