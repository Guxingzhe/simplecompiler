flex，bison，llvm实现简单编译器。

## 实现功能

+ 仅支持加减法运算
+ 输入一行结束后，开始编译。

> 相当于一个非常简陋弱智的计算器^_^。


## 实现过程

+ 词法分析（flex）
+ 语法分析（bison）
+ 生成抽象语法树AST（bison，C++）
+ 生成IR代码（llvm api）
+ 编译IR代码形成编译器

## 编译编译器

运行make clean清除上次编译的中间文件。运行make编译生成编译器。

~~~
make clean
make
~~~

生成的 compiler 文件就是编译器。

## 编译程序

+ 运行`./compiler`命令，根据提示输入加减运算，将程序编译为program.o。
+ 运行`cc program.o -o program`，生成目标程序文件program

示例如下：

~~~
$ ./compiler

Please input the expr:
5+5-2
Generating code...
Code is generated.
Wrote program.o

$ cc program.o -o program
~~~

## 运行目标程序

运行`./program`命令即可输出目标程序计算结果。

~~~
$ ./program
8
~~~
