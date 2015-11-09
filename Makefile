include Makevars

IMAGE = $(IMAGE_PATH)/$(SO_NAME).qcow2
QEMU = qemu-system-x86_64
QEMU_FLAGS = -hda $(IMAGE) -m 512

all: $(TOOLCHAIN_PATH) $(BOOTLOADER_PATH) $(COMMONS_PATH) $(KERNEL_PATH) $(USERLAND_PATH) $(IMAGE_PATH)

$(TOOLCHAIN_PATH):
	$(MAKE) -C $(TOOLCHAIN_PATH) all

$(BOOTLOADER_PATH):
	$(MAKE) -C $(BOOTLOADER_PATH) all

$(COMMONS_PATH):
	$(MAKE) -C $(COMMONS_PATH) all

$(KERNEL_PATH):
	$(MAKE) -C $(KERNEL_PATH) all

$(USERLAND_PATH):
	$(MAKE) -C $(USERLAND_PATH) all

$(IMAGE_PATH): $(TOOLCHAIN_PATH) $(BOOTLOADER_PATH) $(KERNEL_PATH) $(USERLAND_PATH)
	$(MAKE) -C $(IMAGE_PATH) all

clean: cleanall

cleanall:
	$(MAKE) -C $(TOOLCHAIN_PATH) clean
	$(MAKE) -C $(BOOTLOADER_PATH) clean
	$(MAKE) -C $(COMMONS_PATH) clean
	$(MAKE) -C $(KERNEL_PATH) clean
	$(MAKE) -C $(USERLAND_PATH) clean
	$(MAKE) -C $(IMAGE_PATH) clean

run: clean all
	$(QEMU) $(QEMU_FLAGS)

.PHONY: $(TOOLCHAIN_PATH) $(BOOTLOADER_PATH) $(COMMONS_PATH) $(KERNEL_PATH) $(USERLAND_PATH) $(IMAGE_PATH) all cleanall clean
