# LexicalAnalyzer 类C词法分析器



## 开发信息



### 硬件 :computer:

- 型号：Dell Inspiration 7590；
- CPU：Intel Core i7-9750H；
- 内存：16GB 2666MHz；



### 软件 :floppy_disk:

- 系统：Windows 10 Home Basic 64-bit 20H1；
- GUI库：Qt 5.15.2 Open Source Version；
- GUI设计：Qt Creator 5.0.0；
- 编译器：MingGW 8.1.0 64-bit；
- 构建工具：Cmake 3.21.0；
- 版本控制：Git 2.32.0；
- 进程封装：Enigma Virtual Box 9.70；



## 词法分析内容



| **词法单元**                            | **种别码** | **助记符** | **内码**   |
| --------------------------------------- | ---------- | ---------- | ---------- |
| void                                    | 1          | $void      | -          |
| int                                     | 2          | $int       | -          |
| long                                    | 3          | $long      | -          |
| float                                   | 4          | $float     | -          |
| double                                  | 5          | $double    | -          |
| bool                                    | 6          | $bool      | -          |
| string                                  | 7          | $string    | -          |
| if                                      | 8          | $if        | -          |
| elif                                    | 9          | $elif      | -          |
| else                                    | 10         | $else      | -          |
| return                                  | 11         | $return    | -          |
| while                                   | 12         | $while     | -          |
| for                                     | 13         | $for       | -          |
| break                                   | 14         | $break     | -          |
| continue                                | 15         | $continue  | -          |
| switch                                  | 16         | $switch    | -          |
| case                                    | 17         | $case      | -          |
| default                                 | 18         | $default   | -          |
| true                                    | 19         | $true      | -          |
| false                                   | 20         | $false     | -          |
| $alpb ($alpb | $num)*                   | 21         | $id        | 符号表索引 |
| (ε \| + \| -) $num($num)*               | 22         | $integer   | 常数表索引 |
| (ε \| + \| -) $num($num)* . $num($num)* | 23         | $floatnum  | 常数表索引 |
| “any\*"                                 | 24         | $str       | 常数表索引 |
| =                                       | 25         | $assign    | -          |
| +                                       | 26         | $plus      | -          |
| -                                       | 27         | $sub       | -          |
| *                                       | 28         | $mul       | -          |
| /                                       | 29         | $div       | -          |
| %                                       | 30         | %mod       | -          |
| ==                                      | 31         | $eq        | -          |
| >                                       | 32         | $gre       | -          |
| >=                                      | 33         | $geq       | -          |
| <                                       | 34         | $les       | -          |
| <=                                      | 35         | $leq       | -          |
| !=                                      | 36         | $neq       | -          |
| &                                       | 37         | $and       | -          |
| \|                                      | 38         | $or        | -          |
| !                                       | 39         | $not       | -          |
| ;                                       | 40         | $smc       | -          |
| ,                                       | 41         | $cma       | -          |
| (                                       | 42         | $lpar      | -          |
| )                                       | 43         | $rpar      | -          |
| {                                       | 44         | $lbrc      | -          |
| }                                       | 45         | $rbrc      | -          |
| [                                       | 46         | $lsbrc     | -          |
| ]                                       | 47         | $rsbrc     | -          |
| :                                       | 48         | $colon     | -          |
| [a-z] \| [A-Z] \| _                     | 基本字     | $alpb      | -          |
| [0-9]                                   | 基本字     | $num       | -          |
| #                                       | 预处理内容 | $prc       | -          |
| (\t \|   \r \| \l \| 空格)*             | 预处理内容 | $ws        | -          |
| include                                 | 预处理内容 | $inclu     | -          |
| define                                  | 预处理内容 | $define    | -          |
| /* (any)\* */                           | 预处理内容 | $cmtm      | -          |
| //                                      | 预处理内容 | $cmts      | -          |



## 总结

从上表可见，程序中设计了预处理功能，能够支持C语言中的 “#define” 与“#include”，从而使得后续可以支持代码的模块化与包含功能。 

该识别表还支持了浮点数、字符串索引、bool 变量、for 语句以及 switch 语句等等功能，从而将原始类C语言功能扩充，在后续语法、词法分析中可以开发更接近C语言完整功能的编译器模块。

在桌面应用方面，本程序使用了Qt框架，同时在一些错误输入中设置了用户提示以便更正输入以及解决错误问题。

注意：

- 本程序的扫描半区设置为65个Unicode 字符长度，因此标识符不允许超过64字符长度。
- 本程序能识别简单错误，但无法做出错误处理。
