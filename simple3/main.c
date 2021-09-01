#include "efi.h"
#include "gop.h"
#include "common.h"
#include "gui.h"


struct RECT r = {200, 150, 100, 200};

void hello(void){
    ST->ConOut->ClearScreen(ST->ConOut);
    ST->ConOut->OutputString(ST->ConOut, L"Hello UEFI!\n");

}
void draw(void){
    
    draw_rect(r, blue);
}

//获取鼠标状态
void pstat (void)
{
	unsigned long long waitidx;	
	struct EFI_SIMPLE_POINTER_STATE s;
	unsigned long long status;

	SPP->Reset(SPP,FALSE);
    
	while (TRUE) {
        //WaitForEvent是阻塞等待事件发生 WaitForInput是等待鼠标输入的函数
		ST->BootServices->WaitForEvent(1,&(SPP->WaitForInput),&waitidx);
        //获取当前指针设备状态
		status = SPP->GetState(SPP,&s);
		if (!status){
			puth(s.RelativeMovementX, 8);
            puts(L" ");
            puth(s.RelativeMovementY, 8);
            puts(L" ");
            puth(s.RelativeMovementZ, 8);
            puts(L" ");
            puth(s.LeftButton, 1);
            puts(L" ");
            puth(s.RightButton, 1);
            puts(L"\r\n");
		}
	}
}

void efi_main(void *ImageHandle __attribute__ ((unused)),
                        struct EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable);
   
    hello();
    
    draw();

    // pstat();

    gui(r);

    while (1);
}

