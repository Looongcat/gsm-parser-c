#ifndef __ATCOMMS__
#define __ATCOMMS

/**
 *   \brief Header with AT Commands defines STRICTLY for Cinterion BGS2-W
*/

/*! \file */

#define AT_PRESENSE                 "AT\r"      /**< Command to detect modem on physical line */
#define AT_ECHO_OFF                 "ATE0\r"    /**< Turns off received command echo */
#define AT_ECHO_ON                  "ATE1\r"    /**< Resends back the received command */

/* Flow control commands */
/*@{*/
#define AT_FLOW_CONTROL_RTS_CTS     "AT\\Q3\r"  /**< Use RTS/CTS flow control */
#define AT_FLOW_CONTROL_CTS         "AT\\Q2\r"  /**< Use CTS only flow control */
#define AT_FLOW_CONTROL_XON_XOFF    "AT\\Q1\r"  /**< Use XON/XOFF control - works very badly */
#define AT_FLOW_CONTROL_OFF         "AT\\Q0\r"  /**< Use modem without flow control */
/*@}*/

/* Commands to obtain modem IDs */
/*@{*/
#define AT_GET_VENDOR               "AT+CGMI\r" /**< Use to obtain Vendor name */
#define AT_GET_MODEL                "AT+CGMM\r" /**< Use to obtain Model name  */
/*@}*/

/* SMS Commands */
/*@{*/

/*@{*/
#define AT_SMS_TEXT                 1
#define AT_SMS_PDU                  0
/**
 * \brief Sets up SMS format
 *
 * For text format use AT_SMS_MODE(AT_SMS_TEXT).
 * For PDU format use AT_SMS_MODE(AT_SMS_PDU).
*/
#define AT_SMS_MODE(x)              sprintf("AT+CMGF=&u\r",x)
/*@}*/
#define AT_SMS_GETSMSC              "AT+CSCA?\r"/**< Command which returns SMSC number */

/*@}*/

#endif // __ATCOMMS__
