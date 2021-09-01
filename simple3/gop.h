#ifndef _GOP_H_
#define _GOP_H_

#include "efi.h"

//矩形信息
struct RECT {
    unsigned int x, y; //起始地址
    unsigned int w, h; //宽高
};
extern const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL white;
extern const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL blue;


void draw_pixel(unsigned int x, unsigned int y, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL color);
void draw_rect(struct RECT r, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL c);
struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(unsigned int x, unsigned int y);
unsigned char is_in_rect(unsigned int x, unsigned int y, struct RECT r);

#endif
