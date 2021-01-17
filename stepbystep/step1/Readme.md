## 简介
基于flex，bison，llvm实现一个最简单的编译器。包括

+ REPL交互环境(interpreter，交互式运行)
+ JIT解释器(JIT，解释运行)
+ 编译器(compiler，编译为目标代码，用系统链接器链接)

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

生成的 `interpreter`,`jit`,`compiler` 就是编译器执行文件。

## 编译运行程序

### 交互式运行

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



### jit解释运行

~~~
$ ./jit

>1+1
>a=2
>b=3
>a+b+1
>Generating code...
create block
Creating binary operation
create intger
create intger
crate assign 
create intger
crate assign 
create intger
Creating binary operation
Creating binary operation
get identifier
get identifier
create intger
; ModuleID = 'tstjit'
source_filename = "tstjit"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define internal i32 @mainfunc() {
entryblock:
  %a = alloca i32, align 4
  store i32 2, i32* %a, align 4
  %b = alloca i32, align 4
  store i32 3, i32* %b, align 4
  %0 = load i32, i32* %a
  %1 = load i32, i32* %b
  %addrst = add i32 %0, %1
  %addrst1 = add i32 %addrst, 1
  %2 = call i32 (...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 %addrst1)
  ret i32 0
}

declare i32 @printf(...)
Running code:
6
Exiting...

~~~


### 编译程序，运行目标程序

#### 编译目标程序

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

#### 运行目标程序

运行`./program`命令即可输出目标程序计算结果。

~~~
$ ./program
8
~~~
