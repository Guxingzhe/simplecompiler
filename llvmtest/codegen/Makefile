#################################################################
## file        : makefile for generate simple compiler sample  ##
## author      : lileilei                                      ##
## date        : 2020.10.20                                    ##
#################################################################
.PHONY: all build clean
all: build

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=)

build: $(OBJ) 

%: %.cpp
	@#`llvm-config --system-libs core`
	clang++ `llvm-config --cxxflags --ldflags --libs` -o $@ $<
    
clean:
	rm -f $(OBJ) *.o