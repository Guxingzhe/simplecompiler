###############################################################################
## file        : makefile for generate ir assembly code for current dir .c   ##
## author      : lileilei                                                    ##
## date        : 2020.10.20                                                  ##
###############################################################################

.PHONY : all ir bc asm opt clean
all: ir

CC      = clang
RM      = rm -rf
## cache dir
OBJDIR = objs/
## get all source files
SRC    := $(wildcard *.c)
## all .ll based on all .c
IR     := $(SRC:.c=.ll)
BC     := $(OBJDIR)$(SRC:.c=.bc)
ASM    := $(SRC:.c=.s)


ir: $(IR)
bc: $(OBJDIR) $(BC)
asm: $(OBJDIR) $(ASM)


$(OBJDIR):
	@mkdir -p $(OBJDIR)

%.ll: %.c
	$(CC) -S -emit-llvm $< -o $@  

$(OBJDIR)%.bc: %.ll
	llvm-as $< -o $@

%.s: $(OBJDIR)%.bc
	llc $< -o $@
    
opt:
	for name in $(IR); do \
		opt -dce -globaldce -deadargelim -S $$name -o $$name; \
	done

clean:
	@$(RM) $(OBJDIR) $(IR) *.bc *.s
