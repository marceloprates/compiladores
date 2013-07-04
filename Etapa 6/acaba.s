# DATA SECTION

	.LC0:
		.string "%s "
	.LC1:
		.string "%x "
	.LC2:
		.string "%c "
	.LC3:
		.string "\n"

	.globl ___temp5___
	.data
	.align 4
	.type ___temp5___, @object
	.size ___temp5___, 4
	___temp5___:
		.long 0

	.globl a
	.data
	.align 4
	.type a, @object
	.size a, 4
	a:
		.long 0

	.globl b
	.data
	.align 4
	.type b, @object
	.size b, 4
	b:
		.long 1

	.globl c
	.data
	.align 4
	.type c, @object
	.size c, 4
	c:
		.long 66

	.globl x
	.data
	.align 4
	.type x, @object
	.size x, 4
	x:
		.long 0

	.globl y
	.data
	.align 4
	.type y, @object
	.size y, 4
	y:
		.long 0

	.globl z
	.data
	.align 4
	.type z, @object
	.size z, 4
	z:
		.long 0

	.globl ___temp2___
	.data
	.align 4
	.type ___temp2___, @object
	.size ___temp2___, 4
	___temp2___:
		.long 0

	.LC4:
		.string "fim"

	.globl ___temp4___
	.data
	.align 4
	.type ___temp4___, @object
	.size ___temp4___, 4
	___temp4___:
		.long 0

	.globl ___temp1___
	.data
	.align 4
	.type ___temp1___, @object
	.size ___temp1___, 4
	___temp1___:
		.long 0

	.globl ___temp6___
	.data
	.align 4
	.type ___temp6___, @object
	.size ___temp6___, 4
	___temp6___:
		.long 0

	.globl ___temp3___
	.data
	.align 4
	.type ___temp3___, @object
	.size ___temp3___, 4
	___temp3___:
		.long 0

	.globl ___temp0___
	.data
	.align 4
	.type ___temp0___, @object
	.size ___temp0___, 4
	___temp0___:
		.long 0

	.comm	array,64

# CODE SECTION:

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

		# STARTING GET_ARG
			movl	16(%rsp), %edx
			movl	%edx, z(%rip)
		# ENDING GET_ARG

		# STARTING GET_ARG
			movl	24(%rsp), %edx
			movl	%edx, y(%rip)
		# ENDING GET_ARG

		# STARTING GET_ARG
			movl	32(%rsp), %edx
			movl	%edx, x(%rip)
		# ENDING GET_ARG

		# STARTING OUTPUT ARG
			movl	x(%rip), %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	printf
		# ENDING OUTPUT ARG

		# STARTING OUTPUT ARG
			movl	y(%rip), %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	printf
		# ENDING OUTPUT ARG

		# STARTING OUTPUT ARG
			movl	z(%rip), %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	printf
		# ENDING OUTPUT ARG

			movl	$.LC3, %edi
			movl	$0, %eax
			call	printf
		# STARTING SUB
			movl	x(%rip), %eax
			movl	y(%rip), %edx
			subl	%edx, %eax
			movl	%eax, ___temp0___(%rip)
		# ENDING SUB

		# STARTING SUB
			movl	___temp0___(%rip), %eax
			movl	z(%rip), %edx
			subl	%edx, %eax
			movl	%eax, ___temp1___(%rip)
		# ENDING SUB

		# STARTING RET
			movl	___temp1___(%rip), %eax
			popq	%rbp
			.cfi_def_cfa 7, 8
			ret
			.cfi_endproc
		# ENDING RET

	.LFE0:
		.size	foo, .-foo

	.globl	main
	.type	main, @function
	main:
	.LFB1:
		.cfi_startproc
		pushq	%rbp
		.cfi_def_cfa_offset 16
		.cfi_offset 6, -16
		movq	%rsp, %rbp
		.cfi_def_cfa_register 6

		# STARTING MOVE
			movl $0, %edx
			movl %edx, a(%rip)
		# ENDING MOVE

		# STARTING LESS
			movl a(%rip), %edx
			movl $80, %eax
			cmpl %eax, %edx
			setl %al
			movzbl %al, %eax
			movl %eax, ___temp2___(%rip)
		# ENDING LESS

			___label0___:
		# STARTING IFZ
			movl ___temp2___(%rip), %eax
			testl %eax, %eax
			je ___label1___
		# ENDING IFZ

		# STARTING ARRAYASSIGN
			movl a(%rip), %eax
			movl a(%rip), %edx
			cltq
			movl %edx, array(,%rax,4)
		# ENDING ARRAYASSIGN

		# STARTING ARRAYACCESS
			movl a(%rip), %eax
			cltq
			movl array(,%rax,4), %eax
			movl %eax, ___temp4___(%rip)
		# ENDING ARRAYACCESS

		# STARTING OUTPUT ARG
			movl	___temp4___(%rip), %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	printf
		# ENDING OUTPUT ARG

			movl	$.LC3, %edi
			movl	$0, %eax
			call	printf
		# STARTING ADD
			movl	a(%rip), %edx
			movl	$1, %eax
			addl %edx, %eax
			movl %eax, ___temp5___(%rip)
		# ENDING ADD

		# STARTING MOVE
			movl ___temp5___(%rip), %edx
			movl %edx, a(%rip)
		# ENDING MOVE

		# STARTING LESS
			movl a(%rip), %edx
			movl $80, %eax
			cmpl %eax, %edx
			setl %al
			movzbl %al, %eax
			movl %eax, ___temp2___(%rip)
		# ENDING LESS

		# STARTING JUMP
			jmp ___label0___
		# ENDING JUMP

			___label1___:
		# STARTING READ
			movl	$a, %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	__isoc99_scanf
		# ENDING READ

		# STARTING READ
			movl	$b, %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	__isoc99_scanf
		# ENDING READ

		# STARTING READ
			movl	$c, %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	__isoc99_scanf
		# ENDING READ

		# STARTING ARG
			subq	$8, %rsp
			movl a(%rip), %edx
			movl %edx, (%rsp)
		# ENDING ARG

		# STARTING ARG
			subq	$8, %rsp
			movl b(%rip), %edx
			movl %edx, (%rsp)
		# ENDING ARG

		# STARTING ARG
			subq	$8, %rsp
			movl c(%rip), %edx
			movl %edx, (%rsp)
		# ENDING ARG

		# STARTING CALL
			call	foo
			movl	%eax, ___temp6___
		# ENDING CALL

		# STARTING OUTPUT ARG
			movl	___temp6___(%rip), %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	printf
		# ENDING OUTPUT ARG

			movl	$.LC3, %edi
			movl	$0, %eax
			call	printf
		# STARTING OUTPUT ARG
			movl	$.LC4, %esi
			movl	$.LC0, %edi
			movl	$0, %eax
			call	printf
		# ENDING OUTPUT ARG

			movl	$.LC3, %edi
			movl	$0, %eax
			call	printf
		# STARTING RET
			movl	$1, %eax
			popq	%rbp
			.cfi_def_cfa 7, 8
			ret
			.cfi_endproc
		# ENDING RET

	.LFE1:
		.size	main, .-main

