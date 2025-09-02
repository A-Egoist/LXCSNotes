# CPP 基础



### 优化技巧

1.   乘法比除法更快，适当的优化表达式以减少除法的使用。

2.   使用数学函数时需要加上`std::`，这才是CPP的数学函数，全局的数学函数是C语言的。

3.   参数定义为常引用`void func(cconst& a){}`

4.   编译器优化总结

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

5.   对函数来说，现在`inline`比较多余了，编译器会智能决定是否内联

6.   const int* 和 int const* 的辩证：https://www.zhihu.com/question/443195492

7.   推荐将`const`写在类型右侧，比如`int const`，`std::string const`，`std::vector<int> const&`

8.   避免使用`long`数据类型，因为在不同的平台`long`的位数不相同。
     C语言`stdint.h`定义了(C++中是`cstdint`)：

     ```cpp
     typedef char int8_t;
     typedef short int16_t;
     typedef int int32_t;
     typedef long long int64_t;
     
     typedef unsigned char uint8_t;
     typedef unsigned short uint16_t;
     typedef unsigned int uint32_t;
     typedef unsigned long long uint64_t;
     ```

9.   `size_t` 表示大小的整数型，其等价于 `uintptr_t`

10.   在 Modern C++ 中使用 `nullptr` 来表示空指针而不是 `NULL` 或者 `0`
11.   `for (int i = 0; i < n; i ++)` 最好写为 `for (size_t i = 0; i < n; i ++)`，记得 `#include <cstdint>`
12.   使用 `new T[n]` 分配的动态数组，请使用 `delete[]` 释放
13.   使用 `new T` 分配的单个元素，请使用 `delete` 释放
14.   使用 `std::swap` 来交换两个变量的值(`#include <utility>`)
15.   `i++` 和 `++i` 效果差不多，但是推荐使用 `++i`，在使用迭代器时可以减少一些性能开销。
16.   C++中获取C数组的长度可以用`std::size(b)`，而不是`sizeof(b)/sizeof(b[0])`
17.   `# pragma once` 是一个**非标准**的但广泛支持的预处理指令，它告诉编译器该头文件在单个编译过程中只应被包含一次。编译器在第一次遇到 `#pragma once` 时会记住该文件名，并在后续的包含操作中忽略它。
18.   使用预处理指令防止头文件被重复包含（也称为“头文件保护”或“包含卫士”）：`#ifndef`，`#define`，`#endif`
      ```cpp title="example.h"
      #ifndef EXAMPLE_H
      #define EXAMPLE_H
      
      class MyClass {
      public:
          MyClass(); // 构造函数声明
          void myFunction(); // 成员函数声明
      };
      
      #endif
      ```

19.   拷贝并交换
      ```cpp
      // 拷贝赋值运算符
      shared_ptr& operator=(shared_ptr other) { // 注意：这里参数是按值传递
          // 'other' 是通过拷贝构造函数创建的临时副本。
          // 在这行代码之前，'other' 已经拥有了正确增加的引用计数，并安全地拥有了资源。
          
          // std::swap 是原子的，且无异常抛出。
          // 我们交换了两个智能指针的内部状态。
          std::swap(ptr_, other.ptr_);
          std::swap(ref_count_, other.ref_count_);
          std::swap(mtx_, other.mtx_);
      
          // 当 'other' 离开作用域时，其析构函数会自动释放旧的资源。
          return *this;
      }
      ```

      “拷贝并交换”模式如此强大的原因：它巧妙地利用了**构造函数是安全初始化**这个基本特性，将赋值操作中复杂的资源管理（释放旧资源，获取新资源）工作，安全地委托给了编译器自动调用的**拷贝构造函数**和函数结束时自动调用的**析构函数**。



堆栈的分配

栈：array

堆：vector、string



### 匿名函数(Lambda Function)

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



#### 基本语法

```cpp
[capture](parameters) -> return_type { 
    // 函数体 
}
```

#### 基本示例

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

#### 捕获外部变量

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

> :warning:避免默认捕获（`[=]`/`[&]`），显式列出变量更安全！
> 最小捕获原则。



### 类型转换

`static_cast<T*>`

## STL

详见：[STL](./STL.md)

### Container（容器）

#### `std::vector`

