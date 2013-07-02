	.file	"declare.c"
	.globl	x
	.data
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	101
	.globl	y
	.align 4
	.type	y, @object
	.size	y, 12
y:
	.long	1
	.long	2
	.long	3
	.globl	z
	.bss
	.align 8
	.type	z, @object
	.size	z, 8
z:
	.zero	8
	.comm	a,20,16
	.comm	b,0,4
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
	movl	$2, a+12(%rip)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
