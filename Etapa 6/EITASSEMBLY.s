; DATA SECTION

	LC0:
		.string "%s"
	LC1:
		.string "%d"
	LC2:
		.string "%c"

		.globl a
		.data
		.align 4
		.type a, @object
		.size a, 4
		a:
		.long 1

		.globl b
		.data
		.align 4
		.type b, @object
		.size b, 4
		b:
		.long 2

		.globl c
		.data
		.align 4
		.type c, @object
		.size c, 4
		c:
		.long 3

		.globl g
		.data
		.align 4
		.type g, @object
		.size g, 4
		g:
		.long 0

		.globl h
		.data
		.align 4
		.type h, @object
		.size h, 4
		h:
		.long 0

		.globl x
		.data
		.align 4
		.type x, @object
		.size x, 4
		x:
		.long 1

		.globl y
		.data
		.align 4
		.type y, @object
		.size y, 4
		y:
		.long 1

		.globl z
		.data
		.align 4
		.type z, @object
		.size z, 4
		z:
		.long 0

	LC3:
		.string "chupa cabra"
	LC4:
		.string "macaco"
		.globl arr
		.data
		.align 4
		.type arr, @object
		.size arr, 64
	arr:

	LC5:
		.string "banana"
	
; CODE SECTION:

		.globl	main
		.type	main, @function
	main:
	.LFB0:
		.cfi_startproc
		pushq	%rbp
		.cfi_def_cfa_offset 16
		.cfi_offset 6, -16
		movq	%rsp, %rbp		.cfi_def_cfa_register 6
	; STARTING OUTPUT ARG
		movl	$.LC0, %esi
		movl	$.LC5, %edi
		movl	$0, %eax
		call	printf
	; ENDING OUTPUT ARG

	; STARTING OUTPUT ARG
		movl	$66, %esi
		movl	$.LC1, %edi
		movl	$0, %eax
		call	printf
	; ENDING OUTPUT ARG

	; STARTING OUTPUT ARG
		movl	$.LC0, %esi
		movl	$.LC4, %edi
		movl	$0, %eax
		call	printf
	; ENDING OUTPUT ARG

	; STARTING OUTPUT ARG
		movl	$834, %esi
		movl	$.LC1, %edi
		movl	$0, %eax
		call	printf
	; ENDING OUTPUT ARG

	; STARTING OUTPUT ARG
		movl	$.LC0, %esi
		movl	$.LC3, %edi
		movl	$0, %eax
		call	printf
	; ENDING OUTPUT ARG

	; STARTING OUTPUT ARG
		movl	$192950115, %esi
		movl	$.LC1, %edi
		movl	$0, %eax
		call	printf
	; ENDING OUTPUT ARG

	; STARTING OUTPUT ARG
		movl	c(%rip), %esi
		movl	$.LC1, %edi
		movl	$0, %eax
		call	printf
	; ENDING OUTPUT ARG

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
		movq	%rsp, %rbp		.cfi_def_cfa_register 6
	; STARTING GET_ARG
		movl 0(%rsp), g(%rip)
	; ENDING GET_ARG

	; STARTING GET_ARG
		movl 8(%rsp), h(%rip)
	; ENDING GET_ARG

	; STARTING RET
		movl $1, %eax
	; popq %rbp
	; .cfi_def_cfa 7, 8
	; ret
	; .cfi_endproc
	; ENDING RET

	.LFE1:
		.size	f1, .-f1
