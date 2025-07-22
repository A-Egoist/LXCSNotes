# CPP 笔记



模板元编程 (template)

```cpp
#include <iostream>
#include <vector>

template <class Ptr>
void print(Ptr begPtr, Ptr endPtr) {
    for (Ptr ptr = begPtr; ptr != endPtr; ptr ++) {
        auto value = *ptr;
        std::cout << value << std::endl;
    }
}

int main() {
    std::vector<char> a = {'h', 'i', 'j', 'k', 'l'};
    char const* aBegPtr = a.data();
    char const* aEndPtr = a.data() + a.size();
    print(aBegPtr, aEndPtr);
    std::vector<int> b = {1, 2, 3, 4, 5};
    int const* bBegPtr = b.data();
    int const* bEndPtr = b.data() + b.size();
    print(bBegPtr, bEndPtr);

    return 0;
}
```





自动类型推导 (auto)

```cpp

```

类成员不可以定义为 auto



### lambda 表达式

```cpp
#include <iostream>

int main()
{
    auto func = [] (int a) -> int {
        return a * 2;
    };
    std::cout << func(2) << std::endl;
    return 0;
}
```

只有一个`return`时，可以 lambda 表达式可以不通过`->`指定类型，和`-> auto`等价，自动根据函数体内的 `return` 语句决定返回类型，如果没有 `return` 语句，则相当于`-> void`。

lambda函数体重，还可以使用定义他的函数中的变量，只需要把`[]`改为`[&]`即可。

```cpp
#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;
    auto func = [&] () {
        return a + b;
    };
    std::cout << func() << std::endl;
    return 0;
}
```

函数可以引用定义位置所有的变量，这个特性在函数式编程中被称为闭包(closure)。

在使用`[&]`时需要保证lambda对象的生命周期不超过他所捕获的所有引用的寿命。

可以使用`[=]`来捕获值而不是引用，`[=]`会给每一个引用了的变量做一份拷贝。

lambda 作为参数：通常用 `[&]` 存储引用。

lambda 作为返回值：总是用 `[=]` 存储值。



### tuple

tuple 用于函数多个返回值

```cpp
#include <iostream>
#include <tuple>
#include <cmath>

std::tuple<bool, float> mysqrt(float x)
{
    if (x >= 0.f)
    {
        return {true, std::sqrt(x)};
    }
    else
    {
        return {false, 0.0f};
    }
}

int main()
{
    auto [success, value] = mysqrt(4.f);
    if (success)
    {
        printf("Succeed!, the result is %.2f\n", value);
    }
    else
    {
        printf("Failed, the input is lower than 0\n");
    }
    return 0;
}
```



乘法比除法更快，适当的优化表达式以减少除法的使用。

使用数学函数时需要加上`std::`，这才是CPP的数学函数，全局的数学函数是C语言的。

参数定义为常引用`void func(cconst& a){}`

编译器优化总结

>   1.   函数尽量写在同一个文件内
>   2.   避免在 for 循环内调用外部函数
>   3.   非 const 指针加上 __restrict 修饰
>   4.   试着用 SOA 取代 AOS
>   5.   对齐到 16 或 64 字节
>   6.   简单的代码，不要复杂化
>   7.   试试看 #pragma omp simd
>   8.   循环中不变的常量挪到外面来
>   9.   对小循环体用 #pragma unroll
>   10.   -ffast-math 和 -march=native

对函数来说，现在`inline`比较多余了，编译器会智能决定是否内联





const int* 和 int const* 的辩证：https://www.zhihu.com/question/443195492

推荐将`const`卸载类型右侧，比如`int const`，`std::string const`，`std::vector<int> const&`



std::map

std::unordered_map



:warning:避免使用`long`数据类型，因为在不同的平台`long`的位数不相同。

C语言`stdint.h`定义了(C++中是`cstdint`)：

```c
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
```

`size_t`表示大小的整数型，其等价于`uintptr_t`

在Modern C++中使用`nullptr`来表示空指针而不是`NULL`或者`0`

`for (int i = 0; i < n; i ++)`最好写为`for (size_t i = 0; i < n; i ++)`，记得`#include <cstdint>`

使用`new T[n]`分配的动态数组，请使用`delete[]`释放

使用`new T`分配的单个元素，请使用`delete`释放



堆栈的分配

