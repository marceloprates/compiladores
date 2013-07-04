	.file	"in.c"
	.comm	x,4,4
	.comm	y,4,4
	.comm	z,4,4
	.section	.rodata
.LC0:
	.string	"%x"
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
	movl	$x, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$y, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$z, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	x(%rip), %edx
	movl	y(%rip), %eax
	addl	%eax, %edx
	movl	z(%rip), %eax
	addl	%edx, %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
