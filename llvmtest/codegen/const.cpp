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
    // 常量
	Value* const1;
	// int
    const1 = builder.getInt32(1); //推荐
    const1 = ConstantInt::get(builder.getInt32Ty(), 2);  //same to get(Type::getInt32Ty(context), 2);
    const1 = ConstantInt::get(context, APInt(32, 3));
	// builder常量可用方法
	const1 = builder.getTrue(); // ConstantInt* const1;
	const1 = builder.getFalse(); // ConstantInt* const1;
	const1 = builder.getInt1(true); // ConstantInt* const1;
	const1 = builder.getInt8(20); // ConstantInt* const1;
	const1 = builder.getInt16(20); // ConstantInt* const1;
	const1 = builder.getInt32(20); // ConstantInt* const1;
	const1 = builder.getInt64(20); // ConstantInt* const1;
	const1 = builder.getIntN(32,20); // ConstantInt* const1;
	const1 = builder.getInt(APInt(32,20)); //ConstantInt* const1;
	
    
    // 函数返回值
    Value *ret = builder.getTrue();
    //=============================================================================// 
    
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
