	.file	"while.c"
	.globl	t
	.bss
	.align 4
	.type	t, @object
	.size	t, 4
t:
	.zero	4
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.zero	4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6

	jmp	.L2
.L3:
	movl	x(%rip), %eax
	movl	%eax, t(%rip)
.L2:
	movl	t(%rip), %eax
	testl	%eax, %eax
	jne	.L3

	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
