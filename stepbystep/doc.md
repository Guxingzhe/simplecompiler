
## 编译原理及步骤简介

一般编译器有以下工作步骤：

1. **词法分析（Lexical analysis）：** 此阶段的任务是从左到右一个字符一个字符地读入源程序，对构成源程序的字符流进行扫描然后根据构词规则识别 `单词（Token）`，完成这个任务的组件是 `词法分析器（Lexical analyzer，简称Lexer）`，也叫 `扫描器（Scanner）`；

2. **语法分析（Syntactic analysis，也叫 Parsing）：** 此阶段的主要任务是由 `词法分析器` 生成的单词构建 `抽象语法树（Abstract Syntax Tree ，AST）`，完成此任务的组件是 `语法分析器（Parser）`；

3. **目标码生成：** 此阶段编译器会遍历上一步生成的抽象语法树，然后为每个节点生成 `机器 / 字节码`。现代编译器，通常会先生成中间代码（IR），然后再把IR翻译为机器码。

编译器完成编译后，由 `链接器（Linker）` 将生成的目标文件链接成可执行文件，这一步并不是必须的，一些依赖于虚拟机运行的语言（如 Java，Erlang）就不需要链接。

## 工具简介

编译器可以采用任意语言编写，为了降低编码工作量，充分利用现有工具。

本文编译器的构建将使用以下工具：

- **[Flex](http://www.gnu.org/software/flex/):** Flex 是 Lex 开源替代品，他们都是 `词法分析器` 制作工具，它可以根据我们定义的规则生成 `词法分析器` 的代码；

- **[Bison](https://www.gnu.org/software/bison/)：** Bison 是 `语法分析器` 的制作工具，同样它可以根据我们定义的规则生成 `语法分析器` 的代码；

- **[LLVM](http://llvm.org/)：** LLVM 是构架编译器的框架系统。使用llvm可以把 `抽象语法树` 翻译成中间代码（llvm IR），并把中间代码生成目标码，llvm支持各种不同的cpu构架目标码的生成。

在 ubuntu 上可以通过以下命令安装这些工具：

```bash
sudo apt install flex
sudo apt install bison
sudo apt install llvm
```

在windows上可以从下边地址下载安装包，安装

+ Flex:<http://gnuwin32.sourceforge.net/packages/flex.htm>
+ Bison:<http://gnuwin32.sourceforge.net/packages/bison.htm>
+ llvm:<https://releases.llvm.org/>