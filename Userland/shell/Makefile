include ../Makefile.inc

NAME=shell
MODULE=../$(NAME).bin
SOURCES=$(wildcard src/*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
MODULESRC=$(NAME).c
MODULEOBJECT=$(MODULESRC:.c=.o)

all: clean $(MODULE)

$(MODULE): $(MODULEOBJECT) $(OBJECTS) $(OBJECTS_ASM)
	$(LD) -T $(NAME).ld -o $(MODULE) $(MODULEOBJECT) $(OBJECTS) $(OBJECTS_ASM)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(MODULEOBJECT):
	$(GCC) -c $(GCCFLAGS) $(MODULESRC) -o $(MODULEOBJECT)

clean:
	rm -rf asm/*.o *.o *.bin
	rm -rf src/*.o *.o *.bin

.PHONY: all clean
