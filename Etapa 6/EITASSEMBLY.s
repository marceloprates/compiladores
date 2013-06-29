; STARTING MOVE
	movl $1, a(%rip)
; ENDING MOVE

; STARTING MOVE
	movl $2, b(%rip)
; ENDING MOVE

; STARTING MOVE
	movl $3, c(%rip)
; ENDING MOVE

	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	.cfi_def_cfa_register 6
; STARTING ADD
	movl b(%rip), ___temp0___(%rip)
	addl a(%rip), ___temp0___(%rip)
; ENDING ADD

; STARTING MOVE
	movl ___temp0___(%rip), c(%rip)
; ENDING MOVE

; STARTING CALL
	call	f1
	movl	%eax, ___temp1___
; ENDING CALL

; STARTING RET
	movl ___temp1___(%rip), %eax
; popq %rbp
; .cfi_def_cfa 7, 8
; ret
; .cfi_endproc
; ENDING RET

.LFE0:
	.size	main, .-main
	.globl	f1
	.type	f1, @function
f1:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	.cfi_def_cfa_register 6
; STARTING RET
	movl $1, %eax
; popq %rbp
; .cfi_def_cfa 7, 8
; ret
; .cfi_endproc
; ENDING RET

.LFE1:
	.size	f1, .-f1
