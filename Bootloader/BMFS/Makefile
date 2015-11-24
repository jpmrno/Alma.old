include ../../Makevars

GCC_FLAGS = -ansi -std=c99 -Wall -pedantic

all: ../$(FILESYSTEM_NAME)

../$(FILESYSTEM_NAME):
	$(SYS_GCC) $(GCC_FLAGS) bmfs.c -o $@

clean:
	rm -f ../$(FILESYSTEM_NAME)

.PHONY: all clean
