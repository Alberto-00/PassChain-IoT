#include <TFT_eSPI.h>
#include <BleKeyboard.h>
#include <DigitalRainAnim.h>
#include "logo.h"

#define BUTTON1PIN 35
#define BUTTON2PIN 0
#define DEEP_SLEEP T3
#define BLOCKSCREEN_TIME 90000   /* tempo dopo il quale si avvia il block-screen 90s = 1.5 min */
#define DEEPSLEEP_TIME 150000   /*  tempo dopo il quale si avvia il deep-sleep sommato al deep-sleep (90000 + 150000) = 240s = 4min */

#define uS_TO_S_FACTOR 1000000 /* Fattore di conversione da microsecondi a secondi */
#define TIME_TO_SLEEP 30       /* Tempo prima del quale scheda vada in deep_sleep_mode (in secondi) */
#define Threshold 40


/********************
 * Inizializzazione *
 ********************/
TFT_eSPI tft = TFT_eSPI();
BleKeyboard bleKeyboard;
DigitalRainAnim digitalRainAnim = DigitalRainAnim();
touch_pad_t touchPin;

 
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
bool isInactive_device(unsigned long);
void blockScreen();
void restart_time();


/*******************************
 * functions deepSleep_module *
 *******************************/
void wakeup_deepSleep();
void deepSleep();


int buttonState1, buttonState2;
bool connection_status = false;
unsigned long start_time;
unsigned long stop_time;
