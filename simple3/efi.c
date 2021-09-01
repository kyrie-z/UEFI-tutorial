#include "efi.h"
#include "common.h"

struct EFI_SYSTEM_TABLE *ST;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP; //图形
struct EFI_SIMPLE_POINTER_PROTOCOL *SPP; //鼠标

void efi_init(struct EFI_SYSTEM_TABLE *SystemTable)
{
    //图形协议的GUID
	struct EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, \
                    {0x96, 0xfb, 0x7a, 0xde, \
                     0xd0, 0x80, 0x51, 0x6a}};
    //鼠标GUID
     struct EFI_GUID spp_guid = {0x31878c87, 0xb75, 0x11d5, \
                    {0x9a, 0x4f, 0x0, 0x90,    \
                     0x27, 0x3f, 0xc1, 0x4d}};
    //系统表
    ST = SystemTable;
    //BS
    // ST->BootServices->SetWatchdogTimer(0,0,0,NULL);
    //加载协议，并返回一个指向该协议接口处理的接口
	ST->BootServices->LocateProtocol(&gop_guid,NULL,(void**)&GOP); 
    ST->BootServices->LocateProtocol(&spp_guid, NULL, (void **)&SPP);
}
