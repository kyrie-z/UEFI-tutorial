#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned long long status;
	struct EFI_DEVICE_PATH_PROTOCOL *dev_path;
	
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    efi_init(SystemTable);


	ST->ConOut->ClearScreen(ST->ConOut);
    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTRED | EFI_BACKGROUND_LIGHTGRAY);


	dev_path = DPFTP->ConvertTextToDevicePath(L"\\test\\test.efi");
	puts(L"dev_path: ");
	puts(DPTTP->ConvertDevicePathToText(dev_path, FALSE, FALSE));
    puts(L"\r\n");

	while(TRUE)
		;

}

