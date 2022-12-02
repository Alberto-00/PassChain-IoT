
void setup(){
  Serial.begin(115200);
    
 /****************************
  * startDevice_module setup *
  ****************************/ 
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.setTextColor(tft.color565(3, 211, 216), TFT_BLACK);
  tft.setFreeFont(&FreeSans12pt7b);
  tft.pushImage(56, 18, 140, 99, logo);
  
  
  /***************************
  * fingerprint_module setup *
  ****************************/
  fingerprint_setup();

  
  /****************************
  * blockScreen_module setup *
  *****************************/
  digitalRainAnim.init(&tft);
  digitalRainAnim.setTextColor(4, 188, 200);
  digitalRainAnim.setHeadCharColor(4, 254, 253);
  restart_time();
  

  /*************************
  * bluetooth_module setup *
  **************************/
  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT);
  
  bleKeyboard.begin();
  wakeup_deepSleep();


  /*********************
   * WiFi_module setup *
   *********************/ 
   if(load_R_WiFiConfigFile()){
    read_WiFiFile();
    close_WiFiFile();
   }


  /***************************
  * credentials_module setup *
  ****************************/
  if(load_R_credentialsFile()){
    read_credentialsFile();
    close_credentialsFile();
  }

  tft.fillScreen(TFT_BLACK);
  
  tft_bold.begin();   
  tft_bold.setRotation(1);
  tft_bold.setSwapBytes(true);
  tft_bold.setTextColor(tft.color565(3, 211, 216), TFT_BLACK);
  tft_bold.setFreeFont(&FreeSansBold12pt7b);

  tft_lightText.begin();   
  tft_lightText.setRotation(1);
  tft_lightText.setSwapBytes(true);
  tft_lightText.setTextColor(tft.color565(3, 211, 216), TFT_BLACK);
  tft_lightText.setFreeFont(&FreeSans9pt7b);

  tft_menu.begin();   
  tft_menu.setRotation(1);
  tft_menu.setSwapBytes(true);
  tft_menu.setTextColor(TFT_BLACK, tft.color565(3, 211, 216));
  tft_menu.setFreeFont(&FreeSansBold12pt7b);
  
  start_time = millis();
 
  
  /***************************
  *   battery_module setup   *
  ****************************/
  battery_setup();


 /*********************************
  * crypto_module setup (WolfSSL) *
  *********************************/
  WiFi.begin(ssid, password);
  //WiFi.softAP(ssid, password);
  //IPAddress myIP = WiFi.softAPIP();
  
  //Serial.println(myIP);

  Serial.println("Server started");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("AP IP address: ");
  Serial.println(WiFi.localIP());
  
  int err;
  WOLFSSL_METHOD* method;

  method = wolfTLSv1_2_server_method();
  if (method == NULL) {
    Serial.println("unable to get method");
    return;
  }
  
  ctx = wolfSSL_CTX_new(method);
  if (ctx == NULL) {
    Serial.println("unable to get ctx");
    return;
  }

  /* initialize wolfSSL using callback functions */
  wolfSSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, 0); /* SSL_VERIFY_PEER (fa anche authentication client), SSL_VERIFY_NONE solo authentication server */
  wolfSSL_SetIOSend(ctx, EthernetSend);
  wolfSSL_SetIORecv(ctx, EthernetReceive);

  /* setup the private key and certificate */
  err = wolfSSL_CTX_use_PrivateKey_buffer(ctx, ecc_key_der_256, 
    sizeof_ecc_key_der_256, WOLFSSL_FILETYPE_ASN1);
    
  if (err != WOLFSSL_SUCCESS) {
    Serial.println("error setting key");
    return;
  }
  err = wolfSSL_CTX_use_certificate_buffer(ctx, serv_ecc_der_256, 
    sizeof_serv_ecc_der_256, WOLFSSL_FILETYPE_ASN1);
  if (err != WOLFSSL_SUCCESS) {
    Serial.println("error setting certificate");
    return;
  }

  /* Start the server */
  server.begin();
  //return;
}
