#ifndef __GSM_INIT_SCENE__
#define __GSM_INIT_SCENE__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "..\inc\GSM_AL_LEVEL.h"
#include "..\inc\GSM_PL_LEVEL.h"
#include "..\inc\ATCOMM_HAL.h"

uint8_t gsm_init_callback(char* answer, uint8_t action);
void gsm_init_setup(gsm_modem* modem, uint32_t pin[2], uint32_t puk[2]);

#endif // __GSM_INIT_SCENE__
