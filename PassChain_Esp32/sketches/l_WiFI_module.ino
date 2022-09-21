void scanWiFi(){

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    
    if (n == 0) {
      tft.setCursor(5, 47);
      tft.fillRect(0,25,235,110,TFT_BLACK);
      tft.print("No WiFi found.");
      tft.setCursor(5, 73);
      tft.print("Connect it with USB.");
    } else {
      tft.fillScreen(TFT_BLACK);
      tft_bold.setCursor(45, 45);
      tft_bold.println("WiFi Networks");
      
      for (int i = 0; i < n; ++i) {
          // Print SSID for each network found
            
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          delay(10);
      }
    }
    
    // Wait a bit before scanning again
    delay(1500);
}
