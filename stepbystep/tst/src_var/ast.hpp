/* 抽象语法树（Abstract Syntax Tree）定义 */
/* 仅定义抽象语法树的节点类，Ast树通过Bison自动生成 */

#include <string>
#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

typedef IRBuilder<> Builder;

class Node {
public:
	virtual ~Node() {}
	virtual Value* codegen(Builder builder) = 0; 
};

class NBlock: public Node {
public:
	std::vector<Node*> nodes;
	NBlock() { }
	Value* codegen(Builder builder) override;
};

class NInteger : public Node {
public:
	int value;
	NInteger(int value) : value(value) { }
	Value* codegen(Builder builder) override;
};

class NIdentifier : public Node {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	Value* codegen(Builder builder) override;
};

class NAssignment : public Node {
public:
	NIdentifier& lhs;
	Node& rhs;
	NAssignment(NIdentifier& lhs, Node& rhs): lhs(lhs), rhs(rhs) { }
	Value* codegen(Builder builder) override;
};
