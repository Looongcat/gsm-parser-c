#ifndef __AT_COMM__
#define __AT_COMM__

#ifdef __WINX__
    #define EOSchar     '\000'
#elif  __STM32__
    #define EOSchar     '\0'
#endif

#define AT_PRESENSE            "AT"

#define AT_ECHOOFF             "ATE0"

#define AT_ECHOON              "ATE1"

#define AT_GET_VENDOR          "AT+CGMI"
#define AT_GET_MODEL           "AT+CGMM"

#define AT_USSD                "AT+CUSD" // ?, =?, \r, =<int>,<char>,<int>

#define AT_PINCODE             "AT+CPIN"
#define AT_PIN2CODE            "AT+CPIN2"

#define AT_SET_PDUMODE         "AT+CMGF"
#define AT_SEND_PDUSMS         "AT+CMGS"

#define AT_GPRS_RESET          "AT+CIPSHUT"
#define AT_CGATT               "AT+CGATT"
#define AT_CONN_SETTINGS       "AT+CGDCONT"
#define AT_APN_SETTINGS        "AT+CSTT"
#define AT_GPRS_START          "AT+CIICR"
#define AT_GPRS_GETIP          "AT+CIFSR"
#define AT_GPRS_STATUS         "AT+CIPSTATUS"

#endif // __AT_COMM__
