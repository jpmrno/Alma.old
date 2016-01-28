global loader

extern kernel_init
extern kernel_main

loader:
	call kernel_init	; Set up the kernel binary, and get thet stack address
	mov rsp, rax		; Set up the stack with the returned address
	push rax
	call kernel_main
	
hang:
	hlt					; halt machine should kernel return
	jmp hang
