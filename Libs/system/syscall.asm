GLOBAL _syscall

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

; Syscall caller (wrapper)
; Receives syscall parameters from registers
; Receives from stack the syscall number and puts it on rax
align 16
_syscall:
	push rbp
	mov rbp, rsp
	pushfq

	xor rax, rax
	mov rax, [rbp+16] 		; first stack argument == syscall number
	
	int 0x80

	popfq
	mov rsp, rbp
	pop rbp
	ret 					; rax has return value
