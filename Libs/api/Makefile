include ../../Makevars
include ../Makevars
include Makevars

LIB = ../lib$(LIB_NAME).a
DEPS = $(foreach LIB_DEP,$(LIB_DEPS),-l$(LIB_DEP))

SOURCES_C = $(wildcard $(SRC_C)/*.c & $(SRC_C)/**/*.c)
SOURCES_ASM = $(wildcard $(SRC_ASM)/*.asm & $(SRC_ASM)/**/*.asm)

OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_ASM = $(SOURCES_ASM:.asm=.o)

SRC_HEADERS += ../../$(LIBS_HEADERS)
HEADERS = $(foreach HEADER,$(SRC_HEADERS),-I $(HEADER))

GCC_FLAGS += $(GCC_WARNINGS)

all: $(LIB)

$(LIB): $(OBJECTS_C) $(OBJECTS_ASM)
	$(AR) $(AR_FLAGS) $@ $(OBJECTS_C) $(OBJECTS_ASM)

%.o: %.c
	$(GCC) $(GCC_FLAGS) $(HEADERS) -c $< -o $@ -L../../$(LIBS_PATH) $(DEPS)

%.o: %.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

clean:
	rm -f $(LIB) $(OBJECTS_C) $(OBJECTS_ASM)

.PHONY: all clean
