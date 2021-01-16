all: initdir jit
.PHONY: clean

CXX = clang++
CPPFLAGS = `llvm-config --cppflags` 
LINKFLAGS = `llvm-config --ldflags --libs`

BUILDDIR = ../build/
OBJDIR = $(BUILDDIR)objs/
OBJS = $(OBJDIR)lexer.o $(OBJDIR)parser.o $(OBJDIR)irgen.o $(OBJDIR)jit.o
SRC = $(BUILDDIR)ast.hpp $(BUILDDIR)irgen.hpp $(BUILDDIR)irgen.cpp $(BUILDDIR)jit.cpp $(BUILDDIR)lexer.cpp $(BUILDDIR)parser.hpp $(BUILDDIR)parser.cpp

initdir:
	@mkdir -p ../build
	@mkdir -p ../build/objs

$(BUILDDIR)ast.hpp: ast.hpp
	cp $< $@
	
$(BUILDDIR)irgen.hpp: irgen.hpp
	cp $< $@
	
$(BUILDDIR)irgen.cpp: irgen.cpp
	cp $< $@
	
$(BUILDDIR)jit.cpp: jit.cpp
	cp $< $@
	
$(BUILDDIR)lexer.cpp: lexer.l
	flex -o $(BUILDDIR)lexer.cpp lexer.l
	
$(BUILDDIR)parser.hpp $(BUILDDIR)parser.cpp:	 parser.y
	bison -d -o $(BUILDDIR)parser.cpp parser.y
   
$(OBJDIR)%.o: $(BUILDDIR)%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

jit:  $(SRC) $(OBJS)
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS)

clean:
	rm -rf ../build/*
	rm -f jit