vector的`size`和`capacity`是分离的，并不是每次`push_back`都会改变`capacity`。（参考：[std::vector Size vs. Capacity](https://hackingcpp.com/cpp/lang/memory_basics.html)）

当`capacity`改变时，就是重新分配了一次内存，会将原来位置的数据copy到新的位置。

`clear()`只是将`size`变为0

`shrink_to_fit()`将`capacity`缩回到`size`大小。

一对迭代器`begin()`和`end()`就标记了一个区间(range)，区间可以是一个容器的全部，例如`{a.being(), a.end()}`，也可以通过加减得到一个去头去尾的子列表，例如`{a.begin() +1, a.end() + 1}`，相当于python的`a[1:-1]`。



#### `std::list`



#### `std::string`

```cpp
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



#### `std::stack`



#### `std::queue`



#### `std::set`

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



#### `std::map`



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

这意味着如果一个STL模板函数（比如`std::find`）要求迭代器是**前向迭代器**即可，那么也可以给他随机访问迭代器，因为**前向迭代器**是**随机访问迭代器**的子集。

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



### Memory

| Type      |      |      |
| --------- | ---- | ---- |
| Automatic |      |      |
| Dynamic   |      |      |
| Thread    |      |      |
| Static    |      |      |

Heap（堆）

Stack（栈）





初始化列表

```cpp
int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    a.insert(a.begin(), {-3, -2, -1, 0});
    return 0;
}
```

其中`{1, 2, 3, 4, 5}`和`{-3, -2, -1, 0}`就是初始化列表，即`std::initializer_list<int>`，是`c++11`新增的内容。



## 面向对象编程

面向对象编程（Object-Oriented Programming，简称 OOP）是一种编程范式，其核心思想是将现实世界中的事物抽象为程序中的对象。面向对象编程的三大特性是封装、继承和多态。下面将详细介绍这三个特性：

-   **继承（Inheritance）**： 继承是指一个类（子类）可以继承另一个类（父类）的属性和方法。子类除了拥有父类的特性外，还可以具有自己特有的属性和方法。这种方式可以实现代码的重用和模块化，减少重复代码的编写。继承有助于实现类之间的层次关系，并有助于理解和维护代码结构。
-   **封装（Encapsulation）**： 封装是指将数据和操作数据的方法包装在一起，形成一个独立的“对象”。这样的设计有助于降低系统的复杂性，提高可维护性。封装的主要目的是增强安全性，保护数据以免被外部代码随意访问和修改。为此，通常将对象的属性设为私有（private）或受保护（protected），并通过公共（public）方法（如 getter 和 setter 方法）来访问和修改这些属性。
-   **多态（Polymorphism）**： 多态是指允许不同类的对象对同一消息作出响应，即同一方法名可以在不同类中具有不同的实现。多态实现的主要方式有两种：接口实现和重写（覆盖）。



面向对象的设计模式(OOP Design Patterns)

>   Composite, Decorator, Bridge, Visitor, Proxy, Façade, ...
>   Iterator, Strategy, Observer, Command, Template Method, ...
>   Factory Method, Abstract Factory, Singleton, ...



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



### 变量作用域

在C++中，变量作用域（Scope）指的是程序中变量可以被访问的代码区域。作用域决定了变量的生命周期和可见性。

1.  **全局作用域**：在函数外部声明的变量具有全局作用域。它们可以在程序的任何地方被访问，但通常建议在需要时才使用全局变量，因为它们可能导致代码难以理解和维护。
2.  **局部作用域**：在函数内部、代码块（如`if`语句、`for`循环等）内部声明的变量具有局部作用域。它们只能在声明它们的代码块内被访问。一旦离开该代码块，这些变量就不再可见。
3.  **命名空间作用域**：在命名空间中声明的变量（实际上是实体，如变量、函数等）具有命名空间作用域。它们只能在相应的命名空间内被直接访问，但可以通过使用命名空间的名称作为前缀来从外部访问。
4.  **类作用域**：在类内部声明的成员变量和成员函数具有类作用域。成员变量和成员函数可以通过类的对象来访问，或者在某些情况下（如静态成员）可以通过类名直接访问。
5.  **块作用域**：这是局部作用域的一个特例，指的是由大括号`{}`包围的代码块内部声明的变量。这些变量只能在该代码块内被访问。



### 变量生命周期

-   自动存储周期（栈上） - 函数的局部变量，自动析构
-   动态存储周期（堆上） - 通过 new 创建的变量，delete 时析构
-   静态存储周期（static 和 inline） - 全局变量，程序结束时析构



### 存储区域

在C++中，内存存储通常可以大致分为几个区域，这些区域根据存储的数据类型、生命周期和作用域来划分。这些区域主要包括：

1.  代码区（Code Segment/Text Segment）
    *   存储程序执行代码（即机器指令）的内存区域。这部分内存是共享的，只读的，且在程序执行期间不会改变。
    *   举例说明：当你编译一个C++程序时，所有的函数定义、控制结构等都会被转换成机器指令，并存储在代码区。
2.  全局/静态存储区（Global/Static Storage Area）
    *   存储全局变量和静态变量的内存区域。这些变量在程序的整个运行期间都存在，但它们的可见性和生命周期取决于声明它们的作用域。
    *   举例说明：全局变量（在函数外部声明的变量）和静态变量（使用`static`关键字声明的变量，无论是在函数内部还是外部）都会存储在这个区域。
3.  栈区（Stack Segment）
    *   存储局部变量、函数参数、返回地址等的内存区域。栈是一种后进先出（LIFO）的数据结构，用于存储函数调用和自动变量。
    *   举例说明：在函数内部声明的变量（不包括静态变量）通常存储在栈上。当函数被调用时，其参数和局部变量会被推入栈中；当函数返回时，这些变量会从栈中弹出，其占用的内存也随之释放。
4.  堆区（Heap Segment）
    *   由程序员通过动态内存分配函数（如`new`和`malloc`）分配的内存区域。堆区的内存分配和释放是手动的，因此程序员需要负责管理内存，以避免内存泄漏或野指针等问题。
    *   举例说明：当你使用`new`操作符在C++中动态分配一个对象或数组时，分配的内存就来自堆区。同样，使用`delete`操作符可以释放堆区中的内存。
5.  常量区（Constant Area）
    *   存储常量（如字符串常量、const修饰的全局变量等）的内存区域。这部分内存也是只读的，且通常在程序执行期间不会改变。
    *   举例说明：在C++中，使用双引号括起来的字符串字面量通常存储在常量区。此外，使用`const`关键字声明的全局变量，如果其值在编译时就已确定，也可能存储在常量区。



## Class

[类面试常见问题](https://gitbookcpp.llfc.club/sections/cpp/base/cppbase21.html)

### 构造函数(Constructor)

详见：[Class](./Class.md)

```cpp
#include <iostream>
#include <utility> // 包含 std::move

