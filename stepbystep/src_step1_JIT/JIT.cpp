#include <iostream>
#include "irgen.hpp"

extern int yyparse();
extern Node* astroot;

/* LLVM 模块和上下文环境 */
LLVMContext context; //提供了一个用来创建变量等对象的上下文环境。
Module module("JITcalc", context); //LLVM IR 对象的顶级容器。
IRBuilder<> builder(context); //创建 LLVM 指令并将指令插入基础块的类。

Function* genIR() {
    std::cout << "Generating code...\n";
    FunctionType* main_functype;
    Function* main_func;
    main_functype = FunctionType::get(builder.getInt32Ty(), false);
    main_func = Function::Create(main_functype, GlobalValue::InternalLinkage, "mainfunc", module);
    
    /* BasicBlock in function */
    BasicBlock *block = BasicBlock::Create(context, "entryblock", main_func);
    builder.SetInsertPoint(block);
    Value* val = astroot->codegen();    /* Compile the AST into a module */
    
	//打印计算结果
    //先声明printf函数
    FunctionType *printFuncType = FunctionType::get(builder.getInt32Ty(), true);
    FunctionCallee printFunc = module.getOrInsertFunction("printf", printFuncType);
    vector<Value*> printArgs;
    Value *arg1_fmtStr = builder.CreateGlobalStringPtr("%d\n");
    Value *arg2_value = val;
    printArgs.push_back(arg1_fmtStr);
    printArgs.push_back(arg2_value);
    /*call printf*/
    builder.CreateCall(printFunc, printArgs);
    /* set return */
    builder.CreateRet(builder.getInt32(0));
    
    std::cout << "Code is generated.\n";
	std::cout << "Printing IR code...\n";
	module.print(outs(),nullptr);

    return main_func;
}


int main(int argc, char **argv) {
	/* scan token and parse src */
    std::cout << "\nPlease input the expr:\n";
	yyparse();	
	
	/* init target */
    InitializeNativeTarget();
	//InitializeAllTargets();
	//InitializeAllTargetMCs();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();	
	    
     /* init engine */
    std::cout << "\nRunning code:\n";
	ExecutionEngine *ee = EngineBuilder(unique_ptr<Module>(&module)).create();
    ee->addModule(unique_ptr<Module>(&module));
	
	/* init ir function */
    Function* main_func = genIR();
    vector<GenericValue> noargs;
	
	/* runcode */
    ee->finalizeObject();
    GenericValue v = ee->runFunction(main_func, noargs);
	
	std::cout << "Exiting...\n";
    return 0;
}
