#ifndef __SEND_PDU_SMS__
#define __SEND_PDU_SMS

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\inc\GSM_AL_LEVEL.h"
#include "..\inc\GSM_PL_LEVEL.h"
#include "..\inc\ATCOMM_HAL.h"
#include "../inc/SMS_Routines.h"

/* PDU-Type bits */
#define TP_MTIL 0
#define TP_MTIH 1
#define TD_RD   2
#define TP_VPFL 3
#define TP_VPFH 4
#define TP_SRR  5
#define TP_UDHI 6
#define TP_RP   7

typedef struct sms_descriptor {
    enum enc{
        SMS_7BIT_ENC = 0,
        SMS_UCS2_ENC = 1
    } encoding:1;

    char to_number[12];

    uint8_t get_delivery_status:1;  // Future feature
    uint8_t flash:1;                // set to 1 if need flash sms

    char msg[160];
} sms_descriptor;

uint8_t send_pdu_sms_callback(char* answer, uint8_t action);
void send_pdu_sms_setup(gsm_modem* modem, sms_descriptor* sms);

void get_pdu_string(sms_descriptor* sms, char dst[]);
void gsm_number_swap(char* number, char dst[]);


#endif // __SEND_PDU_SMS__
