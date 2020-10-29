
# 生成llvm IR的方法
编译器前端从抽象语法树AST到IR的转换，通常是通过调用llvm的API接口生成的。生成IR主要有两种方法，通常都是结合两种方法实现：

1. 使用llvm提供的c接口来生成IR
2. 使用IRBuilder生成IR

IRBuilder是对C接口指令类的封装，用2生成module、function等，用到指令就用IRBuilder。

# 生成llvm IR的llvm API核心类及流程



# llvm IR基本语句生成方法

## 数据类型定义




## 常量定义

## 变量及赋值

## 函数定义

## 函数调用

### 内部函数调用

### 外部函数调用
