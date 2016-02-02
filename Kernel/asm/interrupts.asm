GLOBAL _interrupt_pic_mask
GLOBAL _interrupt_set
GLOBAL _interrupt_clear

section .text

align 16
%macro pushaq 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	pushfq
%endmacro

align 16
%macro popaq 0
	popfq
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

; -----------------------------------------------------------------------------
; Applies the given mask to the PIC	to enable/disable interrupts              
; @param rdi - the mask to be applied to the PIC              				  
; -----------------------------------------------------------------------------
align 16
_interrupt_pic_mask:
	push rbp
    mov rbp, rsp

    xor rax, rax ; To ensure rax register will be empty
    mov rax, rdi
    out	21h, al

    mov rsp, rbp
    pop rbp
    ret
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; Enables INTR hardware interrupts.
; -----------------------------------------------------------------------------
align 16
_interrupt_set:
	sti
	ret
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; Disables INTR hardware interrupts.
; -----------------------------------------------------------------------------
align 16
_interrupt_clear:
	cli
	ret
; -----------------------------------------------------------------------------
