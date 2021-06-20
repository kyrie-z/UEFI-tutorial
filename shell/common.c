#include "common.h"
#include "efi.h"

//单个字符并打印
void putc(unsigned short c)
{
    unsigned short str[2] = L" ";
    str[0] = c;
    ST->ConOut->OutputString(ST->ConOut, str);
}

//打印字符串
void puts(unsigned short *s)
{
    ST->ConOut->OutputString(ST->ConOut, s);
}

//阻塞wait获取键盘按键事件，返回按键对应值
unsigned short getc(void)
{
    struct EFI_INPUT_KEY key;
    unsigned long long waitidx;

    ST->BootServices->WaitForEvent(1, &(ST->ConIn->WaitForKey), &waitidx);
    while (ST->ConIn->ReadKeyStroke(ST->ConIn, &key))
        ;

    return key.UnicodeChar;
}

//将输入字符串存到一定大小的buffer中，返回字符串大小
unsigned int gets(unsigned short *buf, unsigned int buf_size)
{
    unsigned int i;

    for (i = 0; i < buf_size - 1;) {
        buf[i] = getc();
        putc(buf[i]);
        if (buf[i] == L'\r') {
            putc(L'\n');
            break;
        }
        i++;
    }
    buf[i] = L'\0';

    return i;
}

//比较两个字符串是否相等，相等返回0
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
