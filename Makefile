include Makevars

all: toolchain bootloader libs kernel image

toolchain:
	$(MAKE) -C $(TOOLCHAIN_PATH) all

bootloader:
	$(MAKE) -C $(BOOTLOADER_PATH) all

libs:
	$(MAKE) -C $(LIBS_PATH) all

kernel: libs
	$(MAKE) -C $(KERNEL_PATH) all

userland: libs
	$(MAKE) -C $(USERLAND_PATH) all

image: toolchain bootloader kernel
	$(MAKE) -C $(IMAGE_PATH) all

clean:
	$(MAKE) -C $(LIBS_PATH) clean
	$(MAKE) -C $(KERNEL_PATH) clean
	$(MAKE) -C $(USERLAND_PATH) clean
	$(MAKE) -C $(IMAGE_PATH) clean

cleanall:
	$(MAKE) -C $(TOOLCHAIN_PATH) clean
	$(MAKE) -C $(BOOTLOADER_PATH) clean
	$(MAKE) -C $(LIBS_PATH) clean
	$(MAKE) -C $(KERNEL_PATH) clean
	$(MAKE) -C $(USERLAND_PATH) clean
	$(MAKE) -C $(IMAGE_PATH) clean

run: clean all
	$(QEMU) $(QEMU_DEBUG) $(QEMU_LOG) $(QEMU_SOUND) -hda $(SOURCE_IMAGE) $(QEMU_FLAGS)

.PHONY: all toolchain bootloader libs kernel userland image clean
