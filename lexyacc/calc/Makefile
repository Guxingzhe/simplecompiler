# makefile for flex&bison simple calc

all: simpleCalc

simpleCalc: simpleCalc.l simpleCalc.y
	bison -d simpleCalc.y
	flex simpleCalc.l
	cc -o $@ simpleCalc.tab.c lex.yy.c -lfl

clean:
	rm -f simpleCalc \
	lex.yy.c simpleCalc.tab.c simpleCalc.tab.h