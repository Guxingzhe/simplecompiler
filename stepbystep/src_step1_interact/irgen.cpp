/* 由AST生成IR的代码 */
#include "irgen.hpp"
#include "parser.hpp"

extern IRBuilder<> builder; 

/* -- Code Generation -- */
Value* NInteger::codegen() {//Creating interger
    return builder.getInt32(value);
}

Value* NBinaryOperate::codegen() {//Creating binary operation
    Value* L = lhs.codegen();
    Value* R = rhs.codegen();
	
    switch (op) {
        case ADD:
            return builder.CreateAdd(L, R, "addrst");
        case SUB:
            return builder.CreateSub(L, R, "subrst");
    }
	return nullptr;
}
