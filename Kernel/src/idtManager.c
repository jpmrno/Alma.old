#include <idtManager.h>

/* Segment Descriptor*/
typedef struct {
  word limit,
       base_l;
  byte base_m,
       access,
       attribs,
       base_h;
} DESCR_SEG;

/* Interrupt Descriptor */
typedef struct {
	word 	offset_l,
			selector;
	byte 	zero_l,
			access;
	word	offset_m;
	dword	offset_h;
	dword	zero_h;

} IDT_Descriptor;

/* IDTR */
typedef struct {
	word	limit;
	qword	base;
} IDTR;

static IDT_Descriptor *IDT = (IDT_Descriptor*) 0x0;

void setup_IDT_entry (int index, qword offset, byte access) {
	IDT[index].selector = GDT_CODE_SEGMENT;
	IDT[index].offset_l = offset & 0xFFFF;
	offset >>= 16;
	IDT[index].offset_m = offset & 0xFFFF;
	IDT[index].offset_h = offset >> 16;
	IDT[index].access = access;
	IDT[index].zero_l = IDT[index].zero_h = 0;
}