# 自己动手实现unique_ptr智能指针

## 核心职责

*   独占式资源管理（一个资源只能被一个 `unique_ptr` 拥有）
*   RAII：构造时获取资源，析构时自动释放
*   支持移动语义，禁用拷贝语义



## 接口需求

*   构造：接收裸指针，获取资源所有权
*   析构：自动释放资源
*   访问：`operator*`、`operator->`
*   移动：支持所有权转移
*   重置：reset()、release()
*   查询：get()、operator bool() <-- :warning: 使用 explicit 避免隐式转换



## 代码实现

### 基本功能实现

*   构造函数。使用 `explicit` 关键字防止隐式转换。
*   析构函数。在析构函数处释放资源，这是 RAII 的核心，当 `unique_ptr` 对象离开作用域的时候，其析构函数会自动调用 `delete ptr_` 来释放它所管理的内存，从而避免内存泄露。
*   拷贝控制。`unique_ptr` 的核心思想是**独占所有权**。任何时候只能有一个 `unique_ptr` 对象管理特定的资源。禁用拷贝操作能够确保这个规则不会被破坏，防止同一块内存被多个智能指针同时管理而导致重复释放（double free）。
*   移动语义。移动构造函数允许我们转移所有权。当一个 `unique_ptr` 被移动到另一个新的 `unique_ptr` 的时候，所有权从源对象转移到目标对象。源对象（`other`）的指针被置空，这样它就不会在析构时错误地释放资源。`noexcept` 标记告诉编译器这个操作不会抛出异常，这在 `std::vector` 等容器进行扩容时非常重要，可以确保他们优先使用移动语义而非拷贝，从而提高效率。此外，可以使用 `std::exchange` 更简洁的实现。
*   运算符重载。重载 `*`  和 `->` 运算符，确保能够像原始指针一样方便的访问和操作底层对象。
*   显式重载 `explicit operator bool()`。允许在布尔上下文中判断 `unique_ptr` 是否持有有效指针。比如，`if (my_ptr)` 这样的代码会非常简洁和直观。

```cpp
#pragma once

#include <utility>

template <typename T>
class unique_ptr {
private:
    T* ptr_;
public:
    explicit unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}

    ~unique_ptr() {
        delete ptr_;
    }

    // 禁用拷贝构造和拷贝赋值运算符
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // 实现移动构造函数和移动赋值运算符
    // 使用 noexcept，确保我们在使用容器，比如 vector 来管理 unique_ptr 的时候，在容器重新分配的时候选择移动而非是拷贝
    // 因为 vector 等容器中进行扩容等数据移动的操作时会优先使用 noexcept 的构造函数
    unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    // 赋值运算符重载的时候进行自赋值检查
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this == &other) return *this;

        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;

        return *this;
    }

    // 访问操作
    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    T* get() const {
        return ptr_;
    }

    explicit operator bool() const {
        return ptr_ != nullptr;
    }
};
```



### 加分项

*   添加 `release()` 函数，用于释放所有权，但不销毁对象
*   添加 `reset()` 函数，用于释放所有权，并销毁当前管理的资源，重置管理的资源
*   添加 `swap()` 函数，用于交换两个 `unique_ptr` 管理的资源
*   添加 `swap(unique_ptr<T>&, unique_ptr<T>&)` 模板函数，用于交换两个 `unique_ptr` 管理的资源
*   重载 `==` 和 `!=` 运算符，用于实现两个 `unique_ptr` 的比较或 `unique_ptr` 和 `nullptr` 的比较

```cpp
#pragma once

#include <utility>

template <typename T>
class unique_ptr {
private:
    T* ptr_;
public:
    explicit unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}

    ~unique_ptr() {
        delete ptr_;
    }

    // 禁用拷贝构造和拷贝赋值运算符
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // 实现移动构造函数和移动赋值运算符
    // 使用 noexcept，确保我们在使用容器，比如 vector 来管理 unique_ptr 的时候，在容器重新分配的时候选择移动而非是拷贝
    // 因为 vector 等容器中进行扩容等数据移动的操作时会优先使用 noexcept 的构造函数
    unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    // 也可以使用 std::exchange 来实现
    // unique_ptr(unique_ptr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}

    // 赋值运算符重载的时候进行自赋值检查
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this == &other) return *this;

        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        // 或者使用 std::exchange
        // ptr_ = std::exchange(other.ptr_, nullptr);

        return *this;
    }

    // 访问操作
    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    T* get() const {
        return ptr_;
    }

    explicit operator bool() const {
        return ptr_ != nullptr;
    }

    // 释放所有权，不销毁对象
    T* release() {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    // 释放所有权，并销毁对象，重置管理的资源
    void reset(T* p = nullptr) {
        delete ptr_;
        ptr_ = p;
    }

    void swap(unique_ptr& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }
};

template <typename T>
void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T>
bool operator==(const unique_ptr<T>& lhs, const unique_ptr<T>& rhs) {
    return lhs.get() == rhs.get();
}

template <typename T>
bool operator!=(const unique_ptr<T>& lhs, const unique_ptr<T>& rhs) {
    return !(lhs.get() == rhs.get());
}

template <typename T>
bool operator==(const unique_ptr<T>& lhs, std::nullptr_t) {
    return !lhs;
}

template <typename T>
bool operator!=(const unique_ptr<T>& lhs, std::nullptr_t) {
    return static_cast<bool>(lhs);
}
```



