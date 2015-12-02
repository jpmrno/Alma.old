GLOBAL _cpu_vendor
GLOBAL _port_write_byte

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
; Gets the cpu vendor
; @param  result  - where to write the cpu vendor
; @return         - a pointer to the string result
; -----------------------------------------------------------------------------
align 16
_cpu_vendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid

	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

; TODO: Doc & _port_read_byte
align 16
_port_write_byte:
	push rbp
	mov rbp, rsp
	pushfq
	push rax
	push rdx

	mov rax, rsi
	mov rdx, rdi
	out dx, al

	pop rdx
	pop rax
	popfq
	mov rsp, rbp
	pop rbp
	ret
