#ifndef __GSM_TYPES__
#define __GSM_TYPES__

/* http://hardisoft.ru/soft/otpravka-sms-soobshhenij-v-formate-pdu-teoriya-s-primerami-na-c-chast-1/ */

#define SMS_LATIN   //  uncomment to use 160 symbols sms
//#define SMS_CYR   //  uncomment esli russkiy kruche
typedef struct {
    const char SMS_Center[];
    const char To_Number[13];
    #ifdef SMS_LATIN
    char text[160];
    #elif   SMS_CYR
    char text[70];
    #endif
} SMS_Descriptor;

typedef enum {
    GET;
    POST;
    HEAD;
    CONNECT;
} HTTP_Methods;

typedef struct {
    const char      Server[32];
    HTTP_Methods    HTTP_Method;
} HTTP_Descriptor;

typedef struct

#endif // __GSM_TYPES__
