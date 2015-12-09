#include <interrupt.h>
#include <idtManager.h>
#include <moduleLoader.h>
#include <terminal.h>
#include <memory.h>
#include <terminal01.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const shellAddress = (void *) 0x400000;

terminal_st terminal_active = {0}; // TODO: Remove

typedef int (*EntryPoint)();

void * getStackBase() {
	return (void *)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				// The size of the stack itself, 32KiB
		- sizeof(uint64_t)			// Begin at the top of the stack
	);
}

void * initializeKernelBinary() {	
	void * moduleAddresses[] = {
		shellAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	memset(&bss, 0, &endOfKernel - &bss); // Clear BSS
	
	initTerminal();
	print("[x64BareBones]\n");
	print("\tInitializing kernel's binary... \n");
	print("\t\ttext: 0x");
	printHex((uint64_t)&text);
	print("\n\t\trodata: 0x");
	printHex((uint64_t)&rodata);
	print("\n\t\tdata: 0x");
	printHex((uint64_t)&data);
	print("\n\t\tbss: 0x");
	printHex((uint64_t)&bss);
	print("\n\t[Done]\n");
	print("[Finished]\n\n");

	return getStackBase();
}

int main() {	
	print("[Kernel Main]\n");

	/*************************************************************************/
	/*************************************************************************/
	print("\tDisabling interrupts... ");
	_cli();
	_pic_master_mask((uint8_t) 0xFF);
	print("[Done]\n");

	print("\tLoading drivers... \n");

	print("\t\tLoading Timer Tick... ");
	setup_IDT_entry(0x20, (qword) &_timer_tick_interrupt, ACS_INT);
	print("[Done]\n");

	print("\t\tLoading Keyboard... ");
	setup_IDT_entry(0x21, (qword) &_keyboard_interrupt, ACS_INT);
	print("[Done]\n");

	print("\t\tLoading Systemcall... ");
	setup_IDT_entry(0x80, (qword) &_syscall_interrupt, ACS_INT);
	print("[Done]\n");
	
	print("\tEnabling interrupts... ");
	_pic_master_mask((uint8_t) 0xFC);
	_sti();
	print("[Done]\n\n");
	/*************************************************************************/
	/*************************************************************************/
	
	clearScreen();
	((EntryPoint) shellAddress)();

	return 0;
}