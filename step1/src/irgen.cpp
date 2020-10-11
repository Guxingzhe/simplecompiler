/* 由AST生成IR的代码 */

/* Compile the AST into a module */
void CodeGenContext::generateCode(Module &root) {
    std::cout << "Generating code...\n";

    /* Create the top level interpreter function to call as entry */
    vector<Type *> argTypes;
    FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), makeArrayRef(argTypes), false);
    mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
    BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

    /* Push a new variable/block context */
    pushBlock(bblock);
    root.codeGen(*this); /* emit bytecode for the toplevel block */
    ReturnInst::Create(getGlobalContext(), bblock);
    popBlock();

    /* Print the bytecode in a human-readable format
       to see if our program compiled properly
     */
    std::cout << "Code is generated.\n";
    PassManager<Module> pm;
    pm.addPass(PrintModulePass(outs()));
    pm.run(*module);
}

/* Executes the AST by running the main function */
GenericValue CodeGenContext::runCode() {
    std::cout << "Running code:\n";
    ExecutionEngine *ee = EngineBuilder(unique_ptr<Module>(module)).create();
    ee->finalizeObject();
    vector<GenericValue> noargs;
    GenericValue v = ee->runFunction(mainFunction, noargs);
    return v;
}

/* -- Code Generation -- */

Value *NInteger::codeGen(CodeGenContext &context) {//Creating interger
    return ConstantInt::get(Type::getInt64Ty(getGlobalContext()), value, true);
}

Value *NIdentifier::codeGen(CodeGenContext &context) {//Creating identifier reference
    if (context.locals().find(name) == context.locals().end()) {//Undeclared variable, Creating variable declaration
        AllocaInst *alloc = new AllocaInst(Type::getInt64Ty(getGlobalContext()),
                                           name.c_str(), context.currentBlock());
        context.locals()[name] = alloc;
    }
    return new LoadInst(context.locals()[name], "", false, context.currentBlock());
}


Value *NBinaryOperator::codeGen(CodeGenContext &context) {//Creating binary operation
    Instruction::BinaryOps instr;
    switch (op) {
        case TPLUS:
            instr = Instruction::Add;
            goto math;
        case TMINUS:
            instr = Instruction::Sub;
            goto math;
    }

    return NULL;
    math:
    return BinaryOperator::Create(instr, lhs.codeGen(context),
                                  rhs.codeGen(context), "", context.currentBlock());
}

Value *NAssignment::codeGen(CodeGenContext &context) {//Creating assignment
    if (context.locals().find(lhs.name) == context.locals().end()) {//undeclared variable, Creating variable declaration
        AllocaInst *alloc = new AllocaInst(Type::getInt64Ty(getGlobalContext()), lhs.name.c_str(),
                                           context.currentBlock());
        context.locals()[lhs.name] = alloc;
    }
    return new StoreInst(rhs.codeGen(context), context.locals()[lhs.name], false, context.currentBlock());
}

