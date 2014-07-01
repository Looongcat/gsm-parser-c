#ifndef __BAL_CHECK_SCEN__
#define __BAL_CHECK_SCEN__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "..\inc\GSM_AL_LEVEL.h"
#include "..\inc\GSM_PL_LEVEL.h"
#include "..\inc\ATCOMM_HAL.h"

extern float current_balance;

uint8_t check_balance_callback(char* answer, uint8_t action);
void check_balance_setup(gsm_modem* modem, char* ussd, char* start_marker, char* end_marker);

#endif // __BAL_CHECK_SCEN__