class MyClass {
public:
    // 默认构造函数(Default Constructor)
    MyClass() : value_(0), ptr_(nullptr) {
        std::cout << "Default constructor called." << std::endl;
    }
    
    // 带参构造函数(Parameterized Constructor)
    MyClass(int value) : value_(value), ptr_(nullptr) {
        std::cout << "Parameterized constructor (int) called." << std::endl;
    }
    
    // 带参构造函数(Parameterized Constructor)
    MyClass(int value, int* ptr) : value_(value), ptr_(ptr) {
        std::cout << "Parameterized constructor (int, int*) called." << std::endl;
    }
    
    // 拷贝构造函数(Copy Constructor)
    MyClass(const MyClass &other) : value_(other.value_), ptr_(other.ptr_) {
        std::cout << "Copy constructor called." << std::endl;
    }
    
    // 拷贝赋值运算符(Copy Assignment Operator)
    MyClass& operator=(const MyClass &other) {
        std::cout << "Copy assignment operator called." << std::endl;
  
        // 防止自我赋值
        if (this == &other) return *this;
        value_ = other.value_;
        ptr_ = other.ptr_;
        
        return *this;
    }
    
    // 移动构造函数(Move Constructor)
    MyClass(MyClass&& other) noexcept
        : value_(other.value_), ptr_(other.ptr_) {
            std::cout << "Move constructor called." << std::endl;
            other.value_ = 0;
            other.ptr_ = nullptr;
        }
    
    // 移动赋值运算符(Move Assignment Operator)
    MyClass& operator=(MyClass&& other) noexcept {
        std::cout << "Move assignment operator called." << std::endl;
        
        // 防止自我赋值
        if (this == &other) return *this;
        value_ = other.value_;
        ptr_ = other.ptr_;
        
        other.value_ = 0;
		other.ptr_ = nullptr;
        
        return *this;
    }
    
private:
    int value_;
    int* ptr_;
};

