	.file	"test.c"
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
	movl	24(%rbp), %eax
	movl	16(%rbp), %edx
	addl	%eax, %edx
	movl	32(%rbp), %eax
	addl	%eax, %edx
	movl	40(%rbp), %eax
	addl	%eax, %edx
	movl	48(%rbp), %eax
	addl	%eax, %edx
	movl	56(%rbp), %eax
	addl	%eax, %edx
	movl	64(%rbp), %eax
	addl	%eax, %edx
	movl	72(%rbp), %eax
	addl	%eax, %edx
	movl	80(%rbp), %eax
	addl	%eax, %edx
	movl	88(%rbp), %eax
	addl	%eax, %edx
	movl	96(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foo, .-foo
	.globl	bar
	.type	bar, @function
bar:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$88, %rsp
	movl	$10, 80(%rsp)
	movl	$9, 72(%rsp)
	movl	$8, 64(%rsp)
	movl	$7, 56(%rsp)
	movl	$6, 48(%rsp)
	movl	$5, 40(%rsp)
	movl	$4, 32(%rsp)
	movl	$3, 24(%rsp)
	movl	$2, 16(%rsp)
	movl	$1, 8(%rsp)
	movl	$0, (%rsp)
	call	foo
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	bar, .-bar
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	bar
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
