###############################################################################
## file        : makefile for generate ir assembly code for current dir .c   ##
## author      : lileilei                                                    ##
## date        : 2020.10.20                                                  ##
###############################################################################

.PHONY : all ir bc asm bin opt clean
all: ir

CC      = clang
RM      = rm -rf
## cache dir
OBJDIR = objs/
## get all source files
SRC    := $(wildcard *.c)
## all .ll based on all .c
IR     := $(SRC:.c=.ll)
BC     := $(patsubst %.c,$(OBJDIR)%.bc,$(SRC))
ASM    := $(patsubst %.c,$(OBJDIR)%.s,$(SRC))
BIN    := $(patsubst %.c,$(OBJDIR)%_bin,$(SRC))


ir: $(IR)
bc: $(OBJDIR) $(BC)
asm: $(OBJDIR) $(ASM) $(BC)
bin: $(BUILDDIR) $(BIN)


$(OBJDIR):
	@mkdir -p $(OBJDIR)
    
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

%.ll: %.c
	$(CC) -S -emit-llvm $< -o $@  

$(OBJDIR)%.bc: %.ll
	llvm-as $< -o $@

$(OBJDIR)%.s: $(OBJDIR)%.bc
	llc $< -o $@
    
opt:
	for name in $(IR); do \
		opt -dce -globaldce -deadargelim -S $$name -o $$name; \
	done

$(BUILDDIR)_bin%: $(OBJDIR)%.s
	clang $< -o $@

clean:
	$(RM) $(IR) $(OBJDIR)
