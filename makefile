all:
	make clean
	make build
	make run

clean:
	if [ -f lex.yy.c ]; then rm lex.yy.c; fi
	if [ -f y.tab.c ]; then rm y.tab.c; fi
	if [ -f y.tab.h ]; then rm y.tab.h; fi
	if [ -f parser ]; then rm parser; fi


build:
	yacc -d src/verilogParser.y -Wno-conflicts-sr
	lex src/verilogParser.l
	cc lex.yy.c y.tab.c -o bin/verilogParser -ll 

run:
	./bin/verilogParser

runtest:
	./bin/verilogParser < test.v

