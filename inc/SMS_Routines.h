#ifndef __SMS_ROUTINES__
#define __SMS_ROUTINES__

#include <string.h>
#include <stdint.h>

#define METHOD_TABLE    1   // table method for ucs2 converting
#define METHOD_NONTABLE 0

void gsm_7bit_enc(char msg[], char out_buf[]);
wchar_t char2ucs2(char a);
void strtoucs2(char* src, wchar_t* dst, uint8_t METHOD);

#endif // __SMS_ROUTINES__
