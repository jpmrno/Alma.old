include Makevars

IMAGE = $(IMAGE_PATH)/$(SO_NAME).qcow2
QEMU = qemu-system-x86_64
QEMU_FLAGS = -hda $(IMAGE) -m 512

all: toolchain bootloader common kernel userland image

toolchain:
	$(MAKE) -C $(TOOLCHAIN_PATH) all

bootloader:
	$(MAKE) -C $(BOOTLOADER_PATH) all

common:
	$(MAKE) -C $(COMMONS_PATH) all

kernel: common
	$(MAKE) -C $(KERNEL_PATH) all

userland: common
	$(MAKE) -C $(USERLAND_PATH) all

image: toolchain bootloader kernel userland
	$(MAKE) -C $(IMAGE_PATH) all

clean:
	$(MAKE) -C $(TOOLCHAIN_PATH) clean
	$(MAKE) -C $(BOOTLOADER_PATH) clean
	$(MAKE) -C $(COMMONS_PATH) clean
	$(MAKE) -C $(KERNEL_PATH) clean
	$(MAKE) -C $(USERLAND_PATH) clean
	$(MAKE) -C $(IMAGE_PATH) clean

run: all
	$(QEMU) $(QEMU_FLAGS)

.PHONY: all toolchain bootloader common kernel userland image clean
