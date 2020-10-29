# makefile for flex&bison simple calc
.PHONY: all test clean
all: test

SRC := $(wildcard  *.l)
C := $(SRC:.l=.cpp)
BIN := $(SRC:.l=)

test: $(BIN)

%.cpp: %.l
	flex -+ -o $@ $<
	
%:%.cpp
	clang++ -o $@ $<

clean:
	rm -f $(BIN) $(C)
	