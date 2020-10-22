all: compiler
.PHONY: clean initdir

CXX = clang++
cppFLAGS = `llvm-config --cppflags`
LINKFLAGS = `llvm-config --ldflags --libs`

BUILDDIR = ..\build\
OBJDIR = ..\build\objs\
OBJS = $(OBJDIR)lexer.o $(OBJDIR)parser.o $(OBJDIR)irgen.o $(OBJDIR)compiler.o

initdir:
	@if NOT EXIST $(BUILDDIR) mkdir $(BUILDDIR)
	@if NOT EXIST $(OBJDIR) mkdir $(OBJDIR)
	
$(BUILDDIR)%.cpp: lexer.l
	copy /y ast.hpp $(BUILDDIR)ast.hpp
	copy /y irgen.hpp $(BUILDDIR)irgen.hpp
	copy /y irgen.cpp $(BUILDDIR)irgen.cpp
	copy /y compiler.cpp $(BUILDDIR)compiler.cpp
	flex -o $(BUILDDIR)lexer.cpp lexer.l
	bison -d -o $(BUILDDIR)parser.cpp parser.y
   
$(OBJDIR)%.o: $(BUILDDIR)%.cpp
	$(CXX) -c $(cppFLAGS) -o $@ $<

compiler: $(OBJS)
	$(CXX) $(LINKFLAGS) -o $@ $?

clean:
	rm -rf ../build/*
	rm -f compiler
