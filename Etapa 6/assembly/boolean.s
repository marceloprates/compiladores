	.file	"boolean.c"
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
	.globl	p
	.bss
	.align 4
	.type	p, @object
	.size	p, 4
p:
	.zero	4
	.globl	q
	.data
	.align 4
	.type	q, @object
	.size	q, 4
q:
	.long	1
	.globl	t
	.bss
	.align 4
	.type	t, @object
	.size	t, 4
t:
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
	cmpl	%eax, %edx
	setg	%al
	movzbl	%al, %eax
	movl	%eax, t(%rip)

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax
	movl	%eax, t(%rip)

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	cmpl	%eax, %edx
	setge	%al
	movzbl	%al, %eax
	movl	%eax, t(%rip)

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	cmpl	%eax, %edx
	setle	%al
	movzbl	%al, %eax
	movl	%eax, t(%rip)

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, t(%rip)

	movl	x(%rip), %edx
	movl	y(%rip), %eax
	cmpl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, t(%rip)

	movl	p(%rip), %edx
	movl	q(%rip), %eax
	andl	%edx, %eax
	movl	%eax, t(%rip)

	movl	p(%rip), %edx
	movl	q(%rip), %eax
	orl	%edx, %eax
	movl	%eax, t(%rip)

	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
