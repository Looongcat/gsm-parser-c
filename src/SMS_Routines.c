#include "../inc/SMS_Routines.h"
#include "../inc/ucs2_table.h"

void gsm_7bit_enc(char msg[], char out_buf[]) {
    char* tempPtr   = msg;
    char* outPtr    = out_buf;

    uint8_t i       = 0;
    uint8_t mask    = 0;

    while(*tempPtr != 0) {
        mask = 0;
        for(i = 0; i < 7; i++) {
            if (*msg == 0)
                break;

            mask |= 1<<i;           // update mask
            *outPtr++ = (*tempPtr >> i) | ( (*(tempPtr+1) & mask) << (7-i) );
            tempPtr++;
        }
        tempPtr++;  // skip 8th symbol
    }
    return;
}

wchar_t char2ucs2(char a) {
    if ((uint8_t)a == 168) // YO
        return 0x0451;

    if ((uint8_t)a == 184) // yo
        return 0x0401;

    if ((uint8_t)a >= 0xC0) // russian
        return (wchar_t)(0x0350+(uint8_t)a);//((a-0xC0) + 0x410);

    if ((uint8_t)a <= 0x7F)
        return (wchar_t)a;

        return 0;
}

void strtoucs2(char* src, wchar_t* dst, uint8_t METHOD) {
    while(*src)
        if (METHOD == METHOD_TABLE)
            *(dst++) = cp1251_utf[(uint8_t)*(src++)];
        else
            *(dst++) = char2ucs2(*(src++));
    return;
}
