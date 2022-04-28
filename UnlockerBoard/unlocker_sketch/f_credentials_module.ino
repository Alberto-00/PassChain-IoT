int arraySize = 15;

bool load_credentialsFile(){
  if(!SPIFFS.begin(true)){
    return false;
  }
  
  authFile = SPIFFS.open("/credentials.json");
  if(!authFile){
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
  StaticJsonDocument<6144> doc;
  
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
      else break;
    
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
  int i = 0, j = 0, pos = 0;
  int shift = 30;
  
  while(true){
    buttonState1 = digitalRead(BUTTON1PIN);
    buttonState2 = digitalRead(BUTTON2PIN);

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, shift);
    tft.println("Authentication ?");
    
    if(pos > 2){
      pos = 0;
      i+=3;
    }

    if(pos < 0 && i >= 3){
      pos = 2;
      i -= 3;
    } else if(pos < 0 && i == 0){
      pos = 2;
      i = arraySize;
    }

    if(i > arraySize){
      pos = 0;
      i = 0;
    }

     
    switch(pos){
      case 0: {
        if(credentials[i].getName() != NULL){
          tft.setCursor(0, shift += 30);
          tft.print("> " + credentials[i].getName());
        } else break;

        for(j = i+1; j < i+3; j++){
          if(credentials[j].getName() != NULL){
            tft.setCursor(21, shift += 30);
            tft.print(credentials[j].getName());     
          } else{
            shift = 30;
            break;
          }
        }
        shift = 30;
        break;
      }
      
      case 1:{
        //Serial.println(credentials[i].getName());
        if(credentials[i].getName() != NULL){
          tft.setCursor(21, shift += 30);
          tft.println(credentials[i].getName());
        } else break;

        for(j = i+1; j < i+3; j++){
          if(credentials[j].getName() != NULL){
            if(j == i+1){
              tft.setCursor(0, shift += 30);
              tft.print("> " + credentials[j].getName()); 
            } else{
              tft.setCursor(21, shift += 30);
              tft.print(credentials[j].getName()); 
            }    
          } else{
            shift = 30;
            break;
          }
        }
        shift = 30;
        break;
      }
      
      case 2:{
        if(credentials[i].getName() != NULL){
          tft.setCursor(21, shift += 30);
          tft.println(credentials[i].getName());
        } else break;
        
        for(j = i+1; j < i+3; j++){
          if(credentials[j].getName() != NULL){
            if(j == i+2){
              tft.setCursor(0, shift += 30);
              tft.print("> " + credentials[j].getName()); 
            } else{
              tft.setCursor(21, shift += 30);
              tft.print(credentials[j].getName()); 
            }    
          } else{
            shift = 30;
            break;
          }
        }
        shift = 30;
        break;  
      }
      default:
        break;
    }

    while(buttonState1 == digitalRead(BUTTON1PIN) && buttonState2 == digitalRead(BUTTON2PIN)){
      if(buttonState1 == LOW){
        pos--;
        delay(200);
      }
      else if(buttonState2 == LOW){
        pos++;
        delay(200);
      }
    }
  }
}
