###############################################################################
## file        : makefile for generate ir assembly code for current dir .c   ##
## author      : lileilei                                                    ##
## date        : 2020.10.20                                                  ##
###############################################################################

RM      = rm -rf

OBJDIR = objs/
## get all source files
SRC    := $(wildcard *.ll)
OPT    := $(SRC:.ll=.opt)
BC     := $(SRC:.ll=.bc)    
BIN    := $(SRC:.ll=)
ASM    := $(SRC:.ll=.s)


build: $(OBJDIR) $(BIN)
asm: $(OBJDIR) $(ASM)
opt: $(OPT)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

%.opt:%.ll
	opt -dce -globaldce -deadargelim -S $< -o $@
    
$(OBJDIR)%.bc: %.ll
	llvm-as $< -o $@
    
%.s: $(OBJDIR)%.bc
	llc $< -o $@
    
%: %.s
	clang $< -o $@
    

clean:
	@$(RM) $(OBJDIR) $(BIN) *.s *.opt *.bc a.out
