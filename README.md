##run qemu:
kvm --bios /usr/share/ovmf/OVMF.fd -hda fat:rw:. -net none

**support usbmouse:**
kvm: -usb -device usb-mouse

efishell: load fs0:\EFI\UsbMouseDxe.efi


`apt install dox2unix`
将文本文件转换为UEFI可识别的Unicode编码。
```
cat << EOF | unix2dos | iconv -f UTF-8 -t UCS-2LE > ./abc
        1234567890
        abcdefg
        blah blah blah
        EOF
```

