// On inclut les bibliothèques
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include <ChainableLED.h>

// On inclut nos bibliothèques pour la communication SPI et avec la carte SD
#include <SPI.h>
#include <SD.h>

// Inclusion des bibliothèques pour le capteur BME280(Pression, Température, Humidité)
#include <BME280I2C.h>
#include <Wire.h>

// Inclusion de la bibliothèque pour le capteur RTC
#include "DS1307.h"

// Inlcusion de la bibliothèque pour le capteur GPS
#include <SoftwareSerial.h>

// On inclut le fichier d'en-tete qui definit les numeros de ports
#include "pin.h"

#define PROG_VERSION 2

// Permet d'énumérer et de creer une enumération de constante
typedef enum mode {
    STANDARD,
    ECO,
    MAINTENANCE,
    CONFIG,
    ERROR_RTC,
    ERROR_GPS,
    ERROR_SENSOR,
    ERROR_DATA,
    ERROR_SD_FULL,
    ERROR_SD_RW
} mode;

//Permet de creer les constante pour les 4 données mesurées
enum sensor {
    LUMIN,
    TEMP,
    HYGR,
    PRESSURE
};

// Structure qui permet de creer la variable pour les modes
struct params {
    char MODE;
};

// Structure pour stocker les données
struct mesure {
    signed int lumin[10];
    signed char temp[10];
    signed char hygr[10];
    signed int pressure[10];
};

// Structure pour gerer les interuptions
struct timer {
    unsigned long btn_last;
    unsigned long btn_time;
    unsigned long log_interval;
    unsigned long config;
    unsigned long timeout;
};

// liste chainée 
typedef struct data {
    struct params params;
    struct timer timer;
    struct mesure mesure;
    ChainableLED *led;
    RTC_DS1307 rtc;
    DateTime now;
    String gps;
} data;

//interruptions des deux boutons
void isr(void);
void rbtn(void);
void gbtn(void);
bool btn_r(char btn);

// Lecture des capteurs
void rpc_read(void);
void read_lumin(void);
void bme_read(void);
void read_temp(BME280 *c);
void read_hygr(BME280 *c);
void read_pressure(BME280 *c);
void readp_gps(void);

// Ces fonctions permettent de changer les paramètres dans la struct param
void mode_standard(void);
void mode_eco(void);
void mode_maintenance(void);
void maintenance_console(void);
bool mode_config_check(void);
void mode_config_time(void);

// Clignotement de la LED en fonction du mode ou des erreurs
void led(void);
void led_error(void);

// Manipulation des données
void create_data(void);
void init_data(void);
void push_lumin(signed int value);
void push_temp(signed char value);
void push_hygr(signed char value);
void push_pressure(signed int value);

// Gestion de la carte SD
void logger_init(void);
void logger_archive(void);
void logger_push(void);

//déclaration du pointeur pdata utiliser dans d'autres fichier
extern data *pdata;