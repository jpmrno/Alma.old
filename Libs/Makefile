include ../Makevars

LIBS = shared api

all: shared api

shared:
	$(MAKE) -C $@ all

api: shared
	$(MAKE) -C $@ all

clean:
	$(foreach LIB, $(LIBS), $(MAKE) -C $(LIB) clean;)

.PHONY: all shared api clean
