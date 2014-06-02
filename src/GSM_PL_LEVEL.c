#include "..\inc\GSM_PL_LEVEL.h"

void run_gsm_queue(gsm_modem* modem) {
    switch(modem->state) {
    case 0:
        // SEND CMD
        break;
    case 1:
        // RECEIVE ANSWER
        break;
    }
    return;
}

void add_task(gsm_scenario action){
    // todo

    return;
}
