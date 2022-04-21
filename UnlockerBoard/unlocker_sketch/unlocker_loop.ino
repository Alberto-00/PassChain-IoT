
void loop(){  
 /*************************
  * standbyImage_module loop *
  *************************/
  /*if(){
    digitalRainAnim.loop(); 
  }*/


 /*************************
  * bluetooth_module loop *
  *************************/
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
