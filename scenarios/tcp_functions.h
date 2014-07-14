#ifndef __TCP_FUNCTIONS__
#define __TCP_FUNCTIONS__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\inc\GSM_AL_LEVEL.h"
#include "..\inc\GSM_PL_LEVEL.h"
#include "..\inc\ATCOMM_HAL.h"

uint8_t gprs_init_callback  (char* answer, uint8_t action);
void    gprs_init_setup     (gsm_modem* modem, char APN[]);

uint8_t tcp_init_callback   (char* answer, uint8_t action);
void    tcp_init_setup      (gsm_modem* modem, char* addr, uint16_t port);

#endif // __TCP_FUNCTIONS__
