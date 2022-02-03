
// Valeur des paramètres enregistré dans l'EEPROM

//CHAR

#ifndef E_LUMIN

#define E_LUMIN 1
#define E_TEMP 1
#define E_HYGR 1
#define E_PRESSURE 1

#define E_LOG_INTERVAL 10
#define E_TIMEOUT 30
#define E_VERSION 2

#define E_HYGR_MINT 0
#define E_HYGR_MAXT 50

//INT

#define E_FILE_MAX_SIZE 4096
#define E_LUMIN_LOW 255
#define E_LUMIN_HIGH 768
#define E_MIN_TEMP_AIR -10
#define E_MAX_TEMP_AIR 60
#define E_PRESSURE_MIN 850
#define E_PRESSURE_MAX 1080

#endif

//Fonction reset pour réinitialiser l'ensemble des paramètres
void eeprom_reset(void);

//Modifier/Récupérer les valeurs des paramètres
void eeprom_write_int(int addr, int n);
int eeprom_read_int(int addr, bool s);