#include "efi.h"
#include "gop.h"
#include "common.h"

const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff,0xff,0xff,0xff};
const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL blue = {0xff,0x01,0x01,0xff};


//通过帧缓冲区地址画像素点
void draw_pixel(unsigned int x,unsigned int y,struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL color)
{
    //获取水平分辨率
	unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    //计算所要绘制的像素在帧缓冲区中的偏移量
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = (struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GOP->Mode->FrameBufferBase;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *addr = base + (hr * (y-1)) + x; 

	addr->Blue = color.Blue;
    addr->Green = color.Green;
    addr->Red = color.Red;
    addr->Reserved = color.Reserved;
}


//通过起点坐标和矩形大小，画矩形
void draw_rect(struct RECT r, struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL c)
{
	unsigned int i;
	
	//画上边框
	for (i = r.x; i < (r.x + r.w); i++)
		draw_pixel(i, r.y, c);
	//画下边框
	for (i = r.x; i < (r.x + r.w); i++)
		draw_pixel(i, r.y+r.h, c);
	//画左边框
	for (i = r.y; i < (r.y + r.h); i++)
		draw_pixel(r.x, i, c);
	//画右边框
	for (i = r.y; i < (r.y + r.h); i++)
		draw_pixel(r.x+r.w, i, c);

}

//获取指定位置像素数据
struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(unsigned int x, unsigned int y)
{
    unsigned int hr = GOP->Mode->Info->HorizontalResolution;
    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base = (struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GOP->Mode->FrameBufferBase;
    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x;

    return *p;
}


//判断坐标是否在指定范围内
unsigned char is_in_rect(unsigned int x, unsigned int y, struct RECT r)
{
    if ((r.x <= x) && (x <= (r.x + r.w - 1)) && (r.y <= y) && (y <= (r.y + r.h - 1)))
        return TRUE;
    return FALSE;
}
