
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
  tft.fillRect(0,25,235,110,TFT_BLACK);
}

void update_credentials(int op, String entry){
  int str_len = entry.length() + 1;
  char buffer[str_len]; 
  entry.toCharArray(buffer, str_len);
  
  char *token = strtok(buffer, "-");
  char *data[3]; 
  int i = 0;

  while(token != NULL && i < 4){
    token = strtok(NULL, "-");
    data[i] = token;
    Serial.println(data[i]);
    String mystring(data[i]);
    Serial.print("Decrypt: "); Serial.println(cipher->decryptBuffer(mystring));
    i++;
  }
  
  switch(op){
    case 1: {
      if(write_credentialsFile(data[0], data[1], data[2])){
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(43, 60);
        tft.fillRect(0,25,235,110,TFT_BLACK);
        tft.print("Add Success!");
        tft_logo.pushImage(90, 75, 52, 52, success);
        delay(10000);
      }
      else{
        tft.fillRect(0,25,240,110,TFT_BLACK);
        tft.setCursor(43, 60);
        tft.fillRect(0,25,235,110,TFT_BLACK);
        tft.print("Add Error!");
        tft_logo.pushImage(90, 75, 52, 52, error);
        delay(10000);
      }
      break;
    }
    
    case 2: {
      break;
    }
    
    case 3: {
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
