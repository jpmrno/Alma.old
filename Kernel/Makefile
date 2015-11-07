include ../Makevars
include Makevars

SOURCES_C = $(wildcard *.c & $(SRC_C)/*.c & $(SRC_C)/**/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm & $(SRC_ASM)/**/*.asm)

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECT_LOADER = $(SOURCE_LOADER:.asm=.o)

HEADERS = $(foreach HEADER,$(SRC_HEADERS),-I $(HEADER))

# TODO: Verify & Improve
LIBS = $($(wildcard ../$(COMMON_SRC_ASM)/*.asm):.asm=.o) $($(wildcard ../$(COMMON_SRC_C)/*.c):.c=.o)

all: $(KERNEL_NAME)

$(KERNEL_NAME): $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM) $(LIBS)
	$(LD) $(LD_FLAGS) -T kernel.ld -o $@ $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM) $(LIBS)

%.o: %.c
	$(GCC) $(GCC_FLAGS) $(HEADERS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	rm -f $(KERNEL_NAME) $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM)

.PHONY: all clean