模板函数 `bool operator==(const unique_ptr<T>& lhs, std::nullptr_t)` 和 `bool operator!=(const unique_ptr<T>& lhs, std::nullptr_t)` 用于提升代码的可读性和直观性，方便使用如下的代码：

```cpp
unique_ptr<int> p(new int(10));
unique_ptr<int> empty_p;

if (empty_p == nullptr) {
    std::cout << "empty_p is a nullptr." << std::endl;
}

if (p != nullptr) {
    std::cout << "p is not a nullptr." << std::endl;
}
```

没有这两个重载，就不能直接使用 `== nullptr` 或 `!= nullptr` 来比较的 `unique_ptr`。只能使用 `operator bool()` 转换来达到同样的目的，例如 `if (!empty_p)` 或 `if (p)`。虽然这两种方法都能工作，但提供与 `nullptr` 的直接比较更能让 `unique_ptr` 感觉像是一个“一流公民”，让它的行为与 C++ 内置的原始指针保持一致，从而使代码更自然、更易于理解。



### `std::exchange` 优化

使用 `std::exchange` 优化移动构造函数、移动赋值运算符、`release()`：

```cpp
// 移动构造函数
unique_ptr(unique_ptr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}

// 移动赋值运算符
unique_ptr& operator=(unique_ptr&& other) noexcept {
    if (*this == &other) return *this;
    
    ptr_ = std::exchange(other.ptr_, nullptr);
    return *this;
}

// release()
T* release() {
    return std::exchange(ptr_, nullptr);
}
```



### 其他

在设计类时，如果一个成员函数不修改类的任何成员变量，那么就应该把它声明为 `const`。这是 C++ 中一个重要的**契约**，它能帮助你编写更安全、更易于理解的代码。





## 测试代码

`test_MyUniquePtr.cpp`

