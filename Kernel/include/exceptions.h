#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <define.h>

#define _EXCEPTION_00_CODE "DE"
#define _EXCEPTION_00_DESC "Divide Error"
#define _EXCEPTION_00_SOURCE "DIV and IDIV instructions"
#define _EXCEPTION_00_HALT TRUE

#define _EXCEPTION_02_CODE "--"
#define _EXCEPTION_02_DESC "NMI Interrupt"
#define _EXCEPTION_02_SOURCE "Nonmaskable external interrupt"
#define _EXCEPTION_02_HALT TRUE

#define _EXCEPTION_03_CODE "BP"
#define _EXCEPTION_03_DESC "Breakpoint"
#define _EXCEPTION_03_SOURCE "INT 3 instruction"
#define _EXCEPTION_03_HALT TRUE

#define _EXCEPTION_04_CODE "OF"
#define _EXCEPTION_04_DESC "Overflow"
#define _EXCEPTION_04_SOURCE "INTO instruction"
#define _EXCEPTION_04_HALT TRUE

#define _EXCEPTION_05_CODE "DE"
#define _EXCEPTION_05_DESC "BOUND Range Exceeded"
#define _EXCEPTION_05_SOURCE "BOUND instruction"
#define _EXCEPTION_05_HALT TRUE

#define _EXCEPTION_06_CODE "UD"
#define _EXCEPTION_06_DESC "Invalid Opcode (Undefined Opcode)"
#define _EXCEPTION_06_SOURCE "UD2 instruction or reserved opcode"
#define _EXCEPTION_06_HALT TRUE

#define _EXCEPTION_07_CODE "NM"
#define _EXCEPTION_07_DESC "Device Not Available (No Math Coprocessor)"
#define _EXCEPTION_07_SOURCE "Floating-point or WAIT/FWAIT instruction"
#define _EXCEPTION_07_HALT TRUE

#define _EXCEPTION_08_CODE "DF"
#define _EXCEPTION_08_DESC "Double Fault"
#define _EXCEPTION_08_SOURCE "Any instruction that generates an exception, an NMI or an INTR"
#define _EXCEPTION_08_HALT TRUE

#define _EXCEPTION_09_CODE "--"
#define _EXCEPTION_09_DESC "Coprocessor Segment Overrun (reserved)"
#define _EXCEPTION_09_SOURCE "Floating-point instruction"
#define _EXCEPTION_09_HALT TRUE

#define _EXCEPTION_0A_CODE "TS"
#define _EXCEPTION_0A_DESC "Invalid TSS"
#define _EXCEPTION_0A_SOURCE "Task switch or TSS access"
#define _EXCEPTION_0A_HALT TRUE

#define _EXCEPTION_0B_CODE "NP"
#define _EXCEPTION_0B_DESC "Segment Not Present"
#define _EXCEPTION_0B_SOURCE "Loading segment registers or accessing system segments"
#define _EXCEPTION_0B_HALT TRUE

#define _EXCEPTION_0C_CODE "SS"
#define _EXCEPTION_0C_DESC "Stack-Segment Fault"
#define _EXCEPTION_0C_SOURCE "Stack operations and SS register loads"
#define _EXCEPTION_0C_HALT TRUE

#define _EXCEPTION_0D_CODE "GP"
#define _EXCEPTION_0D_DESC "General Protection"
#define _EXCEPTION_0D_SOURCE "Any memory reference and other protection checks"
#define _EXCEPTION_0D_HALT TRUE

#define _EXCEPTION_0E_CODE "PF"
#define _EXCEPTION_0E_DESC "Page Fault"
#define _EXCEPTION_0E_SOURCE "Any memory reference"
#define _EXCEPTION_0E_HALT TRUE

#define _EXCEPTION_10_CODE "MF"
#define _EXCEPTION_10_DESC "x87 FPU Floating-Point Error (Math Fault)"
#define _EXCEPTION_10_SOURCE "x87 FPU floating-point or WAIT/FWAIT instruction"
#define _EXCEPTION_10_HALT TRUE

#define _EXCEPTION_11_CODE "AC"
#define _EXCEPTION_11_DESC "Alignment Check"
#define _EXCEPTION_11_SOURCE "Any data reference in memory"
#define _EXCEPTION_11_HALT TRUE

#define _EXCEPTION_12_CODE "MC"
#define _EXCEPTION_12_DESC "Machine Check"
#define _EXCEPTION_12_SOURCE "Error codes (if any) and source are model dependent"
#define _EXCEPTION_12_HALT TRUE

#define _EXCEPTION_13_CODE "XM"
#define _EXCEPTION_13_DESC "SIMD Floating-Point Exception"
#define _EXCEPTION_13_SOURCE "SSE/SSE2/SSE3 floating-point instructions"
#define _EXCEPTION_13_HALT TRUE

void exception_00();
void exception_02();
void exception_03();
void exception_04();
void exception_05();
void exception_06();
void exception_07();
void exception_08();
void exception_09();
void exception_0A();
void exception_0B();
void exception_0C();
void exception_0D();
void exception_0E();
void exception_10();
void exception_11();
void exception_12();
void exception_13();

#endif