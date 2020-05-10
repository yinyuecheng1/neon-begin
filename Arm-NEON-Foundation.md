#                        Arm-NEON基础学习

## 寄存器

在arm指令集armv7和armv8上支持SIMD高级指令集NEON，armv7只支持32bit的操作，而armv8全面支持64bit的操作，所以v8的架构也称为“AArch64”，同时v8也保持了对v7的兼容，称为“AArch32”。

arm有通用寄存器和通用指令，以及支持SIMD的NEON寄存器和指令集，本篇主要介绍NEON的指令集，但是也会提及一些Arm通用的指令。

（1）armv7和aarch32

Armv7-A and AArch32 have the same general purpose Arm registers – 16 x 32-bit general purpose Arm registers (R0-R15). 都有16个32bit的通用寄存器。

Armv7-A and AArch32 have 32 x 64-bit NEON registers (D0-D31). These registers can also be viewed as 16x128-bit registers (Q0-Q15). Each of the Q0-Q15 registers maps to a pair of D registers, as shown in the following figure.  v7有32个64bit的NEON寄存器， D0-D31，也可以视作16个128bit的寄存器，Q0-Q15

（2）armv8和aarch64

AArch64 by comparison, has 31 x 64-bit general purpose Arm registers and 1 special register having different names, depending on the context in which it is used. These registers can be viewed as either 31 x 64-bit registers (X0-X30) or as 31 x 32-bit registers (W0-W30).  v8有31个64bit的通用寄存器，1个特殊用途寄存器。

AArch64 has 32 x 128-bit NEON registers (V0-V31). These registers can also be viewed as 32-bit Sn registers or 64-bit Dn registers.  V8有32个128bit的NEON寄存器，V0-V31



## 指令集

The Armv8-A AArch32 instruction set consists of A32 (Arm instruction set, a 32-bit fixed length instruction set) and T32 (Thumb instruction set, a 16-bit fixed length instruction set; Thumb2 instruction set, 16 or 32-bit length instruction set). It is a superset of the Armv7-A instruction set, so that it retains the backwards compatibility necessary to run existing software. There are some additions to A32 and T32 to maintain alignment with the A64 instruction set, including NEON division, and the Cryptographic Extension instructions. NEON double precision floating point (IEEE compliance) is also supported.



#### Armv7-A/AArch32 instruction syntax

V{<mod>}<op>{<shape>}{<cond>}{.<dt>}{<dest>}, src1, src2

example：

VADD.I8 D0, D1, D2

VMULL.S16 Q2, D8, D9



#### AArch64 NEON instruction syntax

{<prefix>}<op>{<suffix>} Vd.<T>, Vn.<T>, Vm.<T>





## 使用NEON的方式

- NEON optimized libraries
- Vectorizing compilers
- NEON intrinsics
- NEON assembly



#### NEON的加速库

别人已经用NEON优化好了，封装好的接口可以直接使用C++来调用。

- OpenMax DL
- Ne10



#### 使用向量化的编译器

Adding vectorizing options in GCC can help C code to generate NEON code. GNU GCC gives you a wide range of options that aim to increase the speed, or reduce the size of the executable files they generate. For each line in your source code there are generally many possible choices of assembly instructions that could be used. The compiler must trade-off a number of resources, such as registers, stack and heap space, code size (number of instructions), compilation time, ease of debug, and number of cycles per instruction in order to produce an optimized image file.



### NEON intrinsics（NEON内联函数）

NEON intrinsics provides a C function call interface to NEON operations, and the compiler will automatically generate relevant NEON instructions allowing you to program once and run on either an Armv7-A or Armv8-A platform. If you intend to use the AArch64 specific NEON instructions, you can use the 

(____aarch64__) macro definition to separate these codes, as in the following example.



调用内联函数接口，编译器会自动生成NEON指令。



### NEON assembly(写汇编)

有以下两种方法来写内联汇编：

- Assembly files
- Inline assembly

#### Assembly files

直接写汇编文件.s或.S，C语言特性的宏定义也可以使用。



#### Inline assembly

写内联汇编，直接在C、C++文件里写内联汇编函数。

You can use NEON inline assembly directly in C/C++ code.

**Pros:**

- The procedure call standard is simple. You do not need to save registers manually.
- You can use C / C ++ variables and functions, so it can be easily integrated into C / C ++ code.

**Cons**:

- Inline assembly has a complex syntax.
- NEON assembly code is embedded in C/C ++ code, and it’s not easily ported to other platforms.



内联汇编的优点是不需要手动保存寄存器，还可以使用C++中的函数和变量，因此容易和C++集成在一起。

但是缺点是内联汇编语法比较复杂，嵌入在C++中的代码不容易移植到其他平台。

#### 小结

内联函数优化的越来越好了，甚至在ARMv8 平台下有优于汇编的性能，同时兼容性方面又比汇编好，因此使用内联函数是上上之选。

毕竟，NEON肯定会更新的，到时一更新你的底层汇编得全部跟着更新，但是使用内联函数的话就不要考虑这些了，反正编译器都帮我们做了嘛！

最后关于内联函数总结几点人生经验：

- 使用的寄存器数量要考虑周全；
- 编译器注意好啊！
- 一定要看看产生的汇编代码啊！



## 基础CV库构建

### 目标

1.体积小

2.性能快

3.依赖少

4.模块之间尽量独立，可以通过编译选项独立编译

### 功能

1.基础的图像处理函数：主要是opencv中imgproc模块的功能







