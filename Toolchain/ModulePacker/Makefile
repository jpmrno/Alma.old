include ../../Makevars

SOURCES = $(wildcard *.c)

all: $(MODULE_PACKER_NAME)

$(MODULE_PACKER_NAME): $(SOURCES)
	$(SYS_GCC) $(SOURCES) -o ../$(MODULE_PACKER_NAME)

clean:
	rm -f ../$(MODULE_PACKER_NAME)

.PHONY: all clean
