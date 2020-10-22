/* 抽象语法树（Abstract Syntax Tree）定义 */
/* 仅定义抽象语法树的节点类，Ast树通过Bison自动生成 */

#include <string>
#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

class Node;
typedef std::vector<Node*> Nodes;

class Node {
public:
	virtual ~Node() {}
	virtual llvm::Value* codegen() = 0; //{ return NULL; }
};

class NodeList: public Node {
public:
	Nodes nodes;
	NodeList() { }
	llvm::Value *codegen() override;
};

class NInteger : public Node {
public:
	long long value;
	NInteger(long long value) : value(value) { }
	llvm::Value *codegen() override;
};

class NIdentifier : public Node {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
    const std::string &getName() const { return name; }
	llvm::Value *codegen() override;
};

class NBinaryOperate : public Node {
public:
	int op;
	Node& lhs;
	Node& rhs;
	NBinaryOperate(Node& lhs, int op, Node& rhs):lhs(lhs), rhs(rhs), op(op) { }
	llvm::Value *codegen() override;
};

class NAssignment : public Node {
public:
	Node& lhs;
	Node& rhs;
	NAssignment(Node& lhs, Node& rhs): lhs(lhs), rhs(rhs) { }
	llvm::Value *codegen() override;
};
