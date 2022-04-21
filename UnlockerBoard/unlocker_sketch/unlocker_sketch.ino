#include <TFT_eSPI.h>
#include <BleKeyboard.h>
#include <DigitalRainAnim.h>
#include "icon.h"

#define BUTTON1PIN 35
#define BUTTON2PIN 0

#define uS_TO_S_FACTOR 1000000  /* Fattore di conversione da microsecondi a secondi*/
#define TIME_TO_SLEEP  30       /* Tempo prima del quale scheda vada in deep_sleep_mode (in secondi)*/

TFT_eSPI tft = TFT_eSPI();
BleKeyboard bleKeyboard;
DigitalRainAnim digitalRainAnim = DigitalRainAnim();



/*******************************
 * function - global variables *
 *      bluetooth_module       *
 *******************************/
void check_connection();
void write_button();

bool connection_status = false;
