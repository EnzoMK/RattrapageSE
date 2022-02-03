#include <Arduino.h>
#include "utils.h"


//Couleur de la led pour les modes et les erreurs
void led(void) {
    if (millis() - pdata->led->time < 1000) return;
    switch (pdata->params.MODE) {
    case STANDARD:
        pdata->led->setColorRGB(0, 255, 0);
        break;
    case ECO:
        pdata->led->setColorRGB(0, 0, 255);
        break;
    case MAINTENANCE:
        pdata->led->setColorRGB(255, 140, 0);
        break;
    case CONFIG:
        pdata->led->setColorRGB(255, 255, 255);
        break;
    case ERROR_RTC:
        if (pdata->led->B == 255) {
            pdata->led->setColorRGB(255, 0, 0);
        } else if (pdata->led->R == 255) {
            pdata->led->setColorRGB(0, 0, 255);
        } else {
            pdata->led->setColorRGB(255, 0, 0);
        }
        pdata->led->time = millis();
        break;
    case ERROR_GPS:
        if (pdata->led->R == 255 && pdata->led->G == 255) {
            pdata->led->setColorRGB(255, 0, 0);
        } else if (pdata->led->R == 255 && pdata->led->G == 0) {
            pdata->led->setColorRGB(255, 255, 0);
        } else {
            pdata->led->setColorRGB(255, 0, 0);
        }
        pdata->led->time = millis();
        break;
    case ERROR_SENSOR:
        if (pdata->led->G == 255) {
            pdata->led->setColorRGB(255, 0, 0);
        } else if (pdata->led->R == 255) {
            pdata->led->setColorRGB(0, 255, 0);
        } else {
            pdata->led->setColorRGB(255, 0, 0);
        }
        pdata->led->time = millis();
        break;
    case ERROR_DATA:
        if (pdata->led->G == 255) {
            pdata->led->setColorRGB(255, 0, 0);
        } else if (pdata->led->playing == 1) {
            pdata->led->playing++;
        } else if (pdata->led->R == 255 && pdata->led->playing == 2) {
            pdata->led->setColorRGB(0, 255, 0);
            pdata->led->playing = 1;
        } else {
            pdata->led->setColorRGB(255, 0, 0);
        }
        pdata->led->time = millis();
        break;
    case ERROR_SD_FULL:
        if (pdata->led->G == 255) {
            pdata->led->setColorRGB(255, 0, 0);
        } else if (pdata->led->G == 0) {
            pdata->led->setColorRGB(255, 255, 255);
        } else {
            pdata->led->setColorRGB(255, 0, 0);
        }
        pdata->led->time = millis();
        break;
    case ERROR_SD_RW:
        if (pdata->led->G == 0) {
            pdata->led->setColorRGB(255, 255, 255);
        } else if (pdata->led->playing == 1) {
            pdata->led->playing++;
        } else if (pdata->led->G == 255 && pdata->led->playing == 2) {
            pdata->led->setColorRGB(255, 0, 0);
            pdata->led->playing = 1;
        } else {
            pdata->led->setColorRGB(255, 0, 0);
        }
        pdata->led->time = millis();
        break;
    default:
        pdata->led->setColorRGB(255, 255, 255);
        break;
    }
}