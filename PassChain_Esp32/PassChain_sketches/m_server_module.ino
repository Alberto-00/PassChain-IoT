
bool connectionToServer(){
  client.setCACert(test_root_ca);           //set the root cert of your CA or of the public CA
  client.setCertificate(test_client_cert); // authenticate this client to the server
  client.setPrivateKey(test_client_key);  // authenticate this client to the server
  unsigned long start_time_listen = millis();
  
  do {
    tft.fillRect(0,25,235,110,TFT_BLACK);
    tft.setCursor(5, 47);
    tft.print("Connecting to");
    tft.setCursor(5, 74);
    tft.print("server");
      
    delay(400); tft.print(".");
    delay(400); tft.print(".");
    delay(400); tft.print(".");
    delay(400);
     
    if((millis() - start_time_listen) > 20000){
       tft.fillRect(0,25,235,110,TFT_BLACK);
       tft.setCursor(5, 47);
       tft.print("Server not");
       tft.setCursor(5, 74);
       tft.print("responding.");
        
       //WiFi.disconnect(true);  // Disconnect from the network
       //WiFi.mode(WIFI_OFF); // Switch WiFi off
        
       delay(2500);
       tft.fillRect(0,25,235,110,TFT_BLACK);
       return false;
     }
  } while (!client.connect(WiFi.gatewayIP(), port));
  
  return true;
}

void startCommunicationToServer(String str){
  client.println(str.length());
  client.println(str);

  /* call some send client if str excedes of 16384 bytes*/
  size_t maxChunk = 16384;
  int numOfChunks = (int) str.length() / maxChunk;
  int counterChars = 0;
  
  for(int i = 0; i < numOfChunks + 1; i++){
    client.println(str.substring(counterChars, counterChars + maxChunk));
    counterChars += maxChunk + 1;
  }
    
  String entry = "";
  int op = 0;
  
  while (client.connected()) {
    while(client.available()){
      char c = client.read();
      entry += c;
    }

    op = entry.substring(0,1).toInt();
    if(op > 0){
      update_credentials(op, entry);
      entry = "";
      op = 0;
    }
  }
  stopConnectionToServer();
}

void stopConnectionToServer(){
  client.stop();
  WiFi.disconnect(true);  // Disconnect from the network
  WiFi.mode(WIFI_OFF); // Switch WiFi off
  restart_time();
}

