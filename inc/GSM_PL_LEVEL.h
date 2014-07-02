/**
 * @file   GSM_PL_LEVEL.h
 * @Author Vasyl Vorobei (looongcat)
 * @date   June, 2014
 * @brief  Presentation layer (PL) level GSM library
 */
#ifndef __GSM_PL_LEVEL__
/** \cond HIDDEN_SYMBOLS */
#define __GSM_PL_LEVEL__

#include "GSM_AL_LEVEL.h"
#include <stdint.h>
/** \endcond */

#define RING_BUFFER_SIZE  1024          /**< Defines buffer size and types of head and tail */

#ifndef RING_BUFFER_SIZE
    #error "RING_BUFFER_SIZE is not defined! See GSM_PL_LEVEL.h"
#endif // RING_BUFFER_SIZE

/** \brief Ring buffer structure
 *
 * Naturally contains 3 fields.
 * Possible way to get out the string: *(buffer->base + buffer->read).
 *
 * Before usage the size of buffer must be defined with RING_BUFFER_SIZE!
 */
typedef struct {
  uint8_t  base[RING_BUFFER_SIZE];     // ring buffer pointer
  #if RING_BUFFER_SIZE < 255
  uint8_t head;
  uint8_t tail;
  #else
  uint16_t head;    /**< points to the next byte for writing */
  uint16_t tail;    /**< points to the next byte for reading */
  #endif
} ring_buf;

// ring buffer ops
#define ring_push(ring, char)    *(ring.base + ring.head++) = char
#define ring_pop (ring)          *(ring.base + ring.tail++)

typedef struct _gsm_modem {
    enum {
        MODEM_CMD_SEND,
        MODEM_ANS_WAIT,
        MODEM_ANS_RECV,
        MODEM_IDLE,          /**< State after scenario execution */
        MODEM_SKIP_CMD       /**< State for skipping next command in queue */
    } state:3;            // if 0 - sending command, else if 1 - receiving answer;

    ring_buf  action_queue;
    ring_buf  answers;
    uint8_t   cur_action;
    uint8_t   skip_cnt;   // new feature
    /*
        How to use skip_cnt:
        Callback must return value as:
        0b 11xx xx11
        where   11 - skip setting marker
                xxxx - number of commands to skip
                11  - must be empty to avoid wrong PL answer parsing
    */

    //void      (*send_cmd) (char* cmd);                    /**< User defined send function */
    void      (*send_cmd) (char* cmd, uint8_t len);                    /**< User defined send function */
    uint8_t   (*callback)(char* answer, uint8_t action);
} gsm_modem;

void    run_gsm_queue(gsm_modem* modem);                           /**< Must be execute in main cycle continuously */
void    gsm_add_task (gsm_modem* modem, gsm_scenario*  scenario);  /**< Creates new task */
void    gsm_queue_halt(gsm_modem* modem);                          /**< Extremal terminating of scenario */

#endif // __GSM_PL_LEVEL__
