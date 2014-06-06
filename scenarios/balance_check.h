#ifndef __BAL_CHECK_SCEN__
#define __BAL_CHECK_SCEN__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "..\inc\GSM_AL_LEVEL.h"
#include "..\inc\GSM_PL_LEVEL.h"
#include "..\inc\ATCOMM_HAL.h"

#define CHECK_BAL_USSD  "1,\"*111#\",15"

// for Kyivstar: +CUSD: 2,Na rahunku: <...> grn
// for Life:     +CUSD: 2,"Balans 35.28grn, bonus

#define BAL_START   "Balans "
#define BAL_END     "grn"

extern float current_balance;

uint8_t check_balance_callback(char* answer, uint8_t action);
void check_balance_setup(gsm_modem* modem);

#endif // __BAL_CHECK_SCEN__
