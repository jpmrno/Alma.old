#include <interrupt.h>
#include <idtManager.h>
#include <moduleLoader.h>
#include <terminal.h>
#include <memory.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const shellAddress = (void *) 0x400000;

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
	//((EntryPoint) shellAddress)();
	video_init();
	video_style_range(80*0, 80*1-1, _VIDEO_STYLER(_VIDEO_COLOR_BRIGHTTEN(_VIDEO_COLOR_WHITE), _VIDEO_COLOR_BRIGHTTEN(_VIDEO_COLOR_BLACK)));
	video_put(79/2-2, 's');
	video_put(79/2-1, 'h');
	video_put(79/2, 'e');
	video_put(79/2+1, 'l');
	video_put(79/2+2, 'l');
	video_put(0, 'j');
	video_put(1, 'u');
	video_put(2, 'a');
	video_put(3, 'n');
	video_style_range(80*1, 80*4-1, _VIDEO_STYLER(_VIDEO_COLOR_BLACK, _VIDEO_COLOR_BRIGHTTEN(_VIDEO_COLOR_WHITE)));
	video_put(80*2+2, 'C');
	video_put(80*2+3, 'o');
	video_put(80*2+4, 'm');
	video_put(80*2+5, 'm');
	video_put(80*2+6, 'a');
	video_put(80*2+7, 'n');
	video_put(80*2+8, 'd');
	video_put(80*2+9, ':');
	video_put(80*2+11, 'c');
	video_put(80*2+12, 'l');
	video_put(80*2+13, 'e');
	video_put(80*2+14, 'a');
	video_put(80*2+15, 'r');
	video_cursor_put(80*2+16);

	return 0;
}