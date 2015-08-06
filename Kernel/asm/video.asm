GLOBAL _cursor_set
GLOBAL _cursor_enable

section .data
	VGA_ADDRESS equ 3D4h
	VGA_DATA equ 3D5h

section .text

;--------------------------------------------------------------
; Sets cursor position (text mode 80x25)                      -
; @param rdi	the cursor's position	                      - 
;                                                             -
; Modified version of:                                        -
; 	> http://wiki.osdev.org/Text_Mode_Cursor                  -
; Set to receive the position instead of the row and column   -
;--------------------------------------------------------------
align 16
_cursor_set:
	push rbp				; Stack frame creation
	mov rbp, rsp

	pushfq					; Flags backup
	push rax				; Registers backup
	push rcx
	push rdx

	xor rax, rax			; CLeans registers
	xor rcx, rcx

	mov ax, di				; TODO: VERIFY!
	mov cx,ax   			; Stores 'position' in CX

	; Cursor LOW port to vga INDEX register
	mov al,0fh	 			; Cursor location low register
	mov dx,VGA_ADDRESS		; VGA port 3D4h
	out dx,al		 		; Sets index to VGA hardware

	mov ax,cx		   		; Restore 'postion' back to AX  
	mov dx,VGA_DATA	 		; VGA port 3D5h
	out dx,al		 	    ; Sends to VGA hardware

	; Cursor HIGH port to vga INDEX register
	mov al,0eh	 			; Cursor location high register
	mov dx,VGA_ADDRESS 		; VGA port 3D4h
	out dx,al		 		; Set index to VGA hardware

	mov ax,cx		   		; Restores 'position' back to AX
	shr ax,8				; Get high byte in 'position'
	mov dx,VGA_DATA	 		; VGA port 3D5h
	out dx,al		   		; Sends to VGA hardware

	pop rdx					; Registers restore
	pop rcx
	pop rax					
	popfq

	mov rsp,rbp				; Stack frame restorage
	pop rbp
	ret

;--------------------------------------------------------------
; Enables the cursor and sets its shape to squared            -
;--------------------------------------------------------------
align 16
_cursor_enable:
	push rbp
	mov rbp, rsp
	pushfq
	push rax
	push rcx
	push rdx

	; Enable cursor and set square shape
	mov al, 0Ah 				; Cursor start location
	mov dx, 3d4h	 			; VGA port 3D4h
	out dx, al					; Send to VGA hardware

	mov al, 0h
	mov dx, 3d5h		 		; VGA port 3D5h
	out dx, al		 	    	; Send to VGA hardware

	pop rdx
	pop rcx
	pop rax
	popfq
	mov rsp,rbp
	pop rbp
	ret