int main() {
    std::cout << "-------------------------------\n";
    std::cout << "1\n";
    MyClass a(12);  // 调用带参构造函数
    std::cout << "-------------------------------\n";
    std::cout << "2\n";
    MyClass b = a;  // 调用拷贝构造函数，等价于 MyClass b(a);
    std::cout << "-------------------------------\n";
    std::cout << "3\n";
    MyClass c;  // 调用默认构造函数
    c = a;  // 调用拷贝赋值运算符
    std::cout << "-------------------------------\n";
    std::cout << "4\n";
    MyClass d = std::move(a);  // 调用移动构造函数
    std::cout << "-------------------------------\n";
    std::cout << "5\n";
    MyClass e;  // 调用默认构造函数
    e = std::move(b);  // 调用移动赋值运算符
    std::cout << "-------------------------------\n";
    
    return 0;
}
```

它们各自的目的：

-   **默认构造函数：** 在不提供参数时创建对象。
-   **带参构造函数：** 允许在创建对象时用特定值初始化成员。
-   **拷贝构造函数：** 用一个已有的对象**初始化**一个新对象。
-   **拷贝赋值运算符：** 将一个已有的对象**赋值**给另一个已有的对象。
-   **移动构造函数：** “窃取”一个临时对象（或即将被销毁的对象）的资源，避免昂贵的深拷贝。
-   **移动赋值运算符：** 将一个临时对象的资源**赋给**一个已有的对象。

区分**初始化**（通过构造函数）和**赋值**（通过赋值运算符）是理解这些概念的关键。

如果没有定义拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符编译器默认生成。

如果不想要编译器默认生成，需要使用 `= delete`，比如：

```cpp
class MyClass {
public:
    // 默认构造函数(Default Constructor)
    MyClass() : value_(0), ptr_(nullptr) {
        std::cout << "Default constructor called." << std::endl;
    }
    
    // 带参构造函数(Parameterized Constructor)
    MyClass(int value) : value_(value), ptr_(nullptr) {
        std::cout << "Parameterized constructor (int) called." << std::endl;
    }
    
    // 带参构造函数(Parameterized Constructor)
    MyClass(int value, int* ptr) : value_(value), ptr_(ptr) {
        std::cout << "Parameterized constructor (int, int*) called." << std::endl;
    }
    
    // 拷贝构造函数(Copy Constructor)
    MyClass(const MyClass &other) = delete;
    
    // 拷贝赋值运算符(Copy Assignment Operator)
    MyClass& operator=(const MyClass &other) = delete;
    
    // 移动构造函数(Move Constructor)
    MyClass(MyClass&& other) = delete;
    
    // 移动赋值运算符(Move Assignment Operator)
    MyClass& operator=(MyClass&& other) = delete;
    
private:
    int value_;
    int* ptr_;
};
```



#### Rule of Three/Five (三/五法则)

1.  **Rule of Three (C++98/03)：** 如果一个类需要显式地定义以下其中一项：
    *   **析构函数 (Destructor)**
    *   **拷贝构造函数 (Copy Constructor)**
    *   **拷贝赋值运算符 (Copy Assignment Operator)**
        那么它很可能也需要显式地定义**全部三项**。
        **为什么？** 这通常意味着你的类正在管理某种资源（动态内存、文件句柄、网络连接、锁等）。编译器生成的默认拷贝操作（浅拷贝）对于资源管理类通常是错误的，会导致双重释放、资源泄漏等问题。如果你定义了析构函数来释放资源，就必须确保拷贝操作也能正确处理资源（通常是深拷贝或禁止拷贝）。

2.  **Rule of Five (C++11 及以后)：** 在 Rule of Three 的基础上，增加了对移动语义的支持。如果一个类需要显式地定义以下其中一项：
    *   析构函数
    *   拷贝构造函数
    *   拷贝赋值运算符
    *   **移动构造函数 (Move Constructor)**
    *   **移动赋值运算符 (Move Assignment Operator)**
        那么它很可能也需要显式地定义**全部五项**（或者仔细考虑哪些需要定义，哪些需要删除 `=delete`，哪些可以用默认 `=default`）。
        **为什么？** 移动语义允许高效地“窃取”资源。如果你定义了析构函数（表明管理资源），并且你希望你的类支持高效的移动操作（而不是回退到拷贝），那么你需要定义移动构造和移动赋值来正确地转移资源所有权。同时，你也需要确保拷贝操作的行为是正确的（深拷贝或禁止）。



### 析构函数

:warning:**虚类的析构函数必须是虚的**

:warning:**析构函数的逆天大坑**

定义了析构函数，就**必须删除移动构造函数、移动赋值函数、拷贝构造函数、拷贝赋值函数**！

原因很复杂，整个故事要从 boost 当年如何设计出右值引用到图灵的停机问题讲起，讲了你也记不住，只需要记住结论：

如果你要定义析构函数，就**必须删除移动构造函数、移动赋值函数、拷贝构造函数、拷贝赋值函数**！



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



## 运算符重载(operator overloading)

### 运算符重载的方法

在C++中，运算符可以通过成员函数或非成员函数（通常是友元函数）来重载。

#### 成员函数方式

运算符作为类的成员函数进行重载时，左操作数是当前对象（`this`）。因此，对于需要修改左操作数的运算符，成员函数方式通常更直观。

```cpp
class ClassName {
public:
    ClassName operator+(const ClassName& other);
};
```



#### 非成员函数方式(友元函数)

当需要对两个不同类型的对象进行运算，或者左操作数不是当前类的对象时，通常使用非成员函数方式。为了访问类的私有成员，非成员函数通常被声明为类的友元函数。

```c++
class ClassName {
    friend ClassName operator+(const ClassName* lhs, const ClassName& rhs);
};
```



#### 示例

```cpp title="Complex.cpp"
#include <iostream>

