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
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println();
  Serial.println("Connesso !!!");
  
  //server.begin();
/*
  while(true){
    WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
            
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State </p>");
            
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State </p>");
            // If the output27State is off, it displays the ON button       
           
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
 }*/
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
