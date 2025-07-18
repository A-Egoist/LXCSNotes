# 基于 CUDA 的异构并行计算

CUDA (Compute Unified Device Architecture，统一计算设备架构) 是 NVIDIA 提出的并行计算架构，结合了 CPU 和 GPU 的优点，主要用来处理密集型及并行计算。CPU 和 GPU 是两个独立的处理器，通过单个计算节点中的 PCI-Express 总线相连，GPU 用来提高计算密集型应用程序中并行程序段的执行速度，CPU 则负责管理设备端的资源。

## 1 并行计算

在 [1.4](#1.4 如何编写并行程序) 中介绍了应用程序的两种并行性：任务并行和数据并行，CUDA 编程非常适合解决==数据并行==的问题。

数据并行程序设计的第一步就是把数据依据线程划分：

* 块划分：每个线程作用于一部分数据，通常这些数据具有相同的大小。
* 周期划分：每个线程作用于数据的多部分。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062343926.png" style="zoom:80%;" />



## 2 异构计算

异构计算，首先必须了解什么是异构，不同的计算机架构就是异构，在 [2.3](#2.3 并行硬件) 中介绍计算机架构，就是为了引出异构的概念，按照指令集划分或者按照内存结构划分。

一个典型的异构架构：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062343234.png" style="zoom: 67%;" />

- 左图：一个四核 CPU 一般有四个 ALU，ALU 是完成逻辑计算的核心，控制单元、缓存也在片上，DRAM 是内存，一般不在片上，CPU 通过总线访问内存。
- 右图：GPU，绿色小方块是 ALU，我们注意红色框内的部分SM，这一组 ALU 公用一个 Control 单元和 Cache，这个部分相当于一个完整的多核 CPU，但是不同的是 ALU 多了，Control 部分变小，可见计算能力提升了，控制能力减弱了，所以对于逻辑复杂的程序，一个 GPU 的 SM 是没办法和 CPU 比较的，但是对于逻辑简单，数据量大的任务，GPU 更加高效，并且一个GPU有多个SM。

CPU 和 GPU 配合，各取所长可以完成更加多样的任务：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062343686.png" style="zoom: 50%;" />



## 3 CUDA

CUDA 不是单单指软件或者硬件，而是建立在 Nvidia GPU 上的一整套平台，并扩展出多语言支持。因此，想要使用 CUDA 就必须得有 NVIDIA GPU 环境。

CUDA C 是标准 ANSI C 语言的扩展，扩展出一些语法和关键字来编写设备端代码，而且 CUDA 库本身提供了大量 API 来操作设备完成计算。

在 CUDA 程序中，通常将代码分为两个部分：

* CPU 主机端(Host)
* GPU 设备端(Device)

在编译代码的时候，使用过 `nvcc` 编译。CUDA nvcc 编译器会自动分离你代码里面的不同部分，如果主机代码用 C 写成，则使用本地的 C 语言编译器编译；设备端代码，也就是核函数(Kernel)，用 CUDA C 编写，通过 nvcc 编译，链接阶段，在内核程序调用或者明显的 GPU 设备操作时，添加运行时库。

**Hello World**

```c
// hello.cu
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
__global__ void hello(void)
{
	printf("Hello world from GPU\n");
}
int main()
{
	printf("Hello world from CPU\n");
	hello << <1, 10 >> > ();
	cudaDeviceReset();
	return 0;
}
```

若在 Linux 系统中运行需要使用如下命令编译代码

```bash
nvcc hello.cu -0 hello.out
```

使用如下命令执行代码

```bash
./hello.out
```

运行结果：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062343133.png" style="zoom: 80%;" />



在上面的代码中，`__global__` 用于声明运行在设备上的核函数；`<<<1, 10>>>` 三重尖括号意味着从主线程到设备端代码的调用，一个核函数通过一组线程来执行，多有线程执行相同的代码，其中的参数是执行配置，用来说明有多少线程来执行核函数；`cudaDeviceReset()` 用于同步，因为 CPU 和 GPU 的执行时异步的，为了防止 GPU 还没有执行完程序，CPU 就已经退出程序了。

CUDA 程序的编写一般分为如下步骤：

1. 分配 Host 内存，并进行数据初始化
2. 分配 GPU 内存
3. 将数据从 Host 拷贝到 Device
4. 调用 CUDA Kernel 在 Device 上计算
5. 将计算结果从 Device 拷贝回 Host
6. 释放 GPU 内存

CUDA 中影响性能的结构：

* 内存层次结构
* 线程层次结构

CUDA 抽象了硬件实现：

* 线程组的层次结构
* 内存的层级结构
* 障碍同步