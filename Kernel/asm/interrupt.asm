GLOBAL _timer_tick_interrupt
GLOBAL _keyboard_interrupt
GLOBAL _syscall_interrupt
GLOBAL _pic_master_mask
GLOBAL _sti
GLOBAL _cli

EXTERN timerTickHandler
EXTERN keyboardHandler
EXTERN syscallHandler

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
; Timertick interrupt. IRQ 0x00, INT 0x20
; This IRQ runs whenever the PIT sends a signal to the processor
; -----------------------------------------------------------------------------
align 16
_timer_tick_interrupt:
	pushaq

	call timerTickHandler

	mov al, 0x20			; Acknowledge the IRQ
	out 0x20, al

	popaq
	iretq
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; Keyboard interrupt. IRQ 0x01, INT 0x21
; This IRQ runs whenever there is input on the keyboard
; -----------------------------------------------------------------------------
align 16
_keyboard_interrupt:
	pushaq

	xor eax, eax

	in al, 0x60			; Get the scancode from the keyboard
	mov rdi, rax
	call keyboardHandler

	mov al, 0x20			; Acknowledge the IRQ
	out 0x20, al

	popaq
	iretq
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; Syscall interrupt. INT 0x80
; This IRQ runs whenever an 'int 80h' instruction is executed. 
; -----------------------------------------------------------------------------
align 16
_syscall_interrupt:
	push rbp
	mov rbp, rsp

	sti 			; Needed to keep handling interrupts

	push rdi
	mov rdi, rax
	call syscallHandler

	pop rdi
	call rax ; No validation of pointer. Should check in future implementation

	mov rsp, rbp
	pop rbp
	iretq
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; Applies the given mask to the PIC	to enable/disable interrupts              
; @param rdi - the mask to be applied to the PIC              				  
; -----------------------------------------------------------------------------
align 16
_pic_master_mask:
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
_sti:
	sti
	ret
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; Disables INTR hardware interrupts.
; -----------------------------------------------------------------------------
align 16
_cli:
	cli
	ret
; -----------------------------------------------------------------------------
