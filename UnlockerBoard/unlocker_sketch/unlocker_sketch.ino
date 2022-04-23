#include <TFT_eSPI.h>
#include <BleKeyboard.h>
#include <DigitalRainAnim.h>
#include "logo.h"

#define BUTTON1PIN 35
#define BUTTON2PIN 0

/********************
 * Inizializzazione *
 ********************/
TFT_eSPI tft = TFT_eSPI();
BleKeyboard bleKeyboard;
DigitalRainAnim digitalRainAnim = DigitalRainAnim();

 
/*******************************
 * functions - global variables *
 *      bluetooth_module       *
 *******************************/
void check_connection();
void write_button();


/*******************************
 * functions blockScreen_module *
 *******************************/
void check_inactivity_device();
bool isInactive_device();
void blockScreen();
void restart_time();

int buttonState1, buttonState2;
bool connection_status = false;
bool isInactive = false;
unsigned long start_time;
unsigned long stop_time;
