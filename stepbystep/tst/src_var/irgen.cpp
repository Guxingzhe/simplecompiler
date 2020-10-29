/* 由AST生成IR的代码 */
#include "irgen.hpp"
#include "parser.hpp"
#include <string> //for cout <<

std::map<std::string, AllocaInst*> namedValues;//键值表保存当前的代码范围内定义的值和记录

Value* NInteger::codegen(Builder builder) {//Creating interger
    std::cout << "create intger\n";
    Value* val = builder.getInt32(value);
    return val;
}

Value* NIdentifier::codegen(Builder builder) {//get identifier reference
    std::cout << "get identifier\n";
    AllocaInst* alloc = namedValues[name];
    
    LoadInst* load = builder.CreateLoad(alloc);//, name.c_str());
    return load;
}

Value* NAssignment::codegen(Builder builder) {//Creating assignment
    std::cout << "crate assign \n";
    Value* val = builder.getInt32(55555);//rhs.codegen(builder);
    AllocaInst* alloc;
    if (namedValues.end() == namedValues.find(lhs.name)) {
	std::cout << " create var alloc " + lhs.name + "\n";
        alloc = builder.CreateAlloca(builder.getInt32Ty(), nullptr, lhs.name);
        //alloc->setAlignment(MaybeAlign(4));
        namedValues[lhs.name] = alloc;
    }else{
	    alloc = namedValues[lhs.name];
    }
    StoreInst* store = builder.CreateStore(val, alloc);
    //varstore->setAlignment(MaybeAlign(4));
    LoadInst* load = builder.CreateLoad(alloc);
    return load;
}

Value* NBlock::codegen(Builder builder) {
    std::cout << "create block\n" ;
    std::vector<Node*>::const_iterator it;
    Value* last = nullptr;
    for (it = nodes.begin(); it != nodes.end(); it++) {
        last = (**it).codegen(builder);
        delete *it;
    }
    return last;
}
