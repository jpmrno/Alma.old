include ../Makevars

SOURCES_C = $(wildcard ../$(COMMONS_SRC_C)/*.c & ../$(COMMONS_SRC_C)/**/*.c)
SOURCES_ASM = $(wildcard ../$(COMMONS_SRC_ASM)/*.asm & ../$(COMMONS_SRC_ASM)/**/*.asm)
SOURCES_HEADERS = $(wildcard ../$(COMMONS_HEADERS) & ../$(COMMONS_HEADERS)/*/.)

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)

HEADERS = $(foreach HEADER,$(SOURCES_HEADERS),-I $(HEADER))

GCC_FLAGS = $(GCC_WARNINGS) -m64 -fno-exceptions -fno-asynchronous-unwind-tables -mno-mmx -mno-sse -mno-sse2 -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc -mno-red-zone -ffreestanding -nostdlib -fno-common -std=c99
ASM_FLAGS = -felf64

all: $(SOURCES_HEADERS) $(OBJECTS_C) $(OBJECTS_ASM)

%.o: %.c
	$(GCC) $(GCC_FLAGS) $(HEADERS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	rm -f $(OBJECTS_C) $(OBJECTS_ASM)

.PHONY: all clean
