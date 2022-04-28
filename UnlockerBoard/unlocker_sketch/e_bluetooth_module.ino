
void check_connection() {
  unsigned long count = 0;
 
  while(true){
    tft.setCursor(0, 30);
    tft.fillScreen(TFT_BLACK);
    tft.print("Connecting.");
    delay(400);
    tft.print(".");
    delay(400);
    tft.print(".");
    delay(400);
    tft.print(".");
    delay(400);
    
    if(bleKeyboard.isConnected()) {
      tft.setCursor(0, 30);
      tft.fillScreen(TFT_BLACK);
      tft.println("The device is\r\nconnected !");
      delay(2500);
      tft.fillScreen(TFT_BLACK);
      return;
    }
    
    count++;
    if(count == 3){
      tft.setCursor(0, 30);
      tft.fillScreen(TFT_BLACK);
      tft.println("Connection\r\nFailed !\r\n\r\nBluetooth off.");
      return;
    }
  }
}

void write_button(){
  tft.setCursor(0, 60);
  tft.fillScreen(TFT_BLACK);
  tft.println("Writing");
  tft.println("password");
  
  bleKeyboard.print("Password");
  delay(2000);
  
  tft.fillScreen(TFT_BLACK);
}
