# C++ 面试八股



## C++ 多态

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

[1] [史上最全C/C++面试、C++面经八股文，一文带你彻底搞懂C/C++面试、C++面经！](https://blog.csdn.net/songbijian/article/details/132507421)

[2] 
