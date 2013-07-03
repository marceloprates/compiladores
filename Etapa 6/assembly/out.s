	.file	"out.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"Hello, world!"
.LC2:
	.string	"!"
.LC3:
	.string	"world"
.LC4:
	.string	" "
.LC5:
	.string	","
.LC6:
	.string	"Hello"
.LC7:
	.string	"%s%s%s%s%s%s"
.LC8:
	.string	"\n"
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
	subq	$16, %rsp
	movl	$1, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %edi
	call	puts
	movl	$.LC1, %edi
	call	puts
	movq	$.LC8, (%rsp)
	movl	$.LC2, %r9d
	movl	$.LC3, %r8d
	movl	$.LC4, %ecx
	movl	$.LC5, %edx
	movl	$.LC6, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
