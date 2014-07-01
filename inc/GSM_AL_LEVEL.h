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

#define SCENARIO_MAX_LEN    20  /**< Maximum length of scenario (number of commands) */
/** \cond HIDDEN_SYMBOLS */
#ifndef SCENARIO_MAX_LEN
#error "SCENARIO_MAX_LEN is not defined! Check GSM_AL_LEVEL.h"
#endif
/** \endcond */

/** \brief Enumeration of possible actions. Refers to AT commands in HAL */
typedef enum {
    AC_PRESENSE,
    AC_ECHOOFF,
    AC_ECHOON,
    AC_GET_VENDOR,
    AC_GET_MODEL,
    AC_USSD,
    AC_PINCODE,
    AC_PIN2CODE,
    AC_SET_PDUMODE,
    AC_SEND_PDUSMS,
    AC_RAW_DATA
    // TODO more
} action_body;

/** \brief Action structure. Fully describes one action in scenario */
typedef struct {
    enum {
        TEST_CMD,       /**< Command with "=?"              */
        READ_CMD,       /**< Command with "?"               */
        WRITE_CMD,      /**< Command with "=<...>"          */
        EXEC_CMD,       /**< Default command (e.g. "AT\r")  */
        SCEN_FINISH     /**< Scenario finish                */
    } action_type;

    action_body cmd;    /**< Action name which refers to real AT command. Contains only body! */

    char pParams[200];      /**< If action_type=WRITE_CMD must contain params which goes after "=" */
} GSM_ACTION;

/** \brief Describes scenario to GSM PL level */
typedef struct {
    GSM_ACTION  actions     [SCENARIO_MAX_LEN];              /**< Array with actions (see GSM_ACTION)           */
    //uint8_t     ans_retry   [SCENARIO_MAX_LEN];              /**< Array with number of strings in action answer */ // OBSOLETE

    /** \brief Receiver AL callback
     * callback() function written by user is used to parse answers
     * \param answer - received string
     * \param action - which action returned the answer
     * \return 1 if last answer received, else 0. If error - returns 2.
     *
     */
    uint8_t     (*callback)(char* answer, uint8_t action);
} gsm_scenario;

#endif // __GSM_AL__
