#include <define.h>
#include <modules.h>
#include <memory.h>
#include <video.h>
#include <output.h>

#define PAGE_SIZE 0x1000

#define MODULE_SHELL_INDEX 0
#define MODULE_SHELL_ADDRESS 0x400000

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

typedef int (* EntryPoint)();

static void * kernel_stack_base();
static void kernel_bss_clear();

static void * moduleAddresses[] = {
	(void *) MODULE_SHELL_ADDRESS // Shell address
};

void * kernel_init() {	
	module_load(&endOfKernelBinary, moduleAddresses);
	kernel_bss_clear();

	return kernel_stack_base();
}

int kernel_main() {
	video_init();
	out_init();
	out_printf("Loading modules... [Done]\n");
	out_printf("Initializing video driver... [Done]\n");
	
	//((EntryPoint) moduleAddresses[MODULE_SHELL_INDEX])();

	return 0;
}

static void * kernel_stack_base() {
	return (void *) (
		(uint64_t) &endOfKernel			// End of kernel address
		+ ((uint64_t) PAGE_SIZE) * 8	// The size of the stack itself, 32KiB
		- sizeof(uint64_t)				// Begin at the top of the stack
	);
}

static void kernel_bss_clear() {
	memset(&bss, 0, &endOfKernel - &bss);
}
