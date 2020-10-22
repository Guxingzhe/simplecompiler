all: initdir compiler
.PHONY: clean

CXX = clang++
CPPFLAGS = `llvm-config --cppflags`
LINKFLAGS = `llvm-config --ldflags --libs`

BUILDDIR = ../build/
OBJDIR = $(BUILDDIR)objs/
OBJS = $(OBJDIR)lexer.o $(OBJDIR)parser.o $(OBJDIR)irgen.o $(OBJDIR)compiler.o

initdir:
	@mkdir -p ../build
	@mkdir -p ../build/objs
	
$(BUILDDIR)%.cpp: lexer.l
	cp ast.hpp $(BUILDDIR)ast.hpp
	cp irgen.hpp $(BUILDDIR)irgen.hpp
	cp irgen.cpp $(BUILDDIR)irgen.cpp
	cp compiler.cpp $(BUILDDIR)compiler.cpp
	flex -o $(BUILDDIR)lexer.cpp lexer.l
	bison -d -o $(BUILDDIR)parser.cpp parser.y
   
$(OBJDIR)%.o: $(BUILDDIR)%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

compiler: $(OBJS)
	$(CXX) $(LINKFLAGS) -o $@ $^

clean:
	rm -rf ../build/*
	rm -f compiler
