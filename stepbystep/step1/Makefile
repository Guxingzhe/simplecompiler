all: initdir compiler jit interpreter
.PHONY: clean

CXX = clang++
CPPFLAGS = `llvm-config --cppflags` -g
LINKFLAGS = `llvm-config --ldflags --libs`

BUILDDIR = ../build/
OBJDIR = $(BUILDDIR)objs/
OBJS = $(OBJDIR)lexer.o $(OBJDIR)parser.o $(OBJDIR)irgen.o
OBJS_INTERP = $(OBJDIR)lexer.o $(OBJDIR)parser_interective.o $(OBJDIR)irgen.o
SRC = $(BUILDDIR)ast.hpp $(BUILDDIR)irgen.hpp $(BUILDDIR)irgen.cpp $(BUILDDIR)compiler.cpp $(BUILDDIR)lexer.cpp $(BUILDDIR)parser.hpp $(BUILDDIR)parser.cpp $(BUILDDIR)parser_interective.hpp $(BUILDDIR)parser_interective.cpp

initdir:
	@mkdir -p ../build
	@mkdir -p ../build/objs

$(BUILDDIR)ast.hpp: ast.hpp
	cp $< $@
	
$(BUILDDIR)irgen.hpp: irgen.hpp
	cp $< $@
	
$(BUILDDIR)irgen.cpp: irgen.cpp
	cp $< $@
	
$(BUILDDIR)compiler.cpp: compiler.cpp
	cp $< $@
    
$(BUILDDIR)jit.cpp: jit.cpp
	cp $< $@
    
$(BUILDDIR)interpreter.cpp: interpreter.cpp
	cp $< $@
	
$(BUILDDIR)lexer.cpp: lexer.l
	flex -o $(BUILDDIR)lexer.cpp lexer.l
	
$(BUILDDIR)parser.hpp $(BUILDDIR)parser.cpp:	 parser.y
	bison -d -o $(BUILDDIR)parser.cpp parser.y
    
$(BUILDDIR)parser_interective.hpp $(BUILDDIR)parser_interective.cpp: parser_interective.y
	bison -d -o $(BUILDDIR)parser_interective.cpp parser_interective.y
   
$(OBJDIR)%.o: $(BUILDDIR)%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

compiler:  $(SRC) $(OBJS) $(OBJDIR)compiler.o
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS) $(OBJDIR)compiler.o
jit:  $(SRC) $(OBJS) $(OBJDIR)jit.o
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS) $(OBJDIR)jit.o
interpreter:  $(SRC) $(OBJS_INTERP) $(OBJDIR)interpreter.o
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS_INTERP) $(OBJDIR)interpreter.o

clean:
	rm -rf ../build/*
	rm -f compiler jit interpreter
	rm -f *.o
	rm -f program a.out
