; STARTING DECL
	.globl a
	.data
	.align 4
	.type a, @object
	.size a, 4
	a:
	.long 1
; ENDING DECL
; STARTING DECL
	.globl b
	.data
	.align 4
	.type b, @object
	.size b, 4
	b:
	.long 1
; ENDING DECL
; STARTING DECL
	.globl c
	.data
	.align 4
	.type c, @object
	.size c, 4
	c:
	.long 1
; ENDING DECL
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
