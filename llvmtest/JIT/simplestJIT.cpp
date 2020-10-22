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
    
    // 在IR中声明一个函数bar，我们会用IR定义这个函数
    FunctionType *func_type = FunctionType::get(Type::getInt32Ty(context), false);
    Function *func = Function::Create(func_type, Function::ExternalLinkage,"funcname", module);//FunctionBuilder不能用了
    
    // 创建函数的代码块
    BasicBlock *bblock = BasicBlock::Create(context, "blockname", func);
    IRBuilder<> builder(bblock);
    // 用一个局部变量
    //Value *var1 = new AllocaInst(Type::getInt32Ty(context), 4, "a"); 
    //Value *var2 = new AllocaInst(Type::getInt32Ty(context), 4, "b");
    Constant *var1 = ConstantInt::get(Type::getInt32Ty(context), 5);
    Constant *var2 = ConstantInt::get(Type::getInt32Ty(context), 7);
    // 给局部变量赋值
    //builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context),5),var1);
    //builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context),7),var2);
    // 创建函数内部算法
    Value *ret = builder.CreateAdd(var1, var2, "var3");
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
