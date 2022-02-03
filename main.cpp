// On inclut les fichiers d'en-tete où l'on a déclarer toutes nos variables, fonction...
#include "utils.h"
#include "eeprom_utils.h"

//appel du pointeur data de la liste chainée
data *pdata;

//Boucle executée au démarrage (Préparation horloge, préparation interruption)
void setup() {
  Serial.begin(9600);
  create_data();
  isr();
  pdata->rtc.begin();
  if (!mode_config_check()) mode_standard();
  pdata->rtc.adjust(DateTime(2022, 01, 10, 9, 48, 0)); 
}

//Boucle où s'exécute les actions de chaque mode 
void loop() {
  led();
  if (pdata->params.MODE == STANDARD || pdata->params.MODE == ECO || pdata->params.MODE == MAINTENANCE) {
    long log_interval = EEPROM.read(E_LOG_INTERVAL) * 100;
    if (pdata->params.MODE == ECO) log_interval /= 2;
    if (pdata->params.MODE == MAINTENANCE) log_interval /= 1000;
    if (millis() - pdata->timer.log_interval > log_interval) {
      rpc_read();
      read_lumin();
      bme_read();
      readp_gps();
      logger_push();
      if (pdata->params.MODE == MAINTENANCE) maintenance_console();
      pdata->timer.log_interval = millis();
    }
  } else {
    mode_config_time();
  }
}