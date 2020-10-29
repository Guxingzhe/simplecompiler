all: wc 

wc: wc.l 
	flex -o wc.lex.yy.c wc.l
	cc wc.lex.yy.c -o wc -lfl

clean:
	rm -f wc wc.lex.yy.c
