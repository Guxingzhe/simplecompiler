/* 抽象语法树（Abstract Syntax Tree）定义 */
/* 仅定义抽象语法树的节点类，Ast树通过Bison自动生成 */

#include <llvm/IR/Value.h>

class Node {
public:
	virtual ~Node() {}
	virtual llvm::Value* codegen() = 0; 
};

class NInteger : public Node {
public:
	int value;
	NInteger(int value) : value(value) { }
	llvm::Value* codegen() override;
};

class NBinaryOperate : public Node {
public:
	int op;
	Node& lhs;
	Node& rhs;
	NBinaryOperate(Node& lhs, int op, Node& rhs):lhs(lhs), rhs(rhs), op(op) { }
	llvm::Value* codegen() override;
};