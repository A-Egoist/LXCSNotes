# C++ 面试八股

### 程序运行的步骤

源文件

:arrow_down:

预编译 (Pre-Processor)：将头文件编译，进行宏替换，输出.i文件

:arrow_down:

编译 (Compiler)：将其转化为汇编语言文件，主要做词法分析，语义分析以及检查错误，检查无误后将代码翻译成汇编语言，生成.s文件

:arrow_down:

汇编 (Assembler)：汇编器将汇编语言文件翻译成机器语言，生成.o文件

:arrow_down:

链接 (Linker)：将目标文件和库链接到一起，生成可执行文件.exe

:arrow_down:

可执行文件

[为什么有些项目会使用多种编程语言？](https://www.bilibili.com/video/BV1aXbXzfEsM/?spm_id_from=333.1245.0.0&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)



### 什么是函数指针



### 回调函数

[【C语言】不管学什么都要会的回调函数](https://www.bilibili.com/video/BV1v8hwzbEfi?spm_id_from=333.1245.0.0)



### Linux 中的一些指令

#### awk

```bash
awk '{print $NF}' test
```

其中 `test.txt`

```text
test1, 123455
test2, sfdf, sfdf
test3, sdt, sdf, sdfsf
```



### Git 中 merge 和 rebase 的区别

[Git：图解 merge 和 rebase 的区别](https://zhuanlan.zhihu.com/p/686538265)



### C 和 C++ 的区别

C++ 是面向对象的，而 C 是面向过程的，这是它们最根本的区别。C++ 有面向对象的三大特性：封装、继承、多态。C++ 引入了模板、引入了 RAII 的内存管理机制。



### C++ 中强制类型转换和 C 语言类型转换的区别

对比表格

| 转换类型   | C 风格            | C++ 风格                       | 安全性     |
| ---------- | ----------------- | ------------------------------ | ---------- |
| 数值转换   | `(type)value`     | `static_cast<type>(value)`     | 相同       |
| 指针转换   | `(type*)ptr`      | `dynamic_cast<type*>(ptr)`     | C++ 更安全 |
| const 转换 | `(type*)constPtr` | `const_cast<type*>(constPtr)`  | 相同       |
| 重新解释   | `(type*)ptr`      | `reinterpret_cast<type*>(ptr)` | 相同       |



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

3.   <mark>引用被创建之后，就不可以进行更改</mark>，指针可以更改

4.   不存在指向空值的引用，必须有具体实体；但是存在指向空值的指针。

<mark>引用在声明的时候必须初始化</mark>



### 左值引用和右值引用的区别

在 C++ 中，**左值引用（lvalue reference）** 和 **右值引用（rvalue reference）** 是两种不同的引用类型，它们的主要区别在于 **绑定对象的类别（左值 or 右值）** 和 **用途（拷贝优化 or 资源转移）**。

**左值**是指既能出现在等号左边也能出现在等号右边的变量(或表达式)，**右值**则只能出现在等号右边。

*   **左值（lvalue）**：可以取地址、有名字的持久对象（如变量、函数返回的引用等）。 **绑定到左值（lvalue）** 的引用，用 `&` 表示。

    ```cpp
    int x = 10;  
    int& lref = x;  // ✅ 左值引用绑定左值
    lref = 20;      // 修改 x 的值
    
    int& bad = 42;  // ❌ 错误：不能绑定到右值（临时对象）
    ```

*   **右值（rvalue）**：临时对象、即将销毁的对象（如字面量、`std::move` 后的对象）。 **绑定到右值（rvalue）** 的引用，用 `&&` 表示。

    ```cpp
    int&& rref = 42;          // ✅ 右值引用绑定右值
    int x = 10;
    int&& rref2 = std::move(x);  // ✅ 使用 std::move 转为右值
    
    int&& bad = x;            // ❌ 错误：不能直接绑定左值
    ```



### 指针常量和常量指针的区别

`const` 默认修饰左侧的内容，如果左侧无内容，则修饰右侧的内容

```cpp
int const* ptr;  // const 修饰 int --> 指向常量整型的指针 --> 指针可以变, 指向的内容不可以变
const int* ptr;  // const 修饰 int --> 指向常量整型的指针 --> 指针可以变, 指向的内容不可以变
int* const ptr;  // const 修饰 * --> 指向整型的常量指针 --> 指针不可以变, 指向的内容可以变
const int* const ptr;  // 第一个 const 修饰 int, 第二个 const 修饰 * --> 指向常量整型的常量指针 --> 指针和指向的内容都不可以变
```

[[C/C++] const int* 与 int const* 的区别](https://blog.csdn.net/tengqi200/article/details/115441616)



### C++ 中的原子变量

C++ 中 `std::atomic` 用于实现原子操作，是 C++11 中引入的新特性。

多个线程可以对同一个变量进行读写操作，不会导致数据竞争或中间状态，也不需要锁的保护，一定程度上简化了代码编写，性能也会有提高。

1）什么是原子操作：

2）如何使用 `std::atomic`：

3）底层实现：`std::atomic` 通过 CPU 提供的原子指令来实现这些不可分割的操作。现代 CPU 会提供一组指令，比如 CMPXCHG, XADD 等来实现原子的读或写。

4）内存序约束：C++ 提供了多种内存序约束，比如 `memory_order_relaxed`, `memory_order_acquire`, `memory_order_release` 等。这些约束让你可以更好地控制程序的内存可见性和行为。
例如，`memory_order_relaxed` 只保证原子性，但不提供任何同步或顺序保证，而 `memory_order_acquire` 和 `memory_order_release` 则提供更严格的同步机制。
atomic 默认使用的是 `memory_order_seq_cst`，也就是最严格的内存序约束，既保证原子性，又提供了同步顺序保证。详见 cppreference。

5）和锁比较：虽然 `std::atomic` 可以在某些场景下替代锁，但它并不是万能的。锁在某些复杂场景下仍然是不可替代的。原子操作更适合一些基本的计数器或标志位，而对于复杂的数据结构，锁的使用仍是较优选择。

6）性能：使用原子操作通常比使用锁要快，因为锁涉及到上下文切换和操作系统调度，而原子操作都是硬件级别的操作。经过优化的原子操作可以使得你的程序在多线程环境下有更好的性能表现。



### 什么是三大范式?

C++ 中的三大编程范式是：

#### 1. 面向过程编程（Procedural Programming）



这是最古老、最基本的范式。它将程序看作一系列的函数调用。

-   **核心思想**：通过调用函数来处理数据。数据和操作数据的函数是分离的。
-   **特点**：
    -   **以过程为中心**：程序由一系列步骤或函数组成，这些函数按照顺序执行。
    -   **自顶向下**：通常采用自顶向下的设计，将大问题分解为若干小问题，每个小问题都由一个函数来解决。
    -   **应用场景**：适合于逻辑简单、数据结构不复杂的项目，如早期的C语言程序。



#### 2. 面向对象编程（Object-Oriented Programming, OOP）

这是 C++ 最核心的范式。它将数据和操作数据的方法封装在一起，形成一个“**对象**”。

-   **核心思想**：将现实世界中的事物抽象为类和对象，并通过它们来组织和构建程序。
-   **三大支柱**：
    -   **封装（Encapsulation）**：将数据（成员变量）和操作数据的代码（成员函数）捆绑成一个类，并通过访问修饰符（`public`, `private`, `protected`）控制对数据的访问，从而隐藏实现细节。
    -   **继承（Inheritance）**：允许一个类（子类）继承另一个类（父类）的属性和行为，实现代码复用和扩展。
    -   **多态（Polymorphism）**：允许使用同一个接口（函数名）来表示不同的行为，这通常通过虚函数和父类指针实现。



#### 3. 泛型编程（Generic Programming）

泛型编程是一种以独立于任何特定类型的方式来编写代码的编程范式。

-   **核心思想**：编写能够处理多种数据类型的通用代码，而无需为每种类型重复编写。
-   **实现方式**：在 C++ 中，**模板（Templates）\**是实现泛型编程的主要工具，包括\**函数模板**和**类模板**。
-   **特点**：
    -   **代码复用**：极大地提高了代码的复用性，避免了为不同数据类型编写重复的代码。
    -   **类型安全**：与 `void*` 这种方式不同，模板在编译时进行类型检查，确保了类型安全。
    -   **性能**：模板在编译时生成特定类型的代码，避免了运行时的开销，性能接近于手写的特定类型代码。



#### 总结

这三大范式在 C++ 中并非相互排斥，而是可以相互结合的。

-   你可以使用**面向对象**的方法来组织程序结构。
-   在对象内部，你仍然可以使用**面向过程**的函数来执行具体的任务。
-   同时，你可以利用**泛型编程**来编写通用、高效的容器（如 `std::vector`）和算法（如 `std::sort`），让它们能够处理任何数据类型。

这种混合范式的支持使得 C++ 成为一种强大而灵活的语言。



### 匿名函数的本质是什么？他的优点是什么？

匿名函数**本质**上是一个对象，在其定义的过程中会创建出一个栈对象，内部通过重载 `()` 符号实现函数调用的外表。

**优点**：使用匿名函数，可以免去函数的声明和定义。这样匿名函数仅在调用函数的时候才会创建函数对象，而调用结束后立即释放，所以匿名函数比非匿名函数更节省空间。



### C++ 面向对象的三大特性

在 C++ 面向对象的程序设计方法中，面向对象的三大特性：

1.   封装：将具体实现过程和数据封装成一个类，只能通过接口进行访问，降低耦合性，使类成为一个具有内部数据的自我隐藏能力、功能独立的软件模块。意义：保护或防止代码在无意之中被破坏，保护类中的成员，不让类中以外的程序直接访问或者修改，只能通过提供的公共接口访问。
2.   继承：子类继承父类的特征和行为，复用了基类的**全体数据**和**成员函数**，具有从基类复制而来的**数据成员**和**成员函数**（基类私有成员可被继承，但是无法被访问），其中**构造函数、析构函数、友元函数、静态数据成员、静态成员函数**都不能被继承。基类中成员的访问方式只能决定派生类能否访问它们。增强了代码耦合性，当父类中的成员变量或者类本身被 `final` 关键字修饰时，修饰的类不能被继承，修饰的成员函数不能重写或修改。意义：基类的程序代码可以被派生类服用，提高了软件复用的效率，缩短了软件开发的周期。
3.   多态：不同继承类的对象对同一消息做出不同的响应，基类的指针指向或绑定到派生类的对象，使得基类指针呈现不同的表现形式。意义：对已存在的代码具有可替代性，对代码具有可扩充性，新增子类不会影响已存在类的各种性质，在程序中体现了灵活多样的操作，提高了使用效率，简化了对应用代码的编写和修改过程。

#### 举个例子

使用动物叫声的例子来解释，能够很好地将抽象概念具象化。

**1、封装**

我们可以创建一个 `Animal` 基类。这个类把动物的**属性**（比如名字、种类）和**行为**（比如叫声 `makeSound()`）封装在一起。

```cpp
class Animal {
protected:
    std::string name;  // 数据
    
public:
    // 设置数据的方法
    void setName(const std::string& n) {
        name = n;
    }
    
    // 获取数据的方法
    std::string getName() const {
        return name;
    }
    
    // 行为，具体叫声由子类实现
    virtual void makeSound() = 0;
};
```

在这里，`name` 属性被声明为 `protected`，这意味着外部代码无法直接访问它。你必须通过 `public` 的 `setName()` 和 `getName()` 方法来间接操作它。这就是**封装**，它保护了数据的完整性，并隐藏了内部实现。

**2、继承**

**继承**允许我们创建一个新类（子类），它可以使用一个已有类（父类）的属性和方法。这促进了代码的**复用**，并且可以很好地表达现实世界中的“is-a”（是一个）关系，比如“狗是一种动物”。

我们可以创建 `Dog`, `Cat`, `Bird` 这三个子类，它们都**继承**自 `Animal` 基类。它们自动获得了 `Animal` 的所有属性和方法，比如 `name`。

```cpp
class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "The dog " << name << " barks!\n";
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "The cat " << name << "meows!\n";
    }
};

class Bird : public Animal {
public:
    void makeSound() override {
        std::cout << "The bird " << name << " chirps!\n";
    }
};
```

在这里，`Dog` 继承了 `Animal`，它也具有 `name` 属性，并且通过重写 `makeSound()` 方法来定义自己独特的行为。

**3、多态**

**多态**是指在运行时，我们可以使用同一个接口（父类指针或引用）来调用不同子类的同名方法，并表现出不同的行为。这使得代码更具**灵活性**和**可扩展性**。

我们可以创建一个 `Animal` 类型的指针，它能够指向任何继承自 `Animal` 的子类对象。当我们通过这个指针调用 `makeSound()` 方法时，程序会根据实际指向的对象类型，调用正确的 `makeSound()` 实现。

```cpp
int main() {
    Dog dog;
    dog.setName("Buddy");

    Cat cat;
    cat.setName("Whiskers");

    Bird bird;
    bird.setName("Tweety");

    // 使用 Animal 基类指针
    Animal* my_animal_1 = &dog;
    Animal* my_animal_2 = &cat;
    Animal* my_animal_3 = &bird;

    // 同一个接口，不同的行为
    my_animal_1->makeSound(); // 输出：The dog Buddy barks!
    my_animal_2->makeSound(); // 输出：The cat Whiskers meows!
    my_animal_3->makeSound(); // 输出：The bird Tweety chirps!
}
```





## 头文件

[米哈游C++一面：头文件相关的面试题、如何解决头文件循环包含的问题？](https://www.bilibili.com/video/BV1SvPueyEjG?spm_id_from=333.1245.0.0)

总结：

*   循环依赖 $\to$ 前置声明
*   依赖扩散 $\to$ Pimpl 惯用法
*   重复包含 $\to$ #pragma once 或 头文件保护宏



### 如果在头文件创建一个函数但在源文件中没有实现它会有bug吗？

头文件通常包含函数的声明，而源文件包含具体的实现。

>   编译阶段：
>
>   检查函数调用是否正确，是否有声明，如果有声明，编译器认为干函数在其他地方定义了，不会报错。
>
>   链接阶段：
>
>   把所有目标文件合并成一个可执行程序，如果在所有目标文件中都没有找到实现，此时链接器就会报错（未定义的引用）。

1.   函数没有使用
     编译和链接都没有问题
2.   函数使用了
     编译没问题，链接会报错
     如果该函数声明为 **inline**，编译期就会报错
     如果该函数是**模板函数**（需要在头文件声明和定义），编译器需要在编译期进行模板实例化（根据模板参数生成具体代码），编译期就会报错。



### 如何解决头文件循环包含的问题？

问题描述：`A.h` 和 `B.h` 互相包含，导致编译错误：

```cpp
// A.h
#include "B.h"
class A {
    B* b;
};

// B.h
#include "A.h"
class B {
    A* a;
};
```

解决方案：前置声明的方式：

当类/结构体仅被用作指针或引用时，无需包含完整定义，用前置声明替代头文件包含。在源文件（.cpp）中再包含具体头文件：

```cpp
// A.h
class B;  // 前置声明代替 #include "B.h"
class A {
    B* b;  // 仅需 B 的声明
};

// B.h
class A;  // 前置声明代替 #include "A.h"
class B {
    A* a;  // 仅需 A 的声明
};

// C.cpp
#include "A.h"
#include "B.h"
...
```



### 如何解决头文件依赖扩散的问题？

**什么是依赖扩散？**

所有包含 `A.h` 的文件都会间接包含 `B.h`

```cpp
// A.h
#ifndef A_H
#define A_H
#include "B.h"
class A {
private:
    B b;
};
#endif
```



**什么是 Pimpl（指向实现的指针）？**

将类的私有实现细节隐藏到源文件中，减少头文件依赖。

```cpp
// A.h
#ifndef A_H
#define A_H
class A {
private:
    struct Impl;  // 前置声明实现类
    Impl* impl;
};
#endif

// A.cpp
#include "A.h"
#include "B.h"
struct A::Impl{
    B b;  // 实现细节隐藏在源文件中
};
```



### 如何解决头文件重复包含的问题？

想要解决 C/CPP 中头文件重复包含的问题，有两种方式：

1.   在头文件的第一行使用预处理指令 **`#pragma once`**，`#pragma once` 是一个**非标准**的但广泛支持的预处理指令，它告诉编译器该头文件在单个编译过程中只应被包含一次。编译器在第一次遇到 `#pragma once` 时会记住该文件名，并在后续的包含操作中忽略它。

2.   使用预处理指令 **`#ifndef`**、**`#define`** 和 **`#endif`** 保护头文件：
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



## 进程和线程

### 进城和线程的区别

```arduino
┌──────────────────────────┐ 高地址
│  内核空间 (仅内核访问)      │
├──────────────────────────┤
│  栈区 (Stack)             │ ← 每个线程独立分配
├──────────────────────────┤
│  堆区 (Heap)              │ ← 进程所有线程共享
├──────────────────────────┤
│  全局/静态区 (.data/.bss)  │ ← 进程共享
├──────────────────────────┤
│  代码段 (.text)           │ ← 进程共享，只读
└──────────────────────────┘ 低地址
```

**堆与线程的关系**

-   堆是进程级资源
    由进程向操作系统申请（如 `brk`/`mmap`），存放动态分配的内存（`malloc` / `new`）。
    所有线程都在同一个进程中运行，因此它们访问的是**同一块堆**。
-   线程共享堆的意义
    多个线程可以访问同一份动态分配的数据，实现数据共享。
    这也是为什么多线程访问堆上的数据时，需要**同步机制**（`mutex`、`spinlock` 等）来避免数据竞争。

**栈与线程的关系**

-   每个线程有**自己独立的栈空间**（stack），用来存放局部变量、函数调用信息等。
-   主线程的栈是在进程创建时分配的，子线程的栈由 `pthread_create` 等函数调用时分配（默认大小一般是 8MB，可修改）。

**结论**

*   同一进程中，不同线程共享堆，共享全局区，独立栈。
*   堆上数据需要多线程同步，栈上数据天然线程安全（不共享）。



### 进程之间的通信方式有哪些？

**管道（Pipe）**：管道（匿名管道），管道本质上是一个内核中的一个缓存，当进程创建管道后会返回两个文件描述符，一个写入端一个输出端。<mark>单向通信</mark>，<mark>父子进程</mark>。缺点：半双工通信，一个管道只能一个进程写，一个进程读。

**命名管道（FIFO）**：

**消息队列（Message Queue）**：可以边发边收，但是每个消息体都有最大长度限制，队列所包含的消息体的总数量也有上限并且在通信过程中存在用户态和内核态之间的数据拷贝问题。适合需要多进程之间进行信息传递的场景。

**共享内存（Shared Memory）**：是最高效的数据传输方式，但需要额外的同步机制来避免数据竞争。 

**信号量（Signal）**：本质上是一个计数器，当使用共享内存的通信方式时，如果有多个进程同时往共享内存中写入数据，有可能先写的进程的内容被其他进程覆盖了，信号量就用于实现进程间的互斥和同步PV操作不限于信号量+-1，而且可以任意加减正整数

**套接字（Socket）**：是最灵活的通信方式，支持本地和远程通信，但效率较低，特别是在远程通信场景中。

**文件（File）**：



### 线程之间的通信方式有哪些？

**互斥锁（Mutex）**：确保同一时间只有一个线程访问共享资源。

**条件变量（Condition Variable）**：让线程等待特定条件的满足。

**读写锁（Read-Write Lock）**：支持多个线程同时读取数据，但只允许一个线程写入数据。

**自旋锁（Spinlock）**：用于等待时间短的场景，通过忙等待方式获取锁。

**信号量（Semaphore）**：控制线程对多个资源的访问。

**原子操作（Atomic Operation）**：轻量级的同步方式，适用于简单的共享数据访问。



### 多线程为什么会发生死锁，死锁是什么？死锁产生的条件，如何解决死锁？

因为在多进程中易发生**资源竞争**，如果一个进程集合里面的每一个进程都在等待这个集合中的其他一个进程才能继续往下执行，若无外力他们将无法推进，这种情况就是死锁。

产生死锁的四个条件：

1.   **互斥条件**
2.   **请求和保持条件**
3.   **不可剥夺条件**
4.   **循环等待条件**

解决死锁的方法就是破坏上述任意一种条件。



### 串行、并行、并发、异步、同步

C++中 串行、并行、并发、同步、异步的区别

[任务执行模式全解析：并发、并行、串行与同步、异步的对比](https://blog.csdn.net/qq_42399932/article/details/144949891)

[深入浅出理解同步 /异步/并发/并行/串行](https://www.cnblogs.com/Archer-Fang/p/8962156.html)



## 并行编程

详见：[并行编程](../CPP/并行编程.md)



### 原子操作



### 内存序

详见：[内存序](../CPP/并行编程.md#_8)



### 互斥锁



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



### 条件变量



### 信号量



### 异步任务



### 协程



## 智能指针

### 既然C++中已经有了指针，为什么要引入智能指针？

传统 C++ 指针（裸指针，如 `int* p = new int;`）在管理动态分配的内存时，存在一系列严重的问题，而智能指针的出现就是为了从根本上解决这些问题。

智能指针（如 `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`）是**封装了裸指针的对象**，它们能够**自动**管理内存的生命周期。

下面是智能指针解决了裸指针的哪些痛点：

1.   内存泄漏（Memory Leaks）。如果你使用 `new` 分配了内存，那么你必须在所有可能的执行路径上都确保调用 `delete` 来释放它。如果忘记释放内存，就会导致**内存泄漏**。</br>
     智能指针利用了 C++ 的**RAII（Resource Acquisition Is Initialization）机制。当智能指针对象超出作用域时，它的析构函数**会自动被调用，而在析构函数中，它会安全地调用 `delete` 来释放所管理的内存。

2.   野指针和悬空指针（Dangling Pointers）。当一个指针所指向的内存被释放后，这个指针本身并不会自动变为 `nullptr`。它就变成了**悬空指针**，再次访问它会导致未定义行为。</br>

     **智能指针的解决方案：**

     1.   `std::unique_ptr` 保证**独占所有权**，避免了多个指针共享同一块内存的问题。当它超出作用域时，内存被释放，其他任何拷贝或移动后的指针都会失效。
     2.   `std::shared_ptr` 通过**引用计数**机制来管理内存。只有当最后一个 `shared_ptr` 离开作用域时，内存才会被释放。这从根本上避免了在多个所有者的情况下，其中一个所有者意外释放内存导致其他所有者变成悬空指针的问题。

3.   多所有权场景的复杂性。当一块内存需要被多个地方共享时，裸指针无法明确地表达所有权关系。你很难判断什么时候应该 `delete` 内存，以及哪个 `delete` 是“合法”的。这在多线程环境下尤其危险。</br>
     `std::shared_ptr` 通过**引用计数**完美地解决了这个问题。每次拷贝 `shared_ptr`，引用计数加一；每次 `shared_ptr` 离开作用域，引用计数减一。只有当引用计数归零时，内存才会被释放。这让多所有权场景下的内存管理变得清晰、安全且自动。

总之，智能指针的引入，是将 C++ 的内存管理从**手动管理**升级为**自动管理**。它通过封装、RAII 和引用计数等机制，解决了裸指针在**内存泄漏、悬空指针和多所有权管理**等方面的痛点，极大地提高了代码的健壮性、安全性和可维护性。



### 智能指针的本质是什么？它们的实现原理是什么？

智能指针本质是一个封装了一个原始C++指针的类模板，为了确保动态内存的安全性而产生的。实现原理是通过一个对象存储需要被自动释放的资源，然后依靠对象的析构函数来释放资源。

其实现原理主要依赖于：

1.   **RAII 范式**：构造函数中获取资源，析构函数中释放资源，当智能指针对象离开作用域的时候，析构函数会自动释放它所持有的原始指针。详见：[RAII](../CPP/CPP 基础.md#raii)
2.   **运算符重载**：重载 `*` 和 `->` 运算符，使其使用起来和普通指针一样。
3.   **引用计数** (`std::shared_ptr`场景)：
     *   通过一个**额外的计数器**记录当前有多少个 `shared_ptr` 指向同一块内存。
     *   当引用计数减为 0 时，自动释放资源。
4.   **移动语义**：`std::unique_ptr` 通过禁止拷贝构造和拷贝赋值，保证"唯一所有权"，但是其支持移动构造和移动赋值，转移所有权而不拷贝资源。

**智能指针的类型**：

1.   `unique_ptr`：独占所有权，不能复制
2.   `shared_ptr`：共享所有权，引用计数
3.   `weak_ptr`：弱引用，不能增加计数

:warning: `shared_ptr` 中可能出现循环引用问题，通过 `weak_ptr` 去解决。如何解决的？



### `unique_ptr`



### `shared_ptr`



### `weak_ptr`

`weak_ptr` 不会导致它所指向的**对象**被释放。`weak_ptr` 的作用就像一个“观察者”，它不拥有对象的所有权，因此它的存在**不会**影响对象的生命周期。它只是提供了一种安全访问对象的方式，同时避免了**循环引用**（Circular References）问题。



### 如何在一个派生类中定义一个父类的指针？



### 如何在类的内部返回一个指向自己的智能指针？



### 智能指针的线程安全性

>   [当我们谈论shared_ptr的线程安全性时，我们在谈论什么](https://zhuanlan.zhihu.com/p/416289479)

`shared_ptr` 是线程安全的吗？

首先，`shared_ptr` 是用于解决所有权(ownership)的，其本身并不负责线程安全。

*   `shared_ptr` 的引用计数是线程安全的。具体来说，对同一个 `shared_ptr` 对象的多个线程同时进行引用计数增减是安全的。因为 `shared_ptr` 内部的引用计数器和弱引用计数器的增减操作采用了原子操作。
*   但对象本身的访问需要额外的同步机制。

    *   **对同一个 `shared_ptr` 对象的多个线程同时进行读写是不安全的。** 例如，一个线程在对一个 `shared_ptr` 对象赋值，而另一个线程同时在读取它，这会导致数据竞争（Data Race），行为是未定义的。

        ```cpp
        std::shared_ptr<int> ptr1(new int(10));
        std::shared_ptr<int> ptr2(new int(20));
        
        // 线程A
        ptr1 = ptr2; // 写操作
        
        // 线程B
        auto val = *ptr1; // 读操作，可能在线程A赋值前后发生，导致不确定性
        ```

    *   **通过多个 `shared_ptr` 访问同一个原始数据，对数据的操作不是线程安全的。** `shared_ptr` 只是一个智能指针，它管理的是对象的生命周期。它不提供对**所指向的数据**的线程安全保证。如果你通过多个 `shared_ptr` 访问同一个数据，并且至少有一个线程要修改这个数据，你需要自己提供同步机制（比如使用互斥锁 `std::mutex`）。

        ```cpp
        auto data_ptr = std::make_shared<int>(10);
        
        // 线程A
        *data_ptr = 20; // 写操作
        
        // 线程B
        int val = *data_ptr; // 读操作，没有同步，导致不确定性
        ```


C++ 20 中新增了 `std::atomic<std::shared_ptr<T>>` 和 `std::atomic<std::weak_ptr<T>>` 来解决线程安全的问题。

### 在构建智能指针的时候 `new` 和 `make_shared` 的区别是什么？

```cpp
std::shared_ptr<int> a(new int);
std::shared_ptr<int> b = std::make_shared<int>();
```

1.   **内存分配和性能**

     这是两者最核心的区别。

     -   **`new` 的内存分配**： `new MyClass()` 和 `shared_ptr` 的构造函数是**两次独立的内存分配**。
         1.  第一次：`new MyClass()` 在堆上为 `MyClass` **对象**本身分配内存。
         2.  第二次：`shared_ptr` 的构造函数在堆上为**控制块（Control Block）分配内存。控制块包含引用计数、弱引用计数等信息。 两次独立的内存分配会增加开销，可能导致缓存未命中**，从而降低性能。
     -   **`std::make_shared` 的内存分配**： `std::make_shared` 在底层只进行**一次内存分配**。 它会一次性分配一块足够大的内存，同时容纳**对象本身**和**控制块**。 这种方式更高效，因为它：
         1.  **减少了内存分配的次数**，降低了系统调用的开销。
         2.  **提高了内存局部性**，因为对象和控制块在内存中是连续的，这有助于 CPU 缓存的命中，提升程序性能。

2.   **异常安全性**

     `std::make_shared` 在某些复杂表达式中提供了更好的**异常安全性**。</br>

     考虑以下场景：
     ```cpp
     // 可能存在异常安全问题
     f(std::shared_ptr<T>(new T()), g());
     ```

     在这个表达式中，`new T()`、`shared_ptr` 构造函数和 `g()` 的调用顺序是不确定的。如果 `new T()` 分配了内存，但 `g()` 在 `shared_ptr` 构造函数调用前抛出异常，那么 `new` 分配的内存将**永远不会被释放**，导致内存泄漏。</br>
     而 `std::make_shared` 将整个创建过程封装在一个原子操作中，避免了这个问题。`std::make_shared` 要么完全成功，要么在失败时不会留下任何内存泄漏。



## C++ 关键字

### `sizeof()`

sizeof(虚函数类) >= 8 字节 (64 位操作系统)，因为有虚函数的类，在编译阶段，编译器会为其生成一个 **虚函数表指针(vptr)**，在 64 位操作系统中，一个指针的大小为 8 字节，在 32 位操作系统中，一个指针的大小为 4 字节。

sizeof(空类) = 1 字节，在 C++ 中，**空类也必须有非零大小**，否则两个不同的对象就可能有相同的地址，破坏对象模型。标准规定：**空类的大小至少为 1 字节**。



### `const` v.s. `#define`

const 定义的是常量，有数据类型，而 define 是 预处理器指令，替换文本，没有数据类型。





### `const` v.s. `constexpr`



### `inline`

内联函数（inline function）是通过在函数定义前加上关键字 inline 来建议编译器将函数代码直接插入到每个调用它的地方，而不是通过函数调用机制。这样可以减少函数调用时的开销。内联函数通常用于那些频繁调用、代码短小的函数。



#### `inline` 的作用是什么

#### `inline` 是怎么加快函数运行效率



### class 和 struct 的区别

在 C++ 中，`struct` 和 `class` 都用于定义自定义数据类型，它们的核心功能几乎相同，主要区别在于**默认访问权限**和**默认继承方式**。

class默认继承的是private继承，struct默认是public继承。

1.   默认访问权限不同：

     ```cpp
     // struct 默认所有成员为 public
     struct Point {
         int x;     // 默认为 public
         int y;     // 默认为 public
     };
     
     // class 默认所有成员为 private
     class Circle {
         double r;  // 默认为 private
     public:
         double area() { return 3.14 * r * r; }
     };
     ```

2.   默认继承方式不同：

     ```cpp
     struct Base { int data; };
     
     // struct 继承默认为 public
     struct DerivedStruct : Base { 
         // 可直接访问 Base::data (public)
     };
     
     class DerivedClass : Base { 
         // 默认为 private 继承，Base::data 不可直接访问
     };
     ```



class 还可用于**定义模板参数**，但是关键字 struct 不能同于定义模板参数，C++ 保留 struct 关键字，原因是保证与 C 语言的向下兼容性，为了保证百分百的与 C 语言中的 struct 向下兼容，，C++ 把最基本的对象单元规定为 class 而不是 struct，就是为了避免各种兼容性的限制。



### 成员访问控制

### 继承方式

`private`、`protected` 和 `public` 这三个关键字在继承中扮演着双重角色：

1.  **成员访问控制**：定义类成员对**类外部**的可见性。
2.  **继承方式**：定义基类的成员在派生类中的**访问权限**。



`public` 继承

`protected` 继承

`private` 继承

```cpp
class Base {
public:
    int public_mem;
protected:
    int protected_mem;
private:
    int private_mem;
};

// public 继承
class PublicDerived : public Base {
public:
    void test() {
        public_mem = 1;      // OK, public_mem is public
        protected_mem = 1;   // OK, protected_mem is protected
        // private_mem = 1;  // ERROR, private_mem is private
    }
};

void testPublic() {
    PublicDerived d;
    d.public_mem = 1;      // OK, public_mem is public
    // d.protected_mem = 1; // ERROR, protected_mem is protected
}

// protected 继承
class ProtectedDerived : protected Base {
public:
    void test() {
        public_mem = 1;      // OK, public_mem becomes protected
        protected_mem = 1;   // OK, protected_mem remains protected
    }
};

void testProtected() {
    ProtectedDerived d;
    // d.public_mem = 1;    // ERROR, public_mem becomes protected
}

// private 继承
class PrivateDerived : private Base {
public:
    void test() {
        public_mem = 1;      // OK, public_mem becomes private
        protected_mem = 1;   // OK, protected_mem becomes private
    }
};

void testPrivate() {
    PrivateDerived d;
    // d.public_mem = 1;    // ERROR, public_mem becomes private
}
```





#### 内联函数的限制

*   函数体不能太大
*   不能有递归调用
*   不能有循环语句
*   编译器可能拒绝内联



### `static`

在 C++ 中，`static` 关键字是一个非常重要的修饰符，它影响着变量的**生命周期**、**作用域**和**链接性**。

**局部变量、全局变量和静态变量的区别**

要理解 `static` 关键字，最好的方法是将其与普通变量进行对比。下面是不同类型变量的详细区别：

**1 局部变量 (Local Variable)**

  * **定义：** 在函数内部定义的变量。
  * **生命周期：** 从定义时开始，到函数执行结束时销毁。每次函数被调用时，都会重新创建该变量。
  * **作用域：** 仅限于定义它的函数内部。在函数外部无法访问。
  * **存储位置：** 通常存储在**栈 (Stack)** 上。

示例：

```cpp
void myFunction() {
    int normal_local_var = 10; // 局部变量
    // ...
}
```

每次调用 `myFunction`，`normal_local_var` 都会被重新初始化为 10。

**2 全局变量 (Global Variable)**

  * **定义：** 在所有函数外部定义的变量。
  * **生命周期：** 程序开始运行时创建，程序结束时销毁。
  * **作用域：** 整个程序。可以在任何文件中、任何函数中访问。
  * **存储位置：** 存储在**静态存储区 (Static/Global Data Segment)**。
  * **链接性：** 具有外部链接性 (external linkage)，意味着可以在其他源文件中通过 `extern` 关键字访问。

示例：

```cpp
int global_var = 20; // 全局变量

void anotherFunction() {
    // 可以在这里访问 global_var
}
```

**3 静态局部变量 (Static Local Variable)**

  * **定义：** 在函数内部，用 `static` 关键字修饰的局部变量。
  * **生命周期：** 程序开始运行时创建，程序结束时销毁。**只会初始化一次**。
  * **作用域：** 仅限于定义它的函数内部。与普通局部变量相同。
  * **存储位置：** 存储在**静态存储区**。
  * **用途：** 保持函数调用之间的状态。

示例：

```cpp
void counter() {
    static int count = 0; // 静态局部变量
    count++;
    std::cout << "Count is: " << count << std::endl;
}

int main() {
    counter(); // 输出: Count is: 1
    counter(); // 输出: Count is: 2
    counter(); // 输出: Count is: 3
    return 0;
}
```

虽然 `count` 定义在 `counter` 函数内，但它只在第一次调用时初始化为 0。随后的每次调用都会沿用上一次的值，因为它没有被销毁。

4 静态全局变量 (Static Global Variable)

  * **定义：** 在所有函数外部，用 `static` 关键字修饰的全局变量。
  * **生命周期：** 程序开始运行时创建，程序结束时销毁。与普通全局变量相同。
  * **作用域：** 仅限于定义它的文件内部。
  * **存储位置：** 存储在**静态存储区**。
  * **链接性：** 具有内部链接性 (internal linkage)，这意味着它**只能在当前文件中访问**。其他文件无法通过 `extern` 访问它，即使它们有相同的变量名。

示例：

file1.cpp:

```cpp
static int static_global_var = 50; // 静态全局变量
void printVar() {
    std::cout << "Value from file1: " << static_global_var << std::endl;
}
```

file2.cpp:

```cpp
#include <iostream>

// 无法访问 file1.cpp 中的 static_global_var
// extern int static_global_var; // 编译会出错
void anotherPrint() {
    // 无法在这里访问 static_global_var
}
```

静态全局变量的目的是为了**限制全局变量的作用域**，避免命名冲突，并确保变量只在定义它的文件内使用。

**总结表格**

| 类型             | 作用域   | 生命周期         | 存储位置   | 链接性   |
| :--------------- | :------- | :--------------- | :--------- | :------- |
| **局部变量**     | 函数内部 | 函数执行期间     | 栈 (Stack) | 无       |
| **全局变量**     | 整个程序 | 整个程序执行期间 | 静态存储区 | 外部链接 |
| **静态局部变量** | 函数内部 | 整个程序执行期间 | 静态存储区 | 无       |
| **静态全局变量** | 当前文件 | 整个程序执行期间 | 静态存储区 | 内部链接 |

总的来说，`static` 关键字主要有两个核心作用：

1.  **改变生命周期：** 将局部变量的生命周期从函数调用期间延长到整个程序执行期间。
2.  **改变链接性：** 将全局变量的外部链接性改为内部链接性，从而限制其作用域在当前文件内部。



### `volatile`



### `extern`

#### C++程序中调用被C编译器编译后的函数，为什么要加extern“C”？如果不加，会有什么影响？

考点：名称修饰（Name Mangling）

**为什么需要 `extern "C"`？**

核心原因是C++和C语言在处理函数名的方式上有所不同：

1.  **C++的函数名修饰**：C++为了支持函数**重载**和**模板**等高级特性，在编译时会对函数名进行**名称修饰**。这个过程会将函数名、参数类型、命名空间等信息编码进一个唯一的符号名。例如，一个C++函数 `void func(int)` 可能会被编译成 `_Z4funci` 这样的符号。
2.  **C语言的函数名处理**：C语言不支持函数重载，所以它不需要名称修饰。C编译器通常直接使用函数名作为符号，或者简单地在函数名前加一个下划线，例如 `_func`。

当C++程序调用一个C语言函数时，C++编译器会误以为这是一个C++函数，并对其进行名称修饰。但是，链接器在C语言编译的库中只能找到未修饰的函数名。这样一来，链接器就无法找到对应的函数，导致链接失败。

**`extern "C"`** 的作用，就是告诉C++编译器：“请对后面声明的函数，不要进行名称修饰，按照C语言的方式来处理。” 这样，C++编译器就会生成正确的、未修饰的函数符号，从而能与C语言库中的函数成功链接。

**如果不加 `extern "C"`，会有什么影响？**

如果不加 `extern "C"`，最直接的影响就是编译和链接阶段会出现**链接错误（Linker Error）**。

具体表现为，链接器会报告 **"undefined reference"**（未定义的引用）错误。这个错误意味着链接器找不到你所调用的函数。它在库中寻找的是一个C++修饰过的函数名（比如 `_Z4funci`），但实际上库里存在的只是一个C语言风格的函数名（比如 `_func`），两者不匹配，链接自然就会失败。

**总结**

`extern "C"` 就像是一个“翻译官”，它负责解决C++和C两种不同语言编译器之间的“沟通障碍”。它保证了C++代码能够正确地找到C语言编译的函数，是实现**C++与C代码混合编程**的关键。

如果面试官追问，你可以进一步举例说明：

-   **头文件**：在C++中包含C语言头文件时，通常会在头文件开头和结尾加上 `extern "C"` 块，以确保其中的函数声明被正确处理。

-   **宏定义**：为了兼容C和C++，很多C库的头文件会用宏来自动适应，比如：

    ```cpp
    #ifdef __cplusplus
    extern "C" {
    #endif
    
    void c_function();
    
    #ifdef __cplusplus
    }
    #endif
    ```



### `friend`

#### 1. `friend` 关键字的作用

-   在 C++ 中，**类的成员有访问权限控制**：
    -   `public`：对所有代码可见
    -   `protected`：仅对子类和友元可见
    -   `private`：仅类本身成员可见
-   有时候我们希望**某个函数或类能够直接访问另一个类的私有成员**，而不必通过公开接口。
     这时候就可以用 **`friend`** 关键字来声明**友元关系**。

**简单理解**：
 👉 `friend` 让一个外部函数或者类 **跳过访问限制**，直接访问你的类的私有/保护成员。

#### 2. 友元函数（Friend Function）

-   **定义**：在类中用 `friend` 声明的函数，就成为该类的“友元函数”。
-   **作用**：友元函数可以访问该类的 `private` 和 `protected` 成员。

示例：

```cpp
#include <iostream>
using namespace std;

class Box {
private:
    int length;

public:
    Box(int l) : length(l) {}

    // 声明友元函数
    friend void printLength(Box b);
};

// 友元函数的实现（不是类的成员函数）
void printLength(Box b) {
    cout << "Box length: " << b.length << endl; // 直接访问私有成员
}

int main() {
    Box b(10);
    printLength(b); // 输出：Box length: 10
    return 0;
}
```

👉 `printLength` 不是 `Box` 的成员函数，但由于被声明为 `friend`，所以可以访问 `Box::length`。

#### 3. 友元类（Friend Class）

-   **定义**：如果一个类被声明为另一个类的友元类，那么该类的所有成员函数都可以访问对方类的 `private` 和 `protected` 成员。
-   **作用**：友元类通常用在**紧密关联**的类之间，例如容器类与迭代器类。

示例：

```cpp
#include <iostream>
using namespace std;

class Engine; // 提前声明

class Car {
private:
    int horsepower;

public:
    Car(int hp) : horsepower(hp) {}

    // 声明 Engine 是 Car 的友元类
    friend class Engine;
};

class Engine {
public:
    void showCarPower(Car& c) {
        // Engine 类可以直接访问 Car 的私有成员
        cout << "Car horsepower: " << c.horsepower << endl;
    }
};

int main() {
    Car car(300);
    Engine engine;
    engine.showCarPower(car); // 输出：Car horsepower: 300
    return 0;
}
```

#### 4. 友元的特点与注意事项

1.  **友元关系是单向的，不对称**
    -   如果 `A` 是 `B` 的友元，`B` 不一定是 `A` 的友元。
2.  **友元关系不会被继承**
    -   父类的友元不自动成为子类的友元。
3.  **友元破坏了封装性**
    -   使用时要谨慎，通常只在需要高效访问或类强耦合的场景下使用。

#### 总结

-   `friend` 关键字允许指定的函数或类访问当前类的私有和保护成员。
-   **友元函数**：外部函数通过 `friend` 声明获得访问权限。
-   **友元类**：另一个类整体获得访问权限。
-   友元声明可以放在 `public`, `protected`, 或 `private` 区域，它们的功能完全一样，没有任何区别。因为<mark>友元关系是一种**单向的、非对称的**关系</mark>，它独立于类的访问控制机制。
    -   **访问控制（`public`, `protected`, `private`）** 是用来控制**外部代码**如何访问类的成员的。
    -   **友元（`friend`）** 是用来授予**特定外部代码**访问私有成员的特殊权限。



## STL

### `std::array` 和 `std::vector` 的区别

`std::array` 是一个固定大小的数组，其底层实现和 C 风格数组非常相似，内存是连续的。其存储的对象一般在栈上。

`std::vector` 是一个动态数组，内存通常在堆上分配，动态扩容机制。



### `std::list`

`std::list` 是一种**双向链表**。这意味着它的元素在内存中不是连续存储的。

优势：

*   高效的插入和删除 O(1)
*   不影响迭代器：在链表中插入或删除元素时，其他元素的地址不会改变，因此已有的迭代器(除了指向被删除元素的迭代器)仍然有效。

劣势：

*   不支持随机访问 O(n)
*   额外的内存开销，每个元素都需要额外的内存来存储前后两个指针。



### `std::vector` 在删除时，是否会产生迭代器失效

迭代器在 `std::vector` 的底层实现就是一个只想其内部元素的<mark>普通指针</mark>。

`std::vector` 在使用 `erase()` 删除元素，迭代器会失效，应该始终使用 `erase()` 返回的新迭代器来继续操作。继续使用旧的迭代器，**这通常会导致未定义行为、程序崩溃或错误输出**。

此外，当 `std::vector` 触发扩容机制的时候，迭代器也会失效。



### `std::map` 和 `std::unordered_map` 的区别

|              | map                                | unordered_map                                              |
| ------------ | ---------------------------------- | ---------------------------------------------------------- |
| 底层数据结构 | 红黑树                             | 哈希表                                                     |
| 时间复杂度   | O(log n)                           | 平均O(1)，最坏情况下(所有元素都在同一个哈希桶中)退化为O(n) |
| 空间复杂度   | 相对较低                           | 相对较高，因为哈希表需要分配额外的空间来存储和处理冲突     |
| 元素顺序     | 有序，按照键排序                   | 无序                                                       |
| 适用场景     | 有序，对时空复杂度严格要求O(log n) | 不关心顺序，需要更快的插入、删除和查询操作                 |



### 对于已知大小的数据 `std::map` 和 `std::unordered_map` 哪一个更省内存？

这是一个关于 C++ 标准库容器内存开销的经典问题。对于已知大小的数据，`std::map` 和 `std::unordered_map` 哪一个更省内存，答案并不是绝对的，需要具体情况具体分析。

#### 核心区别：底层实现

要回答这个问题，首先需要理解两者的底层实现。

-   **`std::map`**：底层是**红黑树**（Red-Black Tree）。每个节点都需要存储键值对、三个指针（指向父节点、左子节点、右子节点）以及一个颜色标记。
-   **`std::unordered_map`**：底层是**哈希表**。它由一个**桶数组**（Bucket Array）组成，每个桶是一个链表。每个节点（即键值对）除了存储数据，还需要存储一个指向下一个节点的指针。

#### 内存开销分析

让我们具体比较一下它们的内存开销。假设我们要存储 N 个键值对。

**`std::map` 的内存开销**

每个节点都会有固定的额外开销，通常包括：

-   **键值对**：$size\_of(key)+size\_of(value)$
-   **节点指针**：三个指针（父、左、右），每个指针在 64 位系统上通常是 8 字节，总计 3×8=24 字节。
-   **颜色标记**：1 字节。

因此，`std::map` 的总内存开销大致为：$N×(size\_of(key)+size\_of(value)+24+1)$ 字节。

**`std::unordered_map` 的内存开销**

`unordered_map` 的内存开销由两部分组成：

1.  **桶数组**：一个指针数组，用于存放每个桶的头节点。它的默认大小通常是 8，并且会随着元素的增加而自动扩容。桶数组的大小是 $load\_factor×N$。
    -   **桶数组大小**：M
    -   **内存开销**：$M×size\_of(pointer)$
2.  **节点**：每个节点除了键值对，还需要一个指针用于连接链表。
    -   **内存开销**：$N×(size\_of(key)+size\_of(value)+8)$

因此，`std::unordered_map` 的总内存开销大致为：$M×8+N×(size\_of(key)+size\_of(value)+8)$ 字节。

#### 结论：谁更省内存？

对于**已知大小**的数据，我们通常可以通过设置 `unordered_map` 的初始桶数量，来控制其内存开销。

-   **当数据量较少或键值对较小**时：`std::map` 可能会更省内存。因为它的每个节点有固定的开销（约 25 字节），而 `unordered_map` 的桶数组会带来额外的初始开销。例如，如果你只存储 10 个键值对，`map` 的额外开销是 $10×25=250$ 字节，而 `unordered_map` 即使只用默认 8 个桶，也需要 $8×8=64$ 字节的桶数组，加上 $10×8=80$ 字节的节点指针，总计 144 字节。但随着数据量增大，`unordered_map` 桶数组的额外开销会被均摊。
-   **当数据量较大**时：`std::unordered_map` 通常会更省内存。尽管 `unordered_map` 有桶数组的开销，但它的每个节点只需要一个指针，而 `map` 需要三个。`unordered_map` 每个节点比 `map` 少了两个指针的开销，这在大量数据的情况下会非常可观（$2×8=16$ 字节）。

#### 最佳实践

如果你知道数据量，并且希望节省内存，可以进行如下操作：

1.  **对于 `std::map`**：它不需要额外的处理，内存开销相对固定。
2.  **对于 `std::unordered_map`**：你可以使用 `reserve()` 函数预先设置桶的数量，从而避免动态扩容带来的额外开销和性能抖动。

**最终的答案是：对于大量数据，`std::unordered_map` 通常更省内存；而对于少量数据，`std::map` 可能会更胜一筹。**

在面试中，如果你能这样分析，并提到底层实现和内存模型，就能展现你对 C++ 容器的深刻理解。



### `std::set` 和 `std::unordered_set` 的区别



## 内存管理

### malloc/free V.S. new/delete

### malloc 的内存分配的方式，有什么缺点？

`malloc` 和 `free` 是 C 语言中用于在堆上分配和释放内存的标准库函数。

**内存分配**

`malloc` 向操作系统请求内存，根据系统平台和库实现的不同，它可以使用 `brk()` 和 `mmap()` 两种方式来从操作系统请求内存。

-   小于 `128KB` 用 `brk()` 系统调用从堆分配内存，实现方式：将堆顶指针向高地址移动，获取内存空间，如果使用free释放空间，并不会将内存归还给操作系统，而是会缓存在malloc的内存池中，待下次使用。
-   大于 `128KB` 用 `mmap()` 系统调用在文件映射区域分配内存，实现方式：使用私有匿名映射的方式，在文件映射区分配一块内存，也就是从文件映射区拿了一块内存，free释放内存的时候，会把内存归还给操作系统，内存得到真正释放。

**缺点**：容易造成内存泄漏和过多的内存碎片，影响系统正常运行，还得注意判断内存是否分配成功，而且内存释放后（使用free函数之后指针变量p本身保存的地址并没有改变），需要将p的赋值为NULL拴住野指针。



**为什么不全用 `mmap()` 来分配内存？**

因为向操作系统申请内存的时候，是要通过系统调用的，执行系统调用要进入内核态，然后再回到用户态，状态的切换会耗费不少时间，所以申请内存的操作应该避免频繁的系统调用，如果都使用mmap来分配内存，等于每次都要执行系统调用。另外，因为mmap分配的内存每次释放的时候都会归还给操作系统，于是每次mmap分配的虚拟地址都是缺页状态，然后在第一次访问该虚拟地址的时候就会触发缺页中断。



**为什么不全用 `brk()` 来分配内存？**

如果全部使用brk申请内存那么随着程序频繁的调用malloc和free，尤其是小块内存，堆内将产生越来越多的不可用的内存碎片。



**内存管理**

`malloc` 使用一种数据结构（通常是链表或树形结构）来管理已分配和未分配的内存块。当用户请求内存时，`malloc` 首先在内存管理数据结构中查找一个合适大小的空闲内存块。如果找到合适的内存块，`malloc` 会将其从空闲列表中移除并返回给用户。如果没有找到合适的内存块，`malloc` 会向操作系统请求更多的内存。



### malloc 只分配内存，不调用构造函数？





### 什么是内存泄漏，产生的原因？



### 虚拟内存和物理内存

[腾讯C++一面：虚拟内存与物理内存的区别？为什么需要虚拟内存](https://www.bilibili.com/video/BV1mKcBejE7Y?spm_id_from=333.1245.0.0)



### 内存对齐

#### 什么是内存对齐？

C++ 内存对齐的两个基本规则：

1.  **成员对齐（Member Alignment）**：每个成员变量的起始地址必须是其自身大小（或其自然对齐边界）的整数倍。
2.  **结构体对齐（Structure Alignment）**：整个结构体的大小必须是其最大成员变量大小（或指定的对齐字节数）的整数倍。如果不是，编译器会在结构体的末尾进行填充。

对齐规则：

1.   基本对齐：成员按最大对齐要求对齐
2.   结构体对齐：结构体大小是最大成员对齐的倍数
3.   数组对齐：数组元素按数组类型对齐

代码示例：

```cpp
#include <iostream>

struct Example1 {
    char a;  // 1字节，填充3字节
    int b;  // 4字节
    char c;  // 1字节，填充7字节
    double d;  // 8字节
};  // 总大小：24字节

struct Example2 {
    char a;  // 1字节
    char c;  // 1字节，填充2字节
    int b;  // 4字节
    double d;  // 8字节
};  // 总大小：16字节

struct Example3 {
    double d;  // 8字节
    char a;  // 1字节，填充3字节
    int b;  // 4字节
    char c;  // 1字节，填充7字节
};  // 总大小：24字节

// 使用 pragma pack 改变对齐
#pragma pack(push, 1)
struct PackedStruct {
    char a;  // 1字节
    int b;  // 4字节
    double c;  // 8字节
};  // 总大小：13字节
#pragma pack(pop)

struct Example4 {
    char a;  // 1字节，填充3字节
    int b[3];  // 4字节 * 3
    char c;  // 1字节，填充3字节
};  // 总大小：20字节

int main() {
    std::cout << "Example1 size：" << sizeof(Example1) << std::endl;
    std::cout << "Example2 size：" << sizeof(Example2) << std::endl;
    std::cout << "Example3 size：" << sizeof(Example3) << std::endl;
    std::cout << "PackedStruct size：" << sizeof(PackedStruct) << std::endl;
    std::cout << "Example4 size：" << sizeof(Example4) << std::endl;
    
    return 0;
}
```

`#pragma pack(push, 1)` 指令会改变其后所有新定义的结构体的对齐规则，直到遇到 `pop` 指令或文件结束。



#### 为什么内存对齐？

*   提高 CPU 访问效率
*   确保硬件兼容性，某些架构要求特定对齐
*   避免性能损失

存储效率和访问效率



#### 结构体大小的内存排序规则





#### 代码分析样例

知识点：多态、内存对齐

分析如下代码的输出结果：

```cpp
#include <iostream>

class Base {
public:
    int a = 1;
    virtual void print(int n = 2) {
        std::cout << "Base: " << a + n << std::endl;
    }
};

class Derive : public Base {
public:
    int b = 3;
    virtual void print(int n = 10) override {
        std::cout << "Derive: " << b + n << std::endl;
    }
};

int main() {
    Base* arr = new Derive[10];
    arr[7].print();  // 输出结果是？
    delete[] arr;

    Base *ptr = new Derive();
    ptr->print();  // 输出结果是？
    delete ptr;

    return 0;
}
```

>   来源：[网易C++一面：代码分析题（多态+内存对齐）【码农Mark】](https://www.bilibili.com/video/BV1DoMwzhETG?spm_id_from=333.1245.0.0)

分析：

首先看代码第 24 行，可以发现使用了多态，**虚函数是动态绑定**的，但是**默认参数是静态绑定**的，所以 Base 类对象的 n = 2 Derive 类对象的 n = 10，所以第 25 行的输出为 5；

>   ```cpp
>   Derive *ptr = new Derive();
>   ptr->print();  // 默认参数来自 Derive::print(int n = 10), 输出结果是13
>   delete ptr;
>   ```
>
>   ```cpp
>   Base *ptr = new Derive();
>   ptr->print();  // 默认参数来自 Base::print(int n = 2), 输出结果是5
>   delete ptr;
>   ```
>
>   **虚函数的动态绑定只影响函数体的选择，不影响默认参数的选择**。默认参数在 **编译期** 按 **静态类型** 绑定。

然后看第 20 行，可以发现构造了一个 Derive 类数组，然后 arr 指向这个数组。第 21 行，想要使用 `arr[7]` 来调用 `Derive::print()` 函数，`arr[7]` 等价于 `*(arr + 7 * sizeof(Base))`，所以这里就要求 sizeof(Base) 和 sizeof(Derive) 相等。假设在 64 位机器上运行，从类的定义可以分别得到 `sizeof(Base) = 8B(虚函数指针) + 4B(整型变量 a) + 4B(填充用于内存对齐) = 16B`，`sizeof(Derive) = 8B(虚函数指针) + 4B(整型变量 a) + 4B(整型变量 b) = 16B`。可以看到这段代码中 sizeof(Base) 和 sizeof(Derive) 很巧合的相等了，那么 arr[7].print() 能够得到预期的结果 5。

所以最终的结果为：
```bash
Derive: 5
Derive: 5
```

:warning:但实际上这是一个很巧合的事情，如果 Derive 类多一个变量 int c，在运行时就会出现段错误。

:warning:**不能用父类指针指向子类对象数组**并用 `[]` 访问，否则是未定义行为。因为数组访问依赖 `sizeof(T)` 做偏移，而指针类型决定了偏移的单位。

解决方案：

1.   直接用**子类指针数组**：
     ```cpp
     Derive* arr = new Derive[10];
     arr[7].print(); // 安全
     delete[] arr;
     ```

2.   如果必须用 `Base*` 来管理多个 `Derive` 对象，使用**单个对象的指针容器**，比如 `std::vector<Base*>`：
     ```cpp
     std::vector<Base*> arr;
     for (int i = 0; i < 10; ++i) arr.push_back(new Derive());
     arr[7]->print();
     for (auto p : arr) delete p;
     ```

3.   用**智能指针**管理多态对象：
     ```cpp
     #include <memory>
     #include <vector>
     
     std::vector<std::unique_ptr<Base>> arr;
     for (int i = 0; i < 10; ++i)
         arr.push_back(std::make_unique<Derive>());
     arr[7]->print();
     ```



### 内存布局

>   [计算机系统篇之链接（10）：.bss、.data 和 .rodata sections 之间的区别](https://csstormq.github.io/blog/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F%E7%AF%87%E4%B9%8B%E9%93%BE%E6%8E%A5%EF%BC%8810%EF%BC%89%EF%BC%9A.bss%E3%80%81.data%20%E5%92%8C%20.rodata%20section%20%E4%B9%8B%E9%97%B4%E7%9A%84%E5%8C%BA%E5%88%AB)
>
>   [What is the difference between .rodata and .rdata](https://stackoverflow.com/questions/65745514/what-is-the-difference-between-rodata-and-rdata)



### 内存泄漏

>   参考：[拼多多C++一面：内存泄露相关面试题，什么是内存泄露？列举检测内存泄露的方案](https://www.bilibili.com/video/BV1T3q5YpEzt/?spm_id_from=333.337.search-card.all.click&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)

#### 什么是内存泄漏

**内存泄露**是指在程序运行过程中，动态分配的内存（使用 `new` 或 `new[]`）在不再使用后，没有被正确地释放（使用 `delete` 或 `delete[]`），从而导致这块内存无法被程序再次利用。随着程序的持续运行，泄露的内存会不断累积，最终可能耗尽系统可用内存，导致程序崩溃或系统运行缓慢。

可以把内存泄露想象成一个没有及时清理的储物柜。你往里面放东西，但从来不拿出来。刚开始空间还很充足，但随着你放的东西越来越多，柜子总会被塞满。同样，内存泄露会导致系统内存被“塞满”，最终导致程序无法再分配新的内存。



#### 什么原因造成了内存泄漏

造成内存泄露的主要原因有：

1.   动态分配的内存未释放。最常见的内存泄漏场景是使用 `new` 或 `malloc()`动态分配的内存没有被及时释放。C++ 需要手动释放动态分配的内存，如果忘记使用 `delete` 或 `free()` 释放这块内存，程序退出之前这部分内存将无法被使用。

     ```cpp
     void memoryLeak() {
         int* arr = new int[100];  // 动态分配内存
         // 忘记释放内存
         // delete[] arr;  // 这行代码没有执行，导致内存泄漏
     }
     ```

2.   在异常处理时未释放内存。当程序抛出异常时，如果没有适当地处理内存释放，可能会导致内存泄漏。特别是在使用 `new` 动态分配内存的过程中，如果在释放内存之前发生了异常，分配的内存将无法被释放。

     ```cpp
     void exceptionLeak() {
         int* data = new int[10];  // 动态分配内存
         throw std::runtime_error("Some error");  // 抛出异常，但没有 delete[] data;
     }
     ```

3.   没有为类的析构函数释放内存。在类中使用 **`new`** 动态分配内存时，如果没有在析构函数中正确释放这部分内存，会导致每次创建对象时动态分配的内存得不到释放，进而造成内存泄漏。

     ```cpp
     class MyClass {
     private:
         int* data;
     public:
         MyClass() {
             data = new int[100];  // 动态分配内存
         }
         ~MyClass() {
             // 如果析构函数没有释放内存
             // delete[] data;  // 忘记释放内存，导致泄漏
         }
     };
     ```

4.   循环引用。在使用智能指针（特别是 std::shared_ptr）时，循环引用是导致内存泄漏的一个常见原因。std::shared_ptr 会使用引用计数来管理内存，当引用计数为 0 时，内存会被释放。然而，如果两个对象通过 std::shared_ptr 互相引用，它们的引用计数永远不会变为 0，导致内存无法释放。

     ```cpp
     #include <memory>
      
     class B;
     class A {
     public:
         std::shared_ptr<B> b_ptr;
     };
      
     class B {
     public:
         std::shared_ptr<A> a_ptr;
     };
      
     void circularReference() {
         std::shared_ptr<A> a = std::make_shared<A>();
         std::shared_ptr<B> b = std::make_shared<B>();
         a->b_ptr = b;  // A 引用 B
         b->a_ptr = a;  // B 引用 A，形成循环引用
         // 循环引用导致两者的引用计数无法变为 0，内存泄漏
     }
     ```

     解决办法是使用 **`std::weak_ptr`** 解决循环引用问题。**`std::weak_ptr`** 不会增加引用计数，从而避免循环引用。 

     ```cpp
     class A {
     public:
         std::weak_ptr<B> b_ptr;  // 使用 weak_ptr
     };
     ```

     

#### 如何避免内存泄漏

1.   代码规范，智能指针或 RAII 机制管理资源
2.   正确捕获异常处理/回滚式编程
3.   使用 `weak_ptr` 解决循环引用



#### 怎么定位内存泄露，原理是什么

*   静态检测工具。使用 cppcheck 或 clang-tidy 来检查代码中是否出现内存泄漏，但是有局限性。
*   动态检测
    *   valgrind。`valgrind --leak-check=full 可执行程序`。将 valgrind 视为虚拟机，将可执行程序当做文件来处理，读取二进制文件的内容，进行指令解析并执行。需要可执行程序携带调试信息，以便定位到具体的代码位置。
    *   hook + backtrace
        *   hook 住内存分配和内存释放的接口
        *   每次申请内存都记录一下，每次释放时也记录一下，然后再把这两种记录进行一个比较，把相同的去掉，剩下的就是没有释放的。
        *   同时在申请内存时，记录其调用堆栈信息
        *   侵入式
        *   需要调试信息
    *   eBPF + uprobes
        *   非侵入式
        *   不需要调试信息
        *   原理和上面一种相同，但是运行在内核

>   参考资料：
>
>   [1] [Linux内存泄露定位1：valgrind篇](https://mp.weixin.qq.com/s/dWbqNIA4pLWs4pd53Gaq8A)
>
>   [2] [Linux内存泄露定位3：hook+backtrace篇](https://mp.weixin.qq.com/s/JX2NVI35ze02k7LwCodhLA)
>
>   [3] [Linux内存泄露定位4：eBPF+uprobes 篇](https://mp.weixin.qq.com/s/gb3hcwgoFXTiZhmWxyf-bg)
>
>   [4] [Linux内存泄露定位5：gdb+python篇](https://mp.weixin.qq.com/s/j1Lc43zN49xhOKfx-eInRQ)
>
>   [5] [Linux内存泄露定位2：mtrace篇](https://mp.weixin.qq.com/s?__biz=MzU4NjY0NTExNA==&mid=2247486485&idx=1&sn=a4ff43bbf0f25700369fd433ac66613a&poc_token=HA0qp2ijFlkKYA-7XZx4Pro38DJgZSW43XV3lm1F)
>
>   [6] [拼多多C++一面：内存泄露相关面试题，什么是内存泄露？列举检测内存泄露的方案](https://www.bilibili.com/video/BV1T3q5YpEzt/?spm_id_from=333.337.search-card.all.click&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)
>
>   [7] [【C++】 使用CRT 库检测内存泄漏](https://blog.csdn.net/qq_65207641/article/details/139372244)



### delete 和 delete[] 的区别





### delete[] 怎么知道要析构多少元素？

[海康威视 C++ 一面：delete和delete[\]的区别,delete[]怎么知道要析构多少元素【码农Mark】](https://www.bilibili.com/video/BV1Yue6zMEA3?spm_id_from=333.1245.0.0)

![image-20250901175213234](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202509011752620.png)



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





### 动态链接和静态链接的区别





## 封装



## 继承

### 什么是对象切片



### 菱形继承

#### 什么是菱形继承？

**菱形继承（Diamond Inheritance）**是一种特殊的多重继承结构，它的类图形状像一个菱形。

-   首先，有一个**基类 A**。
-   然后，有两个**中间类 B 和 C**，它们都**继承**自基类 A。
-   最后，有一个**派生类 D**，它**同时继承**自中间类 B 和 C。

用代码表示就是：

```cpp
class A {
public:
    int data;
};

class B : public A {};
class C : public A {};
class D : public B, public C{};
```

这个继承链从 A 到 B、从 A 到 C，再从 B 和 C 到 D，形成一个菱形。

#### 菱形继承会存在什么问题？

菱形继承主要会带来**数据冗余**和**二义性（Ambiguity）**这两个核心问题。

1.  **数据冗余（Data Redundancy）**

    因为类 D 同时继承了 B 和 C，而 B 和 C 又都继承了 A，所以在 D 的对象中，实际上包含了**两份**基类 A 的成员变量。

    -   一个来自 `D -> B -> A` 的路径。
    -   另一个来自 `D -> C -> A` 的路径。

    比如，在上面的例子中，`D` 的对象里会有两份 `int data;`。这不仅浪费了内存，也可能导致数据不一致。

2.  **二义性（Ambiguity）**

    当你想通过 D 的对象访问基类 A 的成员时，编译器不知道应该访问哪一份。

    例如，如果你想访问 `data` 变量：

    ```cpp
    D obj;
    obj.data = 10; // 编译错误！二义性
    ```

    编译器会报错，因为它无法确定你是想通过 B 的路径去访问 `data`，还是通过 C 的路径。为了解决这个问题，你必须显式地指定路径：

    ```cpp
    obj.B::data = 10;
    obj.C::data = 20;
    ```

    这虽然解决了问题，但增加了代码的复杂性，违背了面向对象的初衷。

#### 如何解决菱形继承问题？

C++ 提供了**虚继承（Virtual Inheritance）**来解决菱形继承带来的问题。

通过在继承时使用 `virtual` 关键字，可以确保在整个继承体系中，公共基类（这里是 A）只被继承**一次**，从而避免了数据冗余和二义性。

解决后的代码是这样的：

```cpp
class A {
public:
    int data;
};

// 使用 virtual 关键字
class B : virtual public A {};

// 使用 virtual 关键字
class C : virtual public A {};

class D : public B, public C {};
```

当 `D` 继承 `B` 和 `C` 时，它会知道 `B` 和 `C` 都是**虚继承**自 `A`，因此 `D` 的对象中只会包含**一份** `A` 的实例。这从根本上解决了数据冗余问题。

现在，你就可以直接访问 `data`，而不会有二义性：

```cpp
D obj;
obj.data = 100; // 正常编译
```

**虚继承**通过让派生类共享一个公共的虚基类子对象，从而解决了菱形继承的问题。这是一个非常重要的概念，因为它展示了 C++ 如何在语言层面解决多重继承的复杂性。

不过虚继承会影响类 B 和 C 的内存布局，编译器会为其添加一个**虚基类表指针(vbptr)**，指向虚基类A的位置。




## 多态

### 介绍多态，具体如何实现

C++ 中的多态分为静态多态和动态多态，静态多态通过**模板和函数重载**实现，动态多态通过**虚函数和继承**实现。没有特别指明的情况下，一般是指动态多态，即使用 virtual 实现的多态。

回答多态的实现原理，主要可以围绕在虚函数、虚函数表和虚函数表指针方向上。

多态通过虚函数实现。通过虚函数，派生类可以重写基类的方法，当通过基类**指针**或**引用**调用时，会根据对象的实际类型调用对应的函数实现。

而这更深层次的原理，是通过虚函数表（vtable）和虚函数表指针（vptr）机制实现的。虚表是一个函数指针数组，包含了该类所有虚函数的地址，而虚表指针存储在对象实例中，指向属于该对象的虚表。



1）虚函数：在基类中使用 `virtual` 关键字声明虚函数之后，子类可以重写这个函数 (override)。

2）虚函数表 (vtable)：</br>
**生成时机**：每一个包含虚函数的<mark>类</mark>在**编译时**都会生成虚函数表 (vtable)，它存储该类所有虚函数的地址，对于每个类，编译器会创建唯一的 vtable。这个表是**类级别**的，和具体对象无关，所以在编译完成后就确定了。</br>
**存储位置**：`vtable` 存储在<mark>代码段 (`.rodata` 或常量区)</mark>。</br>
**生命周期**：程序加载到内存时建立，一直存在到程序结束 (不可修改)。

3）虚函数表指针 (vptr)：</br>
**生成时机**：每个包含虚函数的类的<mark>对象</mark>都会有一个隐藏成员 `vptr`，指向该类对应的虚函数表。这个 `vptr` 是在**构造函数执行时**由**编译器**自动插入代码进行初始化的，在基类构造阶段，`vptr` 会先指向基类的 `vtable`，在派生类构造阶段，`vptr` 会被更新为指向派生类的 `vtable`。在析构时，执行到基类析构函数时，`vptr` 会再次被更新为指向基类的 `vtable` (这也是为什么在基类析构函数中调用虚函数时会表现成"基类版本")。</br>
**存储位置**：<mark>对象内存中 (通常在对象的起始位置)</mark>，栈上/堆上/全局(静态)区取决于对象分配方式。</br>
**生命周期**：随对象创建和销毁而存在。

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

**我的回答**：

在一个存在虚函数的类中，构造函数不能为虚函数，析构函数应该定义为虚函数。

构造函数不能定义为虚函数，是因为虚函数的调用依赖于虚函数表指针 vptr，而 vptr 是在对象被构造的过程中初始化的，如果构造函数本身是虚函数，vptr 没有被正确设置，无法实现多态。

析构函数应该定义为虚函数，以确保正确释放内存，防止内存泄漏。在使用基类指针指向派生类对象时，如果析构函数是虚的，`delete` 操作就会触发多态，调用派生类的析构函数，并自动链式调用基类的析构函数。



### C++ 多态解决了什么问题

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



### 什么是纯虚函数

包含形如 `virtual void makeSound() = 0;` 的函数被称为纯虚函数，包含纯虚函数的类被称为抽象类。

抽象类不能直接实例化。因为一个抽象类**不完整**。它声明了 `makeSound()` 必须存在，但没有提供具体的实现。编译器无法为一个不完整的方法分配内存和生成可执行代码，所以它无法创建一个抽象类的对象。

抽象类的主要作用是作为**接口**。它定义了一系列子类必须实现的公共行为（例如 `makeSound()`），但它并不关心这些行为的具体实现细节。

只有当一个派生类**完全实现**了所有继承的纯虚函数后，它才是一个**具体类（concrete class）**，才可以被实例化。



### 虚函数表的实现原理

虚函数表是 C++ 多态的核心机制，每个包含虚函数的类都有一个虚函数表，存储虚函数的地址。

TODO



## 设计模式

详见[常用的设计模式](../CPP/常用的设计模式.md)

### 单例模式

详见[单例模式](../CPP/常用的设计模式.md#_1)

### 工厂模式

详见[工厂模式](../CPP/常用的设计模式.md#_5)



## Qt

### QT中信号和槽的原理是什么？

>   [C++ 客户端面试题：QT中信号和槽的原理是什么？](https://www.bilibili.com/video/BV1Aht2zdEmK?spm_id_from=333.1245.0.0)





### Qt 中，将一个窗口绘制上屏幕的过程是什么？

这是一个典型的 GUI 框架工作原理问题，考察你对 Qt 渲染管线、事件循环和底层图形系统的理解。这个过程可以简化为以下几个关键步骤：

#### **1 事件触发与更新请求**

一切都始于一个事件，这个事件表明窗口的内容需要更新。这通常由以下情况触发：

-   **窗口大小改变**：用户拖动窗口边缘。
-   **窗口被遮挡后重新暴露**：另一个窗口从它上面移开。
-   **控件状态改变**：比如点击按钮，文本框内容更新。
-   **显式调用**：开发者手动调用 `QWidget::update()` 或 `QWidget::repaint()`。

这些操作会生成一个或多个**绘制事件（Paint Event）**，并将其放入 Qt 的事件队列中。

#### **2 事件循环与 `paintEvent()`**

Qt 的**事件循环（Event Loop）**持续运行，负责从事件队列中取出事件并分发给相应的对象。当它处理到绘制事件时，会调用窗口控件（`QWidget`）的虚函数 `paintEvent()`。

`paintEvent()` 是 Qt 绘制的核心。你的所有自定义绘制代码都应该写在这个函数里。在函数内部，你需要使用一个**画家（`QPainter`）**对象，它封装了各种绘图操作，如绘制线条、文本、图片等。

#### 3 绘制到绘图设备（`QPaintDevice`）

`QPainter` 并不会直接绘制到屏幕上，而是绘制到一个抽象的**绘图设备（`QPaintDevice`）上。`QWidget` 就是一个特殊的 `QPaintDevice`。当你在 `paintEvent()` 中使用 `QPainter` 绘制时，实际上是在一个离屏缓冲区**或**帧缓冲区**上进行操作。

这个离屏缓冲区可以是一个 `QPixmap`、`QImage` 或其他内部缓冲区。这样做的好处是，所有的绘制操作都在内存中完成，避免了直接操作屏幕带来的闪烁问题，这被称为**双缓冲（Double Buffering）**技术。

#### 4 提交到显示系统

`paintEvent()` 执行完毕后，Qt 的内部机制会接管剩下的工作。它会将已经绘制好的离屏缓冲区的内容，通过底层的图形 API（如 OpenGL、Vulkan、DirectX 或平台的原生图形库）提交给显示系统。

这个过程通常包括：

-   **合成（Compositing）**：如果窗口有子控件或多个图层，Qt 的窗口系统会把这些图层合成在一起。
-   **交换缓冲区（Swapping Buffers）**：在双缓冲模式下，Qt 会将已经完成绘制的离屏缓冲区与显示器正在显示的缓冲区进行交换，从而在屏幕上一次性、无闪烁地呈现出最终的窗口画面。

#### 总结

整个过程可以概括为：**事件触发 -> 事件循环分发事件 -> 调用 `paintEvent()` 执行自定义绘制 -> 绘制到离屏缓冲区 -> 提交给底层图形 API并交换缓冲区，最终显示在屏幕上。**



## MySQL

### 什么是索引

在 MySQL 中，索引是一种用于**快速查找数据库表中记录的数据结构**。**索引类似于一本书的目录，可以加速查询操作，但也会增加维护成本**。索引在数据库优化中扮演着关键角色，特别是在涉及大量数据的查询时。



### 建立索引的原则是什么？





### 什么是事务？

事务（Transaction）是数据库管理系统（DBMS）中用于保证数据一致性和完整性的一种机制。事务是一组被看作一个单一逻辑单元的操作，这些操作要么全都成功，要么全都失败。事务可以确保在并发环境中，多个用户或应用程序对数据库的操作不会导致数据不一致。



### 事务的四大特性





### 什么是慢查询

慢查询是指在数据库中执行时间过长，响应速度慢的查询操作。具体的时间阈值可以根据系统的具体需求进行定义。



### MySQL 是 主要通过什么数据结构实现？

MySQL 索引主要通过 B+树数据结构实现的。

原因：

1. 高效的读写：对于数据库读写操作频繁的场景，B+树平衡性能较好，读写性能稳定。

2. 范围查询优势：B+树支持范围擦汗寻，hash表只支持精确查询，而二叉树效率地下。

3. 磁盘读写优化：B+树的节点大小通常和磁盘扇区大小相同，这样可以最大化磁盘I/O的效率

4. 磁盘减少I/O次数：B+树的分支因子大，树的层级较低，可以减少在查询过程中磁盘的I/O的次数 



### 为什么用B+树？



## 网络编程

### Not Modified 状态码

304



### OSI 七层模型



### TCP/IP 四层模型



### TCP 和 UDP 的区别

>   TCP（Transmission Control Protocol）和 UDP（User Datagram Protocol）是两种常见的**传输层协议**。它们的区别主要体现在***\*数据传输方式、可靠性、连接性\****等方面。下面从几个维度详细对比这两种协议： 

1、连接性

*   TCP需要先通过三次握手来建立连接，保证通信双方的连接可靠，数据传输完成之后，还要通过四次挥手来断开连接
*   UDP不需要建立连接，直接将数据发送给目标。因此，UDP通信开销较小，没有连接管理的机制。

2、可靠性

*   TCP 提供可靠的传输。
*   UDP 不保证可靠性。UDP 传输可能会出现数据包丢失、重复或乱序的情况。UDP 适用于对可靠性要求不高的场景。

3、数据传输效率

*   TCP 由于建立连接、确认、重传、拥塞控制等机制，数据传输的开销较大，效率较低。它更适合可靠性和数据完整性的应用。
*   UDP 没有复杂的连接和控制机制，传输效率更高，适合需要低延迟、实时传输的场景。

4、传输单位

*   TCP 基于流传输，TCP 会将数据分片，按需组装成数据流。因此，TCP 更适合连续的数据传输，如文件传输。
*   UDP 基于数据报文传输。UDP 以数据报文为单位传输，每个数据报文是独立的，且大小固定，适合传输短的消息。

5、应用场景

*   如果需要**高可靠性**，使用 TCP。比如文件传输、网页浏览、远程登录等场景。
*   如果追求**低延迟**且**容忍一定的数据丢失**，使用 UDP。比如视频会议、直播、在线游戏等场景。



### HTTP 和 HTTPS 的区别

#### 核心区别

| 特性       | HTTP (HyperText Transfer Protocol) | HTTPS (HyperText Transfer Protocol Secure) |
| ---------- | ---------------------------------- | ------------------------------------------ |
| **安全性** | **不安全**。数据以明文传输。       | **安全**。数据经过加密传输。               |
| **端口**   | 默认端口：`80`                     | 默认端口：`443`                            |
| **认证**   | 不提供身份认证。                   | 提供身份认证，防止中间人攻击。             |
| **连接**   | 无需加密，建立 TCP 三次握手即可。  | 在 TCP 握手后，需要进行 SSL/TLS 握手。     |
| **协议层** | 应用层协议。                       | 基于 SSL/TLS 的应用层协议。                |

#### HTTPS 的安全性体现在哪里？

HTTPS 的安全性主要由 **SSL/TLS 协议**提供，体现在以下三个方面：

1.  **数据加密（Encryption）**：
    -   **目的**：防止数据在传输过程中被窃听。
    -   **原理**：所有在客户端和服务器之间传输的数据都经过加密。即使数据被第三方截获，也无法读取其内容。
2.  **身份认证（Authentication）**：
    -   **目的**：确保你连接的是正确的服务器，而不是一个伪造的服务器。
    -   **原理**：服务器通过**数字证书**向客户端证明自己的身份。证书由权威的证书颁发机构（CA）认证。
3.  **数据完整性（Integrity）**：
    -   **目的**：防止数据在传输过程中被篡改。
    -   **原理**：使用哈希算法（如 SHA-256）对数据进行校验。如果数据在传输过程中被篡改，校验和就会不匹配，从而能立即发现。

#### HTTPS 是如何实现的？

HTTPS 的实现核心是 **SSL/TLS 握手**，这是一个在 TCP 连接建立后，客户端和服务器之间进行的一系列加密和认证协商过程。整个过程可以分为以下几个关键步骤：

1.  **客户端发起“你好”（Client Hello）**：
    -   客户端发送消息给服务器，包含它支持的 SSL/TLS 协议版本、加密套件（Cipher Suites，即各种加密算法的组合）和一段随机数。
2.  **服务器返回“你好”（Server Hello）**：
    -   服务器从客户端提供的列表中，选择一个它支持的最佳 SSL/TLS 版本和加密套件。
    -   服务器发送它的**数字证书**给客户端。证书包含服务器的公钥和身份信息。
    -   服务器也发送一段随机数。
3.  **客户端验证证书并生成密钥**：
    -   客户端验证服务器的数字证书。
    -   如果证书有效，客户端会生成一个**预主密钥（Pre-Master Secret）**，并使用**服务器的公钥**对其进行加密。
    -   客户端将加密后的预主密钥发送给服务器。
4.  **服务器解密并生成会话密钥**：
    -   服务器使用自己的**私钥**解密预主密钥。
    -   客户端和服务器都使用各自的随机数和预主密钥，通过协商好的算法生成一个相同的**会话密钥（Session Key）**。
5.  **加密通信**：
    -   从现在开始，所有数据都使用这个**会话密钥**进行对称加密传输。

#### 总结

-   **HTTP** 是明文传输，**不安全**。
-   **HTTPS** 通过 **SSL/TLS 协议**提供加密、认证和数据完整性，**保证安全**。
-   其实现依赖于一个复杂的**握手过程**，包括非对称加密（用于密钥交换和身份认证）和对称加密（用于实际的数据传输）。

这个回答包含了核心概念、对比和实现细节，应该能很好地应对面试官的提问。



### TCP 三次握手

#### TCP 的三次握手过程

TCP 协议在建立连接时需要进行一个被称为“三次握手”（Three-way Handshake）的过程，以确保客户端和服务器都能正常收发数据。

这个过程涉及三个数据包：

1.  **第一次握手 (SYN)**：
    -   **客户端**向**服务器**发送一个 SYN 包（`SYN = 1`, `seq = x`）。
    -   **目的**：客户端请求建立连接，并告诉服务器它将从**序号 `x`**开始发送数据。
2.  **第二次握手 (SYN-ACK)**：
    -   **服务器**收到 SYN 包后，如果同意建立连接，会向**客户端**发送一个 SYN-ACK 包（`SYN = 1`, `ACK = 1`, `ack = x+1`, `seq = y`）。
    -   **目的**：服务器确认收到了客户端的请求，并告诉客户端它将从**序号 `y`\**开始发送数据。服务器的 `ack = x+1` 则是确认收到了客户端的\**序号 `x`**。
3.  **第三次握手 (ACK)**：
    -   **客户端**收到 SYN-ACK 包后，向**服务器**发送一个 ACK 包（`ACK = 1`, `ack = y+1`）。
    -   **目的**：客户端确认收到了服务器的 SYN-ACK 包，并告诉服务器它准备好发送数据。客户端的 `ack = y+1` 则是确认收到了服务器的**序号 `y`**。

完成这三次握手后，客户端和服务器都进入“已连接”（`ESTABLISHED`）状态，可以开始双向传输数据。

#### 为什么要设计第三次握手？

这个问题是面试的重点。设计第三次握手的根本原因是为了**防止服务器端资源的浪费**，同时确保**双方都能确认对方具备收发能力**。

让我们用一个形象的例子来解释：

-   **第一次握手**：客户端对服务器说：“我准备好了，可以向你发消息了！” (客户端具备发送能力)
-   **第二次握手**：服务器回复客户端：“好的，我收到了你的消息，我也准备好了，可以接收你的消息了！” (服务器具备接收能力，并向客户端确认)
-   **第三次握手**：客户端再次回复服务器：“好的，我收到了你的确认，我知道你准备好了，开始发消息吧！” (客户端具备接收能力，并向服务器确认)

如果只有两次握手，会存在什么问题？这被称为“**失效的连接请求**”问题。

假设客户端发送了一个连接请求（SYN 包），但在网络中因延迟而滞留，客户端误以为请求失败并重发。当新的请求成功建立连接并关闭后，那个滞留的旧 SYN 包才到达服务器。

1.  **旧 SYN 包到达服务器**。服务器以为这是一个新的请求，立即发送 SYN-ACK 包，并进入连接等待状态。
2.  **服务器等待**。但客户端因为旧的请求已经超时，并不会理会这个 SYN-ACK 包。
3.  **服务器资源浪费**。服务器会一直等待客户端的 ACK，直到超时。在这个等待期间，服务器分配了资源（如内存缓冲区、端口号），但这些资源永远无法被使用，造成了资源的浪费。

**第三次握手**正是为了解决这个问题。如果旧的 SYN 包到达了服务器，服务器发送了 SYN-ACK 包，但客户端并不会响应，因为它没有发送过这个请求。服务器收不到客户端的 ACK 确认，就不会建立连接，从而避免了资源的浪费。

**总结来说，第三次握手的核心作用是：**

-   **客户端**通过第三次握手，确认**服务器**具备**收和发**的能力。
-   **服务器**通过第三次握手，确认**客户端**具备**收和发**的能力。

通过这个双向的确认过程，TCP 才能可靠地建立连接。



### TCP 四次挥手

TCP 连接的断开比建立要复杂，需要四次挥手来确保双方都完成数据的发送和接收。

**客户端首先向服务器发送**或者**服务器首先向客户端发送**。

#### TCP 的四次挥手过程

这个过程涉及四个数据包：

1.  **第一次挥手 (FIN)**：
    -   **客户端**发送一个 FIN 包（`FIN = 1`, `seq = u`）给**服务器**，表示它**已经没有数据要发送了**。
    -   此时，客户端进入 `FIN_WAIT_1` 状态。
2.  **第二次挥手 (ACK)**：
    -   **服务器**收到 FIN 包后，会立即发送一个 ACK 包（`ACK = 1`, `ack = u+1`）给**客户端**，表示它已经收到了客户端的关闭请求。
    -   此时，服务器进入 `CLOSE_WAIT` 状态。
    -   **注意**：TCP 连接是**全双工**的，这意味着客户端虽然不发送数据了，但服务器可能还有数据要发送给客户端。在第二次和第三次挥手之间，服务器可以继续发送数据。
3.  **第三次挥手 (FIN)**：
    -   当**服务器**也**没有数据要发送了**时，它会向**客户端**发送一个 FIN 包（`FIN = 1`, `seq = w`, `ack = u+1`），表示它也准备关闭连接了。
    -   此时，服务器进入 `LAST_ACK` 状态。
4.  **第四次挥手 (ACK)**：
    -   **客户端**收到服务器的 FIN 包后，会发送一个 ACK 包（`ACK = 1`, `ack = w+1`）给**服务器**，表示它已经收到了服务器的 FIN 包。
    -   此时，客户端进入 `TIME_WAIT` 状态，并等待一段**超时时间（<mark>2MSL</mark>）**。
    -   服务器收到这个 ACK 包后，会立即关闭连接。
    -   客户端等待 2MSL 后，也关闭连接。

#### 为什么需要四次挥手？

TCP 挥手需要四次，而不是像三次握手那样只需要三次，是因为 TCP 连接是<mark>全双工</mark>的。

-   **握手**时，双方都同时准备好了收和发的能力。
-   **挥手**时，双方各自独立地结束自己的发送。

简单来说：

-   **第一次和第二次挥手**：客户端向服务器发送关闭请求，服务器收到后**只确认**收到请求，但**不立即关闭**连接，因为服务器可能还有数据要发送。
-   **第三次和第四次挥手**：当服务器发送完所有数据后，它会主动发起关闭连接的请求，客户端收到后进行确认，然后双方最终关闭连接。

这个分离的关闭过程，确保了在客户端请求关闭后，服务器仍有机会发送完所有剩余的数据，从而保证了数据的完整传输，避免了数据丢失。

**`TIME_WAIT` 状态的重要性**

第四次挥手后，客户端进入 `TIME_WAIT` 状态，并等待 2MSL（最长报文段寿命）。这个等待时间是为了：

1.  **确保最后一个 ACK 包到达服务器**：如果第四次挥手的 ACK 包丢失，服务器会重发第三次挥手的 FIN 包。客户端在 `TIME_WAIT` 状态下收到重发的 FIN 包后，会再次发送 ACK，并重新计时，确保服务器能正确关闭。
2.  **防止“陈旧”的数据包**：确保本次连接的所有数据包都已经在网络中消失，避免新的同端口连接收到旧的数据包。

四次挥手时的状态：

| 挥手顺序 | 发送方 | 接收方 | 报文  | 发送方状态   | 接收方状态    |
| :------- | :----- | :----- | :---- | :----------- | :------------ |
| **1st**  | 客户端 | 服务器 | `FIN` | `FIN_WAIT_1` | `ESTABLISHED` |
| **2nd**  | 服务器 | 客户端 | `ACK` | `CLOSE_WAIT` | `FIN_WAIT_2`  |
| **3rd**  | 服务器 | 客户端 | `FIN` | `LAST_ACK`   | `FIN_WAIT_2`  |
| **4th**  | 客户端 | 服务器 | `ACK` | `TIME_WAIT`  | `CLOSED`      |



### 一次完整的 HTTP 请求过程：

DNS域名解析 $\to$ TCP 的 3 次握手 $\to$ 建立 TCP 连接，发送 HTTP 请求 $\to$ 服务器响应 HTTP 请求，返回 HTML 代码给浏览器 $\to$ 浏览器解析 HTML 代码并请求其中的资源 (CSS、JS、图片等) $\to$ 浏览器渲染页面呈现给用户

DNS 域名解析：[DNS域名详细解析过程(最全面，看这一篇就够)](https://blog.csdn.net/bangshao1989/article/details/121913780)

TCP 三次握手四次挥手：[简单理解TCP三次握手四次挥手（看一遍你就懂）](https://blog.csdn.net/m0_56649557/article/details/119492899)



### 介绍一下 DHCP 网络协议

知识点：网路协议，IP地址分配

DHCP 是一个网络协议，用于自动分配 IP 地址和其他网络配置参数给网络中的设备。

工作原理：

1.   DHCP Discover：
2.   DHCP Offer：
3.   DHCP Request：
4.   DHCP ACK：

代码示例（简化版 DHCP 客户端模拟）：

```cpp

```

>   [盘点互联网大厂秋招面试题、影石C++二面：继承、虚函数、malloc、static、内存分配、内存对齐【码农Mark】](https://www.bilibili.com/video/BV16FYBzkEtL/?share_source=copy_web&vd_source=b5ed364998fc1b958c57abd6dbda38e3)



#### DHCP 的租约续期





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



### 常见的 I/O 多路复用机制

#### `select`

*   **跨平台**：支持所有主流操作系统（Linux/Windows/macOS）。
*   **基于轮询**：通过遍历文件描述符集合（`fd_set`）检查就绪状态。
*   限制：
    *   单个进程最多监听 **1024** 个文件描述符（FD）。
    *   每次调用需**全量拷贝**`fd_set` 到内核。
*   缺点
    *   O(n) 时间复杂度：每次遍历所有 FD，性能随 FD 数量线性下降。
    *   重复初始化：每次调用需重新设置 `fd_set`。



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
    *   `EPOLL_CTL_ADD` (添加)：将一个新的文件描述符(fd)添加到 `epoll` 实例的监听列表中。
    *   `EPOLL_CTL_MOD` (修改)：修改一个已经存在于 `epoll` 监听列表中的 fd 的事件类型。
        *   `EPOLLIN`：监听可读事件
        *   `EPOLLOUT`：监听可写事件

    *   `EPOLL_CTL_DEL` (删除)：将一个 fd 从 `epoll` 的监听列表中移除。

*   `epoll_wait()`：等待就绪事件。



**触发模式**

*   `EPOLLLT` (水平触发)：只要 FD 可读/可写，epoll_wait() 会持续通知（默认模式，类似 poll）。
*   `EPOLLET` (边沿触发)：仅在 FD 状态变化时通知一次（需一次性处理完数据，否则可能丢失事件）。
*   `EPOLLONESHOT` (一次性触发)：当你为一个文件描述符注册 `EPOLLONESHOT` 后，`epoll` 就会在事件被触发后**自动停止**监听该文件描述符上的任何事件。如果你想继续监听，必须**显式地**再次调用 `epoll_ctl`，重新注册你感兴趣的事件。

**优点**

*   高性能：支持百万级并发（如 Nginx、Redis）。
*   低开销：无需每次调用传递所有 FD。



**为什么使用 `EPOLLET`？**

为了提高效率。在高并发场景下，`EPOLLLT` 的多次唤醒会增加内核和用户空间之间的上下文切换开销。`EPOLLET` 模式要求你“一次性读完”，这减少了 `epoll_wait` 的调用次数，从而提高了服务器的吞吐量。



**为什么使用 `EPOLLONESHOT`？**

为了解决**多线程环境下的竞态条件**。

假设你有多个线程同时处理 `epoll` 返回的事件，并且你没有使用 `EPOLLONESHOT`。一个文件描述符上触发了 `EPOLLIN` 事件，两个线程都收到了通知并尝试处理它。如果没有加锁，这会导致严重的线程安全问题。

而有了 `EPOLLONESHOT`，当一个线程处理一个事件时，`epoll` 会自动停止监听该文件描述符。这确保了在任何一个时刻，**只有一个线程**能够处理这个文件描述符上的事件。当该线程完成处理后，它会再次调用 `epoll_ctl`，将文件描述符重新加入到 `epoll` 的监听列表中，从而避免了竞态条件。



### recv()

`recv()` 函数用于接收数据，它的返回值有三种情况：

1.  **返回值 > 0**：表示成功接收到的**字节数**。
2.  **返回值 = 0**：这是一种特殊情况。它不代表接收了 0 字节的数据，而是表示**连接已经被对端正常关闭**（通过 `close()` 或 `shutdown()`）。当对端发送了 `FIN` 包（连接终止包）后，`recv()` 会返回 0。这是判断连接是否断开的最常用和最可靠的方式。
3.  **返回值 = -1**：表示**发生错误**。你需要检查全局变量 `errno`（在 Windows 上是 `WSAGetLastError()`）来确定具体的错误类型。常见的错误包括连接被重置 (`ECONNRESET`)，或者操作被中断 (`EINTR`)。



### send()



## 零散知识点

*   C++ 中函数调用可以嵌套，但函数定义不能嵌套。

*   C++ 中**回调函数**是通过**函数指针**来实现的
    ```cpp
    #include <iostream>
    
    void printResult(int value) {
        std::cout << "The value is " << value << ".\n";
    }
    
    void performOperation(int a, void (*callback)(int)) {
        int result = a * 2 + 5;
        callback(result);
    }
    
    int main() {
        performOperation(10, printResult);
        return 0;
    }
    ```

*   在现代 C++ 或其他语言中，除了函数指针，还可以使用其他类型来实现类似的回调机制，包括：

    -   **`std::function`**：C++11 引入的通用函数包装器。它比函数指针更强大、更灵活，可以封装普通函数、Lambda 表达式、仿函数和类成员函数。
    -   **Lambda 表达式**：可以看作是一种匿名的、临时的函数对象。它们可以被 `std::function` 捕获，从而实现更简洁的回调。
    -   **仿函数 (Functor)**：即重载了 `operator()` 的类对象。

*   内联函数必须和它的函数体定义（实现）声明在一起，`inline` 关键字才有效。

*   内联函数 vs. 宏定义

    -   **宏定义 (`#define`)**：是**预处理器**的输入。在编译之前，预处理器会进行纯文本替换。它不关心语法，也不进行类型检查。
    -   **内联函数 (`inline`)**：是**编译器**的输入。编译器在处理代码时，会看到 `inline` 关键字，并将其作为一种“建议”。然后，编译器会**尝试**将内联函数的函数体直接插入到调用它的地方。这个过程发生在编译阶段，而不是预处理阶段。

*   在设计模式的思想中，需要复用时，应当优先考虑**组合**

*   可以用 `#elif` 和 `#else` 指令扩展条件编译结构来测试多种条件



## 参考资料

[1] [百度一面面经（C++）](https://blog.csdn.net/qq_29426201/article/details/147271710)

[2] [百度C++开发岗三面面经(已offer)](https://www.nowcoder.com/discuss/353155780922777600)

[3] [百度提前批，三面被推迟一周，喜提秋招第一凉](https://zhuanlan.zhihu.com/p/1935627993805463760)

[4] [百度c++开发面经（已OC）](https://www.nowcoder.com/feed/main/detail/1f237804872148f38fbcb8f6fae03ad9?sourceSSR=dynamic)

[5] [百度后端C++，一面、二面 + 主管面面经（已拿offer）](https://blog.csdn.net/weixin_55305220/article/details/121121416)

[6] [史上最全C/C++面试、C++面经八股文，一文带你彻底搞懂C/C++面试、C++面经！](https://blog.csdn.net/songbijian/article/details/132507421)

[7] [为什么你背八股像是在受刑，别人背就是享受](https://www.bilibili.com/video/BV12YVUzwEoB/?spm_id_from=333.1245.0.0&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)

[8] [网易C++一面：代码分析题（多态+内存对齐）【码农Mark】](https://www.bilibili.com/video/BV1DoMwzhETG?spm_id_from=333.1245.0.0)

[9] [面试中计算机基础到底考什么，应该怎么学](https://www.bilibili.com/video/BV1oS9qYkEm9?spm_id_from=333.1245.0.0)

[10] [盘点互联网大厂秋招面试题、影石C++二面：继承、虚函数、malloc、static、内存分配、内存对齐【码农Mark】](https://www.bilibili.com/video/BV16FYBzkEtL/?share_source=copy_web&vd_source=b5ed364998fc1b958c57abd6dbda38e3)

[11]

[12]

[13]

[14]
