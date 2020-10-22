#include <iostream>
#include "irgen.hpp"

extern int yyparse();
extern NodeList* root;

GenericValue runCode() {
    /* Compile the AST into a module */
    std::cout << "Generating code...\n";
    /* Create the top level interpreter function to call as entry */
    FunctionType* main_functype;
    Function* main_func;
    main_functype = FunctionType::get(builder.getInt32Ty(), false);
    main_func = Function::Create(main_functype, GlobalValue::InternalLinkage, "main", module);
    
    /* BasicBlock in function */
    BasicBlock *block = BasicBlock::Create(context, "entry", main_func);
    //ReturnInst::Create(context, block);

    /* set instructions in block */
    builder.SetInsertPoint(block);
    Value* val = root->codegen(); /* emit bytecode for the toplevel block */
    
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
    
    /* Print the bytecode in a human-readable format
       to see if our program compiled properly
     */
    std::cout << "Code is generated.\n";
    PassManager<Module> pm;
    pm.addPass(PrintModulePass(outs()));
    //pm.run(module);
    
/* Executes the AST by running the main function */
    std::cout << "Running code:\n";
	ExecutionEngine *ee = EngineBuilder(unique_ptr<Module>(&module)).create();
    ee->addModule(unique_ptr<Module>(&module));
    ee->finalizeObject();
    vector<GenericValue> noargs;
    GenericValue v = ee->runFunction(main_func, noargs);
    

    return v;
}



int main(int argc, char **argv) {
    yyparse();
    InitializeNativeTarget();
	//InitializeAllTargets();
	//InitializeAllTargetMCs();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    runCode();    
    std::cout << "Exiting...\n";

    return 0;
}
