include ../../Makevars
include ../Makevars
include Makevars

MODULE = ../$(MODULE_NAME).$(MODULE_TYPE)

SOURCES_C = $(wildcard $(SRC_C)/*.c & $(SRC_C)/**/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm & $(SRC_ASM)/**/*.asm)

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECT_LOADER = $(SOURCE_LOADER:.c=.o)

HEADERS = $(foreach HEADER,$(SRC_HEADERS),-I $(HEADER))

# TODO: Verify & Improve
LIBS = $($(wildcard ../$(COMMON_SRC_ASM)/*.asm):.asm=.o) $($(wildcard ../$(COMMON_SRC_C)/*.c):.c=.o)

all: $(MODULE)

$(MODULE): $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM) $(LIBS)
	$(LD) $(LD_FLAGS) -T $(MODULE_NAME).ld -o $@ $^

%.o: %.c
	$(GCC) $(GCC_FLAGS) $(HEADERS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	rm -f $(MODULE) $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM)

.PHONY: all clean
