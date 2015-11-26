include ../Makevars

LIBS = shared system api

all: shared system api

shared:
	$(MAKE) -C $@ all

system: shared
	$(MAKE) -C $@ all

api: shared system
	$(MAKE) -C $@ all

clean:
	$(foreach LIB, $(LIBS), $(MAKE) -C $(LIB) clean;)

.PHONY: all shared system api clean
