#include "main.h"
#include "tpm20.h"
#include "common.h"

struct EFI_GUID tpm_guid = {0x607f766c, 0x7455, 0x42be, {0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f }};

struct EFI_TCG2_PROTOCOL *TCG;
    typedef struct {
        TPM2_COMMAND_HEADER Header;
        UINT16 bytesRequested;
    } TPM2_GET_RANDOM_COMMAND;

    typedef struct {
        TPM2_RESPONSE_HEADER Header;
        TPM2B_DIGEST randomBytes;
    } TPM2_GET_RANDOM_RESPONSE;


UINT16 SwapBytes16 (UINT16  Value)
{
  return (UINT16)((Value<< 8) | (Value>> 8));
}

UINT32 SwapBytes32 (UINT32  Value)
{
  UINT32  LowerBytes;
  UINT32  HigherBytes;
 
  LowerBytes  = (UINT32)SwapBytes16 ((UINT16)Value);
  HigherBytes = (UINT32)SwapBytes16 ((UINT16)(Value >> 16));
 
  return (LowerBytes << 16 | HigherBytes);
}

void efi_main(void *ImageHandle __attribute__((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello UEFI!\r\n");

    unsigned long long status;
    ST = SystemTable;
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    SystemTable->BootServices->LocateProtocol(&tpm_guid, NULL, (void **)&TCG);

    TPM2_GET_RANDOM_COMMAND CmdBuffer;
    UINT32 CmdBufferSize;
    TPM2_GET_RANDOM_RESPONSE RecvBuffer;
    UINT32 RecvBufferSize;

    CmdBuffer.Header.tag         = SwapBytes16(TPM_ST_NO_SESSIONS);
    CmdBuffer.Header.commandCode = SwapBytes32(TPM_CC_GetRandom);
    CmdBuffer.bytesRequested     = SwapBytes16(16);
    CmdBufferSize = sizeof(CmdBuffer.Header) + sizeof(CmdBuffer.bytesRequested);
    CmdBuffer.Header.paramSize = SwapBytes32(CmdBufferSize);
    RecvBufferSize = sizeof(RecvBuffer);
    status = TCG->SubmitCommand(TCG, CmdBufferSize, (UINT8 *)&CmdBuffer, RecvBufferSize, (UINT8 *)&RecvBuffer);
    assert(status, L"SubmitCommand"); 
    
    UINT16 res = SwapBytes32(RecvBuffer.Header.responseCode);
    puts(L"ResponseCode is");
    puth(res,16);
    puts("\r\n");

    UINT16 i;
    UINT16 size = SwapBytes16(RecvBuffer.randomBytes.size);
    puts(L"generated value: ");
    for(i=0; i<size; i++)
        puth(RecvBuffer.randomBytes.buffer[size-i-1],1);
    puts(L"\r\n");

   
    while (1)
        ;
}