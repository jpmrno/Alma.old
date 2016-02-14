#include <exceptions.h>
#include <kernel.h>

#define _EXCEPTION_THROW(NUMBER) kernel_panic(_EXCEPTION_ ## NUMBER ## _CODE, \
											_EXCEPTION_ ## NUMBER ## _DESC, \
											_EXCEPTION_ ## NUMBER ## _SOURCE, \
											_EXCEPTION_ ## NUMBER ## _HALT)

void exception_00() { // Divide Error: division by zero
	_EXCEPTION_THROW(00);
}

void exception_02() { // Non-maskable interrupt
	_EXCEPTION_THROW(02);
}

void exception_03() { // Breakpoint
	_EXCEPTION_THROW(03);
}

void exception_04() { // Overflow
	_EXCEPTION_THROW(04);
}

void exception_05() { // Bounds
	_EXCEPTION_THROW(05);
}

void exception_06() { // Invalid Opcode
	_EXCEPTION_THROW(06);
}

void exception_07() { // Coprocessor not available
	_EXCEPTION_THROW(07);
}

void exception_08() { // Double fault
	_EXCEPTION_THROW(08);
}

void exception_09() { // Coprocessor Segment Overrun (386 or earlier only)
	_EXCEPTION_THROW(09);
}

void exception_0A() { // Invalid Task State Segment
	_EXCEPTION_THROW(0A);
}

void exception_0B() { // Segment not present
	_EXCEPTION_THROW(0B);
}

void exception_0C() { // Stack Fault
	_EXCEPTION_THROW(0C);
}

void exception_0D() { // General protection fault
	_EXCEPTION_THROW(0D);
}

void exception_0E() { // Page fault
	_EXCEPTION_THROW(0E);
}

void exception_10() { // Math Fault
	_EXCEPTION_THROW(10);
}

void exception_11() { // Alignment Check
	_EXCEPTION_THROW(11);
}

void exception_12() { // Machine Check
	_EXCEPTION_THROW(12);
}

void exception_13() { // SIMD Floating-Point Exception
	_EXCEPTION_THROW(13);
}
