#############################################################################
## file        : makefile for generate ir assembly code for current dir .c ##
## author      : lileilei                                                  ##
## date        : 2020.10.20                                                ##
#############################################################################

.PHONY: all asm opt bin clean
all: bin

RM      = rm -rf
## cache dir
OBJDIR = objs/
BUILDDIR = build/
## get all source files
SRC    := $(wildcard *.ll)
## 
OPT    := $(patsubst %.ll, $(OBJDIR)%.ll, $(SRC))
BIN    := $(patsubst %.ll, $(BUILDDIR)%_bin, $(SRC))
ASM    := $(patsubst %.ll, $(OBJDIR)%.s, $(SRC))

asm: $(OBJDIR) $(ASM)
opt: $(OBJDIR) $(OPT)
bin: $(BUILDDIR) $(OBJDIR) $(BIN)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
    
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(OBJDIR)%.ll:%.ll
	opt -dce -globaldce -deadargelim -S $< -o $@
    
$(OBJDIR)%.s: %.ll
	llc -filetype=asm $< -o $@
    
$(BUILDDIR)%_bin: $(OBJDIR)%.s
	clang $< -o $@
    
clean:
	@$(RM) $(OBJDIR) $(BUILDDIR) *.o *.out
