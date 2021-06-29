#include "efi.h"
#include "common.h"
#include "graphics.h"
#include "shell.h"
#include "gui.h"
#include "file.h"

#define MAX_COMMAND_LEN 100

void pstat(void)
{
    unsigned long long status;
    struct EFI_SIMPLE_POINTER_STATE s;
    unsigned long long waitidx;

    SPP->Reset(SPP, FALSE);

    while (1) {
        ST->BootServices->WaitForEvent(1, &(SPP->WaitForInput), &waitidx);
        status = SPP->GetState(SPP, &s);
        if (!status) {
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

void edit (unsigned short *file_name)
{
	unsigned long long status;
	unsigned short ch;
	int i =0;
	unsigned short file_buf[MAX_FILE_BUF / 2];
	struct EFI_FILE_PROTOCOL *root;
	struct EFI_FILE_PROTOCOL *file;
	unsigned long long buf_size = MAX_FILE_BUF;

	ST->ConOut->ClearScreen(ST->ConOut);
	//输入 直到ESC退出;
	while(TRUE)
	{
		ch = getc();

		if (ch == SC_ESC)
			break;

		putc(ch);
		file_buf[i++] = ch;
		if (ch==L'\r'){
			putc(L'\n');
			file_buf[i++] =	L'\n';
		}
	}
	file_buf[i] = L'\0';

	status = SFSP->OpenVolume(SFSP, &root);
	assert(status, L"SFSP->OpenVolume");

	status = root->Open(root, &file,file_name,EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0);
	assert(status, L"root->Open");

    status = file->Write(file, &buf_size, (void *)file_buf);
    assert(status, L"file->Write");

	file->Flush(file);
	file->Close(file);
	root->Close(root);

}

void cat (unsigned short *file_name)
{
	struct EFI_FILE_PROTOCOL *root;
	unsigned long long status;
	struct EFI_FILE_PROTOCOL *file;
	unsigned long long buf_size = MAX_FILE_BUF;
	unsigned short file_buf[MAX_FILE_BUF / 2]; //unsigend short 可以正常打印

	status = SFSP->OpenVolume(SFSP,&root);
	assert(status,L"SFSP->OpenVolume");
	status = root->Open(root, &file, file_name, EFI_FILE_MODE_READ, 0);
	assert(status,L"root->Open");
	status = file->Read(file, &buf_size, (void *)&file_buf);
	assert(status,L"file->Read");

	puts(file_buf);

	file->Close(file);
	root->Close(root);

}


int ls(void)
{
	unsigned long long status;
    struct  EFI_FILE_PROTOCOL *root;
    unsigned long long buf_size;
    unsigned char file_buf[MAX_FILE_BUF];
	struct EFI_FILE_INFO *file_info;
	int idx = 0;
	int file_num;

    
    status = SFSP->OpenVolume(SFSP,&root);
	assert(status,L"SFSP->OpenVolume");

	while (1)
	{
		buf_size = MAX_FILE_BUF;
		status = root->Read(root, &buf_size, (void *)file_buf);
		assert(status, L"root->Read");
		if (!buf_size) break;  //当读取完后返回buf_size=0
		
		file_info = (struct EFI_FILE_INFO *)file_buf;
		strncpy(file_list[idx].name, file_info->FileName, MAX_FILE_NAME_LEN - 1);
		file_list[idx].name[MAX_FILE_NAME_LEN-1]=L'\0';
		puts(file_list[idx].name);
		puts(L" ");
		idx++;
	}
	puts(L"\r\n");
	file_num = idx;

	root->Close(root);

	return file_num;
	

}

void shell(void)
{
    unsigned short com[MAX_COMMAND_LEN];
    struct RECT r = {10, 10, 100, 200};

    while (TRUE) {
        puts(L"poiOS> ");
        if (gets(com, MAX_COMMAND_LEN) <= 0)
            continue;

        if (!strcmp(L"hello", com))
            puts(L"Hello UEFI!\r\n");
        else if (!strcmp(L"rect", com))
            draw_rect(r, white);
        else if (!strcmp(L"gui", com))
            gui();
        else if (!strcmp(L"pstat", com))
            pstat();
        else if (!strcmp(L"ls", com))
            ls();
        else if (!strcmp(L"cat", com))
            cat(L"qwe");
        else if (!strcmp(L"edit", com))
            edit(L"qwe");
        else
            puts(L"Command not found.\r\n");
    }
}
