# STARTING MOVE
	movl $1 a(%rip)
# ENDING MOVE

# STARTING MOVE
	movl $2 b(%rip)
# ENDING MOVE

# STARTING MOVE
	movl $3 c(%rip)
# ENDING MOVE

# STARTING MOVE
	movl $TRUE x(%rip)
# ENDING MOVE

# STARTING MOVE
	movl $TRUE y(%rip)
# ENDING MOVE

# STARTING MOVE
	movl $FALSE z(%rip)
# ENDING MOVE

# STARTING ADD
	movl b(%rip) ___temp0___(%rip)
	addl a(%rip) ___temp0___(%rip)
# ENDING ADD

# STARTING MOVE
	movl ___temp0___(%rip) c(%rip)
# ENDING MOVE

# STARTING SUB
	movl a(%rip) ___temp1___(%rip)
	subl b(%rip) ___temp1___(%rip)
# ENDING SUB

# STARTING MOVE
	movl ___temp1___(%rip) c(%rip)
# ENDING MOVE

# STARTING MUL
	movl b(%rip) ___temp2___(%rip)
	imull a(%rip) ___temp2___(%rip)
# ENDING MUL

# STARTING MOVE
	movl ___temp2___(%rip) c(%rip)
# ENDING MOVE

# STARTING DIV
	movl a(%rip) %eax
	movl b(%rip) %edx
	movl %edx -4(%rbp)
	movl %eax %edx
	sarl $31 %edx
	idivl -4(%rbp)
	movl %eax ___temp3___(%rip)
# ENDING DIV

# STARTING MOVE
	movl ___temp3___(%rip) c(%rip)
# ENDING MOVE

# STARTING LESS
	movl a(%rip), %edx
	movl b(%rip), %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, ___temp4___(%rip)
# ENDING LESS

# STARTING MOVE
	movl ___temp4___(%rip) z(%rip)
# ENDING MOVE

# STARTING LESS EQUAL
	movl a(%rip), %edx
	movl b(%rip), %eax
	cmpl %eax, %edx
	setle %al
	movzbl %al, %eax
	movl %eax, ___temp5___(%rip)
# ENDING LESS EQUAL

# STARTING MOVE
	movl ___temp5___(%rip) z(%rip)
# ENDING MOVE

# STARTING GREATER
	movl a(%rip), %edx
	movl b(%rip), %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, ___temp6___(%rip)
# ENDING GREATER EQUAL

# STARTING MOVE
	movl ___temp6___(%rip) z(%rip)
# ENDING MOVE

# STARTING GREATER EQUAL
	movl a(%rip), %edx
	movl b(%rip), %eax
	cmpl %eax, %edx
	setge %al
	movzbl %al, %eax
	movl %eax, ___temp7___(%rip)
# ENDING GREATER EQUAL

# STARTING MOVE
	movl ___temp7___(%rip) z(%rip)
# ENDING MOVE

# STARTING EQUAL
	movl a(%rip), %edx
	movl b(%rip), %eax
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, ___temp8___(%rip)
# ENDING EQUAL

# STARTING MOVE
	movl ___temp8___(%rip) z(%rip)
# ENDING MOVE

# STARTING NOT EQUAL
	movl a(%rip), %edx
	movl b(%rip), %eax
	cmpl %eax, %edx
	setne %al
	movzbl %al, %eax
	movl %eax, ___temp9___(%rip)
# ENDING NOT EQUAL

# STARTING MOVE
	movl ___temp9___(%rip) z(%rip)
# ENDING MOVE

# STARTING AND
	movl x(%rip), %edx
	movl y(%rip), %eax
	andl %edx, %eax
	movl %eax, ___temp10___(%rip)
# ENDING AND

# STARTING MOVE
	movl ___temp10___(%rip) z(%rip)
# ENDING MOVE

# STARTING OR
	movl x(%rip), %edx
	movl y(%rip), %eax
	orl %edx, %eax
	movl %eax, ___temp11___(%rip)
# ENDING OR

# STARTING MOVE
	movl ___temp11___(%rip) z(%rip)
# ENDING MOVE

