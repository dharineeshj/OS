#include "stdint.h"

void _cdecl x86_Video_WriteCharTeletype(char c,unint8_t page);
void _cdecl x86_div64_32(unint64_t dividend,unint32_t divisor, unint64_t* quotientOut,unint32_t* remainderOut);
void _cdecl x86_stringNumber(int16_t x,int64_t number,int64_t *number_addr,int16_t multiplyer);
