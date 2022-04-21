#include <TFT_eSPI.h>
#include <BleKeyboard.h>

#define BUTTON1PIN 35
#define BUTTON2PIN 0

TFT_eSPI tft = TFT_eSPI(); 
BleKeyboard bleKeyboard;

void check_connection() {
  int count = 0;
 
  while(1){
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

void setup() {
  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT);
    
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(tft.color565(3, 211, 216), TFT_BLACK);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.setTextSize(1); //la dimensione va da 1 a 5, di default usa 1

  bleKeyboard.begin();

  if(bleKeyboard.isConnected()){
    check_connection();
  }
}

bool connection_status = false;

void loop() {  
  int buttonState1 = digitalRead(BUTTON1PIN);
  int buttonState2 = digitalRead(BUTTON2PIN);

  if(!bleKeyboard.isConnected()){
    if(!connection_status){
      check_connection();
      connection_status = true;
    }
  } else{
    if(connection_status)
      check_connection();
      
    tft.setCursor(0, 30);
    tft.print("Select the place where to write\r\nand press the\r\nbottom button.");
    
    if(buttonState2 == LOW){
      write_button();
    }
    connection_status = false;
  }
}
