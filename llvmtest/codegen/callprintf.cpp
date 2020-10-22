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
    
    //sample=======================================================================//
    /*declare printf*/
    FunctionType *printFuncType = FunctionType::get(builder.getInt32Ty(), true);
    FunctionCallee printFunc = module.getOrInsertFunction("printf", printFuncType);
    /*Set up printf arguments构造实参列表*/
    vector<Value*> printArgs;
    Value *arg1_fmtStr = builder.CreateGlobalStringPtr("%d\n");
    Value *arg2_value = ConstantInt::get(Type::getInt32Ty(context), 20);//printing "20"
    printArgs.push_back(arg1_fmtStr);
    printArgs.push_back(arg2_value);
    /*call printf*/
    builder.CreateCall(printFunc, printArgs);
    builder.CreateCall(printFunc, builder.CreateGlobalStringPtr("hello world\n"));
    //=============================================================================// 
    
    // 函数返回值    /*return value for `main`*/
    Value* ret = ConstantInt::get(context, APInt(32, 0));
    builder.CreateRet(ret);
    
    // 打印IR代码
    //module.dump();//不能用了
    module.print(outs(),nullptr);
	
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(&module)).setEngineKind(EngineKind::JIT).create();
    
    // 运行机器指令
    void *mainAddr = ee->getPointerToFunction(func);
    typedef int (*mainFuncType)();
    mainFuncType mainFunc = (mainFuncType)mainAddr;
    ee->finalizeObject();
    std::cout << "\nmain function out:" << mainFunc() << std::endl;

    return 0;
}
