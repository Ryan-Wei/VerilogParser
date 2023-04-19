clean:
	if [ -f lex.yy.c ]; then rm lex.yy.c; fi
	if [ -f y.tab.c ]; then rm y.tab.c; fi
	if [ -f y.tab.h ]; then rm y.tab.h; fi
	if [ -f parser ]; then rm parser; fi


build:
	yacc -d verilogParser.y
	lex verilogParser.l
	gcc lex.yy.c y.tab.c -o parser

run:
	./parser
