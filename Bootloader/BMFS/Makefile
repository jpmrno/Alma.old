include ../../Makevars
include Makevars

FILESYSTEM_FILE = ../$(FILESYSTEM_NAME)

all: $(FILESYSTEM_FILE)

$(FILESYSTEM_FILE):
	$(SYS_GCC) $(GCC_FLAGS) $(SOURCE_FILESYSTEM) -o $@

clean:
	rm -f $(FILESYSTEM_FILE)

.PHONY: all clean
