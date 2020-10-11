/* 抽象语法树（Abstract Syntax Tree）定义 */

#include <string>
#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

class CodeGenContext;

class Node;
typedef std::vector<Node*> NodeList;

class Node {
public:
	virtual ~Node() {}
	virtual llvm::Value* codeGen(CodeGenContext& context) { return NULL; }
};

class Module: public Node {
public:
	NodeList nodes;
	Module() { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NIdentifier : public Node {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NInteger : public Node {
public:
	long long value;
	NInteger(long long value) : value(value) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NAssignment : public Node {
public:
	NIdentifier& lhs;
	Node& rhs;
	NAssignment(NIdentifier& lhs, Node& rhs) : 
		lhs(lhs), rhs(rhs) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBinaryOperator : public Node {
public:
	int op;
	Node& lhs;
	Node& rhs;
	NBinaryOperator(Node& lhs, int op, Node& rhs) :
		lhs(lhs), rhs(rhs), op(op) { }
	virtual llvm::Value* codeGen(CodeGenContext& context);
};
