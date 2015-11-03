include ../Makevars

MODULES = shell

all:
	$(foreach MODULE, $(MODULES), $(MAKE) -C $(MODULE) all;)

clean:
	$(foreach MODULE, $(MODULES), $(MAKE) -C $(MODULE) clean;)

.PHONY: all clean
