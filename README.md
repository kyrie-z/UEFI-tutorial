##run qemu:
kvm --bios /usr/share/ovmf/OVMF.fd -hda fat:rw:. -net none

**support usbmouse:**
kvm: -usb -device usb-mouse

efishell: load fs0:\EFI\UsbMouseDxe.efi
