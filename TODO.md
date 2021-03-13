# TODO List

## 下一步要做：
 1. [done] 使用ISAParser生成 RV32i指令的 decode/execute 代码 （decode和execute代码合在一起，完成指令的执行）
 1. [done] 准备环境，如 GPR, MemoryAccess , SING_EXT 等 函数/宏，使指令代码可以编译通过
 1. [done] 通过简单的mask 匹配完成指令的解码和匹配 （decoder）
 1. 整合编译，完成一个简单的ELF加载和执行。
 1. ISAParser: 解决racc语法 里面的 shift/reduce conflicts 问题

## 远期计划：
 1. 实现自动生成decode tree， 优化decoder代码。
 1. 分离 decode 过程和 execute 过程，添加指令decode info cache， 优化执行速度。
 1. 测试 clang 或者 mir 动态编译过程， 将多条指令的 执行代码合并到一起， 编译成一个bb块，整体执行。（跳转指令总是跳出来到环境里面）
 1. 优化 bb 块内跳转指令的处理，使得直接跳转无需跳出回到环境
 1. 优化间接跳转的查询处理过程，优化返回的处理过程。 （这个阶段以及可以和qemu速度比较了）

## 功能级仿真功能完善：
 1. 添加更多指令的支持：RISC-V, ARM 等
 1. 添加系统调用的支持，完善用户态支持。（支持RISCV/ARM semihosting）。
 1. 系统级仿真支持： MMU， 中断， Device 的基础支持。
 1. 指令的翻译执行和解释执行 模式混合运行。 允许在目标区域（指令界定）、锁定进程（系统模式）、用户态 的条件下进入解释执行模式。
 1. 解释执行： 不使用动态翻译的执行模式，与采用动态翻译的模式相对应。

## 性能级时序级功能完善：
 1. Replay able CPU的支持。
 1. 指令的 SRC/DST 寄存器分析。（基于解析指令 EXECUTE 部分的 C代码）
 1. 支持对 UOP定义的支持。 （语法定义， ISAParser完善）
 1. Cycle级仿真平台（另一个项目了）

## 文档完善：
 1. hisimu 模型简介，优势是什么？ 与其他平台的对比。
 1. 文档式：容易理解，容易修改添加
 1. 基于C语言的动态翻译拥有比QEMU更大的优化空间，尤其是对浮点/SIMD指令的处理。
 1. hisimu 工作原理
 1. ISA Definition 语法说明