class Complex {
public:
    // 构造函数
    Complex(double real = 0.0, double imag = 0.0) : real_(real), imag_(imag) {}
    // 重载 "+" 运算符(成员函数)
    Complex operator+(const Complex& other) const {
        return Complex(this->real_ + other.real_, this->imag_ + other.imag_);
    }
    // 重载 "<<" 运算符用于输出
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real_;
        if (c.imag_ >= 0) os << " + " << c.imag_ << "i)";
        else os << " - " << -c.imag_ << "i)";
        return os;
    }
private:
    double real_;
    double imag_;
};

int main() {
    Complex c1(3.0, 2.0);
    Complex c2(1.5, -2.5);
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    return 0;
}
```

更多内容请见：[https://gitbookcpp.llfc.club/sections/cpp/base/cppbase30.html](https://gitbookcpp.llfc.club/sections/cpp/base/cppbase30.html)

## 模板(Template)

使用

```cpp
template <typename T>
```

或

```cpp
template <class T>
```

### 模板基础

#### 模板函数(Template Function)

```cpp
template <typename T>
T Vector3<T>::getMax() {
    T temp = m_vec[0] > m_vec[1] ? m_vec[0] : m_vec[1];
    return temp > m_vec[2] ? temp : m_vec[2];
}
```



#### 模板类(Template Class)

```cpp
template <typename T>
class Vector3 {
public:
    Vector3(T v1, T v2, T v3) {
        m_vec[0] = v1;
        m_vec[1] = v2;
        m_vec[2] = v3;
    }
    T getMax();
private:
    T m_vec[3];
};
```

### 模板参数

#### 类型参数



#### 非类型参数



#### 模板模板参数



其他更多模板内容请见：[https://gitbookcpp.llfc.club/sections/cpp/base/cppbase31.html](https://gitbookcpp.llfc.club/sections/cpp/base/cppbase31.html)



## RAII

**RAII（Resource Acquisition Is Initialization）** 是 C++ 的核心编程范式，直译为“资源获取即初始化”。它利用对象生命周期管理资源（如内存、文件句柄、网络连接等），确保资源安全获取和自动释放，避免泄漏。核心思想：**资源在构造函数中获取，在析构函数中释放**。

### 核心原理

1. 构造时获取资源（Acquisition）
2. 析构时释放资源（Release）
3. 对象生命周期绑定资源管理

### 典型应用场景

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

### RAII 的核心优势

| 优势             | 说明                           |
| ---------------- | ------------------------------ |
| **异常安全**     | 即使抛出异常，析构函数仍会调用 |
| **避免泄漏**     | 资源释放由编译器保证           |
| **简化代码**     | 无需手动释放资源               |
| **强资源所有权** | 资源与对象生命周期绑定         |

### 与手动管理的对比

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

### **RAII 的最佳实践**

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



## 虚函数 (virtual functions)

虚函数（Virtual Function）是一种特殊的成员函数，主要用于实现多态（Polymorphism）。虚函数允许基类的指针或引用调用派生类的成员函数，从而实现了对函数的动态绑定。这种绑定方式使得程序在运行时根据对象的实际类型来选择调用哪个函数，提高了代码的可扩展性和维护性。

注意事项

- 构造函数不能为虚函数。
- 析构函数（Destructor）也应该声明为虚函数，这样可以确保在删除基类指针指向的派生类对象时，派生类的析构函数能够被正确调用，避免内存泄漏等问题。
- 如果基类的虚函数没有在派生类中覆盖(override)，则在调用虚函数时会执行基类中的实现。
- 虚函数可以有默认实现，但也可以声明为纯虚函数（Pure Virtual Function）。纯虚函数在基类中没有实现，派生类必须覆盖这些函数。声明纯虚函数的方法是在函数声明后添加`= 0`。<mark>如果一个类包含至少一个纯虚函数，那么这个类就是抽象类（Abstract Class），不能直接实例化。</mark>

```cpp
#include <iostream>
#include <string>

