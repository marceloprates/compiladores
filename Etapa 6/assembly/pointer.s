	.file	"pointer.c"
	.globl	n
	.data
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.long	5
	.globl	p
	.bss
	.align 8
	.type	p, @object
	.size	p, 8
p:
	.zero	8
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6

	movq	$n, p(%rip)

	movq	p(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, n(%rip)

	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
