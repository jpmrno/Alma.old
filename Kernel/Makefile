include ../Makevars

SRC_C = src
SRC_DRIVERS = $(SRC_C)/drivers
SRC_ASM = asm
SRC_HEADERS = include
DIRS = $(SRC_C) $(SRC_DRIVERS) $(SRC_ASM)

SOURCES_C = $(wildcard *.c & $(SRC_C)/*.c & $(SRC_DRIVERS)/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm)
SRC_LOADER = loader.asm

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECT_LOADER = $(SRC_LOADER:.asm=.o)

STATICLIBS =

GCC_FLAGS = -Wall -Wextra -m64 -fno-exceptions -fno-asynchronous-unwind-tables -mno-mmx -mno-sse -mno-sse2 -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc -mno-red-zone -Wall -ffreestanding -nostdlib -fno-common -std=c99
#AR_FLAGS = rvs # ¿¿¿¿????
ASM_FLAGS = -felf64
LD_FLAGS = --warn-common -z max-page-size=0x1000

all: $(KERNEL_NAME)

$(KERNEL_NAME): $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM) $(STATICLIBS)
	$(LD) $(LD_FLAGS) -T kernel.ld -o $(KERNEL_NAME) $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCC_FLAGS) -I $(SRC_HEADERS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

$(OBJECT_LOADER):
	$(ASM) $(ASM_FLAGS) $(SRC_LOADER) -o $(OBJECT_LOADER)

clean:
	$(foreach DIR, $(DIRS), rm -rf $(DIR)/*.o;)
	rm -rf *.o $(KERNEL_NAME)

.PHONY: all clean
