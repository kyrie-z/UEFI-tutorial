#include "efi.h"
#include "gop.h"


void hello(void){
    ST->ConOut->ClearScreen(ST->ConOut);
    ST->ConOut->OutputString(ST->ConOut, L"Hello UEFI!\n");

}
void draw(void){
    const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL white = {0xff,0xff,0xff,0xff};
    const struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL blue = {0xff,0x01,0x01,0xff};
    struct RECT r = {200, 150, 100, 200}; 
    draw_rect(r, blue);
}


void efi_main(void *ImageHandle __attribute__ ((unused)),
                        struct EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable);
   
    hello();
    
    draw();

    while (1);
}