void update_credentials(int op, String entry){  
  int str_len = entry.length() + 1;
  char buffer[str_len]; 
  entry.toCharArray(buffer, str_len);
      
  char *token = strtok(buffer, "Æ");
      
  switch(op){
    case 1: { // ADD credentials
      /*split string*/
      char *data[3];
      
      for(int i = 0; i < 3; i++){
        token = strtok(NULL, "Æ");
        data[i] = token;
      }
      /*end split string*/

      char encrypt_user[256] = {0};
      char encrypt_passw[256] = {0};

      if(!encrypt(data[1], encrypt_user)){
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(43, 60);
        tft.print("Add Error!");
        tft_logo.pushImage(90, 75, 52, 52, error);
        delay(3500);
        break;
      }

      char iv_user[13];
      strcpy(iv_user, iv);

      if(!encrypt(data[2], encrypt_passw)){
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(43, 60);
        tft.print("Add Error!");
        tft_logo.pushImage(90, 75, 52, 52, error);
        delay(3500);
        break;
      }

      char iv_passw[13];
      strcpy(iv_passw, iv);
      
      if(write_credentialsFile(data[0], encrypt_user, encrypt_passw, iv_user, iv_passw)){
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(43, 60);
        tft.print("Add Success!");
        tft_logo.pushImage(90, 75, 52, 52, success);
        delay(3500);
      }
      else{
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(43, 60);
        tft.print("Add Error!");
        tft_logo.pushImage(90, 75, 52, 52, error);
        delay(3500);
      }
      break;
    }
    
    case 2: { // UPDATE credentials
      /*split string*/
      char *data[4];
            
      for(int i = 0; i < 4; i++){
        token = strtok(NULL, "Æ");
        data[i] = token;
      }
      /*end split string*/

      char encrypt_user[256] = {0};
      char encrypt_passw[256] = {0};
      char iv_user[13];
      char iv_passw[13];
      
      if(strcmp(data[2], "NULL") != 0){
        if(!encrypt(data[2], encrypt_user)){
          tft.fillRect(0,25,240,110,TFT_BLACK);
          tft.setCursor(43, 60);
          tft.print("Add Error!");
          tft_logo.pushImage(90, 75, 52, 52, error);
          delay(3500);
          break;
        }
        strcpy(iv_user, iv);
      } 
      else{
        strcpy(encrypt_user, "NULL");
        strcpy(iv_user, "NULL");
      }

      if(strcmp(data[3], "NULL") != 0){
        if(!encrypt(data[3], encrypt_passw)){
          tft.fillRect(0,25,240,110,TFT_BLACK);
          tft.setCursor(43, 60);
          tft.print("Add Error!");
          tft_logo.pushImage(90, 75, 52, 52, error);
          delay(3500);
          break;
        }
        strcpy(iv_passw, iv);
      } 
      else{
        strcpy(encrypt_passw, "NULL");
        strcpy(iv_passw, "NULL");
      }

      if(update_credentialsFile(data[0], data[1], encrypt_user, encrypt_passw, iv_user, iv_passw)){
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("Update Success!");
        tft_logo.pushImage(90, 75, 52, 52, success);
        delay(3500);
      }
      else{
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("Update Error!");
        tft_logo.pushImage(90, 75, 52, 52, error);
        delay(3500);
      }
      break;
    }
    
    case 3: { // DELETE credentials
      char *data = strtok(NULL, "Æ");
  
      if(remove_credentialsFile(data)){        
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("Delete Success!");
        tft_logo.pushImage(90, 75, 52, 52, success);
        delay(3500);
      }
      else{
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("Delete Error!");
        tft_logo.pushImage(90, 75, 52, 52, error);
        delay(3500);
      }
      break;
    }
    
    case 4: { //Set Fingerprint
      token = strtok(NULL, "Æ");
      
      if(strcmp(token, "repair") == 0){
        finger.getTemplateCount();
        int repair_num = finger.templateCount % 6;
                
        for(int i = 0; i < repair_num; i++){
          finger.getTemplateCount();
          
          if(!fingerprint_delete(finger.templateCount)){
            tft.fillRect(0,25,240,110,TFT_BLACK);
            tft.setCursor(30, 60);
            tft.print("Delete Error!");
            tft_logo.pushImage(90, 75, 52, 52, error);
            delay(3500);
            return;
          }
        }
        
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("Delete Success!");
        tft_logo.pushImage(90, 75, 52, 52, success);
        delay(3500);
      }
      else if(strcmp(token, "add") == 0){
        steps_enroll = 1;
        
        for(int i = 0; i < 6; i++){
          finger.getTemplateCount();
          
          if(fingerprint_enroll(finger.templateCount + 1))
            steps_enroll++;
        }
      }
      else if(strcmp(token, "delete") == 0){
        for(int i = 0; i < 6; i++){
          finger.getTemplateCount();
          
          if(!fingerprint_delete(finger.templateCount)){
            tft.fillRect(0,25,240,110,TFT_BLACK);
            tft.setCursor(30, 60);
            tft.print("Delete Error!");
            tft_logo.pushImage(90, 75, 52, 52, error);
            delay(3500);
            return;
          }
        }

        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("Delete Success!");
        tft_logo.pushImage(90, 75, 52, 52, success);
        delay(3500);
      }
      break;
    }
    
    case 5: { // Set HotSpot
      char *data[2];

      for(int i = 0; i < 2; i++){
        token = strtok(NULL, "Æ");
        data[i] = token;
      }
      
      char encrypt_ssid[256] = {0};
      char encrypt_passw[256] = {0};
      
      char iv_ssid[13] = {0};
      char iv_passw[13] = {0};
      
      if(strcmp(data[0], "NULL") != 0){
        if(!encrypt(data[0], encrypt_ssid)){
          tft.fillRect(0,25,240,110,TFT_BLACK);
          tft.setCursor(43, 60);
          tft.print("Add Error!");
          tft_logo.pushImage(90, 75, 52, 52, error);
          delay(3500);
          break;
        }
        strcpy(iv_ssid, iv);
      } 
      else
         strcpy(encrypt_ssid, "NULL");

      if(strcmp(data[1], "NULL") != 0){        
        if(!encrypt(data[1], encrypt_passw)){
          tft.fillRect(0,25,240,110,TFT_BLACK);
          tft.setCursor(43, 60);
          tft.print("Add Error!");
          tft_logo.pushImage(90, 75, 52, 52, error);
          delay(3500);
          break;
        }
        strcpy(iv_passw, iv);
      } 
      else
         strcpy(encrypt_passw, "NULL");
      
      if(update_hotSpot(encrypt_ssid, encrypt_passw, iv_ssid, iv_passw)){     
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("HotSpot Success!");
        tft_logo.pushImage(90, 75, 52, 52, success);
        delay(3500);
      }
      else{
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(30, 60);
        tft.print("HotSpot Error!");
        tft_logo.pushImage(90, 75, 52, 52, error);
        delay(3500);
      }
      break;
    }
  }
  
  tft.fillRect(0,25,235,110,TFT_BLACK);
  tft.setCursor(5, 47);
  tft.print("Esp32 connected to");
  tft.setCursor(5, 74);
  tft.print("server !!");
  return;
}