// 包含至少一个纯虚函数，这个类为抽象类(Abstract Class)
class Base {
public:
    virtual ~Base() = default;  // 基类添加虚析构函数
    // 纯虚函数(Pure Virtual Function)
    virtual void pure_virtual_func() = 0;
};

class Person {
public:
    virtual ~Person() = default;
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





## 并行编程

详见：[并行编程](./并行编程.md)



## 泛型编程

详见：[泛型编程](./泛型编程.md)



## 内存管理

详见：[内存管理](./内存管理.md)



## 设计模式

详见：[常用的设计模式](./常用的设计模式.md)



## 拾遗

### `explicit` 关键字



### `noexcept` 关键字



### Containers library

Sequence containers：

Associative containers：

Unordered associate containers：



`queue` 和 `priority_queue`

`map` 和 `unordered_map`



### 构造函数

默认构造函数

自定义构造函数

拷贝构造函数

移动构造函数





### 构造函数和析构函数的调用顺序

```cpp
#include <iostream>
struct A {
    A()  { std::cout << "A ctor\n"; }
    ~A() { std::cout << "A dtor\n"; }
};

struct B {
    B()  { std::cout << "B ctor\n"; }
    ~B() { std::cout << "B dtor\n"; }
};

struct C : public A {
    B b;
    C()  { std::cout << "C ctor\n"; }
    ~C() { std::cout << "C dtor\n"; }
};

int main() {
    C c;
}
```

运行结果：

```cpp
A ctor   // 先构造基类 A
B ctor   // 然后构造成员 b
C ctor   // 最后执行派生类 C 自己的构造体
C dtor   // 析构时先执行 C 的析构体
B dtor   // 再析构成员 b
A dtor   // 最后析构基类 A
```

总结：

-   **构造**：先基类 → 再成员 → 再派生类自己。
-   **析构**：先派生类自己 → 再成员 → 再基类。
-   这就是 C++ 的对象构造/析构模型，和你理解的一样，只是还有“成员变量”和“虚基类”的顺序需要注意。



### 联合体

联合体的内存对齐和结构体的内存对齐



### 友元函数



### `constexpr` 和 `const` 关键字

用 `constexpr`：

*   需要编译期确定的量（数组大小、模板参数等）
*   强制函数/对象在编译期可计算
*   性能敏感的常量计算

用 `const`：

*   运行时常量
*   函数参数/返回值的只读约束
*   类成员常量（非静态成员不能用 `constexpr`）

**最佳实践**：优先用 `constexpr` 表示编译期常量，用 `const` 表示运行时常量或接口约束。C++17 起 `constexpr` 可替代大部分 `const` 的编译期场景。



### `size_t`、`sizeof()`、`typedef`

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



### `struct` 和 `class` 的区别

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



### (`new`) V.S. (`::operator new` && `placement new`)

#### `new`

当使用普通的 `new` 的时候，会做两件事情：

1.   分配内存（调用 `operator new`，从堆上拿空间）；
2.   调用构造函数（用传入的参数构造对象）；

内存分配和对象构造是在一起的。

但是有的时候我们并不希望内存分配和对象构造在一起执行，比如我们在 `std::vector` 中，我们会申请 `capacity_ * sizeof(T)` 的空间来存储类型 T 的对象，但是我们并不希望在申请空间的时候就初始化这些空间，而是在调用 `push_back()` 或者 `emplace_back()` 才实际构造元素。所以我们需要将内存分配和对象构造分离，这就需要使用到 `::operator new` 和 `placement new` 了。

#### `::operator new` && `placement new`

使用 `::operator new` 和 `placement new` 需要先导入头文件：
```cpp
#include <new>
```

在[自己动手实现vector容器](../Projects/自己动手实现vector容器.md)中，我使用 `::operator new` 来进行内存分配，返回类型是 `void*`，所以需要使用 `static_cast<T*>` 进行类型转换，分配的内存大小为 `capacity * sizeof(T)`。
```cpp
// ::operator new(元素数量 * sizeof(元素类型));
T* allocate(size_t capacity) {
    return static_cast<T*>(::operator new(capacity * sizeof(T)));
}
```

>   :warning: `::operator new(数量 * sizeof(类型))`  好 `::operator new[](数量 * sizeof(类型))` 的区别，更推荐使用 `::operator new(数量 * sizeof(类型))`，避免不必要的开销。

然后又实现了 `emplace_back()` 函数用于在用户调用 `push_back` 或者 `emplace_back()` 的时候实际构造对象：

```cpp
// new (地址) T(arg1, arg2, ...);
new (data_ + size_) T(std::forward<Args>(args)...);
```

对应的，在使用 `::operator new` 和 `placement new` 之后，在析构对象和释放内存的时候也需要手动调用：
```cpp
// 清空 vector，但不释放内存
void clear() {
    for (int i = 0; i < size_; ++ i) {
        // 对应非 POD 类型，需要显式调用每个元素的析构函数
        data_[i].~T();  // 调用元素的析构函数
    }
    size_ = 0;
}
```

```cpp
    // 内存释放
    void deallocate() {
        ::operator delete(data_);
        data_ = nullptr;
        capacity_ = 0;
    }
```



### 左值引用和右值引用

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



### 万能引用



### `std::forward`



### 完美转发 (Perfect Forwarding) 

完美转发是一种在**模板函数**中保持参数的**值类别（左值或右值）**的能力。当一个函数模板接收参数并将其转发给另一个函数时，我们希望原始参数的左值/右值属性能够得到保留。

这主要通过以下两个特性实现：

-   **万能引用 (Universal References) / 转发引用 (Forwarding References)**：当模板参数形如 `T&&`，并且 `T` 是一个推导的模板参数时（例如 `template <typename T> void foo(T&& arg)`），`T&&` 就不再仅仅是右值引用，它会根据传入参数的类型表现出两种行为：
    -   如果传入的是**左值**，`T` 会被推导为 `Type&` (一个左值引用类型)，那么 `Type& &&` 经过引用折叠后变为 `Type&` (左值引用)。
    -   如果传入的是**右值**，`T` 会被推导为 `Type` (一个非引用类型)，那么 `Type&&` 保持为 `Type&&` (右值引用)。 因此，`T&&` 能够“万能地”接收左值和右值。
-   **`std::forward<T>(arg)`**：这是完美转发的核心工具。它是一个条件性转换：
    -   如果 `arg` 最初是**左值**，`std::forward` 会将其转换回**左值引用**（`Type& &&` 折叠为 `Type&`）。
    -   如果 `arg` 最初是**右值**，`std::forward` 会将其转换为**右值引用**（`Type&&` 保持为 `Type&&`）。

这样，`std::forward` 确保了参数在转发过程中保持其原始的值类别。

**代码示例**

```cpp
#include <iostream>
#include <string>
#include <utility>

void real_func(const std::string& s) {
    std::cout << "左值版本: " << s << "\n";
}

void real_func(std::string&& s) {
    std::cout << "右值版本: " << s << "\n";
}

template <typename T>
void wrapper(T&& arg) { // 万能引用
    // 完美转发
    real_func(std::forward<T>(arg));
}

int main() {
    std::string s = "hello";
    wrapper(s);  // 左值调用
    wrapper(std::string("world"));  // 右值调用
}
```

**常见应用场景**

1.  **容器的 `emplace` 系列**
     `std::vector::emplace_back` 用完美转发把参数直接传给元素构造函数，避免临时对象。

2.  **工厂函数**

