#include "efi.h"
#include "common.h"

void putc(unsigned short c)
{
    unsigned short str[2] = L" ";
    str[0] = c;
    ST->ConOut->OutputString(ST->ConOut, str);
}

void puts(unsigned short *s)
{
    ST->ConOut->OutputString(ST->ConOut, s);
}


#define MAX_STR_BUF 100
//16进制数输出
void puth(unsigned long long val, unsigned char num_digits)
{
    int i;
    unsigned short unicode_val;
    unsigned short str[MAX_STR_BUF];

    for (i = num_digits - 1; i >= 0; i--) {
        unicode_val = (unsigned short)(val & 0x0f);
        if (unicode_val < 0xa)
            str[i] = L'0' + unicode_val;
        else
            str[i] = L'A' + (unicode_val - 0xa);
        val >>= 4;
    }
    str[num_digits] = L'\0';

    puts(str);
}


int strcmp(const unsigned short *s1, const unsigned short *s2)
{
    char is_equal = 1;

    for (; (*s1 != L'\0') && (*s2 != L'\0'); s1++, s2++) {
        if (*s1 != *s2) {
            is_equal = 0;
            break;
        }
    }

    if (is_equal) {
        if (*s1 != L'\0') {
            return 1;
        } else if (*s2 != L'\0') {
            return -1;
        } else {
            return 0;
        }
    } else {
        return (int)(*s1 - *s2);
    }
}
