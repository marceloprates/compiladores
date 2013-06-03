etapa4: y.tab.o lex.yy.o hash.o ast.o semantic.o main.o
	gcc -o etapa4 y.tab.o lex.yy.o hash.o ast.o semantic.o main.o

main.o: main.c
	gcc -c main.c

semantic.o: semantic.c
	gcc -c semantic.c

ast.o:
	gcc -c ast.c

hash.o: hash.c
	gcc -c hash.c

y.tab.o: y.tab.c lex.yy.h
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.h: scanner.l
	flex --header-file=lex.yy.h scanner.l

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

clean:
	rm *.o lex.yy.c y.tab.c lex.yy.h y.tab.h y.output etapa4
