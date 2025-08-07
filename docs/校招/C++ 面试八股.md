# C++ 面试八股



### 引用和指针的区别

1.   引用必须在声明时初始化，指针可以不需要初始化
     ```cpp
     #include <iostream>
     
     int main() {
         int value = 10;
         int* p;  // 不初始化
         p = nullptr;  // 将指针设置为空
         p = &value;  // 给指针赋值
         // int& ref_value;  // 报错
         int& ref_value = value;
     
         return 0;
     }
     ```

2.   指针是一个变量，存储的是一个地址，引用跟原来的变量实质上是同一个东西，是原变量的别名，引用本身并不存储地址，而是在底层通过指针来实现对原变量的访问

3.   引用被创建之后，就不可以进行更改，指针可以更改

4.   不存在指向空值的引用，必须有具体实体；但是存在指向空值的指针。



### 引用在声明的时候可以不初始化吗

引用在声明的时候必须初始化



### 指针常量和常量指针的区别

`const` 默认修饰左侧的内容，如果左侧无内容，则修饰右侧的内容

```cpp
int const* ptr;  // 指向常量整型的指针 --> 指针可以变，指向的内容不可以变
const int* ptr;  // 指向常量整型的指针 --> 指针可以变，指向的内容不可以变
int* const ptr;  // 指向整型的常量指针 --> 指针不可以变，指向的内容可以变
const int* const ptr;  // 指向常量整型的常量指针 --> 指针和指向的内容都不可以变
```