    ```
    template <typename T, typename... Args>
    std::unique_ptr<T> make_smart(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
    ```

3.  **通用封装 / 装饰器模式**

    -   例如包装一个日志函数，然后把参数“完美转发”到真实逻辑函数。



### 可变参数模板（variadic templates）

```cpp
// 完美转发
template <typename... Args>
T& emplace_back(Args&&... args) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    new (data_ + size_) T(std::forward<Args>(args)...);  // 完美转发
    return data_[size_ ++];
}
```

在如上完美转发的代码中，使用到了 可变参数模板（variadic templates） 和 参数包展开（parameter pack expansion）。

具体来说：

#### 1. `template <typename... Args>` — 定义参数包

-   `...` 在类型名后面（`typename... Args`）表示 **Args 是一个类型参数包**，可以代表任意多个类型：

    ```cpp
    Args = {int, double, std::string} // 可能的情况
    Args = {std::string}              // 也可以是一个
    Args = {}                         // 甚至可以是空
    ```

-   就好像 `Args` 是一个**类型列表**。

#### 2. `Args&&... args` — 万能引用的参数包

-   `args` 是一个**参数包变量**，里面有多个参数，每个参数类型对应 `Args` 里的一个类型。
-   因为是 `Args&&` 并且 `Args` 是模板参数，所以这里是 **万能引用参数包**，可以同时接收：
    -   任意数量的左值
    -   任意数量的右值
    -   任意混合的左值和右值

#### 3. `std::forward<Args>(args)...` — 参数包展开

-   最后的 `...` 是 **展开操作**（pack expansion）。
-   作用：把 `args` 里的多个参数，依次用 `std::forward` 转发，然后按顺序展开成实参列表。
-   如果你去掉 `...`，编译器会说它不知道怎么把一整个包传给构造函数，因为构造函数是期望**多个参数**，而不是一个“包对象”。

例子：

```cpp
emplace_back(42, 3.14, "hello");

// 展开过程：
std::forward<Args>(args)...   // 展开成：
std::forward<int>(42), std::forward<double>(3.14), std::forward<const char*>("hello")
```

#### 4. 为什么必须展开？

因为 C++ 里构造函数（`T(...)`）的参数是一个一个匹配的，而参数包是一个“集合”，要让编译器自动把它拆成单个参数传过去，就需要 `...` 来展开。

`...` 出现在不同位置的意义：

-   定义类型包：`typename... Args`
-   定义变量包：`Args&&... args`
-   展开：`std::forward<Args>(args)...`

#### 5. 结合你的 `emplace_back`

```cpp
new (data_ + size_) T(std::forward<Args>(args)...);
```

它的意思是：

-   取 `args` 里的每个参数，
-   根据 `Args` 的推导结果决定它是左值还是右值，
-   保留原本的值类别（完美转发），
-   按顺序一个个传给 `T` 的构造函数。



### `std::map`

读取元素时，统一用 `at()`

写入元素时，统一用 `[]`

```cpp
std::map<std::string, int> m;
auto val = m.at("key1");  // 读
m["key2"] = val;  // 写
```



### 浅拷贝与深拷贝

**浅拷贝(Shallow Copy)**和**深拷贝(Deep Copy)**



### `std::pair` 的用法和优势

`std::pair` 是一个简单但极其有用的工具，其核心优势在于：

1. **轻量高效**：零开销抽象
2. **通用性强**：适用于各种场景
3. **与 STL 深度集成**：容器和算法的关键组成部分
4. **类型安全**：编译时类型检查
5. **现代特性支持**：结构化绑定、移动语义等

使用场景建议：

- 需要返回两个值时​ ➔ 替代输出参数
- 创建简单键值对 ➔ 替代简单结构体
- 需要临时组合数据 ➔ 避免定义临时结构
- 与 STL 算法配合 ➔ 利用内置比较操作

当需要组合超过两个值时，可升级到 `std::tuple`，但 `std::pair` 在二元数据组合场景中仍是最简洁高效的选择。



### `std::tuple`

tuple 用于函数多个返回值

```cpp
#include <iostream>
#include <tuple>
#include <cmath>

std::tuple<bool, float> mysqrt(float x) {
    if (x >= 0.f) {
        return {true, std::sqrt(x)};
    } else {
        return {false, 0.0f};
    }
}

int main() {
    auto [success, value] = mysqrt(4.f);
    if (success) {
        printf("Succeed!, the result is %.2f\n", value);
    } else {
        printf("Failed, the input is lower than 0\n");
    }
    return 0;
}
```



### 智能指针

#### `std::unique_ptr`



#### `std::shared_ptr`

```cpp
mysql_connection *conn = mysql_connect("127.0.0.1");
mysql_execute(conn, "drop database paolu");
mysql_close(conn); // 用户可能忘记关闭连接！破坏库设计者想要的用法
```

`std::shared_ptr` 小妙招：构造函数的第二个参数可以指定释放函数，代替默认的 delete

```cpp
auto conn = std::shared_ptr<mysql_connection>(mysql_connect("127.0.0.1"), mysql_close);
mysql_execute(conn.get(), "drop database paolu");
// conn 离开作用域时，会自动调用 mysql_close，杜绝了一个出错的可能
```



### 常量成员函数



```cpp
class MyClass {
    int value = 0;
public:
    void fun(const int& a) const {
        value = a; // 错误！不能修改成员变量
    }
};
```





## 参考资料

[1] [快速学习C和C++，基础语法和优化策略，学了不再怕指针(南科大计算机系原版)](https://www.bilibili.com/video/BV1Vf4y1P7pq), [GitHub](https://github.com/ShiqiYu/CPP)

[2] [合集·高性能并行编程与优化 - 录播](https://space.bilibili.com/263032155/channel/collectiondetail?sid=53025)

[3] [合集·现代C++项目实战](https://space.bilibili.com/263032155/channel/collectiondetail?sid=599074)

[4] [hacking C++](https://hackingcpp.com/)

[5] [学习路线](https://www.zhihu.com/collection/978731703)

[6] 



