GLOBAL _int80

section .text

; Syscall caller (wrapper)
; Receives syscall parameters from registers
; Receives from stack the syscall number and puts it on rax
align 16
_int80:
	push rbp
	mov rbp, rsp
	pushfq

	xor rax, rax
	mov rax, [rbp+16] ; first stack argument == SYS_NUM
	
	int 0x80

	popfq
	mov rsp, rbp
	pop rbp
	ret ; rax tiene el valor de retorno