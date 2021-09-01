#include "efi.h"
#include "gop.h"


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
