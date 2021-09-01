#include "efi.h"
#include "common.h"
#include "gop.h"
#include "gui.h"

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL cursor_tmp = {0, 0, 0, 0};
int old_x;
int old_y;

void draw_cursor(int x, int y)
{
	//先保存旧位置像素信息,再画新位置
	old_x = x;
	old_y = y;
	cursor_tmp=get_pixel(old_x, old_y);
	draw_pixel(x,y,white);
}

void restore_old_cursor()
{
	draw_pixel(old_x, old_y, cursor_tmp);

}

void put_cursor(int x, int y)
{
	restore_old_cursor();

	draw_cursor(x,y);

}

void gui(struct RECT r)
{

    unsigned long long status;
    struct EFI_SIMPLE_POINTER_STATE s;
    int px = 0, py = 0;
    unsigned long long waitidx;
    unsigned char is_highlight = FALSE;


    while (TRUE) {
        ST->BootServices->WaitForEvent(1, &(SPP->WaitForInput), &waitidx);
        status = SPP->GetState(SPP, &s);
        if (!status) {
            /* 更新鼠标指针位置 */
            px += s.RelativeMovementX >> 13;
            if (px < 0)
                px = 0;
            else if (GOP->Mode->Info->HorizontalResolution <= (unsigned int)px)
                px = GOP->Mode->Info->HorizontalResolution - 1;
            py += s.RelativeMovementY >> 13;
            if (py < 0)
                py = 0;
            else if (GOP->Mode->Info->VerticalResolution <= (unsigned int)py)
                py = GOP->Mode->Info->VerticalResolution - 1;

            /* 绘制鼠标指针 */
            put_cursor(px, py);

            /* 鼠标悬浮于矩形图标上时，高亮矩形图标 */
            if (is_in_rect(px, py, r)) {
                if (!is_highlight) {
                    draw_rect(r, blue);
                    is_highlight = TRUE;
                }
            } else {
                if (is_highlight) {
                    draw_rect(r, white);
                    is_highlight = FALSE;
                }
            }
        }
    }
}
