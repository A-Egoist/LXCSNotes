# 一、从零开始实现C++ TinyWebServer 全过程记录

[toc]

## 学习记录

开始时间：2025-6-15

我的实现：[GitHub](https://github.com/A-Egoist/WebServer)

[从零开始实现C++ TinyWebServer（一）---- 项目总述](https://blog.csdn.net/weixin_51322383/article/details/130470806)

1.   [什么是 WebServer？](https://developer.mozilla.org/zh-CN/docs/Learn_web_development/Howto/Web_mechanics/What_is_a_web_server)

     ![通过 HTTP 的客户/服务器连接的基本表示方法](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506151046879.svg)

2.   如何实现一个高并发的 WebServer？

     *   I/O 多路复用技术：[IO多路复用——深入浅出理解select、poll、epoll的实现](https://zhuanlan.zhihu.com/p/367591714)
     *   什么是 socket？
     *   线程池（多线程并发）
     *   Reactor 模型：[高性能网络编程之 Reactor 网络模型（彻底搞懂）](https://blog.csdn.net/ldw201510803006/article/details/124365838)
     *   Proactor 模型：
     *   数据库连接池
     *   定时器 (Timer)

3.   项目框架

     ![WebServer-架构图-001](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506261508970.png)

4.   Logger Class

     *   什么是单例模式？
         *   懒汉模式
         *   饿汉模式
         
     *   同步日志和异步日志

         ![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506182118865.jpeg)

5.   Thread Pool

     *   进程和线程的概念：https://zhuanlan.zhihu.com/p/697963882，线程的五种状态
     *   Linux 多线程 (pthread)
     *   线程同步的主要问题：竞争、死锁、活锁、饥饿
     *   互斥锁和条件变量
     *   读写锁

6.   Connection Pool

     *   RAII (Resource Acquisition Is Initialization)
     *   TCP 连接池

7.   HTTP

     *   [HTTP协议 | 一文详解HTTP报文结构](https://blog.csdn.net/sunyctf/article/details/129002163)
     *   [实现高效的URL编码与解码转换](https://blog.csdn.net/weixin_42527589/article/details/146357740)

8.   Timer Class

     *   定时器的实现，通常采用：排序链表、红黑树、时间堆和时间轮
     *   小根堆和大根堆
     *   Linux 时间机制：https://zhuanlan.zhihu.com/p/697968510
     
9.   Epoll

     *   [Linux epoll完全图解，彻底搞懂epoll机制](https://zhuanlan.zhihu.com/p/17856755436)

10.   阻塞和非阻塞 I/O

      *   1.3 Linux 非阻塞 I/O：https://zhuanlan.zhihu.com/p/697968510
      
11.   定时器

      *   发布者-订阅者模型
      *   计时线程如何设计？
          *   不是所有的线程都需要计时信息，所以计时器不能给所有线程都发通知，这很浪费不可取。因此计时线程要记录，**记录要给哪些线程发通知**。
          *   需要计时器的通知信息的线程可能会增多，可能会减少，所以要允许它们 **既可以订阅，也可以取消订阅**。
          *   计时线程并不知道到底会有多少个线程将来要订阅它的通知，所以它还要**具备良好的可扩展性，能支持大量的线程订阅其信息**。
          *   计时线程作为**发布者通知到订阅者**，一个计时周期已经到了

12.   




## 其他笔记

1.   什么是 explicit 关键字，有什么作用：[【C++】explicit关键字详解（explicit关键字是什么? 为什么需要explicit关键字? 如何使用explicit 关键字）](https://blog.csdn.net/weixin_45031801/article/details/137796214)

2.   手动提交 POST 请求：

     ```bash
     curl -v -X POST 127.0.0.1:8080 -d "username=admin&password=123456"
     ```

3.   HTML 状态码：[HTTP 状态码](https://www.runoob.com/http/http-status-codes.html)
     200, 302, 404
     在用户登录成功之后需要返回 `/welcome.html` 的时候，可以使用 HTTP 的重定向机制。即先发送 302 重定向响应，然后处理重定向后的 GET 请求。

4.   杀死tmux的会话

     ```bash
     # 使用session编号
     tmux kill-session -t 0
     ```

5.   闭包捕获 `[this, client_fd]`，什么是闭包捕获

6.   零拷贝技术 (Zero-copy)



## 知识点整理

### C++ 知识点

#### 1、`explicit` 关键字



#### 2、Containers library

Sequence containers：

Associative containers：

Unordered associate containers：



`queue` 和 `priority_queue`

`map` 和 `unordered_map`



#### 3、多线程和锁

`std::thread`

`std::mutex`

`std::condition_variable`

`std::atomic`



#### 4、`constexpr` 和 `const` 关键字

用 `constexpr`：

*   需要编译期确定的量（数组大小、模板参数等）
*   强制函数/对象在编译期可计算
*   性能敏感的常量计算

用 `const`：

*   运行时常量
*   函数参数/返回值的只读约束
*   类成员常量（非静态成员不能用 `constexpr`）

**最佳实践**：优先用 `constexpr` 表示编译期常量，用 `const` 表示运行时常量或接口约束。C++17 起 `constexpr` 可替代大部分 `const` 的编译期场景。



#### 5、`struct` 和 `class` 的区别

在 C++ 中，`struct` 和 `class` 都用于定义自定义数据类型，它们的核心功能几乎相同，主要区别在于**默认访问权限**和**默认继承方式**。

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

2.   默认继承方式不同

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



#### 6、`class` 相关的知识点

*   构造函数、移动构造函数、拷贝构造函数
*   析构函数
*   运算符重载



#### 7、匿名函数

基本语法

```cpp
[capture](parameters) -> return_type { 
    // 函数体 
}
```

基本示例

```cpp
// 无参Lambda
auto greet = []() {
    std::cout << "Hello, Lambda!";
};
greet(); // 输出: Hello, Lambda!

// 带参Lambda
auto add = [](int a, int b) {
    return a + b;
};
std::cout << add(3, 4); // 输出: 7
```

捕获外部变量
控制Lambda如何访问外部作用域的变量：

```cpp
int x = 10, y = 20;

// 按值捕获（复制变量）
auto copy = [x]() { 
    std::cout << x; // x=10（外部修改不影响内部）
};
x = 100; // 修改外部x
copy();  // 仍输出10

// 按引用捕获（直接操作外部变量）
auto ref = [&y]() { 
    y++; // 修改外部y
};
ref();
std::cout << y; // 输出21
```

捕获方式总结：

| 捕获形式  | 效果                       |
| --------- | -------------------------- |
| `[ ]`     | 不捕获任何变量             |
| `[=]`     | 按值捕获所有外部变量       |
| `[&]`     | 按引用捕获所有外部变量     |
| `[x, &y]` | 混合捕获（x按值，y按引用） |
| `[=, &y]` | 默认按值，但y按引用        |
| `[&, x]`  | 默认按引用，但x按值        |
| `[this]`  | 捕获当前对象指针           |

> ⚠️ 避免默认捕获（`[=]`/`[&]`），显式列出变量更安全！
> 最小捕获原则。



#### 8、回调函数

什么是回调函数？
回调函数（Callback Function）是一种**通过函数指针或函数对象传递的函数**，它会在特定事件发生时被调用。核心思想是："你调用我，我稍后调用你"。

Lambda表达式（现代C++推荐）

```cpp
void asyncOperation(std::function<void(int)> callback) {
    // 模拟耗时操作
    std::thread([callback]() {
        std::this_thread::sleep_for(1s);
        callback(100); // 完成后回调
    }).detach();
}

// 使用
asyncOperation([](int result) {
    std::cout << "Operation result: " << result;
});
```



#### 9、`size_t`、`sizeof()`、`typedef`

实际上，`size_t` 是个无符号整型，它并不是一个全新的数据类型，更不是一个关键字。`size_t` 是由 `typedef` 定义而来的，我们在很多标准库头文件中都能发现。

C 标准头文件`<stddef.h>`中可以找到`size_t`的实际定义。

通常用于：
(1) 表示对象大小和内存分配；
(2) 表示容器大小和索引；
(3) 内存和字符串操作；

为什么需要 `size_t`：
(1) **平台无关性**：自动适配不同架构（32位系统通常为 4 字节，64位系统为 8 字节）
(2) **足够大的表示范围**：能表示系统中最大可能对象的大小（包括整个内存空间）
(3) **类型安全**：区分普通整数和大小/索引值
(4) **标准化**：所有标准库容器和内存相关函数统一使用



#### 10、模板函数和模板类



#### 11、虚函数

##### C++ 虚函数详解

虚函数是C++实现**运行时多态**的核心机制，它允许派生类重写基类的函数实现，并通过基类指针或引用调用派生类的实现。

**定义方式**

在基类中使用 `virtual` 关键字声明函数：
```cpp
class Base {
public:
    virtual void func() {
        std::cout << "Base implementation\n";
    }
};
```

**重写规则**

派生类重写虚函数时：
- 函数签名必须完全相同（函数名、参数列表、返回类型）
- 可选的 `override` 关键字（C++11起）增强安全性
- 可选的 `virtual` 关键字（推荐省略）

```cpp
class Derived : public Base {
public:
    void func() override {  // 正确重写
        std::cout << "Derived implementation\n";
    }
};
```

**虚函数的工作原理**（虚函数表）

C++通过**虚函数表（vtable）** 实现多态：
1. 每个包含虚函数的类都有一个虚函数表
2. 表中存储指向该类虚函数的指针
3. 每个对象包含一个指向vtable的指针（vptr）
4. 调用虚函数时，通过vptr找到vtable，再调用对应的函数

```plaintext
+----------------+      +-----------------+
|    Base对象    |      | Base vtable     |
| +----------+  |      | +-------------+ |
| | vptr     |----->| | &Base::func | |
| +----------+  |      | +-------------+ |
+----------------+      +-----------------+

+-----------------+     +------------------+
|   Derived对象   |     | Derived vtable   |
| +------------+ |     | +--------------+ |
| | vptr       |---->| | &Derived::func| |
| +------------+ |     | +--------------+ |
+-----------------+     +------------------+
```

**虚函数的关键特性**

1. 运行时多态

```cpp
Base* obj = new Derived();
obj->func();  // 调用Derived::func()
```

2. 虚析构函数

当基类指针指向派生类对象时，必须将基类析构函数声明为虚函数：
```cpp
class Base {
public:
    virtual ~Base() {}  // 虚析构函数
};

class Derived : public Base {
public:
    ~Derived() override {}  // 派生类析构函数
};

Base* obj = new Derived();
delete obj;  // 正确调用Derived和Base的析构函数
```

3. 纯虚函数与抽象类

纯虚函数强制派生类实现特定接口：
```cpp
class Shape {  // 抽象类
public:
    virtual double area() const = 0;  // 纯虚函数
};

class Circle : public Shape {
public:
    double area() const override {
        return 3.14 * radius * radius;
    }
private:
    double radius;
};
```

##### 虚函数使用场景

1. **多态行为**：不同派生类对同一消息的不同响应
2. **框架设计**：定义通用接口，具体实现由派生类完成
3. **回调机制**：通过基类指针调用不同实现
4. **插件系统**：动态加载不同实现

##### 虚函数性能考虑

- 虚函数调用比普通函数调用稍慢（多一次指针间接访问）
- 每个对象增加一个指针大小的存储开销（vptr）
- 虚函数表本身占用少量内存
- 在性能关键代码中需谨慎使用

##### 虚函数最佳实践

1. **为多态基类声明虚析构函数**
2. **使用 `override` 关键字明确重写意图**
3. **考虑将不需要重写的函数声明为 `final`**
4. **避免在构造函数和析构函数中调用虚函数**
5. **合理使用纯虚函数定义接口契约**
6. **在性能敏感场景评估虚函数开销**

虚函数是C++面向对象编程的基石，正确理解和使用虚函数对于设计灵活、可扩展的软件架构至关重要。



#### 12、RAII (Resource Acquisition Is Initialization) 是什么？

**RAII（Resource Acquisition Is Initialization）** 是 C++ 的核心编程范式，直译为“资源获取即初始化”。它利用对象生命周期管理资源（如内存、文件句柄、网络连接等），确保资源安全获取和自动释放，避免泄漏。核心思想：**资源在构造函数中获取，在析构函数中释放**。

**核心原理**

1. **构造时获取资源**（Acquisition）
2. **析构时释放资源**（Release）
3. **对象生命周期绑定资源管理**

**典型应用场景**

```cpp
#include <iostream>
#include <fstream> // 标准库中的 RAII 范例

// 示例 1：文件操作（自动关闭）
void readFile() {
    std::ifstream file("data.txt"); // 构造时打开文件（获取资源）
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
} // 离开作用域时 file 析构 → 自动关闭文件（释放资源）

// 示例 2：内存管理（智能指针）
#include <memory>
void manageMemory() {
    auto ptr = std::make_unique<int>(42); // 构造时分配内存
    // 使用 ptr...
} // 离开作用域时 unique_ptr 析构 → 自动释放内存

// 示例 3：自定义锁管理
class MutexLock {
public:
    MutexLock(Mutex& m) : mutex(m) { mutex.lock(); } // 构造时加锁
    ~MutexLock() { mutex.unlock(); }                // 析构时解锁
private:
    Mutex& mutex;
};

void safeWrite() {
    Mutex m;
    {
        MutexLock lock(m); // 进入作用域时加锁
        // 临界区操作...
    } // 离开作用域时 lock 析构 → 自动解锁
}
```

**RAII 的核心优势**

| 优势             | 说明                           |
| ---------------- | ------------------------------ |
| **异常安全**     | 即使抛出异常，析构函数仍会调用 |
| **避免泄漏**     | 资源释放由编译器保证           |
| **简化代码**     | 无需手动释放资源               |
| **强资源所有权** | 资源与对象生命周期绑定         |

**与手动管理的对比**

```cpp
// 非 RAII 风格（危险！）
void unsafeExample() {
    int* arr = new int[100]; // 手动分配
    // ... 使用 arr
    delete[] arr; // 必须手动释放（可能忘记或因异常跳过）
}

// RAII 风格（安全）
void safeExample() {
    std::vector<int> arr(100); // 构造时分配
    // ... 使用 arr
} // 自动释放（即使抛出异常）
```

**RAII 的最佳实践**

1. **优先使用标准库工具**
   - 内存管理：`std::unique_ptr`, `std::shared_ptr`, `std::vector`
   - 文件处理：`std::ifstream`/`std::ofstream`
   - 线程同步：`std::lock_guard`

2. **自定义 RAII 类**
   - 构造函数获取资源（打开文件、分配内存、加锁）
   - 析构函数释放资源（关闭文件、释放内存、解锁）
   - 禁用复制/移动（或实现深拷贝/转移所有权）

3. **遵循规则三/五/零**
   - 管理资源时需正确处理拷贝/移动语义

> 📌 **关键结论**：RAII 是 C++ 区别于其他语言的核心特性，它通过对象生命周期自动化资源管理，是现代 C++ 避免资源泄漏的基石。几乎所有 C++ 标准库组件（容器、智能指针、流等）都基于 RAII 实现。



#### 13、左值引用和右值引用

在 C++ 中，**左值引用（lvalue reference）** 和 **右值引用（rvalue reference）** 是两种不同的引用类型，它们的主要区别在于 **绑定对象的类别（左值 or 右值）** 和 **用途（拷贝优化 or 资源转移）**。

**左值**是指既能出现在等号左边也能出现在等号右边的变量(或表达式)，**右值**则只能出现在等号右边。

*   **左值（lvalue）**：可以取地址、有名字的持久对象（如变量、函数返回的引用等）。
    **绑定到左值（lvalue）** 的引用，用 `&` 表示。

    ```cpp
    int x = 10;  
    int& lref = x;  // ✅ 左值引用绑定左值
    lref = 20;      // 修改 x 的值
    
    int& bad = 42;  // ❌ 错误：不能绑定到右值（临时对象）
    ```

*   **右值（rvalue）**：临时对象、即将销毁的对象（如字面量、`std::move` 后的对象）。
    **绑定到右值（rvalue）** 的引用，用 `&&` 表示。

    ```cpp
    int&& rref = 42;          // ✅ 右值引用绑定右值
    int x = 10;
    int&& rref2 = std::move(x);  // ✅ 使用 std::move 转为右值
    
    int&& bad = x;            // ❌ 错误：不能直接绑定左值
    ```



#### 14、函数重载和运算符重载

重载：函数名相同，参数列表不同。



#### 15、`std::map`

读取元素时，统一用 `at()`

写入元素时，统一用 `[]`

```cpp
std::map<std::string, int> m;
auto val = m.at("key1");  // 读
m["key2"] = val;  // 写
```



#### 16、浅拷贝与深拷贝

**浅拷贝（Shallow Copy）** 和 **深拷贝（Deep Copy）**



#### 17、OOP Design Patterns

>   Composite, Decorator, Bridge, Visitor, Proxy, Façade, ...
>   Iterator, Strategy, Observer, Command, Template Method, ...
>   Factory Method, Abstract Factory, Singleton, ...



#### 18、重写和重载

在 C++ 中，**override（重写）** 和 **overload（重载）** 是两个重要的概念，它们分别用于不同的场景，主要区别如下：

---

##### 1. 重载（Overload）
📌 定义

在**同一个作用域内**（如类内部或全局作用域），定义多个**同名函数**，但它们的**参数列表不同**（参数类型、个数或顺序不同）。返回类型可以相同也可以不同。

⚙️ 关键点

- **作用域**：同一个类或命名空间内  
- **函数签名**：**必须不同**（参数类型、数量或顺序）  
- **返回类型**：可以不同（但仅返回类型不同不足以构成重载）  
- **virtual**：不需要  
- **多态性**：编译时多态（静态绑定）

💡 用途

- 提供**功能类似但处理不同参数类型**的函数  
- 增强代码可读性和灵活性  
- 例如：同一个 `print` 函数处理 `int`、`double` 或 `string`

📝 示例

```cpp
class Printer {
public:
    // 重载示例：同名函数，参数不同
    void print(int i) {
        cout << "整数: " << i << endl;
    }
    
    void print(double f) {
        cout << "浮点数: " << f << endl;
    }
    
    void print(const string& s) {
        cout << "字符串: " << s << endl;
    }
};

Printer p;
p.print(10);       // 调用 print(int)
p.print(3.14);     // 调用 print(double)
p.print("Hello");  // 调用 print(string)
```

---

##### 2. 重写（Override）
📌 定义

在**派生类中重新实现基类**的虚函数（`virtual`），函数签名**必须完全相同**（包括参数列表、返回类型和 `const` 限定）。C++11 引入了 `override` 关键字显式标记。

⚙️ 关键点

- **作用域**：基类与派生类之间  
- **函数签名**：**必须完全相同**  
- **virtual**：基类函数必须声明为 `virtual`  
- **override 关键字**：显式声明重写（编译器会检查签名）  
- **多态性**：运行时多态（动态绑定）

💡 用途

- 实现**运行时多态**  
- 支持**接口继承**和**多态行为**  
- 例如：基类定义通用接口，派生类定制具体行为

📝 示例

```cpp
class Animal {
public:
    virtual void makeSound() const { // 基类虚函数
        cout << "动物叫声" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() const override { // 显式重写
        cout << "汪汪!" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override { // 显式重写
        cout << "喵喵!" << endl;
    }
};

// 多态调用
Animal* animal = new Dog();
animal->makeSound(); // 输出 "汪汪!"（动态绑定）
delete animal;
```

---

##### 常见错误与 `override` 的作用

如果不小心写错函数签名（如参数类型、`const` 修饰符），编译器会认为这是一个**新函数**而非重写，导致多态失效。使用 `override` 关键字可以强制编译器检查：
```cpp
class Base {
public:
    virtual void func(int) const {}
};

class Derived : public Base {
public:
    void func(int) override {}         // 错误：缺少 const 修饰符
    void func(double) const override;  // 错误：参数类型不匹配
};
```
编译器会直接报错，避免潜在问题。

---

##### 📊 对比总结
| 特性         | 重载（Overload）        | 重写（Override）               |
| ------------ | ----------------------- | ------------------------------ |
| **作用域**   | 同一作用域（类内/全局） | 派生类重写基类虚函数           |
| **函数签名** | 必须不同（参数列表）    | 必须完全相同                   |
| **virtual**  | 不需要                  | 基类函数必须为 `virtual`       |
| **关键字**   | 无                      | C++11 可用 `override` 显式标记 |
| **多态性**   | 编译时多态（静态绑定）  | 运行时多态（动态绑定）         |
| **目的**     | 处理不同类型参数        | 实现多态，定制派生类行为       |

---

##### ✅ 关键结论
- **重载**：解决**同名函数处理不同参数**的问题（静态多态）。  
- **重写**：实现**运行时多态**，是面向对象继承的核心机制。  
- **最佳实践**：  
  - 重写时始终使用 `override` 关键字避免错误。  
  - 基类析构函数应为 `virtual`（确保派生类对象正确释放）。



#### 19、`std::pair` 的用法和优势

`std::pair` 是一个简单但极其有用的工具，其核心优势在于：

1. **轻量高效**：零开销抽象
2. **通用性强**：适用于各种场景
3. **与 STL 深度集成**：容器和算法的关键组成部分
4. **类型安全**：编译时类型检查
5. **现代特性支持**：结构化绑定、移动语义等

使用场景建议：
- 需要返回两个值时 ➔ 替代输出参数
- 创建简单键值对 ➔ 替代简单结构体
- 需要临时组合数据 ➔ 避免定义临时结构
- 与 STL 算法配合 ➔ 利用内置比较操作

当需要组合超过两个值时，可升级到 `std::tuple`，但 `std::pair` 在二元数据组合场景中仍是最简洁高效的选择。



#### 20、`std::shared_ptr`

```cpp
mysql_connection *conn = mysql_connect("127.0.0.1");
mysql_execute(conn, "drop database paolu");
mysql_close(conn); // 用户可能忘记关闭连接！破坏库设计者想要的用法
```

shared_ptr 小妙招：构造函数的第二个参数可以指定释放函数，代替默认的 delete

```cpp
auto conn = std::shared_ptr<mysql_connection>(mysql_connect("127.0.0.1"), mysql_close);
mysql_execute(conn.get(), "drop database paolu");
// conn 离开作用域时，会自动调用 mysql_close，杜绝了一个出错的可能
```



### 数据结构

#### 1、小根堆

#### 2、循环数组



### 网络编程

#### 1、一次完整的 HTTP 请求过程：

DNS域名解析 $\to$ TCP 的 3 次握手 $\to$ 建立 TCP 连接，发送 HTTP 请求 $\to$ 服务器响应 HTTP 请求，返回 HTML 代码给浏览器 $\to$ 浏览器解析 HTML 代码并请求其中的资源 (CSS、JS、图片等) $\to$ 浏览器渲染页面呈现给用户

DNS 域名解析：[DNS域名详细解析过程(最全面，看这一篇就够)](https://blog.csdn.net/bangshao1989/article/details/121913780)

TCP 三次握手四次挥手：[简单理解TCP三次握手四次挥手（看一遍你就懂）](https://blog.csdn.net/m0_56649557/article/details/119492899)



#### 2、`epoll`





## 参考资料

[1] [从零开始实现C++ TinyWebServer 全过程记录](https://blog.csdn.net/weixin_51322383/article/details/130464403)，JehanRio's [TinyWebServer](https://github.com/JehanRio/TinyWebServer)

[2] [从零开始自制实现C++ High-Performance WebServer 全流程记录](https://love6.blog.csdn.net/article/details/123754194)

[3] [万字详解由C++14实现的Webserver](https://zhuanlan.zhihu.com/p/721880618)

[4] [【C++17】小彭老师陪你从零手搓HTTP服务器](https://www.bilibili.com/video/BV1Mz421i7Fm)

[5] [烂大街的WebServer分享一下](https://www.nowcoder.com/share/jump/1750039736048)

[6] [TinyWebServer](https://geekdaxue.co/read/qingyubailou@gygiq6/tihx6bwirgug3b9d)

[7] [用C++实现的高性能WEB服务器](https://blog.csdn.net/weixin_47243756/article/details/129494126)

[8] markparticle's [WebServer](https://github.com/markparticle/WebServer)

[9] [Tinywebserver——服务器常问面试题！](https://zhuanlan.zhihu.com/p/368154495)

[10] [一个简单的从零开始的Linux网络服务器项目过程](https://zhuanlan.zhihu.com/c_1774157245946933248)，HuangCheng72's [WebServer](https://github.com/HuangCheng72/WebServer)

[11] [基于Epoll的边缘触发（ET）模式下的回声服务器](https://www.yuque.com/lianlianfengchen-cvvh2/qkmqzb/foc1ba268rg4370x)
