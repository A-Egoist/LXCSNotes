# GDB

### 什么是 GDB？

**GDB** (GNU Debugger) 是一个功能强大的命令行调试工具，用于调试 C、C++、Go、Rust 等多种语言编写的程序。对于以后想称为一个 Linux 下工作的 C/C++ 程序员，GDB 是必不可少的工具，所以本篇来从零讲解 GDB 在 Linux 的调试。你可以用它来：

-   启动程序，并设置断点让程序在指定位置停止。
-   检查程序停止时内存中的变量和数据。
-   逐步执行代码，一行一行地观察程序的执行流程。
-   修改变量的值，并继续执行程序。

简单来说，GDB 就像是你程序的一个“X光机”，让你能深入地看到程序运行时的每一个细节，从而更高效地定位和修复问题。

### GDB 安装

**查看是否安装**

使用 `which` 或 `command -v` 命令判断是否安装 `GDB`：

```bash
which gdb
```

```bash
command -v gdb
```

**安装**

```bash
sudo apt update
sudo apt install gdb
```



### GDB 快速入门：调试 C++ 程序

要使用 GDB 调试 C++ 程序，你需要先用一个特定的编译选项来编译你的代码：**`-g`**。这个选项会在编译时将调试信息嵌入到可执行文件中，这些信息包括变量名、函数名、行号等，GDB 才能理解你的源代码。

这是一个简单的 C++ 程序 `main.cpp`：

```cpp
#include <stdio.h>

int AddToTop(int top) {
    printf("Enter AddToTop\n");

    int count = 0;
    for (int i = 0; i <= top; ++ i) {
        count += i;
    }

    printf("Quit AddToTop\n");

    return count;
}
int main() {
    int top = 10;
    int ret = AddToTop(top);

    printf("ret = %d\n", ret);
    return 0;
}
```



#### 1. 编译带调试信息的代码

在终端中，使用 `g++` 编译器，并加上 `-g` 选项：

```bash
g++ -g main.cpp -o main
```

`-g` 表示编译为【Debug】版本，g++ 默认编译为【Release】版本。【Debug】版本相比于【Release】版本多了**调试信息**。



#### 2. 启动 GDB

运行 GDB 并加载可执行文件：

```bash
gdb ./main
```

你会看到 GDB 的命令行提示符 `(gdb)`。



#### 3. 设置断点

**断点** (breakpoint) 是程序中你希望暂停执行的位置。你可以用 `b` 或 `break` 命令来设置。

-   **按函数名设置断点：**

    ```
    (gdb) b main
    (gdb) b printVector
    ```
    
-   **按行号设置断点：**

    ```
    (gdb) b example.cpp:11
    ```





#### 4. 运行程序

使用 `r` 或 `run` 命令开始运行程序。程序会在第一个断点处停止。

```
(gdb) r
```



#### 5. 常用调试命令

一旦程序停止，你可以使用以下命令来检查程序状态：

-   **`n` (next)：** 单步执行，跳到下一行代码。如果下一行是函数调用，`n` 会把这个函数当作一个整体执行，而不是进入函数内部。

-   **`s` (step)：** 单步执行，但会进入函数内部。

-   **`c` (continue)：** 继续执行，直到遇到下一个断点或程序结束。

-   **`p <变量名>` (print)：** 打印变量的值。

    ```
    (gdb) p sum
    (gdb) p numbers
    ```
    
-   **`bt` (backtrace)：** 打印函数调用栈，可以看到程序是如何一步步走到当前位置的。

-   **`l` (list)：** 查看源代码。可以指定行号或函数名，例如 `l main` 或 `l 15`。

-   **`i b` (info breakpoints)：** 查看所有已设置的断点。

-   **`d <断点编号>` (delete)：** 删除一个或多个断点。



#### 6. 结束调试

-   **`q` (quit)：** 退出 GDB。



### GDB 调试实战

```cpp
#include <stdio.h>

void swap(int* x, int* y) {
	int t = *x;
	*x = *y;
	*y = t;                                                                 
}

int main(void) {
	int a = 10;
	int b = 20;
	printf("a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);
	return 0;
}
```



### 指令总结

#### :sparkles: 行号显示

l(list) 行号——显示对应的代码和行号

【l】随机显示10行内容

【l 0】从第一行开始往下列10行

若想看到后面的代码，只需要多按几次【Enter】键就行，gbd 会自动记忆上次命令

![image-20250822111346573](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221113128.png)



#### :sparkles: 断点设置

【b 行号】——在这一行打断点

【b 源文件: 函数名】——在该函数的第一行打断点

