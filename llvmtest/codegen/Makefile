#################################################################
## file        : makefile for generate simple compiler sample  ##
## author      : lileilei                                      ##
## date        : 2020.10.20                                    ##
#################################################################
.PHONY: all build clean
all: build

BUILDDIR = build/
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, $(BUILDDIR)%_bin, $(SRC))

build: $(BUILDDIR) $(OBJ)

$(BUILDDIR):
	@mkdir -p $@

$(BUILDDIR)%_bin: %.cpp
	@#`llvm-config --system-libs core`
	clang++ `llvm-config --cxxflags --ldflags --libs` -o $@ $<
    
clean:
	rm -rf $(BUILDDIR) 