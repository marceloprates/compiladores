

etapa2: y.tab.o lex.yy.o hash.o main.o
	gcc -o etapa2 y.tab.o lex.yy.o hash.o main.o

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

y.tab.o: y.tab.c lex.yy.h
	gcc -c y.tab.c

y.tab.c: unambig_parser.y
	yacc -d unambig_parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.h:
	flex --header-file=lex.yy.h scanner.l

lex.yy.c:
	flex --header-file=lex.yy.h scanner.l

clean:
	rm *.o lex.yy.c y.tab.c lex.yy.h y.tab.h etapa2