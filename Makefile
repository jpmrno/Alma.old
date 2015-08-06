
all:  bootloader kernel userland image

bootloader:
	cd Bootloader; make all

kernel:
	cd Kernel; make all

userland:
	cd Userland; make all

image: kernel bootloader userland
	cd Image; make all

clean:
	cd Bootloader; make clean
	cd Image; make clean
	cd Kernel; make clean
	cd Userland; make clean

run: clean all
	qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512

.PHONY: bootloader image collections kernel userland all clean
