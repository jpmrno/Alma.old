include ../Makevars

SRC_C = src
SRC_DRIVERS = $(SRC_C)/drivers
SRC_ASM = asm
HEADERS = include ../$(COMMON_HEADERS)
DIRS = $(SRC_C) $(SRC_DRIVERS) $(SRC_ASM)

SOURCES_C = $(wildcard *.c & $(SRC_C)/*.c & $(SRC_DRIVERS)/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm)
SRC_LOADER = loader.asm

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECT_LOADER = $(SRC_LOADER:.asm=.o)

# TODO: Verify
LIBS = $($(wildcard ../$(COMMON_SRC_ASM)/*.asm):.asm=.o) $($(wildcard ../$(COMMON_SRC_C)/*.c):.c=.o)

GCC_FLAGS = $(GCC_WARNINGS) -m64 -fno-exceptions -fno-asynchronous-unwind-tables -mno-mmx -mno-sse -mno-sse2 -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc -mno-red-zone -ffreestanding -nostdlib -fno-common -std=c99
#AR_FLAGS = rvs # ¿¿¿¿????
ASM_FLAGS = -felf64
LD_FLAGS = --warn-common -z max-page-size=0x1000

all: $(KERNEL_NAME)

$(KERNEL_NAME): $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM) $(LIBS)
	$(LD) $(LD_FLAGS) -T kernel.ld -o $(KERNEL_NAME) $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM) $(LIBS)

%.o: %.c
	$(GCC) $(GCC_FLAGS) $(foreach HEADER, $(HEADERS), -I $(HEADER)) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

$(OBJECT_LOADER):
	$(ASM) $(ASM_FLAGS) $(SRC_LOADER) -o $(OBJECT_LOADER)

clean:
	$(foreach DIR, $(DIRS), rm -rf $(DIR)/*.o;)
	rm -rf *.o $(KERNEL_NAME)

.PHONY: all clean
