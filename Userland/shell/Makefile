include ../../Makevars
include ../Makevars

# Change name for new module
MODULE_NAME = shell
# ^^^^^^^^^^^^^^^^^^^^^^^^^^

MODULE = ../$(MODULE_NAME).$(MODULE_TYPE)

SRC_C = src
SRC_ASM = asm
SRC_HEADERS = include
DIRS = $(SRC_C) $(SRC_ASM)

SOURCES_C = $(wildcard $(SRC_C)/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm)
SRC_LOADER = $(MODULE_NAME).c

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECT_LOADER = $(SRC_LOADER:.c=.o)

STATICLIBS =

all: $(MODULE)

$(MODULE): $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM)
	$(LD) $(LD_FLAGS) -T $(MODULE_NAME).ld -o $(MODULE) $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM)

%.o: %.c
	$(GCC) $(GCC_FLAGS) -I $(SRC_HEADERS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

$(OBJECT_LOADER):
	$(GCC) -c $(GCC_FLAGS) $(SRC_LOADER) -o $(OBJECT_LOADER)

clean:
	$(foreach DIR, $(DIRS), rm -rf $(DIR)/*.o;)
	rm -rf *.o
	rm -f $(MODULE)

.PHONY: all clean
