	.file	"arithmetic.c"
	.globl	x
	.data
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	6
	.globl	y
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.long	9
	.globl	z
	.bss
	.align 4
	.type	z, @object
	.size	z, 4
z:
	.zero	4
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

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	addl	%edx, %eax
	movl	%eax, z(%rip)

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, z(%rip)

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	imull	%edx, %eax
	movl	%eax, z(%rip)

	movl	x(%rip), %eax
	movl	y(%rip), %edx
	movl	%edx, -4(%rbp)
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-4(%rbp)
	movl	%eax, z(%rip)

	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
