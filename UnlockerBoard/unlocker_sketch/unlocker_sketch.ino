#include <TFT_eSPI.h>
#include <BleKeyboard.h>
#include <DigitalRainAnim.h>
#include "icon.h"

#define BUTTON1PIN 35
#define BUTTON2PIN 0

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
