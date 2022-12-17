
void loop(){
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);
  int menu = 0;

 /************************
  * menu_module loop *
  ************************/
  menu = mainMenu();
  tft.fillRect(0,25,240,110,TFT_BLACK);

  switch(menu){
    case 0:{
      bleKeyboard.begin();
      credentialsMenu();
      break;
    }

    case 1:{
      break;
    }

    case 2:{
      
      break;
    }

    case 3:{
      tft.fillRect(0,25,240,110,TFT_BLACK);
      accessPoint_start();
      break;
    }
  }
}
