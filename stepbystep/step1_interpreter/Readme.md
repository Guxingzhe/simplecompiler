flex，bison，llvm实现简单交互式解释器。

## 实现功能

+ 仅支持加减法运算
+ 输入一行后，开始解释执行。
+ 输出结果后提示输入新表达式。
+ 输入q退出程序。

> 相当于一个非常简陋弱智的计算器^_^。


## 实现过程

+ 词法分析（flex）
+ 语法分析（bison）
+ 生成抽象语法树AST（bison，C++）
+ 生成IR代码（llvm api）
+ 解释执行IR代码

## 编译生成解释器

~~~
make clean
make
~~~

生成的 interpreter 文件就是解释器。


## 解释器运行(交互式)

编译完成后运行`./interpreter`命令，根据提示输入加减运算，将显示IR代码及运算结果。

示例如下：

~~~
$ ./interpreter

initing engine....

>1+1
2
=IR================================
; ModuleID = 'interpreterCalc'
source_filename = "interpreterCalc"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define internal i32 @mainfunc() {
entryblock:
  %0 = call i32 (...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 2)
  ret i32 0
}

declare i32 @printf(...)
===================================

>2+2
4
=IR================================
; ModuleID = 'JITcalc'
source_filename = "JITcalc"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define internal i32 @mainfunc() {
entryblock:
  %0 = call i32 (...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 4)
  ret i32 0
}

declare i32 @printf(...)
===================================

>q
~~~
