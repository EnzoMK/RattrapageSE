#include "eeprom_utils.h"
#include "utils.h"


//Allocation de structure de données 
 

void create_data(void) {
    pdata = malloc(sizeof(data));
    init_data();
}


//La structure de données définit la valeur par défaut


void init_data(void) {
    // LED
    pdata->led = new ChainableLED(PIN_RGB1, PIN_RGB2, 0);
    pdata->led->time = 0;
    pdata->led->playing = 1;
    // Mesure
    for (int i = 0; i < 10; i++) {
        pdata->mesure.temp[i] = 0;
        pdata->mesure.hygr[i] = 0;
        pdata->mesure.pressure[i] = 0;
        pdata->mesure.lumin[i] = 0;
    }
    // Bouton
    pdata->timer.btn_last = 0;
    pdata->timer.btn_time = 0;
    pdata->timer.log_interval = 0;
    pdata->timer.config = 0;
    pdata->timer.timeout = 0;
}


//Enregistre mesure de luminosité
//Avec la valeur en parametre 


void push_lumin(signed int value) {
    int i = 0;
    for (; i < 9; i++) {
        pdata->mesure.lumin[i+1] = pdata->mesure.lumin[i];
    }
    pdata->mesure.lumin[0] = value;
}


//Enregistre mesure de température
//Avec la valeur en parametre
 

void push_temp(signed char value) {
    int i = 0;
    for (; i < 9; i++) {
        pdata->mesure.temp[i+1] = pdata->mesure.temp[i];
    }
    pdata->mesure.temp[0] = value;
}


//Enregistre mesure d'hygrométrie
//Avec la valeur en parametre
 

void push_hygr(signed char value) {
    int i = 0;
    for (; i < 9; i++) {
        pdata->mesure.hygr[i+1] = pdata->mesure.hygr[i];
    }
    pdata->mesure.hygr[0] = value;
}


//Enregistre mesure de la pression
//Avec la valeur en parametre


void push_pressure(signed int value) {
    int i = 0;
    for (; i < 9; i++) {
        pdata->mesure.pressure[i+1] = pdata->mesure.pressure[i];
    }
    pdata->mesure.pressure[0] = value;
}