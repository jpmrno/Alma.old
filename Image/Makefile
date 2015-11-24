include ../Makevars

SYSTEM_PACKED = system.bin
USERLAND_FILES = $(wildcard ../$(USERLAND_PATH)/*.bin)

VMDK = $(SO_NAME).vmdk
QCOW2 = $(SO_NAME).qcow2
IMG = $(SO_NAME).img
IMG_SIZE = 6291456

QEMU_CONVERT = qemu-img convert -f raw

all: $(SYSTEM_PACKED) $(IMG) $(VMDK) $(QCOW2)

$(SYSTEM_PACKED): $(USERLAND_FILES)
	../$(MODULE_PACKER) ../$(KERNEL) $<

$(IMG): $(SYSTEM_PACKED)
	../$(FILESYSTEM) $(IMG) initialize $(IMG_SIZE) ../$(FILESYSTEM_MBR) ../$(BOOTLOADER) $<

$(VMDK): $(IMG)
	$(QEMU_CONVERT) -O vmdk $(IMG) $(VMDK)

$(QCOW2): $(IMG)
	$(QEMU_CONVERT) -O qcow2 $(IMG) $(QCOW2)

clean:
	rm -f $(IMG) $(VMDK) $(QCOW2) $(SYSTEM_PACKED)

.PHONY: all clean
