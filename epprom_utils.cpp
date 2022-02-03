// On inclut les biblioth�ques
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include <ChainableLED.h>

// On inclut nos biblioth�ques pour la communication SPI et avec la carte SD
#include <SPI.h>
#include <SD.h>

#include <EEPROM.h>
#include "utils.h"
#include "eeprom_utils.h"


//R�initialiser l'EEPROM avec les donn�es par d�faut :


void eeprom_reset(void) {
    EEPROM.write(E_LUMIN, 1);
    EEPROM.write(E_TEMP, 1);
    EEPROM.write(E_HYGR, 1);
    EEPROM.write(E_PRESSURE, 1);
    EEPROM.write(E_LOG_INTERVAL, 10);
    EEPROM.write(E_TIMEOUT, 30);
    EEPROM.write(E_VERSION, PROG_VERSION);
    EEPROM.write(E_HYGR_MINT, 0);
    EEPROM.write(E_HYGR_MAXT, 50);
    eeprom_write_int(E_FILE_MAX_SIZE, 2048);
    eeprom_write_int(E_LUMIN_LOW, 255);
    eeprom_write_int(E_LUMIN_HIGH, 768);
    eeprom_write_int(E_MIN_TEMP_AIR, -10);
    eeprom_write_int(E_MAX_TEMP_AIR, 60);
    eeprom_write_int(E_PRESSURE_MIN, 850);
    eeprom_write_int(E_PRESSURE_MAX, 1080);
}


//�crire un entier dans l'EEPROM
//param addr -> Adresse m�moire EEPROM
//param n -> Valeur � �crire


void eeprom_write_int(int addr, int n) {
    unsigned char byte1 = n & 0xFF;
    unsigned char byte2 = n >> 8 & 0xFF;
    EEPROM.write(addr, byte1);
    EEPROM.write(addr+1, byte2);
}


//Lire un entier sign� ou non sign� � partir de l'EEPROM
//param addr -> Adresse m�moire EEPROM
//param s -> Vrai sign� | Faux non sign�
//return int -> valeur enti�re


int eeprom_read_int(int addr, bool s) {
    unsigned char byte1 = EEPROM.read(addr);
    unsigned char byte2 = EEPROM.read(addr+1);
    if (s) {
        signed int n_u = (byte2 << 8) + byte1;
        return n_u;
    } else {
        unsigned int n_s = (byte2 << 8) + byte1;
        return n_s;
    }
}