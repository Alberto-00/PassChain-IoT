#include <TFT_eSPI.h>
#include <BleKeyboard.h>

#define BUTTON1PIN 35
#define BUTTON2PIN 0

TFT_eSPI tft = TFT_eSPI(); 

BleKeyboard bleKeyboard;

void toggleButton1() {  
  while(1){
    tft.setCursor(0, 30);
    tft.fillScreen(TFT_BLACK);
    tft.print("Connecting.");
    delay(500);
    tft.print(".");
    delay(500);
    tft.print(".");
    delay(500);
    if(bleKeyboard.isConnected()) {
      tft.setCursor(0, 30);
      tft.fillScreen(TFT_BLACK);
      tft.println("Connected!!!");
      Serial.println("Connected");
      delay(3000);
      exit(1);
    }
  }
}

void toggleButton2(){
  tft.setCursor(0, 60);
  tft.fillScreen(TFT_BLACK);
  tft.println("Writing");
  tft.println("password");

  Serial.println("Sending the string...");
  bleKeyboard.print("Password");
  delay(1000);

  Serial.println("Sending Enter key...");
  bleKeyboard.write(KEY_RETURN);

  delay(1000);
   
  tft.setCursor(0, 30);
  tft.fillScreen(TFT_BLACK);
  tft.print("Press the bottom button to start writing");

  // Below is an example of pressing multiple keyboard modifiers 
  // which by default is commented out.
  /*
  Serial.println("Sending Ctrl+Alt+Delete...");
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(KEY_DELETE);
  delay(100);
  bleKeyboard.releaseAll();
  */
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT);

  //attachInterrupt(BUTTON1PIN, toggleButton1, FALLING);
  
  tft.begin();
  tft.setRotation(1); //Landscape
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.setTextSize(1); //la dimensione va da 1 a 5, di default usa 1

  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  delay(1000);
  if (!bleKeyboard.isConnected()){
    tft.setCursor(0, 30);
    tft.fillScreen(TFT_BLACK);
    tft.print("Press the top button to start the connection");
  }

  if (bleKeyboard.isConnected()){
    tft.setCursor(0, 30);
    tft.fillScreen(TFT_BLACK);
    tft.print("Press the bottom button to start writing");
  }
  
}

void loop() {

  //Serial.println("Test");
  
  int buttonState1, buttonState2;
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);

  if (buttonState1 == LOW )
    toggleButton1();

  if (buttonState2 == LOW && bleKeyboard.isConnected()){
    tft.setCursor(0, 30);
    tft.fillScreen(TFT_BLACK);
    tft.println("Select the palce where to write(you have 5 seconds)");
    delay(5000);
    toggleButton2();
  }

}
