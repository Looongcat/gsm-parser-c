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

#define AT_CONN_STATUS         "AT+CGDCONT"

#endif // __AT_COMM__
