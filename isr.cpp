
#include "utils.h"

//Pr�paration des interruptions lors de l'appuis sur le bouton rouge ou vert
void isr(void) {
    pinMode(BTN_R, INPUT); //Broches des boutons
    pinMode(BTN_V, INPUT);
    attachInterrupt(0, rbtn, CHANGE); //Lorsque le bouton rouge est appuy�, la fonction rbtn est ex�cut�e
    attachInterrupt(1, gbtn, CHANGE); //Lorsque le bouton vert est appuy�, la fonction gbtn est ex�cut�e
}

//Interruption lors du changement d'�tat du bouton rouge
//Calcul du temps d'appuis sur le bouton et changement de mode
void rbtn(void) {
    if (!btn_r(BTN_R)) return;
    if (digitalRead(BTN_R)) {
        if (millis()-pdata->timer.btn_last > 1000 && (pdata->params.MODE == STANDARD || pdata->params.MODE == ECO)) {
            mode_maintenance();
        } else if (millis()-pdata->timer.btn_last > 1000 && (pdata->params.MODE == MAINTENANCE)) {
            mode_standard();
        }
    } else {
        pdata->timer.btn_last = millis();
    }
}

//Interruption lors du changement d'�tat du bouton vert
//Calcul du temps d'appuis sur le bouton et changement de mode
void gbtn(void) {
    if (!btn_r(BTN_V)) return;
    if (digitalRead(BTN_V)) {
        if (millis()-pdata->timer.btn_last > 1000 && pdata->params.MODE == STANDARD) {
            mode_eco();
        } else if (millis()-pdata->timer.btn_last > 1000 && pdata->params.MODE == ECO) {
            mode_standard();
        }
    } else {
        pdata->timer.btn_last = millis();
    }
}

//Change la valeur de l'�tat d'un bouton
bool btn_r(char btn) {
    if (millis()-pdata->timer.btn_time > 100) {
        pdata->timer.btn_time = millis();
        return true;
    } else {
        return false;
    }
}