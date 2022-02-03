
// On inclut les fichiers d'en-tete où l'on a déclarer toutes nos variables, fonction...
#include "utils.h"
#include "eeprom_utils.h"


//Lecture de l'horloge RTC
void rpc_read(void) {
    pdata->now = pdata->rtc.now();
    if (pdata->now.hour() > 24) {
        pdata->params.MODE = ERROR_RTC;
    }
}

//Lecture du capteur de luminosité
void read_lumin(void) {
    if (!EEPROM.read(E_LUMIN)) return;
    signed int value = analogRead(PIN_LUMIN);
    if (value >= 0 && value <= 1023) {
        push_lumin(value);
    } else {
        pdata->params.MODE = ERROR_SENSOR;
    }
}

//Lecture du capteur BME pour la pression, température et hygrométrie
void bme_read(void) {
    BME280 c;
    c.settings.commInterface = I2C_MODE; 
    c.settings.I2CAddress = 0x76;
    c.settings.runMode = 3; 
    c.settings.tStandby = 0;
    c.settings.filter = 0;
    c.settings.tempOverSample = 1 ;
    c.settings.pressOverSample = 1;
    c.settings.humidOverSample = 1;

    c.begin();
    
    read_temp(&c);
    read_hygr(&c);
    read_pressure(&c);
}

void read_temp(BME280 *c) {
    if (!EEPROM.read(E_TEMP)) return;
    signed char value = c->readTempC();
    if (value >= -40 && value <= 85) {
        push_temp(value);
    } else {
        pdata->params.MODE = ERROR_SENSOR;
    }
}

void read_hygr(BME280 *c) {
    if (!EEPROM.read(E_HYGR)) return;
    signed char value = c->readFloatHumidity();
    if (value >= -40 && value <= 85) {
        push_hygr(value);
    } else {
        pdata->params.MODE = ERROR_SENSOR;
    }
}

void read_pressure(BME280 *c) {
    if (!EEPROM.read(E_PRESSURE)) return;
    signed int value = c->readFloatPressure() / 100;
    if (value >= 300 && value <= 1100) {
        push_pressure(value);
    } else {
        pdata->params.MODE = ERROR_SENSOR;
    }
}

// GPS
void readp_gps(void) {
    if (pdata->params.MODE == ECO) {
        pdata->gps = "ECO";
        return;
    }
    SoftwareSerial SoftSerial(5, 6);
    SoftSerial.begin(9600);
    pdata->gps = "ND";
    pdata->timer.timeout = millis();

    while (millis() - pdata->timer.timeout < EEPROM.read(E_TIMEOUT)*1000) {
        if (SoftSerial.available()) { 
            String temp = SoftSerial.readStringUntil('\n');
            if (temp.startsWith("$GPGGA",0)) {
                pdata->gps = temp;
                break;
            }
        }
    }
}
