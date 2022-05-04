
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
  tft.print("."); delay(670);
  
  bleKeyboard.print(credentials);
  
  tft.print("."); delay(670);
  tft.print("."); delay(670);
  tft.print(".");
  tft.fillRect(0,25,235,110,TFT_BLACK);
}
