#ifndef __BAL_CHECK_SCEN__
#define __BAL_CHECK_SCEN__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "..\inc\GSM_AL_LEVEL.h"
#include "..\inc\GSM_PL_LEVEL.h"
#include "..\inc\ATCOMM_HAL.h"

//#define __KYIVSTAR_SIM__
//
//#ifdef __LIFE_SIM__
//#define CHECK_BAL_USSD  "1,\"*111#\",15"
//
//#define BAL_START   "Balans "
//#define BAL_END     "grn"
//#endif // __LIFE_SIM__
//
//#ifdef __KYIVSTAR_SIM__
//#define CHECK_BAL_USSD  "1,\"*111#\",15"
//
//#define BAL_START   "rahunku: "
//#define BAL_END     " grn"
//#endif // __KYIVSTAR_SIM__d

extern float current_balance;

uint8_t check_balance_callback(char* answer, uint8_t action);
void check_balance_setup(gsm_modem* modem, char* ussd, char* start_marker, char* end_marker);

#endif // __BAL_CHECK_SCEN__
