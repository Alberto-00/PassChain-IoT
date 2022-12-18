
bool connectionToServer(){
  client.setCACert(test_root_ca);
  client.setCertificate(test_client_cert); // for client verification
  client.setPrivateKey(test_client_key);  // for client verification
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
        
       WiFi.disconnect(true);  // Disconnect from the network
       WiFi.mode(WIFI_OFF); //Switch WiFi off
        
       delay(3000);
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
  WiFi.mode(WIFI_OFF); //Switch WiFi off
  restart_time();
  tft.fillRect(0,25,235,110,TFT_BLACK);
}

void update_credentials(int op, String entry){
  int str_len = entry.length() + 1;
  char buffer[str_len]; 
  entry.toCharArray(buffer, str_len);
      
  char *token = strtok(buffer, "-");
  String entry_string[2]; 
      
  switch(op){
    case 1: {
      /*split string*/
      char *data[3];
      
      for(int i = 0; i < 3 && token != NULL; i++){
        token = strtok(NULL, "-");
        data[i] = token;
        
        if(i == 0)
          continue;
          
        String char_to_string(data[i]);
        entry_string[i-1] = cipher->encryptString(char_to_string);
      }
      /*end split string*/
  
      if(write_credentialsFile(data[0], entry_string[0], entry_string[1])){        
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
    
    case 2: {
      /*split string*/
      char *data[4];
            
      for(int i = 0; i < 4 && token != NULL; i++){
        token = strtok(NULL, "-");
        data[i] = token;
        
        if(i < 2)
          continue;

        String char_to_string(data[i]);
        
        if(strcmp(data[i], "NULL") != 0)
          entry_string[i-2] = cipher->encryptString(char_to_string);
        else
          entry_string[i-2] = char_to_string;
      }
      /*end split string*/
  
      if(update_credentialsFile(data[0], data[1], entry_string[0], entry_string[1])){        
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
    
    case 3: {
      char *data = strtok(NULL, "-");
  
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
    
    case 4: {
      break;
    }
    
    case 5: {
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
