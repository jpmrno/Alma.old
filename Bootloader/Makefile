include ../Makevars

DIRS = BMFS Pure64

all:
	$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) all;)

clean:
	$(foreach DIR, $(DIRS), $(MAKE) -C $(DIR) clean;)

.PHONY: all clean
