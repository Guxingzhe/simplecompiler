/* 由AST生成IR的代码 */
#include "irgen.hpp"
#include "parser.hpp"

/* -- Code Generation -- */
Value *NInteger::codegen() {//Creating interger
    return ConstantInt::get(Type::getInt64Ty(context), value);
}

Value *NIdentifier::codegen() {//Creating identifier reference
    Value* V = namedValues[name];
    return V;
}

Value *NBinaryOperate::codegen() {//Creating binary operation
    Value* L = lhs.codegen();
    Value* R = rhs.codegen();
    switch (op) {
        case ADD:
            return builder.CreateAdd(L, R, "addrst");
        case SUB:
            return builder.CreateSub(L, R, "subrst");
    }
}

Value *NAssignment::codegen() {//Creating assignment
    NIdentifier *lhse = static_cast<NIdentifier*>(&lhs);
    Value *Val = rhs.codegen();
    Value *Variable = namedValues[lhse->getName()];
    builder.CreateStore(Val, Variable);
    return Val;
}

Value *NodeList::codegen() {
    std::vector<Node*>::const_iterator it;
    Value *last = NULL;
    for (it = nodes.begin(); it != nodes.end(); it++) {
        last = (**it).codegen();
    }
    return last;
}
