
flex scanner.lex

g++ lex.yy.c symbol_table.c -o scanner.exe

scanner.exe mytext.txt

pause