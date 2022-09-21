#include <TFT_eSPI.h>
#include <BleKeyboard.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <DigitalRainAnim.h>
#include <Adafruit_Fingerprint.h>
#include <Pangodream_18650_CL.h>
#include "logo/logo.h"
#include "logo/home.h"
#include "battery/battery_01.h"
#include "battery/battery_02.h"
#include "battery/battery_03.h"
#include "battery/battery_04.h"
#include "battery/battery_05.h"
#include "battery/battery_low.h"
#include "Credential.h"
#include "esp_gap_ble_api.h"
#include "WiFi.h"

#define BUTTON1PIN 35
#define BUTTON2PIN 0
#define DEEP_SLEEP T3
#define BLOCKSCREEN_TIME 120000   /* tempo dopo il quale si avvia il block-screen 120s = 2min */
#define DEEPSLEEP_TIME 150000   /*  tempo dopo il quale si avvia il deep-sleep sommato al deep-sleep (120000 + 150000) = 270s = 4.5m*/

#define uS_TO_S_FACTOR 1000000 /* Fattore di conversione da microsecondi a secondi */
#define TIME_TO_SLEEP 30       /* Tempo prima del quale scheda vada in deep_sleep_mode (in secondi) */
#define Threshold 40

#define MIN_USB_VOL 4.50
#define ADC_PIN 34
#define CONV_FACTOR 1.8
#define READS 20
#define ARRAY_SIZE 5

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif


/****************************
 *     Global Variables     *
 ****************************/
TFT_eSPI tft = TFT_eSPI();
TFT_eSPI tft_menu = TFT_eSPI();
TFT_eSPI tft_battery = TFT_eSPI();
TFT_eSPI tft_logo = TFT_eSPI();
TFT_eSPI tft_bold = TFT_eSPI();
TFT_eSPI tft_credentials = TFT_eSPI();

BleKeyboard bleKeyboard;
StaticJsonDocument<12288> doc;
DigitalRainAnim digitalRainAnim = DigitalRainAnim();
Credential credentials[100];
touch_pad_t touchPin;
File authFile;

Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);
char *batteryImages[ARRAY_SIZE] = {"battery/battery_01", "battery/battery_02", "battery/battery_03", "battery/battery_04", "battery/battery_05"};
TaskHandle_t TaskHandle_2;
double _vs[100] = {3.505, 3.510, 3.515, 3.520, 3.525, 3.530, 3.540, 3.550, 3.600, 3.650, 3.700,
                3.703, 3.706, 3.710, 3.713, 3.716, 3.719, 3.723, 3.726, 3.729, 3.732, 3.735, 
                3.739, 3.742, 3.745, 3.748, 3.752, 3.755, 3.758, 3.761, 3.765, 3.768, 3.771, 
                3.774, 3.777, 3.781, 3.784, 3.787, 3.790, 3.794, 3.797, 3.800, 3.805, 3.811, 
                3.816, 3.821, 3.826, 3.832, 3.837, 3.842, 3.847, 3.853, 3.858, 3.863, 3.868, 
                3.874, 3.879, 3.884, 3.889, 3.895, 3.900, 3.906, 3.911, 3.917, 3.922, 3.928, 
                3.933, 3.939, 3.944, 3.950, 3.956, 3.961, 3.967, 3.972, 3.978, 3.983, 3.989, 
                3.994, 4.000, 4.008, 4.015, 4.023, 4.031, 4.038, 4.046, 4.054, 4.062, 4.069, 
                4.077, 4.085, 4.092, 4.100, 4.111, 4.122, 4.133, 4.144, 4.156, 4.167, 4.178, 
                4.200};

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

int buttonState1, buttonState2;
bool connection_status = false;
unsigned long start_time;
unsigned long stop_time;
unsigned int sizeJson;


/*******************************
 *  functions battery_module   *
 *******************************/
int getBatteryLevel();


/*******************************
 * functions bluetooth_module  *
 *******************************/
void check_connection();
void write_button(String, String);
void sendSequence(String);


/**************************
 * functions WiFi_module  *
 **************************/
 void scanWiFi();
 

/********************************
 * functions blockScreen_module *
 ********************************/
bool check_inactivity_device();
bool isInactive_device(unsigned long);
void blockScreen();
void restart_time();


/*******************************
 * functions deepSleep_module  *
 *******************************/
void wakeup_deepSleep();
void deepSleep();


/********************************
 * functions credentials_module *
 ********************************/
bool load_R_credentialsFile();
bool load_W_credentialsFile();
bool close_credentialsFile();
void read_credentialsFile();
bool write_credentialsFile(char*, char*, char*, char*);
bool update_credentialsFile(char *, char*, char*, char*, char*);
bool remove_credentialsFile(char*);
void updateArray(int);
int menuList();


/********************************
 * functions fingerprint_module *
 ********************************/
void fingerprint_setup();
void fingerprint_info();
bool fingerprint_enroll();
void fingerprint_deleteAll();
void fingerprint_delete();
bool fingerprint_match();


/******************************
 *  functions menu_module *
 ******************************/
int mainMenu();
void credentialMenu();
