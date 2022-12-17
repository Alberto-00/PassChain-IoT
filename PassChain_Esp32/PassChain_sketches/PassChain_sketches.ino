#include <TFT_eSPI.h>
#include <BleKeyboard.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <DigitalRainAnim.h>
#include <Adafruit_Fingerprint.h>
#include <Pangodream_18650_CL.h>
#include "logo/logo.h"
#include "logo/home.h"
#include "logo/wifi.h"
#include "logo/success.h"
#include "logo/error.h"
#include "logo/bluetooth.h"
#include "battery/battery_01.h"
#include "battery/battery_02.h"
#include "battery/battery_03.h"
#include "battery/battery_04.h"
#include "battery/battery_05.h"
#include "battery/battery_low.h"
#include "Credential.h"
#include "WiFiClientSecure.h"
#include "Cipher.h"

//#include "esp_gap_ble_api.h" //forse non serve**************

//For restart esp ESP.restart();


#define BUTTON1PIN 35
#define BUTTON2PIN 0
#define DEEP_SLEEP T3
#define BLOCKSCREEN_TIME 120000   /* tempo dopo il quale si avvia il block-screen 120s = 2min */
#define DEEPSLEEP_TIME 150000   /*  tempo dopo il quale si avvia il deep-sleep sommato al deep-sleep (120000 + 150000) = 270s = 4.5m */

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
TFT_eSPI tft_lightText = TFT_eSPI();

BleKeyboard bleKeyboard;
StaticJsonDocument<12288> doc;
StaticJsonDocument<128> wifi_config;
DigitalRainAnim digitalRainAnim = DigitalRainAnim();
Credential credentials[100];
touch_pad_t touchPin;
File authFile, WiFiFile;
Cipher* cipher = new Cipher();

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

const char* hostname = "example.org";
unsigned int port = 11111;
WiFiClientSecure client(hostname);

const char* test_root_ca = \
                           "-----BEGIN CERTIFICATE-----\n" \
                           "MIID4jCCAsqgAwIBAgIUbenEW900x1q5XiVRI3szwnzNBSkwDQYJKoZIhvcNAQEL\n" \
                           "BQAwgYYxCzAJBgNVBAYTAml0MQswCQYDVQQIDAJpdDELMAkGA1UEBwwCaXQxFDAS\n" \
                           "BgNVBAoMC2V4YW1wbGUub3JnMRQwEgYDVQQLDAtleGFtcGxlLm9yZzEUMBIGA1UE\n" \
                           "AwwLZXhhbXBsZS5vcmcxGzAZBgkqhkiG9w0BCQEWDGdhQGdtYWlsLmNvbTAeFw0y\n" \
                           "MjEyMDkyMDU0MzlaFw0yMzEyMDkyMDU0MzlaMIGGMQswCQYDVQQGEwJpdDELMAkG\n" \
                           "A1UECAwCaXQxCzAJBgNVBAcMAml0MRQwEgYDVQQKDAtleGFtcGxlLm9yZzEUMBIG\n" \
                           "A1UECwwLZXhhbXBsZS5vcmcxFDASBgNVBAMMC2V4YW1wbGUub3JnMRswGQYJKoZI\n" \
                           "hvcNAQkBFgxnYUBnbWFpbC5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n" \
                           "AoIBAQC8/ZiExCt3m9vcD3iRGINWysb6WuvTHMB+sI59cxBG2jUY2mOUiRNeTOKU\n" \
                           "8IKNna3fqdBADQIzIMsXERKh1i7rGP8MoxOzblB6s3kNw8+7ukUrxi/8RBEjMZDD\n" \
                           "6hS1w4Ar/NUfUz22AFrPEno00NqSLEk9/4jeaEvyFMEO0S1L0TmhmV/E/21APwm8\n" \
                           "KZB0AL7MJLQP7j4iDFg37OoULq7uTexaqRvPofvDa040LTRC9r8NkAJXxhaTPgGv\n" \
                           "glIJW/dkFQ7O67zn2+5kdLb6uqugk1AykZXZWnrjRnLswLl7xwdJp2vU8k1+HtCy\n" \
                           "R/2hFDWVP4VVVi+OsNm1fJr1Yk9nAgMBAAGjRjBEMB8GA1UdIwQYMBaAFFZznupu\n" \
                           "uIjUbe5FDjRvT3XdruuQMAkGA1UdEwQCMAAwFgYDVR0RBA8wDYILZXhhbXBsZS5v\n" \
                           "cmcwDQYJKoZIhvcNAQELBQADggEBADAORO3n5PSTvYN06oe1L2pnXO0XyD1bWyrU\n" \
                           "QEdxlu1CQvj3g7YNztKfwQ8tcCFKK1JkRboZ8GPVJIlw/MSxJha7pLy69Y68Wtgz\n" \
                           "fzJsHYcMPHEtjXnRVsbfYKF6vYBCUUvw6QGGsc07NsNZ//jPt2WUzTY8XvG/CFD7\n" \
                           "rJbPjeridcll5e9mSBiBxhSIs4/4cgwHbhXhHD4pPMuk1XB6Yb1xx7P7T2+2mNg2\n" \
                           "6knD8QoS6u1StfwVgkGNXrocqfam1/dK8UOwiqfQ+6WWA8LEVAr3ABS3zRTJNkXx\n" \
                           "bKSKBJAdqSRJ8aapbpKKL4CjdZu1+pu5uFR+ZYHo+73790OdVJY=\n" \
                           "-----END CERTIFICATE-----\n";