栈：array

堆：vector、string



## C++ 标准库五大件

### Iterator（迭代器）

|                | **提供的运算符重载**                | **具有此迭代器的容器** | **相应的** **C++20 concept** |
| -------------- | ----------------------------------- | ---------------------- | ---------------------------- |
| 输入迭代器     | *（可读取），!=，==，++（一次性）   | istream_iterator       | input_iterator               |
| 输出迭代器     | *（可写入），!=，==，++（一次性）   | back_insert_iterator   | output_iterator              |
| 前向迭代器     | *，!=，==，++                       | forward_list           | forward_iterator             |
| 双向迭代器     | *，!=，==，++，--                   | set，map，list         | bidirectional_iterator       |
| 随机访问迭代器 | *，!=，==，++，--，+，-，+=，-=，[] | vector，array，deque   | random_access_iterator       |
| 迭代器外包装   | 和他所包装的迭代器保持一致          | reverse_iterator       | 和所包装的迭代器一致         |

包含关系：前向迭代器＞双向迭代器＞随机访问迭代器

这意味着如果一个STL模板函数（比如std::find）要求迭代器是**前向迭代器**即可，那么也可以给他随机访问迭代器，因为**前向迭代器**是**随机访问迭代器**的子集。

迭代器帮手函数

| **帮手函数**                 | **等价于**     |
| ---------------------------- | -------------- |
| it2  = std::next(it1, n)     | it2  = it1 + n |
| it2  = std::prev(it1, n)     | it2  = it1 - n |
| it2  = std::next(it1)        | it2  = it1 + 1 |
| it2  = std::prev(it1)        | it2  = it1 - 1 |
| std::advance(it1,  n)        | it1  += n      |
| std::advance(it1,  -n)       | it1  -= n      |
| n =  std::distance(it1, it2) | n =  it2 - it1 |



### Container（容器）

#### Vector

vector的`size`和`capacity`是分离的，并不是每次`push_back`都会改变`capacity`。（参考：[`std::vector` Size vs. Capacity](https://hackingcpp.com/cpp/lang/memory_basics.html)）

当`capacity`改变时，就是重新分配了一次内存，会将原来位置的数据copy到新的位置。

`clear`只是将`size`变为0

`shrink_to_fit()`将`capacity`缩回到`size`大小。

一对迭代器`begin`和`end`就标记了一个区间(range)，区间可以是一个容器的全部，例如`{a.being(), a.end()}`，也可以通过加减得到一个去头去尾的子列表，例如`{a.begin() +1, a.end() + 1}`，相当于python的`a[1:-1]`。



#### Set

Set是用红黑树实现的，内部的元素从小到大排序。

set中查询是否存在某个元素：

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> a = {1, 2, 3, 4, 5};
    if (a.find(6) != a.end()) {
        std::cout << "6 is in a" << std::endl;
    } else {
        std::cout << "6 is not in a" << std::endl;
    }

    if (a.find(2) != a.end()) {
        std::cout << "2 is in a" << std::endl;
    } else {
        std::cout << "2 is not in a" << std::endl;
    }
    return 0;
}
```

更短的用法是用`count`代替`find`

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> a = {1, 2, 3, 4, 5};
    if (a.count(6)) {
        std::cout << "6 is in a" << std::endl;
    } else {
        std::cout << "6 is not in a" << std::endl;
    }

    if (a.count(2)) {
        std::cout << "2 is in a" << std::endl;
    } else {
        std::cout << "2 is not in a" << std::endl;
    }
    return 0;
}
```



lower_bound 和 upper_bound 函数

lower_bound(x) 找第一个**大于等于** **x**的元素。

upper_bound(x) 找第一个**大于** **x**的元素。



将set转换为vector

```cpp
std::set<int> b = {0, 1, 2, 3, 4};
std::vector<int> arr(b.begin(), b.end());
```



给vector自动排序和去重：

```cpp
std::vector<int> arr = {9, 8, 5, 2, 1, 1};
std::set<int> b(arr.begin(), a.end());
arr.assign(b.begin(), b.end());
```



set的不去重版本：multiset



