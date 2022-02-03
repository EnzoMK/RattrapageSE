
#include "utils.h"

void mode_standard(void) {
    pdata->params.MODE = STANDARD;
}

void mode_eco(void) {
    pdata->params.MODE = ECO;
}

void mode_maintenance(void) {
    pdata->params.MODE = MAINTENANCE;
}

void maintenance_console(void) {
    Serial.print(pdata->now.day());
    Serial.print(F("/"));
    Serial.print(pdata->now.month());
    Serial.print(F("/"));
    Serial.print(pdata->now.year());
    Serial.print(F(" "));
    Serial.print(pdata->now.hour());
    Serial.print(F(":"));
    Serial.print(pdata->now.minute());
    Serial.print(F(":"));
    Serial.print(pdata->now.second());
    Serial.print(F(" | Temperature : "));
    Serial.print(pdata->mesure.temp[0]);
    Serial.print(F("°C | Humidity : "));
    Serial.print(pdata->mesure.hygr[0]);
    Serial.print(F("% | Luminosity : "));
    Serial.print(pdata->mesure.lumin[0]);
    Serial.print(F("lm | Pressure : "));
    Serial.print(pdata->mesure.pressure[0]);
    Serial.print(F("hPa | GPS : "));
    Serial.print(pdata->gps);

    Serial.println("");
}


//Mode configuration si le bouton rouge est enfoncé au démarrage
//Renvoie True s'il est activée
//Renvoie False s'il n'est pas activée
 

bool mode_config_check(void) {
    long time = millis();
    while (!digitalRead(BTN_R));
    if (digitalRead(BTN_R) && millis() - time > 500) {
        pdata->params.MODE = CONFIG;
        pdata->timer.config = millis();
        return true;
    }
    return false;
}


//Désactiver le mode configuration après 30 minutes


void mode_config_time(void) {
    if (millis() - pdata->timer.config  > 60L*30L*1000L) mode_standard();
}