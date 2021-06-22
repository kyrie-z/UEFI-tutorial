#include "efi.h"
#include "common.h"

struct EFI_SYSTEM_TABLE *ST;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
struct EFI_SIMPLE_POINTER_PROTOCOL *SPP;
void efi_init(struct EFI_SYSTEM_TABLE *SystemTable)
{
	struct EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51,0x6a}};
	struct EFI_GUID spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};

	ST=SystemTable;
	ST->BootServices->SetWatchdogTimer(0,0,0,NULL);
	ST->BootServices->LocateProtocol(&gop_guid,NULL,(void**)&GOP);

	int val = ST->BootServices->LocateProtocol(&spp_guid,NULL,(void**)&SPP);
	if (val != 0){
		SystemTable->ConOut->OutputString(SystemTable->ConOut, L"NO SPP!\r\n");
	}
//判断像素格式
//	unsigned int pf = GOP->Mode->Info->PixelFormat;
//	ST->ConOut->OutputString(ST->ConOut,L"----------\r\n");
//	if (pf == 0)
//		ST->ConOut->OutputString(ST->ConOut,L"PixelRedGreenBlueReserved8BitPerColor\r\n");
//	else if (pf ==1)
//		ST->ConOut->OutputString(ST->ConOut,L"PixelBlueGreenRedReserved8BitPerColor\r\n");
//	else if (pf ==2)
//		ST->ConOut->OutputString(ST->ConOut,L"PixelBitMask\r\n");
//	else if (pf ==3)
//		ST->ConOut->OutputString(ST->ConOut,L"PixelBltOnly\r\n");
//	else if (pf==4)
//		ST->ConOut->OutputString(ST->ConOut,L"PixelFormatMax\r\n");
//	unsigned int mm = GOP->Mode->MaxMode;
//	puth(pf, 8);
//	puth(mm, 8);

}
