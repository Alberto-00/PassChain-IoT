
bool load_R_credentialsFile(){
  if(!SPIFFS.begin(true)){
    return false;
  }
  
  authFile = SPIFFS.open("/credentials.json");
  if(!authFile){
    return false;
  }
  return true;
}

bool load_W_credentialsFile(){
  if(!SPIFFS.begin(true)){
    return false;
  }
  
  authFile = SPIFFS.open("/credentials.json", "w");
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
  if(authFile){
    DeserializationError error = deserializeJson(doc, authFile);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    sizeJson = doc["credentials"].size();

    for(int i = 0; i < sizeJson; i++){
      if(doc["credentials"][i].containsKey("name") && doc["credentials"][i]["name"] != NULL)
        credentials[i].setName(doc["credentials"][i]["name"]);
      else break;
    
      if(doc["credentials"][i].containsKey("username") && doc["credentials"][i]["username"] != NULL)
         credentials[i].setUsername(doc["credentials"][i]["username"]);

      if(doc["credentials"][i].containsKey("password") && doc["credentials"][i]["password"] != NULL)
         credentials[i].setPassword(doc["credentials"][i]["password"]);

      if(doc["credentials"][i].containsKey("ivUser") && doc["credentials"][i]["ivUser"] != NULL)
         credentials[i].setIVUser(doc["credentials"][i]["ivUser"]);

      if(doc["credentials"][i].containsKey("ivPassword") && doc["credentials"][i]["ivPassword"] != NULL)
         credentials[i].setIVPassword(doc["credentials"][i]["ivPassword"]);
    }
  } else
    ESP.restart();
}

bool write_credentialsFile(char *name, char *username, char *password, char *ivUser, char *ivPassword){
  if(sizeJson + 1 < 80){
    if(load_W_credentialsFile()){
      if(name != NULL){
        doc["credentials"][sizeJson]["name"] = name;
        credentials[sizeJson].setName(doc["credentials"][sizeJson]["name"]);
      }

      if(username != NULL){
        doc["credentials"][sizeJson]["username"] = username;
        credentials[sizeJson].setUsername(doc["credentials"][sizeJson]["username"]);
      }

      if(password != NULL){
        doc["credentials"][sizeJson]["password"] = password;
        credentials[sizeJson].setPassword(doc["credentials"][sizeJson]["password"]);
      }

      if(ivUser != NULL){
        doc["credentials"][sizeJson]["ivUser"] = ivUser;
        credentials[sizeJson].setIVUser(doc["credentials"][sizeJson]["ivUser"]);
      }

      if(ivPassword != NULL){
        doc["credentials"][sizeJson]["ivPassword"] = ivPassword;
        credentials[sizeJson].setIVPassword(doc["credentials"][sizeJson]["ivPassword"]);
      }
    
      sizeJson++;
      serializeJsonPretty(doc, authFile);
      close_credentialsFile();
      return true;
    } 
    return false;
  } else
      return false;
}

bool update_credentialsFile(char *oldName, char* newName, char* username, char* password, char *ivUser, char *ivPassword){
  if(load_W_credentialsFile()){
    if(oldName != NULL){
      for(int i = 0; i < sizeJson; i++){
        if(strcmp(doc["credentials"][i]["name"], oldName) == 0){
          
          if(newName != NULL && strcmp(newName, "NULL") != 0){
            doc["credentials"][i]["name"] = newName;
            credentials[i].setName(doc["credentials"][i]["name"]);
          }

          if(username != NULL && strcmp(username, "NULL") != 0){
            doc["credentials"][i]["username"] = username;
            credentials[i].setUsername(doc["credentials"][i]["username"]);
          }

          if(password != NULL && strcmp(password, "NULL") != 0){
            doc["credentials"][i]["password"] = password;
            credentials[i].setPassword(doc["credentials"][i]["password"]);
          }

          if(ivUser != NULL && strcmp(ivUser, "NULL") != 0){
            doc["credentials"][i]["ivUser"] = ivUser;
            credentials[i].setIVUser(doc["credentials"][i]["ivUser"]);
          }

          if(ivPassword != NULL && strcmp(ivPassword, "NULL") != 0){
            doc["credentials"][i]["ivPassword"] = ivPassword;
            credentials[i].setIVPassword(doc["credentials"][i]["ivPassword"]);
          }
          
          serializeJsonPretty(doc, authFile);
          close_credentialsFile();
          return true;
        }
      }
    }
    close_credentialsFile();
    return false;
  }
  return false;
}

bool remove_credentialsFile(char* name){
  if(load_W_credentialsFile()){
    if(name != NULL){
      for(int i = 0; i < sizeJson; i++){
        if(strcmp(doc["credentials"][i]["name"], name) == 0){
          JsonArray cred = doc["credentials"];
          cred.remove(i);
          updateArray(i);
          serializeJsonPretty(doc, authFile);
          close_credentialsFile();
          return true;
        }
      }
    }
    close_credentialsFile();
    return false;
  }
  return false;
}

