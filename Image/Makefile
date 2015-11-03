include ../Makevars

MAIN_FOLDER = ..

KERNEL_PACKED = packedKernel.bin
USERLAND_FILES = $(wildcard $(MAIN_FOLDER)/$(USERLAND_PATH)/*.bin)

VMDK = $(SO_NAME).vmdk
QCOW2 = $(SO_NAME).qcow2
IMG = $(SO_NAME).img
IMG_SIZE = 6291456

QEMU_CONVERT = qemu-img convert -f raw

all: $(IMG) $(VMDK) $(QCOW2)

$(KERNEL_PACKED): $(USERLAND_FILES)
	$(MAIN_FOLDER)/$(MODULE_PACKER) $(MAIN_FOLDER)/$(KERNEL) $(USERLAND_FILES)

$(IMG): $(KERNEL_PACKED)
	$(MAIN_FOLDER)/$(FILESYSTEM) $(IMG) initialize $(IMG_SIZE) $(MAIN_FOLDER)/$(FILESYSTEM_MBR) $(MAIN_FOLDER)/$(BOOTLOADER) $(KERNEL_PACKED)

$(VMDK): $(IMG)
	$(QEMU_CONVERT) -O vmdk $(IMG) $(VMDK)

$(QCOW2): $(IMG)
	$(QEMU_CONVERT) -O qcow2 $(IMG) $(QCOW2)

clean:
	rm -rf $(IMG) $(VMDK) $(QCOW2) *.bin

.PHONY: all clean
