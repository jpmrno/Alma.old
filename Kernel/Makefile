include ../Makevars
include Makevars

SOURCES_C = $(wildcard *.c & $(SRC_C)/*.c & $(SRC_C)/**/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm & $(SRC_ASM)/**/*.asm)

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)
OBJECT_LOADER = $(SOURCE_LOADER:.asm=.o)

SRC_HEADERS += ../$(LIBS_HEADERS)
HEADERS = $(foreach HEADER,$(SRC_HEADERS),-I $(HEADER))
DEPS = $(foreach LIB_DEP,$(LIB_DEPS),-l$(LIB_DEP))

GCC_FLAGS += $(GCC_WARNINGS)

all: ../$(KERNEL)

../$(KERNEL): $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM)
	$(LD) $(LD_FLAGS) -T kernel.ld -o $@ $^ -L../$(LIBS_PATH) $(DEPS)

%.o: %.c
	$(GCC) $(GCC_FLAGS) $(HEADERS) -c $< -o $@ -L../$(LIBS_PATH) $(DEPS)

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	rm -f ../$(KERNEL) $(OBJECT_LOADER) $(OBJECTS_C) $(OBJECTS_ASM)

.PHONY: all clean
