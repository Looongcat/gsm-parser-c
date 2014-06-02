/**
 * @file   GSM_AL_LEVEL.h
 * @Author Vasyl Vorobei (looongcat)
 * @date   June, 2014
 * @brief  Application layer (AL) level GSM library
 */
#ifndef __GSM_AL__
/** \cond HIDDEN_SYMBOLS */
#define __GSM_AL__
#include <stdint.h>
/** \endcond */

#define SCENARIO_MAX_LEN    10  /**< Maximum length of scenario (number of commands) */

/** \brief Enumeration of possible actions. Refers to AT commands in HAL */
typedef enum _GSM_ACTION {
    CHECK_MODEM,
    CHECK_BALANCE,
    SEND_SMS
} GSM_ACTION;

/** \brief Describes scenario to GSM PL level */
typedef struct _gsm_scenario {
    GSM_ACTION  actions     [SCENARIO_MAX_LEN];              /**< Array with actions (see GSM_ACTION)           */
    uint8_t     ans_retry   [SCENARIO_MAX_LEN];              /**< Array with number of strings in action answer */

    /** \brief Receiver AL callback
     * callback() function written by user is used to parse answers
     * \param answer - received string
     * \param action - which action returned answer
     * \return 1 if last answer received, else 0
     *
     */
    uint8_t     (*callback)(char* answer, uint8_t action);
} gsm_scenario;

#endif // __GSM_AL__
