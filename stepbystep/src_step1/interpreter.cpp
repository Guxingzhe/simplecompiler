#include <iostream>
#include "irgen.hpp"

extern int yyparse();
extern Node* stmt;

/* LLVM 模块和上下文环境 */
LLVMContext context; //提供了一个用来创建变量等对象的上下文环境。
Module module("interpreterCalc", context); //LLVM IR 对象的顶级容器。
IRBuilder<> builder(context); //创建 LLVM 指令并将指令插入基础块的类。
ExecutionEngine* engine;
Function* main_func;
vector<Value*> printArgs;

void runcode(){
	/* ad stmt ir to block */
	Value* val = stmt->codegen();
    
    /* remove ret and printf for last time */
    if (!builder.GetInsertBlock()->getInstList().empty()){
    builder.GetInsertBlock()->getInstList().pop_back();}
    if (!builder.GetInsertBlock()->getInstList().empty()){
    builder.GetInsertBlock()->getInstList().pop_back();}
    
    /* ir for print ans */
    FunctionType *printFuncType = FunctionType::get(builder.getInt32Ty(), true);
    FunctionCallee printFunc = module.getOrInsertFunction("printf", printFuncType);
    //printArgs.clear();
    printArgs.pop_back();
    printArgs.push_back(val);
    builder.CreateCall(printFunc, printArgs);
    builder.CreateRet(builder.getInt32(0));
    
    
    
    /* run code */
    engine->finalizeObject();
    vector<GenericValue> noargs;
    //main_func->recalculateIntrinsicID();
    engine->runFunction(main_func, noargs);
    
    std::cout << "=IR================================\n";
    module.print(outs(),nullptr);
    std::cout << "===================================\n";
    
    
	std::cout << "\n>";
}



int main(int argc, char **argv) {	
	/* init jit engine */
	printf("initing engine....\n");
	InitializeNativeTarget();
	InitializeAllTargets();
	InitializeAllTargetMCs();
	InitializeNativeTargetAsmPrinter();
	InitializeNativeTargetAsmParser();
	
	engine = EngineBuilder(unique_ptr<Module>(&module)).setEngineKind(EngineKind::Interpreter).create();//JIT模式结果会有问题。
	engine->addModule(unique_ptr<Module>(&module));
	
	/* gen ir main func */
    FunctionType* main_functype;
    main_functype = FunctionType::get(builder.getInt32Ty(), false);
    main_func = Function::Create(main_functype, Function::InternalLinkage, "mainfunc", module);//GlobalValue::ExternalLinkage
    BasicBlock *block = BasicBlock::Create(context, "entryblock", main_func);
    builder.SetInsertPoint(block);
    
    Value *arg1_fmtStr = builder.CreateGlobalStringPtr("%d\n");
    printArgs.push_back(arg1_fmtStr);
    printArgs.push_back(nullptr);
	
	/* scan token and parse src */
    std::cout << "\n>";
	yyparse();
		
	std::cout << "Exiting...\n";	
    return 0;
}
