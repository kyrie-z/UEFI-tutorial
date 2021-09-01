#ifndef _EFI_H_
#define _EFI_H_


struct EFI_GUID {
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
};


struct EFI_SYSTEM_TABLE {
    char _buf[60];
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
        unsigned long long _buf;
        unsigned long long (*OutputString)(
            struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
            unsigned short *String);
        unsigned long long _buf2[4];
        unsigned long long (*ClearScreen)(
             struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    } *ConOut;
    unsigned long long _buf3[3];
    //BS系统表
    struct EFI_BOOT_SERVICES {
        char _buf1[24];

        // Task Priority Services
        unsigned long long _buf2[2];

        // Memory Services
        unsigned long long _buf3[5];

        // Event & Timer Services
        unsigned long long _buf4[2];
        unsigned long long (*WaitForEvent)(
            unsigned long long NumberOfEvents,
            void **Event,
            unsigned long long *Index);
        unsigned long long _buf4_2[3];

        // Protocol Handler Services
        unsigned long long _buf5[9];

        // Image Services
        unsigned long long _buf6[5];

        // Miscellaneous Services
        unsigned long long _buf7[2];
        unsigned long long (*SetWatchdogTimer)(
            unsigned long long Timeout,
            unsigned long long WatchdogCode,
            unsigned long long DataSize,
            unsigned short *WatchdogData);

        // DriverSupport Services
        unsigned long long _buf8[2];

        // Open and Close Protocol Services
        unsigned long long _buf9[3];

        // Library Services
        unsigned long long _buf10[2];
        unsigned long long (*LocateProtocol)(
            struct EFI_GUID *Protocol,
            void *Registration,
            void **Interface);
        unsigned long long _buf10_2[2];

        // 32-bit CRC Services
        unsigned long long _buf11;

        // Miscellaneous Services
        unsigned long long _buf12[3];
    } * BootServices;
};



//定义像素在帧缓冲区中的格式 32位 (将数据转移到图形屏幕，像素在帧缓冲区中的格式)
struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL {
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reserved;
};

//图形输出协议，绘制图形是通过向帧缓冲区写入像素数据来实现的
struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
    unsigned long long _buf[3];
    struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
        unsigned int MaxMode; //显示模式的最大值
        unsigned int Mode; //图形设备的当前模式
        struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION { //获取屏幕分辨率和像素格式
            unsigned int Version;
            unsigned int HorizontalResolution;
            unsigned int VerticalResolution;
            enum EFI_GRAPHICS_PIXEL_FORMAT { //像素格式
                PixelRedGreenBlueReserved8BitPerColor,
                PixelBlueGreenRedReserved8BitPerColor,
                PixelBitMask,
                PixelBltOnly,
                PixelFormatMax
            } PixelFormat;
        } *Info;
        unsigned long long SizeOfInfo;
        unsigned long long FrameBufferBase; //帧缓冲区的起始地址
    } *Mode;
};

//指针设备状态
struct EFI_SIMPLE_POINTER_STATE {
    int RelativeMovementX;      /* X轴方向的相对移动量 */
    int RelativeMovementY;      /* Y轴方向的相对移动量 */
    int RelativeMovementZ;      /* Z轴方向的相对移动量 */
    unsigned char LeftButton;   /* 左键状态，按下为1，松开为0 */
    unsigned char RightButton;  /* 右键状态，同上 */
};


//鼠标指针协议
struct EFI_SIMPLE_POINTER_PROTOCOL {
    unsigned long long (*Reset)(
        struct EFI_SIMPLE_POINTER_PROTOCOL *This,
        unsigned char ExtendedVerification);
    unsigned long long (*GetState)(
        struct EFI_SIMPLE_POINTER_PROTOCOL *This,
        struct EFI_SIMPLE_POINTER_STATE *State);
    void *WaitForInput;
};



extern struct EFI_SYSTEM_TABLE *ST;
extern struct EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
extern struct EFI_SIMPLE_POINTER_PROTOCOL *SPP;

void efi_init(struct EFI_SYSTEM_TABLE *SystemTable);

#endif