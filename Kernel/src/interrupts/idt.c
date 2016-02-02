#include <idt.h>

#define IDT_BASE_ADDRESS 0x0

#define GET_WORD(x) ((x) & 0xFFFF)

// Segment Descriptor // TODO: Remove?
typedef struct {
	word_t 	limit,
			base_l;		// Low
	byte_t 	base_m,		// Mid
       		access,
       		attributes,
       		base_h;		// High
} segment_st;

// Interrupt Descriptor
typedef struct {
	word_t 	offset_l,	// Low
			selector;
	byte_t 	zero_l,		// Low
			access;
	word_t	offset_m;	// Mid
	dword_t	offset_h;	// High
	dword_t	zero_h;		// High
} interrupt_st;

// IDTR // TODO: 
typedef struct {
	word_t	limit;
	qword_t	base;
} idtr_st;

static interrupt_st * idt = (interrupt_st *) IDT_BASE_ADDRESS;
//static interrupt_st idt[_IDT_ENTRIES];
static idtr_st idtr;

void idt_init() {
	idtr.limit = _IDT_ENTRIES * sizeof(interrupt_st) - 1; // TODO: Preguntar
	idtr.base = (qword_t) idt;

	// TODO: Set idtr
}

int idt_entry(unsigned int index, qword_t offset, byte_t access) {
	if(index >= _IDT_ENTRIES) {
		return _IDT_ERROR_INDEX_INVALID;
	}

	idt[index].selector = _GDT_CODE_SEGMENT;
	idt[index].offset_l = GET_WORD(offset);
	offset >>= 16;
	idt[index].offset_m = GET_WORD(offset);
	offset >>= 16;
	idt[index].offset_h = GET_WORD(offset);
	idt[index].access = access;
	idt[index].zero_l = idt[index].zero_h = 0;

	return OK;
}