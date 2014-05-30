#ifndef __GSM__
#define __GSM__

#include <stdint.h>
#include "gsm_types.h"

/**
 *   \brief Header for main kitchen
*/

/*! \file */

/** \brief PDU SMS Converter
 *
 * Read more about PDU format and conversions at: http://hardisoft.ru/soft/otpravka-sms-soobshhenij-v-formate-pdu-teoriya-s-primerami-na-c-chast-1/
 * \param SMS - SMS Descriptor (see SMS_Descriptor)
 * \return Returns (char*) with data for modem
 *
 */
char*   sms2pdu (SMS_Descriptor* SMS);

/** \brief SMS Send function
 *
 * \param format - SMS_TEXT_MODE or SMS_PDU_MODE
 * \param SMS - pointer to SMS Descriptor (see SMS_Descriptor)
 * \param modem - pointer to GSM modem descriptor
 * \return Returns zero if received SMS ID from modem (successful send)
 *
 */
uint8_t sms_send(SMS_Send_Format format, SMS_Descriptor* SMS); // , GSM_Modem modem);

/** \brief gsm_init - try to find gsm modem and if it's found - tries to enter PIN/PUK code
 *
 * \param modem - pointer to the GSM_Modem structure
 * \return 0 if sim is ready
 *
 */
uint8_t gsm_init(GSM_Modem* modem);
#endif // __GSM__