[[C/C++] const int* 与 int const* 的区别](https://blog.csdn.net/tengqi200/article/details/115441616)



### C++ 中的原子变量

C++ 中 `std::atomic` 用于实现原子操作，是 C++11 中引入的新特性。

多个线程可以对同一个变量进行读写操作，不会导致数据竞争或中间状态，也不需要锁的保护，一定程度上简化了代码编写，性能也会有提高。

1）什么是原子操作：

2）如何使用 `std::atomic`：

3）底层实现：`std::atomic` 通过 CPU 提供的原子指令来实现这些不可分割的操作。现代 CPU 会提供一组指令，比如 CMPXCHG, XADD 等来实现原子的读或写。

4）内存序约束：C++ 提供了多种内存序约束，比如 memory_order_relaxed, memory_order_acquire, memory_order_release 等。这些约束让你可以更好地控制程序的内存可见性和行为。
例如，memory_order_relaxed 只保证原子性，但不提供任何同步或顺序保证，而 memory_order_acquire 和 memory_order_release 则提供更严格的同步机制。
atomic 默认使用的是 memory_order_seq_cst，也就是最严格的内存序约束，既保证原子性，又提供了同步顺序保证。详见 cppreference。

5）和锁比较：虽然 `std::atomic` 可以在某些场景下替代锁，但它并不是万能的。锁在某些复杂场景下仍然是不可替代的。原子操作更适合一些基本的计数器或标志位，而对于复杂的数据结构，锁的使用仍是较优选择。

6）性能：使用原子操作通常比使用锁要快，因为锁涉及到上下文切换和操作系统调度，而原子操作都是硬件级别的操作。经过优化的原子操作可以使得你的程序在多线程环境下有更好的性能表现。



### map 和 unordered_map 的区别

|              | map                                | unordered_map                                              |
| ------------ | ---------------------------------- | ---------------------------------------------------------- |
| 底层数据结构 | 红黑树                             | 哈希表                                                     |
| 时间复杂度   | O(log n)                           | 平均O(1)，最坏情况下(所有元素都在同一个哈希桶中)退化为O(n) |
| 空间复杂度   | 相对较低                           | 相对较高，因为哈希表需要分配额外的空间来存储和处理冲突     |
| 元素顺序     | 有序，按照键排序                   | 无序                                                       |
| 适用场景     | 有序，对时空复杂度严格要求O(log n) | 不关心顺序，需要更快的插入、删除和查询操作                 |



### 介绍红黑树

[【数据结构】史上最好理解的红黑树讲解，让你彻底搞懂红黑树](https://blog.csdn.net/cy973071263/article/details/122543826)



### 常见的排序算法有哪些？

| 排序算法     | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 稳定性 | 适用场景                     |
| ------------ | -------------- | -------------- | ---------- | ------ | ---------------------------- |
| **冒泡排序** | O(n²)          | O(n²)          | O(1)       | 稳定   | 教学用途，小规模数据         |
| **选择排序** | O(n²)          | O(n²)          | O(1)       | 不稳定 | 简单但低效                   |
| **插入排序** | O(n²)          | O(n²)          | O(1)       | 稳定   | 小规模或基本有序数据         |
| **希尔排序** | O(n log n)     | O(n²)          | O(1)       | 不稳定 | 改进的插入排序，中等规模数据 |
| **归并排序** | O(n log n)     | O(n log n)     | O(n)       | 稳定   | 大数据量，外部排序           |
| **快速排序** | O(n log n)     | O(n²)          | O(log n)   | 不稳定 | 通用最快，内存排序           |
| **堆排序**   | O(n log n)     | O(n log n)     | O(1)       | 不稳定 | 无需额外空间，优先级队列     |
| **计数排序** | O(n + k)       | O(n + k)       | O(k)       | 稳定   | 整数范围小且密集的数据       |
| **桶排序**   | O(n + k)       | O(n²)          | O(n + k)   | 稳定   | 均匀分布的数据               |
| **基数排序** | O(n × k)       | O(n × k)       | O(n + k)   | 稳定   | 多关键字排序（如字符串）     |



### I/O模型有哪些？

| I/O 模型         | 阻塞？ | 同步？ | 核心机制              | 适用场景             |
| ---------------- | ------ | ------ | --------------------- | -------------------- |
| **阻塞 I/O**     | 是     | 同步   | 线程全程等待          | 简单低并发程序       |
| **非阻塞 I/O**   | 否     | 同步   | 线程轮询检查          | 需兼顾其他任务的程序 |
| **I/O 多路复用** | 是[^1] | 同步   | `select`/`epoll` 监听 | 高并发网络服务       |

[^1]: I/O 多路复用中，`select`/`epoll` 调用本身是阻塞的，但可监听多个 I/O。



*   阻塞 I/O
    *   调用 I/O 操作时，线程一直等待，直到数据就绪或操作完成。
    *   期间线程无法执行其他任务（CPU 闲置）。
*   非阻塞 I/O
    *   调用 I/O 操作时，若数据未就绪，立即返回错误（如 EWOULDBLOCK）。
    *   线程需轮询检查数据是否就绪（消耗 CPU）。
    *   线程可执行其他任务（但需主动轮询）。
*   I/O 多路复用
    *   使用 select/poll/epoll等系统调用，单线程监听多个 I/O 事件。
    *   当某个 I/O 就绪时，通知线程处理。



### 常见的多路复用机制

#### `select`

*   **跨平台**：支持所有主流操作系统（Linux/Windows/macOS）。
*   **基于轮询**：通过遍历文件描述符集合（`fd_set`）检查就绪状态。
*   限制：
    *   单个进程最多监听 **1024** 个文件描述符（FD）。
    *   每次调用需**全量拷贝**`fd_set` 到内核。
*   缺点
    *   O(n) 时间复杂度：每次遍历所有 FD，性能随 FD 数量线性下降。
    *   重复初始化：每次调用需重新设置 `fd_set`。

```cpp
```



#### `poll`

*   改进 `select` 的 FD 数量限制，使用**链表**存储 FD（理论无上限）。
*   仍需要**遍历所有 FD** 检查就绪状态（O(n) 时间复杂度）。



#### `epoll`

*   Linux
*   **事件驱动**：内核通过**回调机制**直接通知就绪的 FD，无需遍历（O(1) 时间复杂度）。
*   **高效内存**：使用**红黑树**管理 FD，支持**水平触发（LT）**和**边缘触发（ET）**模式。

**核心函数**

*   `epoll_create()`：创建 epoll 实例。
*   `epoll_ctl()`：添加/修改/删除监听的 FD。
*   `epoll_wait()`：等待就绪事件。

```cpp
```



**触发模式**

*   水平触发：只要 FD 可读/可写，epoll_wait() 会持续通知（默认模式，类似 poll）。
*   边沿触发：仅在 FD 状态变化时通知一次（需一次性处理完数据，否则可能丢失事件）。

**优点**

*   高性能：支持百万级并发（如 Nginx、Redis）。
*   低开销：无需每次调用传递所有 FD。





### 读写锁

多线程环境下对共享资源的读多写少场景，使用读写锁正适合，它通过区分读操作和写操作，可以显著提高并发性能。

*   读锁：多个线程可同时持有读锁（共享访问）。
*   写锁：仅一个线程能持有写锁，且期间不允许任何读锁或其他写锁（独占访问）。

优势：

*   读操作不互斥，适合读多写少的场景（如缓存、数据库）。
*   写操作独占资源，避免数据竞争。

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202508071125294.jpeg)



### 读饥饿

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202508071125819.jpeg" alt="img" style="zoom:50%;" />

读饥饿是读写锁中的一种现象，指写线程因读线程持续占用锁而长时间无法获取写锁，导致写操作被“饿死”（无法执行）。这种现象在高并发读场景下很常见。

原因：

*   多个读线程频繁获取读锁（共享访问）。
*   写线程尝试获取写锁时，必须等待所有读锁释放。
*   若读锁的获取是连续的（无间隙），写线程将无限等待。

危害：

*   数据更新延迟：写操作无法执行，导致数据长时间不更新。
*   系统响应下降：写线程阻塞可能引发超时或死锁。
*   公平性破坏：违背“先来先服务”原则。

解决方案：

*   公平读写锁：通过队列或优先级机制，保证写锁请求不会被后续读锁插队。比如一旦有写锁请求，后续读锁必须等待写锁完成。
*   限制读锁持有时间：设置读锁的最大持有时间，超时后自动释放。
*   避免长期持有读锁：将长耗时读操作拆分为多个短操作，间歇释放锁。



### 什么是三大范式?



### 什么是内存泄漏，产生的原因？



### 



### 如何解决 C/CPP 中头文件重复包含的问题

想要解决 C/CPP 中头文件重复包含的问题，有两种方式：

1.   在头文件的第一行使用预处理指令 `#pragma once`，`#pragma once` 是一个**非标准**的但广泛支持的预处理指令，它告诉编译器该头文件在单个编译过程中只应被包含一次。编译器在第一次遇到 `#pragma once` 时会记住该文件名，并在后续的包含操作中忽略它。

2.   使用预处理指令 `#ifndef`、`#define` 和 `#endif` 保护头文件：
     ```cpp
     #ifndef EXAMPLE_H
     #define EXAMPLE_H
     
     class MyClass {
     public:
         MyClass(); // 构造函数声明
         void myFunction(); // 成员函数声明
     };
     
     #endif
     ```

     



## C++ 多态

### 介绍多态，具体如何实现

C++ 中的多态分为静态多态和动态多态，没有特别指明的情况下，一般是指动态多态，即使用 virtual 实现的多态。

在 C++ 面向对象的程序设计方法中，面向对象的三大特性：

1.   封装
2.   继承
3.   多态

1）虚函数：在基类中使用 `virtual` 关键字声明虚函数之后，子类可以重写这个函数 (override)。

2）虚函数表 (vtable)：每一个包含虚函数的类在**编译时**都会生成虚函数表 (vtable)。它存储该类所有指向虚函数的指针，对于每个类，编译器会创建唯一的 vtable。

3）虚函数表指针 (vptr)：每个包含虚函数的对象实例**编译器**会为其生成一个隐藏的虚函数表指针 (vptr)，它在对象创建时自动初始化，指向该类的 vtable。不同类型的对象，其 vptr 指向不同的虚表。

4）多态的调用机制：当通过基类指针或引用调用虚函数时，程序会通过该指针或引用找到对应的对象，然后通过 vptr 从 vtable 中找到对应的虚函数函数地址，最终调用适当的函数实现，这样程序能够在**运行时决定**调用哪一个函数实现。

5）实例：

```cpp
#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void Draw() const = 0;
};

class Circle : public Shape {
public:
    virtual void Draw() const override {
        std::cout << "Draw a circle.\n";
    }
};

class Square : public Shape {
public:
    virtual void Draw() const override {
        std::cout << "Draw a square.\n";
    }
};

void RenderAll(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        shape->Draw();  // 动态绑定，调用具体实现
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Square>());
    RenderAll(shapes);

    return 0;
}
```

6）:warning:注意事项：

*   使用多态会有一定的内存和性能开销，因为每个类需要维护 vtable，每个对象也需要存储 vptr；
*   虚函数调用通常比普通函数调用更慢，因为多了一次指针间接寻址。



### 析构函数可以是虚函数吗，构造函数可以是虚函数吗

**构造函数不能是虚函数**。

虚函数的机制依赖于虚函数表，而虚表对象的建立需要在调用构造函数之后才能完成。因为构造函数是用来初始化对象的，而在对象的初始化阶段虚表对象还没有被建立，如果构造函数是虚函数，就会导致对象初始化和多态机制的矛盾，因此，构造函数不能是虚函数。

虽然构造函数不能是虚函数，但是**析构函数应当是虚函数**，特别是在基类中。这样做的目的是为了确保在删除一个指向派生类对象的基类指针时，能正确调用派生类对象的析构函数，从而避免资源泄露



### C++ 多态解决了什么问题

多态分为静态多态和动态多态

静态多态通过模板和函数重载实现

动态多态通过虚函数和继承实现

![image-20250806110659917](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202508061107767.png)

**静态多态**

```cpp
#include <iostream>
#include <string>

class Circle {
public:
    void Draw() const {
        std::cout << "Draw a circle.\n";
    }
};

class Square {
public:
    void Draw() const {
        std::cout << "Draw a square.\n";
    }
};

template <typename T>
void Draw(const T& shape) {
    shape.Draw();  // 编译时绑定
}

int main() {
    Circle c;
    Square s;

    Draw(c);  // 模板参数推导
    Draw(s);  // 模板参数推导

    return 0;
}
```

1.   复用：Draw 模板适用于任何有 Draw 方法的类型

2.   扩展：新增只需实现 Draw，无需修改模板

3.   解耦：Draw 不依赖基类，仅依赖隐式接口



**动态多态**

```cpp
#include <iostream>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void Draw() const = 0;
};

class Circle : public Shape {
public:
    virtual void Draw() const override {
        std::cout << "Draw a circle.\n";
    }
};

class Square : public Shape {
public:
    virtual void Draw() const override {
        std::cout << "Draw a square.\n";
    }
};

void RenderAll(const std::vector<Shape*>& shapes) {
    for (const auto* shape : shapes) {
        shape->Draw();  // 动态绑定，调用具体实现
    }
}

int main() {
    std::vector<Shape*> shapes = {new Circle(), new Square()};
    RenderAll(shapes);

    for (auto* shape : shapes) {
        delete shape;
    }

    return 0;
}
```

1.   复用：RenderAll
2.   扩展：新增只需继承 Shape 并实现 Draw()，无需修改 RenderAll
3.   解耦：RenderAll 只依赖抽象 Shape，不依赖具体图形类



[字节后端C++一面：C++多态解决了什么问题？【码农Mark】](https://www.bilibili.com/video/BV1vNTtzuEVj/?spm_id_from=333.1391.0.0&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)



## 堆栈

### 堆和栈在操作系统的底层实现

扩展问题：

1.   为什么栈的分配速度比堆快？
2.   多线程程序中，栈和堆如何隔离？

![image-20250806150652747](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202508061509556.png)

[一步一图带你深入理解 Linux 虚拟内存管理 ](https://www.cnblogs.com/binlovetech/p/16824522.html)

栈在操作系统底层实现：

1.   线程创建的时候，操作系统为其创建栈空间；

2.   栈的使用：只需移动栈指针；

3.   硬件支持：寄存器 x86 下为 rsp 和 rbp；

4.   操作系统管理：

     a. 函数调用时，先将参数压栈；
     b. 执行 call 指令，将返回地址（返回上一级函数的下一条指令）压栈；
     c. 创建栈帧，保存旧的 rbp，设置新的 rbp；
     d. 可能为局部变量分配栈空间，以及清理局部变量等的栈空间；
     e. 恢复之前的 rbp 和 rsp，ret 指令弹出返回地址。



栈又分为进程栈和线程栈：
进程栈(主线程栈)：进程启动时创建；
线程栈：pthread_create clone 系统调用。



![image-20250806150912686](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202508061509668.png)

堆在用户态空间以及扩展方向(低地址向高地址扩展)。



1.   为什么栈的分配速度比堆快？
     答：因为栈只需要移动栈指针，而堆需要查找空闲块、处理碎片和系统调用。
2.   多线程程序中，栈和堆如何隔离？
     答：栈是线程私有的，堆是进程共享的，需要用同步机制控制，比如锁。



[拼多多C++二面：堆和栈在操作系统底层的实现、为什么栈的分配速度比堆快？](https://www.bilibili.com/video/BV1pZPieyEym/?spm_id_from=333.1391.0.0&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)



## 参考资料

[1] [百度一面面经（C++）](https://blog.csdn.net/qq_29426201/article/details/147271710)

[2] [百度C++开发岗三面面经(已offer)](https://www.nowcoder.com/discuss/353155780922777600)

[3] [百度提前批，三面被推迟一周，喜提秋招第一凉](https://zhuanlan.zhihu.com/p/1935627993805463760)

[4] [百度c++开发面经（已OC）](https://www.nowcoder.com/feed/main/detail/1f237804872148f38fbcb8f6fae03ad9?sourceSSR=dynamic)

[5] [百度后端C++，一面、二面 + 主管面面经（已拿offer）](https://blog.csdn.net/weixin_55305220/article/details/121121416)

[6] [史上最全C/C++面试、C++面经八股文，一文带你彻底搞懂C/C++面试、C++面经！](https://blog.csdn.net/songbijian/article/details/132507421)

[7] 
