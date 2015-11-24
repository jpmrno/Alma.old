include ../Makevars

LIBS = shared system general

all: shared system general

shared:
	$(MAKE) -C $@ all

system: shared
	$(MAKE) -C $@ all

general: shared system
	$(MAKE) -C $@ all

clean:
	$(foreach LIB, $(LIBS), $(MAKE) -C $(LIB) clean;)

.PHONY: all shared system general clean
