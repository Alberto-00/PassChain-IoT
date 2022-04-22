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

int buttonState1 = digitalRead(BUTTON1PIN);
int buttonState2 = digitalRead(BUTTON2PIN);


/*******************************
 * functions - global variables *
 *      bluetooth_module       *
 *******************************/
void check_connection();
void write_button();

bool connection_status = false;


/*******************************
 * functions blockScreen_module *
 *******************************/
bool isInactive_device();
void blockScreen();
