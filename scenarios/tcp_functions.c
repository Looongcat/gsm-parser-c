#include "tcp_functions.h"

uint8_t gprs_init_callback  (char* answer, uint8_t action){
    switch(action){
        case 0: // AT+CIPSHUT
            if (strcmp(answer, "\r\n")==0)
                return 0;
            else
            if (strcmp(answer, "SHUT OK\r\n")==0)
                return 1;
            else {
                printf("Failed: %s \r\n",answer);
                return 2;
            }
            break;
        case 1: // AT+CGATT=1
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
        case 2: // AT+CIPSTATUS
            if ((strcmp(answer, "\r\n")==0) || (strcmp(answer, "OK\r\n")==0))
                return 0;
            else
            if (strcmp(answer, "STATE: IP INITIAL\r\n")==0)
                return 1;
            else {
                printf("Failed: %s \r\n",answer);
                return 2;
            }
            break;
        case 3: // AT+CSTT
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
        case 4: // AT+CIPSTATUS
            if ((strcmp(answer, "\r\n")==0) || (strcmp(answer, "OK\r\n")==0))
                return 0;
            else
            if (strcmp(answer, "STATE: IP START\r\n")==0)
                return 1;
            else {
                printf("Failed: %s \r\n",answer);
                return 2;
            }
            break;
        case 5: // AT+CIICR
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
        case 6: // AT+CIPSTATUS
            if ((strcmp(answer, "\r\n")==0) || (strcmp(answer, "OK\r\n")==0))
                return 0;
            else
            if (strcmp(answer, "STATE: IP GPRSACT\r\n")==0)
                return 1;
            else {
                printf("Failed: %s \r\n",answer);
                return 2;
            }
            break;
        case 7: // AT+CIFSR
            if (strcmp(answer, "\r\n")==0)
                return 0;
            else {
                uint8_t q = 0;
                if (sscanf(answer, "%u.%u.%u.%u", &q, &q, &q, &q) == 4)
                    return 1;
                else {
                    printf("Failed: %s \r\n",answer);
                    return 2;
                }
            }
            break;
        case 8: // AT+CIPSTATUS
            if ((strcmp(answer, "\r\n")==0) || (strcmp(answer, "OK\r\n")==0))
                return 0;
            else
            if (strcmp(answer, "STATE: IP STATUS\r\n")==0)
                return 1;
            else {
                printf("Failed: %s \r\n",answer);
                return 2;
            }
            break;
        default:
            break;
    }
    return 2;
}

void    gprs_init_setup     (gsm_modem* modem, char APN[]){
    gsm_scenario scene;

    modem->action_queue.head  = 0;
    modem->action_queue.tail  = 0;
    /*
    scene.actions[0] = (GSM_ACTION) { WRITE_CMD,    AC_CGATT,           "1" };
    scene.actions[1] = (GSM_ACTION) { WRITE_CMD,    AC_CONN_SETTINGS,   "" };   // 1,"IP","www.ab.kyivstar.net"
    sprintf(scene.actions[1].pParams, "%s", CGDCONT);
    scene.actions[2] = (GSM_ACTION) { WRITE_CMD,    AC_APN_SETTINGS,    "" };    // "Kyivstar","",""
    sprintf(scene.actions[2].pParams, "%s", APNSET);
    scene.actions[3] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_START,      "" };
    scene.actions[4] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_GETIP,      "" };
    scene.actions[5] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_STATUS,     "" };
    scene.actions[6] = (GSM_ACTION) { SCEN_FINISH,  0,                  "" };
    */
    scene.actions[0] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_RESET,      ""  };
    scene.actions[1] = (GSM_ACTION) { WRITE_CMD,    AC_CGATT,           "1" };
    scene.actions[2] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_STATUS,     ""  };
    scene.actions[3] = (GSM_ACTION) { WRITE_CMD,    AC_APN_SETTINGS,    ""  };    // "<apn>","",""
    sprintf(scene.actions[3].pParams, "%s", APN);
    scene.actions[4] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_STATUS,     ""  };
    scene.actions[5] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_START,      ""  };
    scene.actions[6] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_STATUS,     ""  };
    scene.actions[7] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_GETIP,      ""  };
    scene.actions[8] = (GSM_ACTION) { EXEC_CMD,     AC_GPRS_STATUS,     ""  };
    scene.actions[9] = (GSM_ACTION) { SCEN_FINISH,  0,                  ""  };

    scene.callback   = &gprs_init_callback;

    gsm_add_task(modem,&scene);
    return;
}

uint8_t tcp_init_callback   (char* answer, uint8_t action){
    return 2;
}

void    tcp_init_setup      (gsm_modem* modem, char* addr, uint16_t port){
/*
    7) AT+CIPSTART="TCP","<url>","<port>"
    8) AT+CIPSEND
*/
    return;
}
