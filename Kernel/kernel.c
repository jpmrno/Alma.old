#include <video.h>
#include <output.h>
#include <modules.h>
#include <memory.h>

#define PAGE_SIZE 0x1000

#define MODULE_SHELL_INDEX 0
#define ADDRESS_SHELL 0x400000

typedef int (* EntryPoint)();

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static void * getStackBase();

static void * moduleAddresses[] = {
	(void *) ADDRESS_SHELL // Shell address
};

void * kernel_init() {	
	module_load(&endOfKernelBinary, moduleAddresses);
	memset(&bss, 0, &endOfKernel - &bss); // Clear BSS
	
	return getStackBase();
}

int kernel_main() {
	video_init();
	out_init();
	out_printf("Loading modules... [Done]\n");
	out_printf("Initializing video driver... [Done]\n");
	
	//((EntryPoint) moduleAddresses[MODULE_SHELL_INDEX])();
	while(1) {}

	return 0;
}

static void * getStackBase() {
	return (void *) (
		(uint64_t) &endOfKernel			// End of kernel address
		+ ((uint64_t) PAGE_SIZE) * 8	// The size of the stack itself, 32KiB
		- sizeof(uint64_t)				// Begin at the top of the stack
	);
}