// You can use x.509 client certificates if you want
const char* test_client_key = \
                              "-----BEGIN RSA PRIVATE KEY-----\n" \
                              "MIIEpQIBAAKCAQEA21VzTHsxzVYiJyzXp1nUXV9KJPPa0zxLGXi1u7X+JSroHby5\n" \
                              "gpckZRfcZ8A6QmiU6oSV7Kw/LvGR0VjuFrPmyq2UY35c67jcuFgtqr0lcNueFFZE\n" \
                              "5VsJZYvEBwyQt1PEPcKAOU5vv6BgTwAWAoR2fnLen5+MLs+Pg6nh4tb4JBTji+n6\n" \
                              "vWoKrjjV16AQYtpmmO7yYU6AdkOWrUuBcSiIuctnROHa9nFuieY42R05HO1nuPnH\n" \
                              "SSCtnKf5DFQtS3xIAxvKhUCONxoPZ+dEpCVK3bQhPtShKyvY2cKti6CEFFJKP+/H\n" \
                              "UfrJWmlm5Cl37MV9f6FcogEpPHV31PFvuAYBwwIDAQABAoIBACyWm4DhzocKypii\n" \
                              "MhkQVu7Ab2dBt6uXp0C/XFqTrd3KcjORaTkWFs0CY8knt/BGKHfgikX54kJd06H2\n" \
                              "bThqTDHJxc/QIX2+MAi9zFLYbuMZknJZ81mY/zkIh8pTEJxkSBGyF7UOsAMJzGpi\n" \
                              "/xZ17UzZd06F9c6SXX+LqqMdxoY25IGBfe/Vi/1rqOgbPFig7UYccSHqcuNbpjnb\n" \
                              "ZoSgClY9sXvqV9notvsC5tYAAMNElBmKJ1KnAVY9jn7cO25Rhkh4aTkxI+Nop+H3\n" \
                              "ZnYNgX+JzmrlBiVFaYBrA5A2E6HCYRw3DeTWRX/fa7+9KCRzdWWnT/oRB4g2SHK1\n" \
                              "3UHS5uECgYEA9P813g7prATyn5lWLTZsKf4I2f7dzeaUFiShIScMOs3Ie8Nf9RE+\n" \
                              "NILk3zoVo7QGjsHJQ4jJng8x3CY+ZOilxz8DxnqPTnjVab3QuupRxH/5gB4WWs1M\n" \
                              "1w+XMDL/YkP5Gl7nv+oVovubhOSoC3Zrl+JqScAJrlx4Iwe7yrr7sVMCgYEA5S8v\n" \
                              "Skqh4kirJDR8faAeRCfiSTjPQfwkrrd67Wc13GUaYvjuaLSYQryqRWi2VBLtgg3q\n" \
                              "dbV/H7767mjxmHQc6fyhQSIvaZUtH1wNCaF2YTQkY5aePizrihp6bL1+zE+M/i2K\n" \
                              "uf26yzZM/x/xLgV9lPeRssM0HFVC+PlIUm2UL9ECgYEA27+Z8n5Py7J4aPzhVhZt\n" \
                              "eFDaYaYADvIVu7LJL/JVPt1bSN9aT3dS40jQvwTbagVMqHla7A9iQDqCz2MiLeKa\n" \
                              "55c27Kz7ozgwu/K8qRsJkoXzJZ5XEMT6eiAKzPnBJcOwSJ39op71H0YtHUr3C6kB\n" \
                              "Iq+8BECSrmlUfJ8wKswCe+8CgYEAjYq9nxlGr3UH1V1hAUkRSDCFrYkbX3o0wX7p\n" \
                              "uZMDjbEXQcbRnvLiEl1on2NTL8tcyfSEN9w2vcl6OiGwC+KyNMRkZtCRDZkm+/Yi\n" \
                              "yy7f6JqGWscbxfSCJ5HAyEWj+NSslBJWWhXc9kH7/ZihoDWd4JGhdxDdrx3tNczn\n" \
                              "IJkyavECgYEApzdrYvSk+ZwBkfHvo9Z3t7gV9BIsZJG5SZZ/pAgFryBmdVIPTcmV\n" \
                              "mcQLz7DEDP8IKsyGdoqOMwKTvBoxLwvEym1ICFwIzVG2hM8Kzr/Uui6LGKda8TXk\n" \
                              "xcDqZuDxfbwW4EHzIU/ZNb+v5dQYB9GrwmLd/x3i9hZo/lVSd9/aIXc=\n" \
                              "-----END RSA PRIVATE KEY-----\n";