【b 源文件: 行号】——在该源文件中的这一行打断点

![image-20250822111441053](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221114609.png)



#### :sparkles: 查看断点信息

【info】——查看所有的调试信息

【info b】——查看断点的信息

字段信息：

*   Num——编号
*   Type——类型
*   Disp——状态
*   Enb——是否可用
*   Address——地址
*   What——断点位置

![image-20250822111303447](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221113830.png)



#### :sparkles: 删除断点

【d 断点编号】——删除对应断点

【d breakpoints】——删除所有断点

![image-20250822111640648](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221118947.png)

:warning: 在退出 gdb 之前，断点编号是不断累加的，即现在删除了断点5之后，下次增加的断点编号为6，而不是5：

![image-20250822111823690](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221118352.png)



#### :sparkles: 开启 / 禁用断点

【disable b】——使所有断点无效，即禁用所有断点

【enable b】——使所有断点有效，即启用所有断点

【disable b 断点编号】——使一个断点无效，禁用断点

【enable b 断点编号】——使一个断点有效，启用断点

![image-20250822112141621](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221121012.png)



#### :sparkles: 运行 / 调试

r(run)——F5，无断点直接运行，有断点则会停在第一个断点处

![image-20250822112637822](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221126591.png)



#### :sparkles: 逐过程和逐语句

n(next)——逐过程，相当于F10，单步执行。如果函数中不存在断点，则不会进入函数；如果函数中存在断点则会进入函数。

s(step)——逐语句，相当于F11，单步执行，可以进入函数。

c(continue)——继续运行，直到遇到断点或程序结束。

![image-20250822112958345](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221141060.png)

如图所示，启用的断点为第6行、第11行、第16行和第19行的断点。



#### :sparkles: 打印 / 追踪变量

p(print)——打印变量值

【print 变量名】

![image-20250822114138009](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221141993.png)

【display 变量名】——跟踪查看一个变量，每次停下来都会显示它的值。

【display &变量名】——追踪变量的地址。

【undisplay 变量名编号】——取消追踪指定变量



#### :sparkles: 查看函数调用

【bt】——看到底层函数调用的过程，函数压栈



#### :sparkles: 修改变量的值

【set var 变量名=变量值】——修改变量的值

![image-20250822114735490](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221147206.png)

:warning: 不能在第16行的位置修改 top 的值，因为在断点位置停下的时候并没有运行这一行代码，所以需要使用【n】运行到下一行，然后再修改 top 的值。



#### :sparkles: 指定行号跳转

【until 行号】——进行指定位置挑战，执行完区间代码

如下所示，在进入 for 循环之后，使用 【n】会逐步运行 for 循环，非常麻烦：

![image-20250822115043452](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508221152197.png)

使用【until】就可以运行完 for 循环且在没有断点的位置——第11行停止：

![image-20250822115457406](C:\Users\Amonologue\AppData\Roaming\Typora\typora-user-images\image-20250822115457406.png)



#### :sparkles: 强制执行函数

finish——在一个函数内部，执行到当前函数返回，然后停下来等待命令

*   有时候我们会有这样的需求，在初步排查的时候推断可能是某个函数内部的逻辑出了问题，但是呢又不想一步步地进到函数内部进行调试，在VS中其实很简单，只需要在函数下方设个断点，然后F5直接运行到断点处即可。
*   但是在Linux下的gdb中，我们可以使用【finsh】指令来直接使一个函数执行完毕。从下图我们可以看到，首先【s】进到函数内部，接下去我直接使用finish，可以看到它直接回到了调用函数的位置，returned了一个返回值。
*   然后可以看到，在获取到返回值后，也就直接进行了printf打印。



#### :sparkles: 跳转到下一个断点

`c(continue)`

【c】——从一个断点处，直接运行至下一个断点处。



### GDB 小技巧

-   **命令自动补全：** 在 GDB 命令行中，按 `Tab` 键可以自动补全命令和变量名。

-   **历史命令：** 使用上下方向键可以查看和重复之前的命令。

-   **设置观察点：** `watch <表达式>`。当表达式的值发生变化时，程序会自动停止。这对于跟踪变量何时被意外修改非常有用。例如：

    ```
    (gdb) watch sum
    ```
    
-   **查看局部变量：** `i locals`。打印当前函数的所有局部变量。

掌握这些基本命令和技巧，你就可以快速上手使用 GDB 来定位和解决 C++ 程序中的 Bug 了。



## 参考资料

[1] [【Linux】GDB保姆级调试指南（什么是GDB？GDB如何使用？）](https://blog.csdn.net/weixin_45031801/article/details/134399664)