#include "..\inc\GSM_PL_LEVEL.h"
#include "..\inc\GSM_AL_LEVEL.h"
#include "..\inc\ATCOMM_HAL.h"
#include <string.h>
#include <stdio.h>

void run_gsm_queue(gsm_modem* modem) {
    char buf[15] = "";
    uint8_t i = 0;
    switch(modem->state) {
    case 0:
        // CMD send mode, need extract command from queue and send it
        for(i = modem->action_queue.tail;(*(modem->action_queue.base+modem->action_queue.tail) != EOSchar); i++)
            buf[i] = *(modem->action_queue.base+modem->action_queue.tail++);
        modem->send_cmd(buf);
        modem->state = MODEM_ANS_RECV;
        break;
    case 1:
        // RECEIVE ANSWER
        for(i = modem->answers.tail;( *(modem->answers.base + modem->answers.tail) != '\n' ); i++)
            buf[i] = *(modem->answers.base + modem->answers.tail++);
        buf[i] = '\n';buf[i+1]=EOSchar;
        // dummy \n write

        switch(modem->callback(buf,modem->cur_action)) {
        case 0:     // next cmd
            // take a rest, bro
            break;
        case 1:     // go to next action
            modem->cur_action++;
            modem->state = MODEM_CMD_SEND;
            break;
        case 2:
            printf("Error. Whoopsie! (c) Catbug \r\n");
            break;
        default:
            printf("Catched in default answer handler \r\n");
            break;
        }
        break;
    }
    return;
}

void add_task(gsm_modem* modem, gsm_scenario* scenario){
    #if SCENARIO_MAX_LEN < 255
    uint8_t i = 0;
    #else
    uint16_t i = 0;
    #endif // SCENARIO_MAX_LEN
    uint8_t j = 0;
    char _cmd[15] = "";
    /* matching AL commands with AT commands */
    while(scenario->ans_retry[i] != 0) {  // goes over all actions
        switch(scenario->actions[i].cmd) {
        case AC_PRESENSE:
            strcpy(_cmd, AT_PRESENSE);
            break;
        case AC_ECHOOFF:
            strcpy(_cmd, AT_ECHOOFF);
            break;
        case AC_ECHOON:
            strcpy(_cmd, AT_ECHOON);
            break;
        case AC_GET_VENDOR:
            strcpy(_cmd, AT_GET_VENDOR);
            break;
        case AC_GET_MODEL:
            strcpy(_cmd, AT_GET_MODEL);
            break;
        case AC_USSD:
            strcpy(_cmd, AT_USSD);
            break;
        }
        /* copying command in buffer */
        for (j = 0; _cmd[j] != '\0' ;j++) {
            *(modem->action_queue.base + modem->action_queue.head) = *(_cmd+j);
            modem->action_queue.head++;
        }
        /* looking for end of command */
        switch(scenario->actions[i].action_type) {
        case EXEC_CMD:
            *(modem->action_queue.base + modem->action_queue.head++) = '\r';
            //modem->action_queue.head++;
            break;
        case TEST_CMD:
            *(modem->action_queue.base + modem->action_queue.head++) = '=';
            //modem->action_queue.head++;
            *(modem->action_queue.base + modem->action_queue.head++) = '?';
            //modem->action_queue.head++;
            *(modem->action_queue.base + modem->action_queue.head++) = '\r';
            //modem->action_queue.head++;
            break;
        case READ_CMD:
            *(modem->action_queue.base + modem->action_queue.head++) = '?';
            //modem->action_queue.head++;
            *(modem->action_queue.base + modem->action_queue.head++) = '\r';
            //modem->action_queue.head++;
            break;
        case WRITE_CMD:
            // special magic
            break;
        }
        *(modem->action_queue.base + modem->action_queue.head++) = EOSchar;
        //modem->action_queue.head++;
        i++;
    }
    modem->callback = scenario->callback;
    modem->cur_action = 0;
    return;
}
