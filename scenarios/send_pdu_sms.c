#include "send_pdu_sms.h"

uint8_t send_pdu_sms_callback(char* answer, uint8_t action) {
    // TODO
    switch(action) {
    case 0:
        // \r\nOK\r\n
        if (strcmp(answer, "\r\n")==0)
            return 0;
        else
        if (strcmp(answer, "OK\r\n")==0)
            return 1;
        else {
            printf("Failed: %s \r\n",answer);
            return 2;
        }
        break;

    case 1:
        // \r\n>
        if (strcmp(answer, "\r\n>")==0)
            return 1;
        else {
            printf("Failed: %s \r\n",answer);
            return 2;
        }
        break;

    case 2:
        // TODO
        break;

    default:
        break;
    }
    return 2;
}

void send_pdu_sms_setup(gsm_modem* modem, sms_descriptor* sms) {
    // TODO
    gsm_scenario scene;
    char str[200]    = "";
    char tpdu_len[3] = "";
    uint8_t i = 0;
    char *ptr1, *ptr2;

    modem->action_queue.head  = 0;
    modem->action_queue.tail  = 0;

    get_pdu_string(sms, str);
    while(str[i++]!=0x1A);
    //sprintf(tpdu_len,"%0X",i-1);
    sprintf(tpdu_len,"%d",i-1);

    // HERE is scenario
    scene.actions[0] = (GSM_ACTION) { WRITE_CMD,  AC_SET_PDUMODE, "0"             };    // set up PDU mode

    scene.actions[1] = (GSM_ACTION) { WRITE_CMD,  AC_SEND_PDUSMS, ""              };
    strcpy(scene.actions[1].pParams, tpdu_len);

    scene.actions[2] = (GSM_ACTION) { WRITE_CMD,  AC_RAW_DATA,    ""              };
    ptr1 = (char*)&str;
    ptr2 = (char*)&(scene.actions[2].pParams);
    while(*ptr1 != 0x1A)
        *ptr2++ = *ptr1++;
    *ptr2 = *ptr1;

    scene.actions[3] = (GSM_ACTION) { SCEN_FINISH, 0, "" };

    scene.callback   = &send_pdu_sms_callback;
    gsm_add_task(modem,&scene);
    return;
}

void gsm_number_swap(char* number, char dst[]) {
    char str[8] = "";
    char* pStr = str;
    char* pNumber = number;

    while( *pNumber != 0 ) {
        if ( strlen(pNumber) == 1 ) {
            *pStr++ = 0xF0 | (*(pNumber)-'0');
            break;
        }
        else
            *pStr++ = ((*(pNumber+1)-'0') << 4) | (*(pNumber)-'0');

        pNumber+=2;

    }
    strncat(str,"\0",1);
    strcpy(dst, str);
    return;
}

void get_pdu_string(sms_descriptor* sms, char dst[]) {
    char    tempnum[8]  = "";
    char*   pTemp       = dst;
    uint8_t i           = 0;

    // SMSC
    *pTemp++ = 0x00;
    // PDU-Type
    *pTemp++ = (0<<TP_MTIH) | (1<<TP_MTIL) | (1<<TP_VPFH) | (0<<TP_VPFL);       // MTI = 01 - outbox sms, VPF = 0b10, relative format
    // TP-MR
    *pTemp++ = 0x00;                                                            // unnecessary
    // TP-DA
    *pTemp++ = strlen(sms->to_number);                                          // address number length
    *pTemp++ = 0x91;                                                            // address number format (0x91 - international)
    //*pTemp++ = 0x81;                                                          // address number format (0x81 - unknown)
    gsm_number_swap(sms->to_number,tempnum);
    i = (((*(pTemp-2) & 0x01) == 0x01)? (*(pTemp-2)+1) : *(pTemp-2))>>1;
    strncpy(pTemp, tempnum, i );                                                // address number
    pTemp += i;
    // TP-PID
    *pTemp++ = 0;
    // TP-DCS
    switch(sms->encoding) {
        case SMS_7BIT_ENC:
            *pTemp++ = 0x00;
            break;
        case SMS_UCS2_ENC:
            *pTemp++ = 0x08;
            break;
    }
    if (sms->flash == 1)
        *(pTemp-1) |= 0x10;
    // TP-VP
    *pTemp++ = 170; // 1 day + 4 hour?
    // TP-UDL
    switch(sms->encoding) {
        case SMS_7BIT_ENC:
            *pTemp++ = strlen(sms->msg);
            break;
        case SMS_UCS2_ENC:
            *pTemp++ = strlen(sms->msg) << 1;
            break;
    }
    // TP-UD
    switch(sms->encoding) {
        case SMS_7BIT_ENC: {
            char packed_msg[140] = "";
            char* pMsg = packed_msg;
            gsm_7bit_enc(sms->msg, packed_msg);
            while(*pMsg != 0)
                *pTemp++ = *pMsg++;
        } break;

        case SMS_UCS2_ENC: {
            wchar_t wmsg[70] = L"";
            wchar_t* pMsg = wmsg;
            strtoucs2(sms->msg, wmsg, METHOD_TABLE);
            while(*pMsg != 0) {
                *pTemp++ = (char) (*pMsg >> 8);
                *pTemp++ = (char) (*pMsg++);
            }
        } break;
    }
    *(pTemp-1) = 0x1A;

//    printf("DEBUG\r\n\r\n PDU String:\r\n");
//    pTemp = dst;
//    while(*pTemp != 0x1A)
//        printf("0x%02X ", *pTemp++);
    return;
}
