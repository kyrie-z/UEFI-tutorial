#include "efi.h"
#include "common.h"

unsigned char is_exit = FALSE;
void key_notice(struct EFI_KEY_DATA *KeyData __attribute__((unused)))
{
	is_exit = TRUE;
}

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned long long status;
	struct EFI_KEY_DATA key_data= {{0,L'q'},{0,0}};
 	void *notify_handle;
	
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    efi_init(SystemTable);


	ST->ConOut->ClearScreen(ST->ConOut);
    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTRED | EFI_BACKGROUND_LIGHTGRAY);

	puts(L"Waiting for the 'q' key input...\r\n");

	status = STIEP->RegisterKeyNotify(STIEP,&key_data, key_notice, &notify_handle); //按键事件被合理的设置 返回0
	assert(status, L"RegisterKeyNotify"); 

	while (!is_exit) //等待事件的发生
		;

	puts(L"exit.\r\n");

    while (TRUE)
        ;

}

