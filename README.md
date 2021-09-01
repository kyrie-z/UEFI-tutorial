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

通过LoadImage()加载的UEFI应用程序，它的可执行文件必须是一个可重定位目标文件(shared object), 在编译时加上-share


启动内核运行后需要找到一个根文件系统，root=... 告诉内核根文件系统的挂载地方。可以通过busybox和脚本来构建一个基于busybox的根文件系统镜像，也可通过debootstrap构建一个基于发行版的..., 或者通过initramfs生成，这也是在linux桌面发行版本用的最多的工具。
生成根文件系统后需要挂载到qemu中，通过 -drive file=./hdb/rootfs.img,index=1,format=raw  将根文件系统挂载到虚拟机的/dev/sdb中