| **函数**       | **含义**                       | **set** | **multiset** | **unordered_set** |
| -------------- | ------------------------------ | ------- | ------------ | ----------------- |
| insert(x)      | 插入一个元素  x                | √       | √            | √                 |
| erase(x)       | 删除所有等于  x 的元素         | √       | √            | √                 |
| count(x)       | 有多少个等于  x 的元素         | √，0或1 | √            | √，0或1           |
| find(x)        | 指向第一个等于  x 的元素       | √       | √            | √                 |
| lower_bound(x) | 指向第一个大于等于  x 的元素   | √       | √            | ×                 |
| upper_bound(x) | 指向第一个大于  x 的元素       | √       | √            | ×                 |
| equal_range(x) | 所有等于  x 的元素所组成的区间 | √       | √            | √                 |



#### String

```
auto s1 = "seven of"s;  // type of s1 is std::string
```

| `R"(...)"`                            |                |       |
| ------------------------------------- | -------------- | ----- |
| `R"(raw "C"-string c:\users\joe)"`    | `char const[]` | C++11 |
| `R"(raw "std"-string c:\users\moe)"s` | `std::string`  | C++14 |

`std::getline`



`<cctype>`中的帮手函数

>   isupper(c) 判断是否为大写字母（‘A’ <= c && c <= ‘Z’）
>
>   islower(c) 判断是否为小写字母（‘a’ <= c && c <= ‘z’）
>
>   isalpha(c) 判断是否为字母（包括大写和小写）
>
>   isdigit(c) 判断是否为数字（‘0’ <= c && c <= ‘9’）
>
>   isalnum(c) 判断是否为字母或数字（包括字母和数字）
>
>   isxdigit(c) 判断是否为十六进制数字（0~9 或 a-f 或 A-F）
>
>   isspace(c) 判断是否为等价于空格的字符（‘ ’ 或 ‘\t’ 或 ‘\n’ 或 ‘\v’ 或 ‘\r’）
>
>   iscntrl(c) 判断是否为控制字符（0 <= c && c <= 31 或 c == 127）
>
>   toupper(c) 把小写字母转换为大写字母，如果不是则原封不动返回
>
>   tolower(c) 把大写字母转换为小写字母，如果不是则原封不动返回



C 语言规定，双引号包裹的字符串是 `const char *` 类型的

`using namespace std::literials` 可以使用 `"hello"s` 来定义string了

`<sstream>`中的`stringstream`

to_string模板：[【C++标准库】std::string用法指南&源码剖析](https://www.bilibili.com/video/BV1ja411M7Di/) 1:26:57

cout 有输出的精度，当需要输出高精度的数时(比如 3.14159265358)，需要使用`std::setprecision(100)`来设置精度





智能指针



### Memory

| Type      |      |      |
| --------- | ---- | ---- |
| Automatic |      |      |
| Dynamic   |      |      |
| Thread    |      |      |
| Static    |      |      |

Heap（堆）

Stack（栈）









使用`std::swap`来交换两个变量的值(`#include <utility>`)



`i++`和`++i`效果差不多，但是推荐使用`++i`，在使用迭代器时可以减少一些性能开销。



初始化列表

```cpp
int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    a.insert(a.begin(), {-3, -2, -1, 0});
    return 0;
}
```

其中`{1, 2, 3, 4, 5}`和`{-3, -2, -1, 0}`就是初始化列表，即`std::initializer_list<int>`，是`c++11`新增的内容。

C++中获取C数组的长度可以用`std::size(b)`，而不是`sizeof(b)/sizeof(b[0])`



`# pragma once`







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

#### 拷贝赋值构造函数(copy assignment constructor)

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

继承类型：

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



### 运算符重载(operator overloading)

```c++

```

### 友元函数(friend function)

```c++

```



## 模板(Template)

### 模板函数(Template Function)



### 模板类(Template Class)





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



## 参考资料

[1] [快速学习C和C++，基础语法和优化策略，学了不再怕指针(南科大计算机系原版)](https://www.bilibili.com/video/BV1Vf4y1P7pq), [GitHub](https://github.com/ShiqiYu/CPP)

[2] [合集·高性能并行编程与优化 - 录播](https://space.bilibili.com/263032155/channel/collectiondetail?sid=53025)

[3] [合集·现代C++项目实战](https://space.bilibili.com/263032155/channel/collectiondetail?sid=599074)

[4] [hacking C++](https://hackingcpp.com/)

[5] [学习路线](https://www.zhihu.com/collection/978731703)

[6] 



