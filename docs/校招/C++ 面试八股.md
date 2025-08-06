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
