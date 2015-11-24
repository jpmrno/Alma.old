include ../../Makevars

SOURCES = $(wildcard *.c)

all: ../$(MODULE_PACKER_NAME)

../$(MODULE_PACKER_NAME): $(SOURCES)
	$(SYS_GCC) $< -o $@

clean:
	rm -f ../$(MODULE_PACKER_NAME)

.PHONY: all clean
