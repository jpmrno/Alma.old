include Makefile.inc

MODULE=shell

all: $(MODULE)

$(MODULE):
	cd $(MODULE); make

clean:
	cd $(MODULE); make clean
	rm -rf *.bin


.PHONY: $(MODULE) all clean
