#include "efi.h"


struct EFI_SYSTEM_TABLE *ST;

void efi_init(struct EFI_SYSTEM_TABLE *SystemTable)
{
	ST = SystemTable;
}


void efi_main(void *ImageHandle __attribute__ ((unused)),
    struct EFI_SYSTEM_TABLE *SystemTable)
{
    efi_init(SystemTable);
    ST->ConOut->ClearScreen(SystemTable->ConOut);
    ST->ConOut->OutputString(SystemTable->ConOut, L"Hello UEFI!\n");
    while (1);
}
