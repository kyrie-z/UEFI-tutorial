#include "efi.h"
#include "common.h"

void efi_main(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned long long status;
	struct EFI_LOADED_IMAGE_PROTOCOL *lip;
    struct EFI_DEVICE_PATH_PROTOCOL *dev_path;
    struct EFI_DEVICE_PATH_PROTOCOL *dev_node;
    struct EFI_DEVICE_PATH_PROTOCOL *dev_path_merged;
	struct EFI_LOADED_IMAGE_PROTOCOL *lip_bzimage;
	void *image;
	unsigned short options[] = L"root=/dev/sdb rootwait";  //传参
	//root=...告诉内核使用哪个设备作为根文件系统, init=...告诉内核在启动后执行哪个程序

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    efi_init(SystemTable);


	ST->ConOut->ClearScreen(ST->ConOut);
    ST->ConOut->SetAttribute(ST->ConOut, EFI_LIGHTRED | EFI_BACKGROUND_LIGHTGRAY);
	
	//先打开当前运行的镜像
	status = ST->BootServices->OpenProtocol(ImageHandle, &lip_guid, (void **)&lip, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	assert(status, L"OpenProtocol(lip)");

	//通过镜像找到当前设备
	status = ST->BootServices->OpenProtocol(lip->DeviceHandle, &dpp_guid, (void **)&dev_path, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	assert(status, L"OpenProtocol(dpp)");

	//指定要打开的文件节点
	dev_node = DPFTP->ConvertTextToDeviceNode(L"\\test\\bzImage.efi");  //仅路径

	//将文件节点附加到设备路径后
	dev_path_merged = DPUP->AppendDeviceNode(dev_path, dev_node);
	//转换字符串
	puts(DPTTP->ConvertDevicePathToText(dev_path_merged, FALSE, FALSE));
    puts(L"\r\n");

	//加载镜像
	status = ST->BootServices->LoadImage(FALSE, ImageHandle, dev_path_merged, NULL, 0, &image);
	assert(status, L"LoadImage");
    puts(L"LoadImage: Success!\r\n");

	//通过协议打开将要运行的镜像 （为了对镜像传参）
	status = ST->BootServices->OpenProtocol(image, &lip_guid, (void **)&lip_bzimage, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	assert(status,L"OpenProtocol(lip_bzimage)");
	lip_bzimage->LoadOptions = options;
	lip_bzimage->LoadOptionsSize = (strlen(options) + 1)* sizeof(unsigned short);

	//运行image
	status = ST->BootServices->StartImage(image, NULL, NULL);
    assert(status, L"StartImage");
    puts(L"StartImage: Success!\r\n");
	while(TRUE)
		;

}