const char* test_client_cert = \
                               "-----BEGIN CERTIFICATE-----\n" \
                               "MIID1jCCAr6gAwIBAgIUE7dBt+qr7xJqsGNjxeQZN0N3EjkwDQYJKoZIhvcNAQEL\n" \
                               "BQAwgYYxCzAJBgNVBAYTAml0MQswCQYDVQQIDAJpdDELMAkGA1UEBwwCaXQxFDAS\n" \
                               "BgNVBAoMC2V4YW1wbGUub3JnMRQwEgYDVQQLDAtleGFtcGxlLm9yZzEUMBIGA1UE\n" \
                               "AwwLZXhhbXBsZS5vcmcxGzAZBgkqhkiG9w0BCQEWDGdhQGdtYWlsLmNvbTAeFw0y\n" \
                               "MjEyMTMxMDU5NTNaFw0yMzEyMTMxMDU5NTNaMHwxCzAJBgNVBAYTAml0MQswCQYD\n" \
                               "VQQIDAJpdDELMAkGA1UEBwwCaXQxITAfBgNVBAoMGEludGVybmV0IFdpZGdpdHMg\n" \
                               "UHR5IEx0ZDETMBEGA1UEAwwKY2xpZW50Lm9yZzEbMBkGCSqGSIb3DQEJARYMZ2FA\n" \
                               "Z21haWwuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA21VzTHsx\n" \
                               "zVYiJyzXp1nUXV9KJPPa0zxLGXi1u7X+JSroHby5gpckZRfcZ8A6QmiU6oSV7Kw/\n" \
                               "LvGR0VjuFrPmyq2UY35c67jcuFgtqr0lcNueFFZE5VsJZYvEBwyQt1PEPcKAOU5v\n" \
                               "v6BgTwAWAoR2fnLen5+MLs+Pg6nh4tb4JBTji+n6vWoKrjjV16AQYtpmmO7yYU6A\n" \
                               "dkOWrUuBcSiIuctnROHa9nFuieY42R05HO1nuPnHSSCtnKf5DFQtS3xIAxvKhUCO\n" \
                               "NxoPZ+dEpCVK3bQhPtShKyvY2cKti6CEFFJKP+/HUfrJWmlm5Cl37MV9f6FcogEp\n" \
                               "PHV31PFvuAYBwwIDAQABo0UwQzAfBgNVHSMEGDAWgBRWc57qbriI1G3uRQ40b091\n" \
                               "3a7rkDAJBgNVHRMEAjAAMBUGA1UdEQQOMAyCCmNsaWVudC5vcmcwDQYJKoZIhvcN\n" \
                               "AQELBQADggEBAF3jyMFSTztahBHPG/+FFYDJHcUVjZn5ZbeykEqzMnNiSaT9Ocf/\n" \
                               "yR+dCOjxV8dB1X9o7BIrjb4RS55S55FxmEL8+jLczKdkLwnWumQKDW6ObFecNJ2k\n" \
                               "q/MP3I6jWOLJmCfIHmNNNsaJYSfAAi1sOPi2F/PuoyI6Yg+oiTbeTINjhWIorUke\n" \
                               "fJMueTDwBb1nXcC5wFI2A943lCKLD0dUCpCBnwb2SciaNKaMHplfUZcDGTxDlZRC\n" \
                               "mYhISMFYFUel5hDP6y3HacfFAhCJpJ0V3D8u4qaGcBZCPmQpcB98hfHHlPL0kLD5\n" \
                               "cNxNs1NZ0k5xhUuS/pCbQ/nSVJauUKB54n4=\n" \
                               "-----END CERTIFICATE-----\n";


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
bool load_R_WiFiConfigFile();
void read_WiFiFile();
bool close_WiFiFile();
void accessPoint_start();
 

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
bool write_credentialsFile(char*, String, String);
bool update_credentialsFile(char *, char*, char*, char*);
bool remove_credentialsFile(char*);
void updateArray(int);
int subMenuCredentials();


/********************************
 * functions fingerprint_module *
 ********************************/
void fingerprint_setup();
void fingerprint_info();
bool fingerprint_enroll();
void fingerprint_deleteAll();
void fingerprint_delete();
bool fingerprint_match();


/**************************
 *  functions menu_module *
 **************************/
int mainMenu();
void credentialsMenu();
void sendUsername(bool *, String);
void sendPassword(bool *, String);
int scrollText(String, String, bool, bool, bool *);
int verify_Ble_FingerPrint(bool *);


/***************************
 * functions server_module *
 ***************************/
bool connectionToServer();
void startCommunicationToServer(String);
void stopConnectionToServer();
void update_credentials(int, String);
