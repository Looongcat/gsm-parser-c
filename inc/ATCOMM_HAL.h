#ifndef __AT_COMM__
#define __AT_COMM__

#define PRESENSE            "AT\r"
#define ECHOOFF             "ATE0\r"
#define ECHOON              "ATE1\r"

#define GET_VENDOR          "AT+CGMI\r"
#define GET_MODEL           "AT+CGMM\r"

#define USSD_head           "AT+CUSD" // ?, =?, \r, =<int>,<char>,<int>

#define CONN_STATUS_head    "AT+CGDCONT"

#endif // __AT_COMM__
