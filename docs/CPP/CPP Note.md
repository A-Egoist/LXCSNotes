# C++ 笔记



[toc]



### 面向对象三大特性

面向对象编程（Object-Oriented Programming，简称 OOP）是一种编程范式，其核心思想是将现实世界中的事物抽象为程序中的对象。面向对象编程的三大特性是封装、继承和多态。下面将详细介绍这三个特性：

-   **继承（Inheritance）**： 继承是指一个类（子类）可以继承另一个类（父类）的属性和方法。子类除了拥有父类的特性外，还可以具有自己特有的属性和方法。这种方式可以实现代码的重用和模块化，减少重复代码的编写。继承有助于实现类之间的层次关系，并有助于理解和维护代码结构。
-   **封装（Encapsulation）**： 封装是指将数据和操作数据的方法包装在一起，形成一个独立的“对象”。这样的设计有助于降低系统的复杂性，提高可维护性。封装的主要目的是增强安全性，保护数据以免被外部代码随意访问和修改。为此，通常将对象的属性设为私有（private）或受保护（protected），并通过公共（public）方法（如 getter 和 setter 方法）来访问和修改这些属性。
-   **多态（Polymorphism）**： 多态是指允许不同类的对象对同一消息作出响应，即同一方法名可以在不同类中具有不同的实现。多态实现的主要方式有两种：接口实现和重写（覆盖）。



### 命名空间

```cpp
namespace MyNameSpace {
    int foo(int a, int b) {
        return a + b;
    }
};
```

```cpp
std::cout << MyNameSpace::foo(0, 1) << std::endl;
```



### 常量表达式和constexpr





## Class

### 构造函数(Constructor)
#### 默认构造函数(Default Constructor)

#### 带参数构造函数(Parameterized Constructor)

#### 拷贝构造函数(Copy Constructor)

```c++
MyTime::MyTime(MyTime &t){...}

int main()
{
    MyTime t1(1, 59);
    MyTime t2(t1);  // copy constructor
    MyTime t3 = t1;  // copy constructor
}
```

如果没有定义 copy constructor 编译器默认生成一个,  copy constructor 会复制所有非静态成员.

#### copy assignment constructor

```c++
MyTime &MyTime::operator=(MyTime &){...}

int main()
{
    MyTime t1(1, 59);
    MyTime t2 = t1;  // copy constructor
    t2 = t1;  // copy assignment
}
```

如果没有定义 copy assignment constructor 编译器默认生成一个, copy assignment constructor 会复制所有非静态成员.

#### 移动构造函数(Move Constructor)



### 类的继承

*   public 继承
*   protected 继承
*   private 继承

#### 定义不能被继承的类

在 C++ 中，要设计一个不能被继承的类，可以使用**关键字** `final`。将 `final` 关键字添加到类定义中，可以阻止其他类继承这个类。如果尝试继承带有 `final` 关键字的类，编译器将报错。

```cpp
class NonInheritable final {
public:
    // 类的成员和方法定义
};
```

`final` 关键字添加到类定义中，可以确保类不能被继承，从而实现类的封闭性。



### operator overloading

```c++
```

### friend function

```c++
```



## template





## 虚函数 (virtual functions)

虚函数（Virtual Function）是一种特殊的成员函数，主要用于实现多态（Polymorphism）。虚函数允许基类的指针或引用调用派生类的成员函数，从而实现了对函数的动态绑定。这种绑定方式使得程序在运行时根据对象的实际类型来选择调用哪个函数，提高了代码的可扩展性和维护性。

注意事项
- 构造函数不能为虚函数。
- 析构函数（Destructor）也应该声明为虚函数，这样可以确保在删除基类指针指向的派生类对象时，派生类的析构函数能够被正确调用，避免内存泄漏等问题。
- 如果基类的虚函数没有在派生类中覆盖，则在调用虚函数时会执行基类中的实现。
- 虚函数可以有默认实现，但也可以声明为纯虚函数（Pure Virtual Function）。纯虚函数在基类中没有实现，派生类必须覆盖这些函数。声明纯虚函数的方法是在函数声明后添加`= 0`。如果一个类包含至少一个纯虚函数，那么这个类就是抽象类（Abstract Class），不能直接实例化。

```cpp
#include <iostream>
#include <string>

# 包含至少一个纯虚函数，这个类为抽象类(Abstract Class)
class Base {
public:
    # 纯虚函数(Pure Virtual Function)
    virtual void pure_virtual_func() = 0;
}

class Person {
public:
    std::string name;
    Person(std::string n): name(n){}
    virtual void print() {
        std::cout << "Name: " << name << std::endl;
    }
};

class Student: public Person {
public:
    std::string id;
    Student(std::string n, std::string i): Person(n), id(i){}
    void print() override {
        std::cout << "Name: " << name << ". ID: " << id << std::endl;
    }
};

void printObjectInfo(Person &p) {
    p.print();
}

int main() {
    {
        Student stu("long", "2000");
        printObjectInfo(stu);
    }

    {
        Person *p = new Student("xing", "1225");
        p->print();
        delete p;
    }
    return 0;
}
```

[让虚函数再次伟大！](https://parallel101.github.io/cppguidebook/design_virtual/)

**总结**

带有虚函数（前面加入`virtual`）的类，编译器会为其分配一个虚函数表，里面记录的是虚函数的函数的地址。当该类被继承时，子类如果重写了虚函数就在子类的虚函数表中将父类的虚函数覆盖，否则继承父类的虚函数地址。

实例化之后，内存分配给对象虚函数指针+成员变量，虚函数指针指向虚函数表，这样程序运行的时候，通过虚函数指针找到虚函数表就是根据对象的类型来指向的，也就是实现了`运行时多态`。

### 多态

