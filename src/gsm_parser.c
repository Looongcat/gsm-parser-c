#include "../inc/gsm_parser.h"
#include "../inc/gsm_types.h"
#include <stdio.h>

char*   sms2pdu (SMS_Descriptor* SMS) {
    // TODO
    return "NONE";
}

uint8_t sms_send(SMS_Send_Format format,SMS_Descriptor* SMS){
    // TODO
    return 0;
}

uint8_t gsm_init(GSM_Modem* modem) {
    modem->send_command(AT_ECHO_OFF);  // echo off

    modem->send_command(AT_PRESENSE);
    // check answer

    modem->send_command(sprintf("AT+IPPR=%lu\r",modem->baudrate));
    // check answer

    modem->send_command("AT+CPIN?\r");
    // check answer
    /*
    if ("\r\n+CPIN: SIM PIN\r\n") {
        modem->send_command("AT+CPIN=&lu\r",modem->pin1);
    } else
    if ("\r\n+CPIN: SIM PIN2\r\n") {
        modem->send_command("AT+CPIN2=&lu\r",modem->pin2);
    } else
    if ("\r\n+CPIN: SIM PUK\r\n") {
        modem->send_command("AT+CPIN==&lu,&lu\r",modem->puk1,modem->pin1);
    } else
    if ("\r\n+CPIN: SIM PUK2\r\n") {
        modem->send_command("AT+CPIN2=&lu,&lu\r",modem->puk2,modem->pin1);
    } else
    if ("\r\nERROR\r\n") {
        return 9; // sim card is broken or not present
    }
    if ("+CPIN: READY") {
        // init finished
        // debug("SIM init finished!\r\n");
    }
    */
    return 0;
}
