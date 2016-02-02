#include <define.h>
#include <modules.h>
#include <memory.h>
#include <video.h>
#include <output.h>
#include <debug.h>
#include <idt.h>
#include <interrupts.h>
#include <pic.h>

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

static void * module_addresses[] = {
	(void *) MODULE_SHELL_ADDRESS // Shell address
};

void * kernel_init() {	
	module_load(&endOfKernelBinary, module_addresses);

	kernel_bss_clear();

	return kernel_stack_base();
}

int kernel_main() {
	video_init();
	out_init();
	out_printf("Initializing video driver... [Done]\n");
	out_printf("Loading modules... [Done]\n");

	out_printf("Initializing serial port... ");
	serial_init();
	out_printf("[Done]\n");

	debug_init();
	debug("# Kernel Main\n");
	debug("## Kernel's binary\n");
	debug("\ttext: %h\n", (uint64_t)&text);
	debug("\trodata: %h\n", (uint64_t)&rodata);
	debug("\tdata: %h\n", (uint64_t)&data);
	debug("\tbss: %h\n\n", (uint64_t)&bss);

	debug("\tSerial inited\n\n");

	idt_init(); // TODO:

	out_printf("Disabling interrupts... ");
	_interrupt_clear();
	debug("\tCLI\n");
	_pic_mask((uint8_t) 0xFF); // TODO: 0xFF define
	debug("\tPIC Masc set to: 0xFF\n");
	out_printf("[Done]\n");

	out_printf("Drivers loading: \n");

	out_printf("Enabling interrupts... ");
	_interrupt_set();
	debug("\tSTI\n");
	_pic_mask((uint8_t) 0xFC); // TODO: 0xFC define
	debug("\tPIC Masc set to: 0xFC\n\n");
	out_printf("[Done]\n");
	
	//((EntryPoint) module_addresses[MODULE_SHELL_INDEX])();

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
