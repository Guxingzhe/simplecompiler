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
	//类型类
	Type* type1;
	PointerType* ptr_type1;
	//类型声明方法
	type1=Type::getInt32Ty(context);	//int
	type1=builder.getInt32Ty();
	type1=IntegerType::get(context, 32);	//int可以使用IntegerType的get方法声明，但是没有上边两种方便
	
	
	type1=Type::getFloatTy(context);	//float
	type1=Type::getDoubleTy(context);	//double
	type1=Type::getInt8Ty(context);	//char
	type1=Type::getVoidTy(context);	//void
	//basic type
	type1 = Type::getVoidTy(context);
	type1 = Type::getIntNTy(context, 32);//iN
	type1 = Type::getInt1Ty(context);//i1    IntegerType* type1;
	type1 = Type::getInt8Ty(context);//i8
	type1 = Type::getInt16Ty(context);//i16
	type1 = Type::getInt32Ty(context);//i32
	type1 = Type::getInt64Ty(context);//i64
	type1 = Type::getInt128Ty(context);//i128
	type1 = Type::getHalfTy(context); // f16
	type1 = Type::getFloatTy(context);// f32
	type1 = Type::getDoubleTy(context);// f64
	type1 = Type::getFP128Ty(context);// f128
	type1 = Type::getLabelTy(context);// labels
	type1 = Type::getMetadataTy(context);// metadata
	type1 = Type::getTokenTy(context); // Tokens
	// DerivedTypes
	//Interger
	type1 = IntegerType::get(context, 32); // IntegerType* type1;
	
	//Pointer
	ptr_type1 = PointerType::get(Type::getInt32Ty(context), 32);// pointerType with //PointerType::get(sometype, AddrSpace);
	// PointerType to basic type
	ptr_type1 = PointerType::getInt1PtrTy(context);
	ptr_type1 = PointerType::getInt8PtrTy(context);
	ptr_type1 = PointerType::getInt16PtrTy(context);
	ptr_type1 = PointerType::getInt32PtrTy(context);
	ptr_type1 = PointerType::getInt64PtrTy(context);
	ptr_type1 = PointerType::getHalfPtrTy(context);
	ptr_type1 = PointerType::getFloatPtrTy(context);
	ptr_type1 = PointerType::getDoublePtrTy(context);
	ptr_type1 = PointerType::getFP128PtrTy(context);
	

	//数组类型Array //static ArrayType *get(Type *ElementType, uint64_t NumElements);
	ArrayType* array_type = ArrayType::get(Type::getInt32Ty(context), 4);	//长度为4的整型数组，int[4]

	////Vector
	//	static VectorType *get(Type *ElementType, ElementCount EC);
	// static VectorType *get(Type *ElementType, unsigned NumElements, bool Scalable = false) ; 
	VectorType* vector_type = VectorType::get(builder.getInt32Ty(), 4); //长度为4的整型向量
	
		
	////Function
	//FunctionType::get(Type *Result, ArrayRef<Type*> Params, bool isVarArg);
    //FunctionType::get(Type *Result, bool isVarArg);//FunctionType taking no parameters
	//定义一个变参数长度的函数，以int printf(...)为例
	FunctionType* printfuncType = FunctionType::get(builder.getInt32Ty(), true);
	//定义一个函数，以int max(int,a int b){}为例
	Type* returnType = builder.getInt32Ty();//返回值类型
	SmallVector<Type*, 2> argsType;//函数参数类型
	argsType.push_back(builder.getInt32Ty());
	argsType.push_back(builder.getInt32Ty());
	FunctionType* maxfunc_type = FunctionType::get(returnType, argsType, /*isVarArg*/ false);
	

	////结构体类型Struct
	/*/// This creates an identified struct.
	static StructType *create(LLVMContext &Context, StringRef Name);
	static StructType *create(LLVMContext &Context);

	static StructType *create(ArrayRef<Type *> Elements, StringRef Name, bool isPacked = false);
	static StructType *create(ArrayRef<Type *> Elements);
	static StructType *create(LLVMContext &Context, ArrayRef<Type *> Elements, StringRef Name, bool isPacked = false);
	static StructType *create(LLVMContext &Context, ArrayRef<Type *> Elements);

	/// This static method is the primary way to create a literal StructType.
	static StructType *get(LLVMContext &Context, ArrayRef<Type*> Elements, bool isPacked = false);
	static StructType *create(LLVMContext &Context, ArrayRef<Type *> Elements);
	/// Create an empty structure type.
	static StructType *get(LLVMContext &Context, bool isPacked = false);
	*/
	
	struct Number{
		int precision;
		int scale;
		double value;
		char* name;
	};
	StructType* structType = module.getTypeByName("Number");	//获取当前module中名为Number的结构体
	if(!structType)	//如果当前module中没有，就创建一个
		structType = StructType::create(context, "Number");
	std::vector<Type*> elements;	//结构体元素
	elements.push_back(Type::getInt32Ty(context));
	elements.push_back(Type::getInt32Ty(context));
	elements.push_back(Type::getDoubleTy(context));
	elements.push_back(PointerType::get(Type::getInt8Ty(context), 0));
	structType->setBody(elements);



    // 函数返回值
    Value *ret = builder.getInt32(1);
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