void updateArray(int pos){
  if(pos == 0 && sizeJson == 1){
    credentials[pos].setName("");
    credentials[pos].setUsername("");
    credentials[pos].setPassword("");
    credentials[pos].setIVUser("");
    credentials[pos].setIVPassword("");
    sizeJson = 0;
    return;
  }
  
  for(int i = pos; i < sizeJson - 1; i++){
    if(credentials[i+1].getName() != NULL && !(credentials[i+1].getName()).isEmpty()){
      credentials[i].setName(credentials[i+1].getName());
    } 
  
    if(credentials[i+1].getUsername() != NULL && !(credentials[i+1].getUsername()).isEmpty()){
      credentials[i].setUsername(credentials[i+1].getUsername());
    }
  
    if(credentials[i+1].getPassword() != NULL && !(credentials[i+1].getPassword()).isEmpty()){
      credentials[i].setPassword(credentials[i+1].getPassword());
    }

    if(credentials[i+1].getIVUser() != NULL && !(credentials[i+1].getIVUser()).isEmpty()){
      credentials[i].setIVUser(credentials[i+1].getIVUser());
    }

    if(credentials[i+1].getIVPassword() != NULL && !(credentials[i+1].getIVPassword()).isEmpty()){
      credentials[i].setIVPassword(credentials[i+1].getIVPassword());
    }
  }

  if(credentials[sizeJson-1].getName() != NULL && !(credentials[sizeJson-1].getName()).isEmpty()){
    credentials[sizeJson-1].setName("");
    credentials[sizeJson-1].setUsername("");
    credentials[sizeJson-1].setPassword("");
    credentials[sizeJson-1].setIVUser("");
    credentials[sizeJson-1].setIVPassword("");
  }
  
  sizeJson--;
}

int subMenuCredentials(){
  int i = 0, j = 0, pos = 0, current = i;
  boolean title = false;
  
  tft_bold.setCursor(45, 45);
  tft_bold.println("Authentication");
  
  while(true){
    
    if(title){
      title = false;
      tft_bold.setCursor(45, 45);
      tft_bold.println("Authentication");
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
      if(sizeJson % 3 == 0){
        pos = 2;
        i = sizeJson - 3;
      } else if(sizeJson % 3 == 1){
        pos = 0;
        i = sizeJson - 1;
      } else{
        pos = 1;          
        i = sizeJson - 2;
      }
    }
     
    switch(pos){
      case 0: {
        if(credentials[i].getName() != NULL && !(credentials[i].getName()).isEmpty()){
          tft.setCursor(5, shift += 28);
          tft.print("> " + credentials[i].getName());
          current = i; 
        } else break;
        
        for(j = i+1; j < i+3; j++){
          if(credentials[j].getName() != NULL && !(credentials[j].getName()).isEmpty()){
            tft.setCursor(26, shift += 28);
            tft.print(credentials[j].getName());
          } else break;
        }
        break;
      }
      
      case 1:{
        if(credentials[i].getName() != NULL && !(credentials[i].getName()).isEmpty()){
          tft.setCursor(26, shift += 28);
          tft.println(credentials[i].getName());
        } else break;

        for(j = i+1; j < i+3; j++){
          if(credentials[j].getName() != NULL && !(credentials[j].getName()).isEmpty()){
            if(j == i+1){
              tft.setCursor(5, shift += 28);
              tft.print("> " + credentials[j].getName());
              current = j; 
            } else{
              tft.setCursor(26, shift += 28);
              tft.print(credentials[j].getName()); 
            }    
          } else break;
        }
        break;
      }
      
      case 2:{
        if(credentials[i].getName() != NULL && !(credentials[i].getName()).isEmpty()){
          tft.setCursor(26, shift += 28);
          tft.println(credentials[i].getName());
        } else break;
        
        for(j = i+1; j < i+3; j++){
          if(credentials[j].getName() != NULL && !(credentials[j].getName()).isEmpty()){
            if(j == i+2){
              tft.setCursor(5, shift += 28);
              tft.print("> " + credentials[j].getName()); 
              current = j;
            } else{
              tft.setCursor(26, shift += 28);
              tft.print(credentials[j].getName()); 
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

      if(!bleKeyboard.isConnected()){
        return -1;
      }
      
      if(buttonState1 == LOW){
        pos--;
        delay(200);
      }
      else if(buttonState2 == LOW){
        if(pos == 2){
          if(credentials[i+3].getName() != NULL && !(credentials[i+3].getName()).isEmpty()){
            pos++;
            delay(200);
          } else{
            pos = 0;
            i = 0;
            delay(200);
          }
        } 
        else if(pos == 0){
           if(credentials[i+1].getName() != NULL && !(credentials[i+1].getName()).isEmpty()){
            pos++;
            delay(200);
          } else{
            pos = 0;
            i = 0;
            delay(200);
          }
        } 
        else if(pos == 1){
          if(credentials[i+2].getName() != NULL && !(credentials[i+2].getName()).isEmpty()){
            pos++;
            delay(200);
          } else{
            pos = 0;
            i = 0;
            delay(200);
          }
        }
      }

      uint8_t id = fingerprint_match();
      if((id > 0 && id < 7) || id > 12)
        return current;
        
      else if(id > 6 && id < 13)
        return -1;
    }
  }
}
