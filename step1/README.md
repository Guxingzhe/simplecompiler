## 简介
仅实现 **整数** **加减法** 运算的最简单语言的一编译器

## 源文件说明

+ lexical.l: Flex源文件，用于词法分析，识别源代码输出token。
+ syntax.y: Bison源文件，用于语法和语义分析，根据token输出语法树。
+ node.h：抽象语法树类
+ sample：文件夹内包含示例

> 由于语法过于简单，不进行语义分析

## 示例