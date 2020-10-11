#include <iostream>
#include "ast.hpp"
#include "irgen.hpp"

using namespace std;

extern int yyparse();

extern Module *rootNode;

int main(int argc, char **argv) {
    yyparse();
    cout << rootNode << endl;
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    CodeGenContext context;
    context.generateCode(*rootNode);
    context.runCode();

    std::cout << "Exiting...\n";

    return 0;
}
