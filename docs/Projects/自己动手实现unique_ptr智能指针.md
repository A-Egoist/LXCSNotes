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



## 参考资料

[1] [字节C++三面：手撕 unique_ptr，源码分享~【码农Mark】](https://www.bilibili.com/video/BV11cG5zwEBU)
