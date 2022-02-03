#include <Arduino.h>
#include "utils.h"
#include <SD.h>
#include "eeprom_utils.h"

//Initialisation de la carte SD
void logger_init(void) {
    File log_file;
    if (!SD.begin(PIN_SD)) {
        pdata->params.MODE = ERROR_SD_RW;
        return;
    }
    if (!SD.exists(F("instant.log"))) {
        log_file = SD.open(F("instant.log"), FILE_WRITE);
        log_file.println(F("Time, Temperature, Luminosity, Humidity, Pressure"));
        log_file.close();
    } else {
        log_file = SD.open(F("INSTANT.LOG"), FILE_READ);
        if (log_file.size() * 1+(5/100) >= eeprom_read_int(E_FILE_MAX_SIZE, false)) logger_archive();
        log_file.close();
    }
}

//Archiver les données de la carte SD
void logger_archive(void) {
    File log_file;
    File archive;
    log_file = SD.open(F("instant.log"), FILE_READ);
    archive = SD.open("archive.log", FILE_WRITE);
    size_t n;  
    uint8_t buf[64];
    while ((n = log_file.read(buf, sizeof(buf))) > 0) {
        archive.write(buf, n);
    }
    archive.close();
    log_file.close();
    SD.remove(F("instant.log"));
}

//Ajout des données dans la carte SD
void logger_push(void) {
    if (pdata->params.MODE == MAINTENANCE) return;
    File log_file;
    logger_init();
    if (pdata->params.MODE == ERROR_SD_RW || pdata->params.MODE == ERROR_SD_FULL) return;
    log_file = SD.open(F("instant.log"), FILE_WRITE);
    log_file.print(pdata->now.day());
    log_file.print(F("/"));
    log_file.print(pdata->now.month());
    log_file.print(F("/"));
    log_file.print(pdata->now.year());
    log_file.print(F(" "));
    log_file.print(pdata->now.hour());
    log_file.print(F(":"));
    log_file.print(pdata->now.minute());
    log_file.print(F(":"));
    log_file.print(pdata->now.second());
    log_file.print(F(" | Temperature : "));
    log_file.print(pdata->mesure.temp[0]);
    log_file.print(F("°C | Humidity : "));
    log_file.print(pdata->mesure.hygr[0]);
    log_file.print(F("% | Luminosity : "));
    log_file.print(pdata->mesure.lumin[0]);
    log_file.print(F("lm | Pressure : "));
    log_file.print(pdata->mesure.pressure[0]);
    log_file.print(F("hPa"));

    log_file.println("");
    log_file.close();
}
