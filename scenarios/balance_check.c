#include "balance_check.h"
#include <stdio.h>

float current_balance = 0.0;

uint8_t SKIP_BAL = 0;   // flag to skip forced AT+CUSD=0

static char BAL_START[10];
static char BAL_END[10];

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
            else {
                printf("Failed: %s\r\n",answer);
                return 2;   // error !
            }
            break;

        case 1: // AT+CUSD?
            if (strcmp(answer, "\r\n")==0) {
                return 0;
            } else
            if (strcmp(answer, "+CUSD: 0\r\n")==0) {
                SKIP_BAL = 1;
                return 0;
            } else
            if (strcmp(answer, "+CUSD: 1\r\n")==0) {
                return 0;
            } else
            if (strcmp(answer,"OK\r\n")==0) {
                if (SKIP_BAL == 1)
                    return (1<<2) + 0xC3;
                else
                    return 1;
            } else {
                printf("Failed: %s\r\n",answer);
                return 2;
            }
            break;
        case 2:
            if (strcmp(answer, "\r\n") == 0)
                return 0;   // echo catch, everything's fine
            else
            if (strcmp(answer, "OK\r\n") == 0)
                return 1;
            break;
        case 3: // AT+CUSD=...

            if ((strcmp(answer, "\r\n")==0) || (strcmp(answer,"OK\r\n")==0))
              return 0;

            if (strncmp(answer,"+CUSD",5) == 0) {

              while(strncmp((answer+(a_start++)),BAL_START,strlen(BAL_START)) != 0) ; // find start of number

              a_start+=strlen(BAL_START);         // shift pointer over BAL_START constant
              a_end = a_start;

              while(strncmp((answer+(a_end++)),BAL_END,strlen(BAL_END)) != 0) ;

              strncpy(_buf, answer+a_start-1, a_end-a_start);

              current_balance = atof(_buf);

              printf("Current balance: %4.2f UAH \r\n", current_balance);

              return 1;
            } else {
                printf("Failed: %s\r\n",answer);
                return 2;
            }
            break;
        case 4:         // AT+CUSD = 0 \r\n
            if (strcmp(answer, "\r\n") == 0)
                return 0;   // echo catch, everything's fine
            else
            if (strcmp(answer, "OK\r\n") == 0)
                return 1;
            break;

          default:
            printf("Failed: %s\r\n",answer);
            return 2;
            break;
        }
    } else return 0;
    printf("Failed: %s\r\n",answer);
    return 2;
}

void check_balance_setup(gsm_modem* modem, char* ussd, char* start_marker, char* end_marker) {
    gsm_scenario scene;
    char str[20]="";

    modem->action_queue.head  = 0;
    modem->action_queue.tail  = 0;

    strcpy(BAL_START,start_marker);
    strcpy(BAL_END,end_marker);
    sprintf(str,"1,\"%s\",15",ussd); // format: <n>,<str>,<dcs>

    scene.actions[0] = (GSM_ACTION) { EXEC_CMD,  AC_ECHOOFF,  ""             };
    scene.actions[1] = (GSM_ACTION) { READ_CMD,  AC_USSD,     ""             };
    scene.actions[2] = (GSM_ACTION) { WRITE_CMD, AC_USSD,     "0"            };
    scene.actions[3] = (GSM_ACTION) { WRITE_CMD, AC_USSD,     str            };
    scene.actions[4] = (GSM_ACTION) { WRITE_CMD, AC_USSD,     "0"            };

    scene.actions[5] = (GSM_ACTION) { SCEN_FINISH, 0, "" };

    scene.callback   = &check_balance_callback;
    gsm_add_task(modem,&scene);

    return;
}
