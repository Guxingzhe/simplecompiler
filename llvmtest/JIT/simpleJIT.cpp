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
 
int var_a = 20;
int var_b = 30;


int main(){
    static LLVMContext context;
    Module module("test", context);
    
    // 在IR代码中声明一个全局变量
    GlobalVariable *v1 = cast<GlobalVariable>(module.getOrInsertGlobal("a", Type::getInt32Ty(context)));
    GlobalVariable *v2 = cast<GlobalVariable>(module.getOrInsertGlobal("b", Type::getInt32Ty(context)));
    
    // 在IR中声明一个函数bar，我们会用IR定义这个函数
    FunctionType *bar_type = FunctionType::get(Type::getInt32Ty(context), false);
    Function *bar = Function::Create(bar_type, Function::ExternalLinkage,"bar", module);//FunctionBuilder不能用了
    
    // 创建函数bar的代码块
    BasicBlock *entry = BasicBlock::Create(context, "entry", bar);
    IRBuilder<> builder(entry);
    // 用一个局部变量获取全局变量v的值
    Value *v_IR1 = builder.CreateLoad(v1);
    Value *v_IR2 = builder.CreateLoad(v2);
    // 调用函数
    Value *ret = builder.CreateAdd(v_IR1, v_IR2, "addrst");
    // 返回值
    builder.CreateRet(ret);
    
    //module.dump();//不能用了
    module.print(errs(),nullptr);
	
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(&module)).setEngineKind(EngineKind::JIT).create();
    
    ee->addGlobalMapping(v1, &var_a);
    ee->addGlobalMapping(v2, &var_b);
    //运行机器指令
    void *barAddr = ee->getPointerToFunction(bar);
    typedef int (*FuncType)();
    FuncType barFunc = (FuncType)barAddr;
    ee->finalizeObject();
    std::cout << barFunc() << std::endl;

    return 0;
}
