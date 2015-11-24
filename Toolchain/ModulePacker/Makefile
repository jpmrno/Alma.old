include ../../Makevars

SOURCES = $(wildcard *.c)
HEADERS = -I .

all: ../$(MODULE_PACKER_NAME)

../$(MODULE_PACKER_NAME): $(SOURCES)
	$(SYS_GCC) $< $(HEADERS) -o $@

clean:
	rm -f ../$(MODULE_PACKER_NAME)

.PHONY: all clean
