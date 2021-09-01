TARGET = draw.efi
ARCH = x86_64
CC   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -e efi_main -nostdinc -nostdlib -shared -fno-builtin -Wl,--subsystem,10 -v

target: $(TARGET)
	echo $(TARGET)

%.efi: *.c 
	$(CC) $(CFLAGS) -o $@ $^
