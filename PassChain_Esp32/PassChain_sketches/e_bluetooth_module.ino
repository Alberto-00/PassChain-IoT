
void check_connection() {
  unsigned long count = 0;
 
  while(true){
    tft.setCursor(5, 47);
    tft.fillRect(0,25,235,110,TFT_BLACK);
    
    tft.print("Connecting.");
    delay(400);
    tft.print(".");
    delay(400);
    tft.print(".");
    delay(400);
    tft.print(".");
    delay(400);
    
    if(bleKeyboard.isConnected()) {
      tft.setCursor(5, 47);
      tft.fillRect(0,25,235,110,TFT_BLACK);
      tft.print("The device is");
      tft.setCursor(5, 73);
      tft.print("connected !");

      delay(2500);
      
      tft.fillRect(0,25,235,110,TFT_BLACK);
      return;
    }
    
    count++;
    if(count == 3){
      tft.setCursor(5, 47);
      tft.fillRect(0,25,235,110,TFT_BLACK);
      tft.print("Connection");
      tft.setCursor(5, 73);
      tft.print("Failed !");

      tft.setCursor(5, 122);
      tft.print("Bluetooth off.");
      return;
    }
  }
}

void write_button(String type, String credentials){
  tft.setCursor(5, 60);
  tft.fillRect(0,25,235,110,TFT_BLACK);
  
  tft.print("Writing");
  tft.setCursor(5, 88); 
  tft.print(type);
  tft.print("."); delay(370);

  sendSequence(credentials);
  
  tft.print("."); delay(370);
  tft.print("."); delay(370);
  tft.print(".");
  tft.fillRect(0,25,235,110,TFT_BLACK);
}

void sendSequence(String sequence){
  int len = sequence.length();
  int special=0;
  for (int i=0;i<=len;i++) {
    if (special == 1) {
      if (sequence.charAt(i) == 'r') {special=0;bleKeyboard.write(KEY_RETURN);Serial.println("[KEY_RETURN]");}    //add CR
      else if (sequence.charAt(i) == 's') {special=0;bleKeyboard.write(32);Serial.println("[SPACE]");}    //add space
      else if (sequence.charAt(i) == 'c') {special=0;bleKeyboard.write(':');Serial.println(":");}    //add colon
      else if (sequence.charAt(i) == 't') {special=0;bleKeyboard.write(KEY_TAB);Serial.println("[KEY_TAB]");}       //add horizontal tab
      else if (sequence.charAt(i) == '\\') {special=1;bleKeyboard.print('\\');Serial.println("[\\]");}       //Dual slash situation
      else {
        special=0;
        bleKeyboard.print("\\");
        bleKeyboard.print(sequence.charAt(i));
      }        
    }        
    else {
      if(sequence.charAt(i) == '\\')
        special=1;
      
      else 
        bleKeyboard.print(sequence.charAt(i));
      
      bleKeyboard.releaseAll();
      delay(20);
    }
  }
}
