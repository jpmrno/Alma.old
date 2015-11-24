include ../../Makevars

SRC_PATH = src
BOOTSECTORS_PATH = $(SRC_PATH)/bootsectors

ASM-FLAGS =

all: ../$(BOOTLOADER_PXESTART_NAME) ../$(FILESYSTEM_MBR_NAME) ../$(BOOTLOADER_NAME)

../$(BOOTLOADER_PXESTART_NAME):
	$(ASM) $(ASM-FLAGS) $(BOOTSECTORS_PATH)/pxestart.asm -o $@

../$(FILESYSTEM_MBR_NAME):
	$(ASM) $(ASM-FLAGS) $(BOOTSECTORS_PATH)/bmfs_mbr.asm -o $@

../$(BOOTLOADER_NAME):
	cd $(SRC_PATH); $(ASM) $(ASM-FLAGS) pure64.asm -o ../$@

clean:
	rm -f ../$(BOOTLOADER_PXESTART_NAME)
	rm -f ../$(FILESYSTEM_MBR_NAME)
	rm -f ../$(BOOTLOADER_NAME)

.PHONY: all clean
