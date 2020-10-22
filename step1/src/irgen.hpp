/* 由AST生成IR的代码 */

#include <stack>
#include <typeinfo>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
//#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

#include "ast.hpp"

using namespace std;
using namespace llvm;

/* LLVM 模块和上下文环境 */
static LLVMContext context; //提供了一个用来创建变量等对象的上下文环境。
static Module module("top", context); //LLVM IR 对象的顶级容器。
static IRBuilder<> builder(context); //创建 LLVM 指令并将指令插入基础块的类。
static std::map<std::string, Value*> namedValues;//键值表保存当前的代码范围内定义的值和记录