```cpp
#include <iostream>
#include <string>
#include <vector>
#include "MyUniquePtr002.h"

struct MyObject {
    int value;
    static int creation_count;
    static int deletion_count;

    MyObject(int val) : value(val) {
        creation_count++;
        std::cout << "MyObject(" << value << ") created. Total: " << creation_count << std::endl;
    }

    ~MyObject() {
        deletion_count++;
        std::cout << "MyObject(" << value << ") destroyed. Total: " << deletion_count << std::endl;
    }
};
int MyObject::creation_count = 0;
int MyObject::deletion_count = 0;

void print_status(const unique_ptr<MyObject>& ptr, const std::string& name) {
    std::cout << "--- Status of " << name << " ---" << std::endl;
    std::cout << name << " is " << (ptr ? "not null" : "null") << std::endl;
    if (ptr) {
        std::cout << "Value: " << (*ptr).value << std::endl;
        std::cout << "Pointer address: " << ptr.get() << std::endl;
    }
    std::cout << "----------------------" << std::endl << std::endl;
}

int main() {
    std::cout << "--- Test unique_ptr ---" << std::endl << std::endl;

    // 1. 基本构造和析构
    std::cout << "Step 1: Basic construction and destruction." << std::endl;
    {
        unique_ptr<MyObject> p1(new MyObject(10));
        print_status(p1, "p1");
    } // p1 离开作用域，MyObject(10) 被自动销毁
    
    std::cout << "MyObject::deletion_count: " << MyObject::deletion_count << std::endl << std::endl;

    // 2. 移动构造
    std::cout << "Step 2: Move construction." << std::endl;
    unique_ptr<MyObject> p2(new MyObject(20));
    unique_ptr<MyObject> p3 = std::move(p2);
    print_status(p2, "p2");
    print_status(p3, "p3");
    
    // 检查 p2 是否为空，p3 是否接管所有权
    if (!p2 && p3 && p3->value == 20) {
        std::cout << "Move construction successful." << std::endl;
    } else {
        std::cout << "Move construction failed." << std::endl;
    }
    std::cout << std::endl;

    // 3. 移动赋值
    std::cout << "Step 3: Move assignment." << std::endl;
    unique_ptr<MyObject> p4(new MyObject(30));
    unique_ptr<MyObject> p5(new MyObject(40));
    print_status(p4, "p4 before move");
    print_status(p5, "p5 before move");
    p4 = std::move(p5); // MyObject(30) 应该被销毁
    print_status(p4, "p4 after move");
    print_status(p5, "p5 after move");
    
    if (p4 && !p5 && p4->value == 40) {
        std::cout << "Move assignment successful." << std::endl;
    } else {
        std::cout << "Move assignment failed." << std::endl;
    }
    std::cout << std::endl;

    // 4. release()
    std::cout << "Step 4: release() method." << std::endl;
    unique_ptr<MyObject> p6(new MyObject(50));
    MyObject* raw_ptr = p6.release();
    print_status(p6, "p6 after release");
    std::cout << "Raw pointer address: " << raw_ptr << std::endl;
    if (!p6 && raw_ptr->value == 50) {
        std::cout << "release() successful." << std::endl;
    } else {
        std::cout << "release() failed." << std::endl;
    }
    delete raw_ptr; // 必须手动释放
    std::cout << std::endl;

    // 5. reset()
    std::cout << "Step 5: reset() method." << std::endl;
    unique_ptr<MyObject> p7(new MyObject(60));
    print_status(p7, "p7 before reset");
    p7.reset(new MyObject(70)); // MyObject(60) 应该被销毁
    print_status(p7, "p7 after reset");
    p7.reset(); // MyObject(70) 应该被销毁
    print_status(p7, "p7 after final reset");
    
    if (!p7) {
        std::cout << "reset() successful." << std::endl;
    } else {
        std::cout << "reset() failed." << std::endl;
    }
    std::cout << std::endl;

    // 6. swap()
    std::cout << "Step 6: swap() method." << std::endl;
    unique_ptr<MyObject> p8(new MyObject(80));
    unique_ptr<MyObject> p9(new MyObject(90));
    std::cout << "Before swap:" << std::endl;
    print_status(p8, "p8");
    print_status(p9, "p9");
    // p8.swap(p9);
    swap(p8, p9);
    std::cout << "After swap:" << std::endl;
    print_status(p8, "p8");
    print_status(p9, "p9");
    
    if (p8->value == 90 && p9->value == 80) {
        std::cout << "swap() successful." << std::endl;
    } else {
        std::cout << "swap() failed." << std::endl;
    }
    std::cout << std::endl;

    // 7. 运算符重载 (==, !=, bool)
    std::cout << "Step 7: Operator overloads." << std::endl;
    unique_ptr<MyObject> p10(new MyObject(100));
    unique_ptr<MyObject> p11(p10.release());
    unique_ptr<MyObject> p12; // 默认构造为 nullptr
    
    std::cout << "p10 == p11: " << std::boolalpha << (p10 == p11) << std::endl; // false
    std::cout << "p10 != p11: " << std::boolalpha << (p10 != p11) << std::endl; // true
    std::cout << "p10 == nullptr: " << std::boolalpha << (p10 == nullptr) << std::endl; // true
    std::cout << "p11 != nullptr: " << std::boolalpha << (p11 != nullptr) << std::endl; // true
    std::cout << "p12 == nullptr: " << std::boolalpha << (p12 == nullptr) << std::endl; // true
    std::cout << "if (p11) is " << std::boolalpha << (bool)p11 << std::endl; // true
    std::cout << "if (p12) is " << std::boolalpha << (bool)p12 << std::endl; // false

    // 8. 验证禁用拷贝
    std::cout << "Step 8: Verify copy semantics are deleted." << std::endl;
    // unique_ptr<MyObject> p_copy = p11; // 这一行会产生编译错误，如果你的实现正确
    // unique_ptr<MyObject> p_assign;
    // p_assign = p11; // 这一行也会产生编译错误
    
    std::cout << "Total created: " << MyObject::creation_count << std::endl;
    std::cout << "Total destroyed: " << MyObject::deletion_count << std::endl;

    return 0;
}
```



## 参考资料

[1] [字节C++三面：手撕 unique_ptr，源码分享~【码农Mark】](https://www.bilibili.com/video/BV11cG5zwEBU)

[2] [【C++11】自己动手实现unique_ptr智能指针，都有哪些难点？](https://www.bilibili.com/video/BV1Hw411y7g5)
