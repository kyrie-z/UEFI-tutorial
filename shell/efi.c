#include "common.h"
#include "efi.h"

struct EFI_SYSTEM_TABLE *ST;

void efi_init(struct EFI_SYSTEM_TABLE *SystemTable)
{
	ST = SystemTable;
	ST->BootServices->SetWatchdogTimer(0,0,0,NULL);
}
