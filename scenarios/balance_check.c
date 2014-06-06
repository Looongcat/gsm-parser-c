#include "balance_check.h"

float current_balance = 0.0;

uint8_t check_balance_callback(char* answer, uint8_t action) {
    uint8_t a_start=0, a_end=0;
    char _buf[6];
    if (strlen(answer) != 0) {
        switch(action) {
        case 0: // ECHO OFF
            if ((strcmp(answer ,"ATE0\r\r\n") == 0) || (strcmp(answer, "\r\n") == 0))
                return 0;   // echo catch, everything's fine
            else
            if (strcmp(answer, "OK\r\n") == 0)
                return 1;   // OK catch, finish the action
            else
                return 2;   // error !
            break;

        case 1: // AT+CUSD?
            if (strcmp(answer, "\r\n")==0) {
                return 0;
            } else
            if (strcmp(answer, "+CUSD: 0\r\n")==0) {
                    return 0;
            } else
            if (strcmp(answer,"OK\r\n")==0) {
                    return 1;
            } else {
                return 2;
            }
            break;

        case 2: // AT+CUSD=...

            if ((strcmp(answer, "\r\n")==0) || (strcmp(answer,"OK\r\n")==0))
              return 0;

            if (strncmp(answer,"+CUSD",5) == 0) {

              while(strncmp((answer+(a_start++)),BAL_START,sizeof(BAL_START)-1) != 0) ; // find start of number

              a_start+=sizeof(BAL_START)-1;         // shift pointer over BAL_START constant
              a_end = a_start;

              while(strncmp((answer+(a_end++)),BAL_END,sizeof(BAL_END)-1) != 0) ;

              strncpy(_buf, answer+a_start-1, a_end-a_start);

                //strncpy(_buf, strstr(answer, BAL_START), strstr(answer, BAL_START)-strstr(answer, BAL_END));

                current_balance = atof(_buf);

                return 1;

            } else return 2;

            break;
          default:
            return 2;
            break;
        }
    } else return 0;
    return 2;
}

void check_balance_setup(gsm_modem* modem) {
    gsm_scenario scene;

    modem->action_queue.head  = 0;
    modem->action_queue.tail  = 0;

    scene.actions[0] = (GSM_ACTION) { EXEC_CMD,  AC_ECHOOFF,  ""             };
    scene.actions[1] = (GSM_ACTION) { READ_CMD,  AC_USSD,     ""             };
    scene.actions[2] = (GSM_ACTION) { WRITE_CMD, AC_USSD,     CHECK_BAL_USSD };

    scene.actions[3] = (GSM_ACTION) { SCEN_FINISH, 0, "" };

    scene.callback   = &check_balance_callback;
    gsm_add_task(modem,&scene);

    return;
}
