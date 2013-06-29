	.file	"array.c"
	.comm	a,20,16
	.comm	x,4,4
	.comm	i,4,4
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

	movl	i(%rip), %eax
	movl	x(%rip), %edx
	cltq
	movl	%edx, a(,%rax,4)

	movl	i(%rip), %eax
	cltq
	movl	a(,%rax,4), %eax
	movl	%eax, x(%rip)

	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
