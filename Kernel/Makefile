include ../Makevars
include Makevars

SOURCES_C = $(wildcard *.c & $(SRC_C)/*.c & $(SRC_C)/**/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm & $(SRC_ASM)/**/*.asm)

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECT_LOADER = $(SOURCE_LOADER:.asm=.o)

LIBS = $(wildcard ../$(COMMONS_SRC_C)/*.o & ../$(COMMONS_SRC_C)/**/*.o)
LIBS += $(wildcard ../$(COMMONS_SRC_ASM)/*.o & ../$(COMMONS_SRC_ASM)/**/*.o)

SRC_HEADERS += $(wildcard ../$(COMMONS_HEADERS) & ../$(COMMONS_HEADERS)/*/.)
HEADERS = $(foreach HEADER,$(SRC_HEADERS),-I $(HEADER))

GCC_FLAGS += $(GCC_WARNINGS)

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
