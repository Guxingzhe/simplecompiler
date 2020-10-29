#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/Support/TargetSelect.h"
#include <llvm/Support/Casting.h>
#include <iostream>

using namespace llvm;
using namespace std;
 
int main(){
    static LLVMContext context;
    Module module("filename", context);
    
    // 在IR中声明一个函数bar
    FunctionType *func_type = FunctionType::get(Type::getInt32Ty(context), false);
    Function *func = Function::Create(func_type, Function::ExternalLinkage,"funcname", module);//FunctionBuilder不能用了
    
    // 创建函数的代码块
    BasicBlock *bblock = BasicBlock::Create(context, "blockname", func);
    IRBuilder<> builder(bblock);
    
    //sample====================================================//
    // 常量
    Value* const1 = builder.getInt32(1);
    // 变量
    AllocaInst* alloc_a = builder.CreateAlloca(builder.getInt32Ty(), NULL, "a");
    alloc_a->setAlignment(MaybeAlign(4));

    StoreInst* store_a = builder.CreateStore(const1, alloc_a, false);
    store_a->setAlignment(MaybeAlign(4));

    LoadInst* a = builder.CreateLoad(alloc_a);

    // 函数返回值
    Value *ret = a;
    //===========================================================// 
    
    // 函数返回值
    builder.CreateRet(ret);
    
    // 打印IR代码
    //module.dump();//不能用了
    module.print(errs(),nullptr);
	
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(&module)).setEngineKind(EngineKind::JIT).create();
    
    //运行机器指令
    void *barAddr = ee->getPointerToFunction(func);
    typedef int (*FuncType)();
    FuncType barFunc = (FuncType)barAddr;
    ee->finalizeObject();
    std::cout << barFunc() << std::endl;

    return 0;
}
