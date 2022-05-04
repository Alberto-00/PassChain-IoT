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

#define BUTTON1PIN 35
#define BUTTON2PIN 0
#define DEEP_SLEEP T3
#define BLOCKSCREEN_TIME 90000   /* tempo dopo il quale si avvia il block-screen 90s = 1.5min */
#define DEEPSLEEP_TIME 150000   /*  tempo dopo il quale si avvia il deep-sleep sommato al deep-sleep (90000 + 150000) = 240s = 4min */

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
TFT_eSPI tft_battery = TFT_eSPI();
TFT_eSPI tft_logo = TFT_eSPI();
TFT_eSPI tft_bold = TFT_eSPI();

BleKeyboard bleKeyboard;
StaticJsonDocument<6144> doc;
DigitalRainAnim digitalRainAnim = DigitalRainAnim();
Credential credentials[80];
touch_pad_t touchPin;
File authFile;

Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);
char *batteryImages[ARRAY_SIZE] = {"battery/battery_01", "battery/battery_02", "battery/battery_03", "battery/battery_04", "battery/battery_05"};
TaskHandle_t TaskHandle_2;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

int buttonState1, buttonState2;
bool connection_status = false;
unsigned long start_time;
unsigned long stop_time;
unsigned int sizeJson;


/*******************************
 * functions bluetooth_module  *
 *******************************/
void check_connection();
void write_button(String, String);


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
