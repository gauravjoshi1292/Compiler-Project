stage1exe:driver.o SymbolTable.o parser.o stack.o gj_lexer_final.o
	gcc -o stage1exe driver.o SymbolTable.o parser.o stack.o gj_lexer_final.o
driver.o: driver.c
	gcc -c driver.c
SymbolTable.o: SymbolTable.c
	gcc -c SymbolTable.c
parser.o:parser.c
	gcc -c parser.c
stack.o:stack.c
	gcc -c stack.c
gj_lexer_final.o:gj_lexer_final.c
	gcc -c gj_lexer_final.c
clear:
	rm driver.o SymbolTable.o parser.o stack.o gj_lexer_final.o
