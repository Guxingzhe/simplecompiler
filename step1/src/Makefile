all: copy compiler

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` # -std=c++14
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic
LIBS = `$(LLVMCONFIG) --libs`

BUILDDIR = ../build/
OBJDIR = $(BUILDDIR)objs/

OBJS = $(OBJDIR)parser.o $(OBJDIR)irgen.o $(OBJDIR)lexer.o $(OBJDIR)irgen.o $(OBJDIR)compiler.o

%.cpp: lexer.l parser.y
	bison -d -o $(BUILDDIR)parser.cpp parser.y
	flex -o $(BUILDDIR)lexer.cpp lexer.l

copy:
	mkdir -p ../build/objs
	cp ast.hpp $(BUILDDIR)ast.hpp
	cp irgen.hpp $(BUILDDIR)irgen.hpp
	cp compiler.cpp $(BUILDDIR)compiler.cpp
   
$(OBJDIR)%.o: $(BUILDDIR)%.cpp
	g++ -c $(CPPFLAGS) -o $@ $<
    
compiler: $(OBJS)
	g++ -o $@ $<  $(LIBS) $(LDFLAGS)

clean:
	rm -rf ../build/*