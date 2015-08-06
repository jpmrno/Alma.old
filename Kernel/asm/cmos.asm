GLOBAL _read_CMOS
GLOBAL _write_CMOS:

section .text

;--------------------------------------------------------------
; Reads from the CMOS address		                      	  -
; @param rdi - the address to be read  		                  -
; @return rax - the read value								  -
;--------------------------------------------------------------
align 16
_read_CMOS:
	push rbp
	mov rbp, rsp

	xor rax, rax
	mov rax, rdi

	cli
	out 0x70, al ; set the address to read
	call _delay
	in al, 0x71 ; reads the set address 

	sti 

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
;--------------------------------------------------------------

;--------------------------------------------------------------
; Writes the given value at the desired CMOS address          -
; @param rdi - the address to be written  		              -
; @param rsi - the value to be written 		                  -
;--------------------------------------------------------------
align 16
_write_CMOS:
	push rbp
	mov rbp, rsp

	xor rax, rax
	mov rax, rdi

	cli

	out 0x70, al ; sets the address to write
	call _delay
	mov rax, rsi
	out 0x71, al ; writes the value at the set address

	sti

	pop rcx
	pop rbx

	mov rsp, rbp
	pop rbp 
	ret
;--------------------------------------------------------------

;--------------------------------------------------------------
; Delays WAITING_TIME units the process that called 		  -
; this function.	       									  -
;--------------------------------------------------------------
_delay:
	push rbp
	mov rbp, rsp
	pushf
	push rcx
	mov rcx, WAITING_TIME
.loop:
	cmp rcx, 0
	jz .end
	dec rcx
	jmp .loop

.end:
	pop rcx
	popf
	mov rsp, rbp
	pop rbp 
	ret
;--------------------------------------------------------------

section .data
	WAITING_TIME db 1