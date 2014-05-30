#ifndef __GSM_TYPES__
#define __GSM_TYPES__

#include <stdint.h>

/**
 *   \brief Header with GSM structures
*/

/*! \file */

/** \def Defines ring buffer size */
#define RING_BUFFER_SIZE  1024          /**< Defines buffer size and types of head and tail */

/** \brief Ring buffer structure
 *
 * Naturally contains 3 fields:
 * Possible way to get out the string: *(buffer->base + buffer->read)
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

/** \brief GSM Modem descriptor
 *
 * Contains:
 * -# query - ring buffer structure
 * -# send_command - pointer to the send function callback (e.g. USART_SendString, ...)
 * -# pin1/2 - pin codes for SIM Card
 * -# puk1/2 - PUK codes for SIM Card
 * -# baudrate - baud rate of rs232 channel, set 0 for auto baud rate;
 */
typedef struct {
    ring_buf      query;
    /*@{*/
    uint32_t pin1;
    uint32_t pin2;
    uint32_t puk1;
    uint32_t puk2;
    uint32_t baudrate;
    /*@}*/
    uint8_t       (*send_command) (char* cmd);  /**< Pointer to the HAL send function */
} GSM_Modem;

/** \brief Modem ID Structure
 *
 * Used to identify modem. Contains next fields:
 * -# vendor - vendor of modem (e.g. SIMCOM, Cinterion...)
 * -# name - name of the modem (may be used for different modem AT Commands set later?)
 */
typedef struct {
    char    vendor[10];
    char    name[10];
    // anything else ?
} Modem_ID;

/**
 *  Used in send_sms"(" SMS_Send_Format format,SMS_Descriptor* SMS ")" function
 */
typedef enum {
    SMS_TEXT_MODE,
    SMS_PDU_MODE
} SMS_Send_Format;

#define SMS_LATIN   //  uncomment to use 160 symbols sms
//#define SMS_CYR   //  uncomment esli russkiy kruche

/** \brief SMS Descriptor structure
 *
 * Needs one of defines:
 * -# SMS_LATIN - for Latin alphabet SMS (up to 160 symbols)
 * -# SMS_CYR   - for Cyrillic (and another national languages) (up to 70 symbols)
 */
typedef struct {
    /**
     * @name Necessary numbers
     */
    /*@{*/
    const char SMS_Center   [13];     /**< SMS Center number (e.g. +(country code) (number) */
    const char To_Number    [13];   /**< To who we're sending SMS? */
    /*@}*/
    /**
     * @name Message text
     */
    /*@{*/
    #ifdef SMS_LATIN
    char text[160];
    #elif   SMS_CYR
    char text[70];
    #endif
    /*@}*/
} SMS_Descriptor;

/** \brief HTTP call methods enumerator
 *  Support GET, POST, HEAD and CONNECT
 */
typedef enum {
    GET,
    POST,
    HEAD,
    CONNECT
} HTTP_Methods;

/** \brief HTTP Descriptor, used for internet communications
 *
 */
typedef struct {
    const char      Server[32];
    HTTP_Methods    HTTP_Method;
} HTTP_Descriptor;

/** \brief Descriptor for internet settings
 *
 *  All parameters except apn_name possibly could be "\0"
 */
typedef struct {
    char apn        [20];
    char domains    [2][15];    /**< Two domains IPs */
    char apn_name   [20];
    char user_id    [20];
    char password   [20];
} Internet_Settings;

#endif // __GSM_TYPES__
