# 从零开始实现C++ TinyWebServer



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

     [curl 的用法指南](https://www.ruanyifeng.com/blog/2019/09/curl-reference.html)

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

#### 3、多线程和锁

#### 4、`constexpr` 和 `const` 关键字

#### 5、`struct` 和 `class` 的区别

#### 6、`class` 相关的知识点

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

#### 13、左值引用和右值引用

#### 14、函数重载和运算符重载

重载：函数名相同，参数列表不同。



#### 15、`std::map`

#### 16、浅拷贝与深拷贝

#### 17、OOP Design Patterns

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

#### 20、`std::shared_ptr`



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
