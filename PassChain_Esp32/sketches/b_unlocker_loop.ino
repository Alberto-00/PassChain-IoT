
void loop(){
  buttonState1 = digitalRead(BUTTON1PIN);
  buttonState2 = digitalRead(BUTTON2PIN);
  int menu = 0;

 /************************
  * menu_module loop *
  ************************/
  menu = mainMenu();

  switch(menu){
    case 0:{
      tft.fillRect(0,25,240,110,TFT_BLACK);
      credentialMenu();
      break;
    }

    case 1:{
      break;
    }

    case 2:{
      break;
    }

    case 3:{
      break;
    }
  }
}
