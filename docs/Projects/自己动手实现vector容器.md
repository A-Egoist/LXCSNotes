# 自己动手实现vector容器

>   参考资料：
>   [1] [拼多多C++一面：手撕 std::vector,源码文档分享~【码农Mark】](https://www.bilibili.com/video/BV1XSNizpEah?spm_id_from=333.1245.0.0)
>   [2] [【C++标准库】自己动手实现vector容器](https://www.bilibili.com/video/BV1V84y127Pi/?spm_id_from=333.1387.collection.video_card.click&vd_source=f4cc25a44af6631d6f4db023b3bb88e4)
>
>   [3] [拼多多、足下科技C++一面：手把手带你手撕 std::vector（第二版）【码农Mark】](https://www.bilibili.com/video/BV15HN2zpErf/?spm_id_from=333.1387.list.card_archive.click&vd_source=cec2e4e6aff81caf6c36bcd4265ba034)

实现一个什么样的 vector？动态数组

包含关键特性：

1.   内存管理（分离内存分配和对象构造，分离内存释放和对象析构，扩容机制）
2.   移动语义优化（移动构造和移动赋值）
3.   增、删操作数据移动
4.   支持迭代器
5.   不提供范围操作，仅提供单个元素的操作，目的是展示对 vector 的理解
6.   采用 `T*`，`size_t size_, capacity_` 来实现

>   什么是 POD 类型：[什么是 POD 数据类型？](https://zhuanlan.zhihu.com/p/45545035)
>
>   什么是完美转发？什么是万能引用？什么是“具名的”？
>
>   test-driven development
>
>   size_t 类型
>
>   拷贝构造不是异常安全的？为什么？怎么解决？
>
>   什么是 `static_cast<T*>(::operator new(capacity* sizeof(T)));` ？
>
>   try {} catch (...) {} 捕获所有的异常
>
>   采用移动语义进行优化：`std::move_if_noexcept()` 优先使用移动构造，否则使用拷贝构造
>
>   `throw` 关键字
>
>   扩容逻辑保持和 GCC 一致
>
>   区分拷贝构造、拷贝赋值、移动构造等

---

想要实现一个自己的 vector 类 `MyVector`，需要先理解 `std::vector` 的核心概念，`std::vector` 有三个关键概念：

1.   指向数据开头的指针：一个指向 `std::vector` 内部存储元素的内存块的起始位置，存储的数据类型为模板参数 `T`；
2.   容量 (Capacity)：当前已分配内存块能够容纳的元素总数。当 `vector` 的元素数量 `size_` 大于 `capacity_` 时会扩容，它会重新分配一块更大的内存，将现有的元素移动/拷贝过去，然后释放旧的内存。在这里扩容逻辑保持和 GCC  一致，即两倍扩容；
3.   大小 (Size)：当前 `vector` 中实际存储的元素数量，它总是小于等于 `capacity_`。



逐步实现 `MyVector` 类

1.   定义 `MyVector` 类的基本结构，包括三个核心成员变量：`data_` (指向数据的指针)，`capacity_` (容量)，`size_` (大小)；
2.   定义默认构造函数、显式带参数的构造函数、析构函数、常用的成员函数 (`size()`，`capacity()`，`empty()`)；
3.   实现访问元素的功能，包括使用 `[]` 运算符访问、使用 `at()` 访问、访问第一个元素 `front()` 以及访问最后一个元素 `back()`。此外，还要实现对应的 const 版本；
4.   动态扩容。这是 `std::vector` 最核心的机制，当 `size_` 达到 `capacity_` 的时候，就需要分配更大的内存 (这里我们将扩容逻辑和 GCC 保持一致，当 `capacity_` 为 0 的时候，令 `capacit_` 为 1，否则令 `capacity_` 变为两倍)。实现一个 `reserve()` 用于手动预留内存，实现一个内部辅助函数 `reallocate()` 用于实际的内存扩容；
5.   添加元素 `push_back()`，首先需要检查 `size_` 是否等于 `capacity_`，如果相等则需要扩容。然后将旧内存中的元素拷贝到新内存。此外，还需要支持移动语义；
6.   移出元素 `pop_back()` 和 `clear()`。对于 POD 类型，可以直接 `-- size_`，但是对用非 POD 类型，还需要考虑调用元素的析构函数；
7.   拷贝构造函数和赋值运算符。用于从一个 `MyVector` 对象初始化另一个 `MyVector` 对象；
8.   移动构造函数和移动赋值运算符 (C++11)。用于优化性能，避免不必要的内存分配和拷贝，显著提升性能。`noexcept` 用于表示这些操作不会抛出异常；
9.   实现迭代器的简单版本。将 `iterator` 和 `const_iterator` 简单的定义为 `T*` 和 `const T*`，因为指针本身就可以作为迭代器使用。此外，实现 `begin()` 和 `end()` 分别用于获取 `vector` 的第一个元素指针，和最后一个元素的下一个元素的指针，对齐 `std::begin()` 和 `std::end()`。

完整代码：

```cpp
#pragma once
#include <cstddef>  // size_t
#include <stdexcept>  // std::out_of_range
#include <algorithm>  // std::copy

template <typename T>
class MyVector {
public:
    MyVector() : data_(nullptr), capacity_(0), size_(0) {}

    // explicit 关键字防止隐式转换
    explicit MyVector(size_t init_size) : capacity_(init_size), size_(init_size) {
        // 分配空间
        data_ = new T[capacity_];

        // 调用类型 T 的默认构造函数
        for (int i = 0; i < init_size; ++ i) {
            data_[i] = T();
        }
    }

    // 拷贝构造函数
    MyVector(const MyVector& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++ i) {
            data_[i] = other.data_[i];
        }
    }

    // 拷贝赋值运算符
    MyVector& operator=(const MyVector& other) {
        if (this == &this) {
            // 处理自我赋值
            return *this;
        }

        delete[] data_;

        // 拷贝其他 MyVector 的shuju
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++ i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    // 移动构造函数(C++11 及更高版本)
    MyVector(MyVector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // 移动赋值运算符(C++11 及更高版本)
    MyVector& operator=(MyVector&& other) noexcept {
        if (this == &other) {
            // 处理自我赋值
            return *this;
        }

        delete[] data_;  // 释放当前资源

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    // 定义迭代器类型
    using iterator = T*;
    using const_iterator = const T*;

    // 返回指向第一个元素的迭代器
    iterator begin() {
        return data_;
    }

    // 返回指向第一个元素的迭代器(const)
    const_iterator begin() const {
        return data_;
    }

    // 返回指向最后一个元素下一个位置的迭代器
    iterator end() {
        return data_ + size_;
    }

    // 返回指向最后一个元素下一个位置的迭代器(const)
    const_iterator end() const {
        return data_ + size_;
    }

    // 析构函数：释放内存
    ~MyVector() {
        // clear();  // 对象析构
        // deallocate();  // 内存释放
        delete[] data_;
    }

    // 返回当前实际存储的元素数量
    size_t size() const {
        return size_;
    }

    // 返回当前已分配内存能容纳的元素总数
    size_t capacity() const {
        return capacity_;
    }

    // 检查 vector 是否为空
    bool empty() const {
        return size_ == 0;
    }

    // 重载 [] 运算符，提供对元素的非 const 引用
    T& operator[](size_t index) {
        return data_[index];
    }

    // 重载 [] 运算符，提供对元素的 const 引用
    const T& operator[](size_t index) const {
        return data_[index];
    }

    // 边界检查的元素访问，如果越界则抛出 std::out_of_range
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("MyVector::at: out of range\n");
        }
        return data_[index];
    }

    // 边界检查的元素访问，const 版本
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("MyVector::at: out of range\n");
        }
        return data_[index];
    }

    // 访问第一个元素
    T& front() {
        if (empty()) {
            throw std::out_of_range("MyVector::front: vector is empty\n");
        }
        return data_[0];
    }

    // 访问第一个元素(const 版本)
    const T& front() const {
        if (empty()) {
            throw std::out_of_range("MyVector::front: vector is empty\n");
        }
        return data_[0];
    }

    // 访问最后一个元素
    T& back() {
        if (empty()) {
            throw std::out_of_range("MyVector::back: vector is empty\n");
        }
        return data_[size_ - 1];
    }

    // 访问最后一个元素(const 版本)
    const T& back() const {
        if (empty()) {
            throw std::out_of_range("MyVector::back: vector is empty\n");
        }
        return data_[size_ - 1];
    }

    // 预留内存，确保容量至少为 new_capacity
    void reserve(size_t new_capacity) {
        if (capacity_ < new_capacity) {
            reallocate(new_capacity);
        }
    }

    // 向 vector 的末尾添加元素
    void push_back(const T& value) {
        if (size_ == capacity_) {
            // 容量不足，需要扩容，扩容逻辑和 GCC 保持一致，当 capacity 为 0 的时候，新容量为 1，否则为 2 倍扩容
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        data_[size_ ++] = value;  // 拷贝构造或赋值
    }

    // 移动语义版本的 push_back (C++11 及更高版本)
    void push_back(T&& value) {
        if (size_ == capacity_) {
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        data_[size_ ++] = std::move(value);  // 移动赋值
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("MyVector::pop_back: vector is empty\n");
        }
        -- size_;
    }

    // 清空 vector，但不释放内存
    void clear() {
        // 对应非 POD 类型，需要显式调用每个元素的析构函数
        // 简单将 size_ 置为 0，内存仍然保留
        size_ = 0;
    }

private:
    
    // 内存分配
    void allocate();

    // 重新分配内存
    void reallocate(size_t new_capacity) {
        if (capacity_ >= new_capacity) {
            return ;  // 新容量不大于旧容量，无需重新分配
        }

        T* new_data = new T[new_capacity];

        // 将旧数据拷贝到新内存
        // std::copy 会正确处理 POD 类型，对于非 POD 类型，需要考虑移动语义或拷贝构造
        for (int i = 0; i < size_; ++ i) {
            new_data[i] = data_[i];
        }

        // 释放旧内存
        delete[] data_;
        
        data_ = new_data;
        capacity_ = new_capacity;
    }

    // 内存释放
    void deallocate();

    T* data_;
    size_t capacity_;
    size_t size_;
};
```

以上代码提供了一个 `MyVector` 的基础实现，但是参考 `std::vector`，该类存在一些改进的地方：

### 1. 将内存分配和对象构造分离：

```cpp
// ... (之前的代码)

template <typename T>
class MyVector {
public:
    // ... (之前的构造函数、析构函数、拷贝/移动构造和赋值)
    
    // explicit 关键字防止隐式转换
    explicit MyVector(size_t init_size) : capacity_(init_size), size_(init_size) {
        data_ = allocate(capacity_);  // 分配内存

        for (int i = 0; i < init_size; ++ i) {
            data_[i] = T();  // 构造对象，调用类型 T 的默认构造函数
        }
    }

private:
    // ... (之前的成员变量和函数)
    
    // 内存分配
    T* allocate(size_t capacity) {
        return static_cast<T*>(::operator new(capacity * sizeof(T)));
    }
};
```

#### `new T[capacity_]` 的行为

因为原来的 `new T[capacity_]` 会做两件事情：1）分配内存，分配足够的原始内存来存储 `capacity_` 个 `T` 类型的对象；2）构造对象，调用 `T` 的**默认构造函数**，在分配的内存上对 `capacity_` 个对象进行原地构造（placement new）。

**优点**：

*   简单方便：一步到位，同时分配内存和构造对象。

**缺点**：

*   效率问题：如果 `vector` 需要很大的容量，但大多数元素并不会立即被使用或赋值，那么提前构造这些对象是浪费时间和资源的。对于**非平凡类型**（non-trivial types，即有自定义构造函数、析构函数、拷贝/移动操作的类型），默认构造可能会有显著的开销。
*   不必要的构造：我们希望在 `push_back` 或 `emplace_back` 时才实际构造元素，而不是在 `reserve` 或 `resize` 时就构造。

#### `::operator new` (和 `placement new`) 的行为

`::operator new` 是一个全局的内存分配函数（就像 `malloc`），它只负责分配指定大小的原始、未初始化的内存块。它**不会**调用任何对象的构造函数。

后续你需要手动在这些原始内存上构造对象，这通常通过**定位 new (placement new)** 来完成。例如，当你 `push_back` 一个元素时：
```cpp
// 假设 data_ 已经通过 ::operator new 分配了原始内存
// 并在 MyVector::size_ 处有足够的空间

// 使用定位 new 在 data_[size_] 的内存位置构造一个 T 类型的对象
new (data_ + size_) T(value); // 调用 T 的拷贝构造函数
// 或者 new (data_ + size_) T(std::move(value)); // 调用 T 的移动构造函数
```

**优点：**

-   **性能优化**：它允许你将内存分配和对象构造分离，这意味着只有在真正需要时才构造对象。这对于需要大量预留内存但不立即填充的容器来说，可以避免不必要的构造开销，提高性能。例如，`vector::reserve` 只需要分配内存，而不需要构造对象。
-   **精确控制**：你可以更精确地控制何时、何地以及如何构造和销毁对象。这对于实现像 `std::vector` 这样需要管理生命周期的复杂容器至关重要。

`::operator new` 返回的是一个 `void*` 指针。`void*` 是一个通用指针类型，它可以指向任何类型的数据，但它本身没有类型信息，不能直接进行指针算术运算（如 `ptr + 1`）或解引用。为了能够将这块原始内存视为存储 `T` 类型对象的数组，并对其进行后续操作（例如，通过 `data_[index]` 访问元素或使用定位 `new` 构造对象），我们需要将这个 `void*` 指针转换为 `T*` 类型的指针。

`static_cast<T*>` 的核心作用就是将 `::operator new` 返回的通用 `void*` 指针**明确地转换为 `T` 类型的指针**，从而使我们能够以类型安全的方式管理和操作这块内存，将其作为 `T` 类型对象的存储区域。

### 2. 

---

**深入理解和学习 `std::vector` 的关键点**

在实现 `MyVector` 的过程中，你需要注意以下几点，这能帮助你更深入地理解 `std::vector`：

-   **内存管理**：`std::vector` 最重要的职责是内存管理。你需要手动 `new` 和 `delete` 数组，并处理好内存的分配、释放和重新分配。这是面试中考察的重点。
-   **深拷贝与浅拷贝**：在实现拷贝构造函数和赋值运算符时，务必进行深拷贝。如果只是简单地拷贝指针，会导致两个 `vector` 共享同一块内存，当其中一个被销毁时，另一个就会成为“悬空指针”，引发程序崩溃（双重释放）。
-   **移动语义 (C++11)**：为了避免不必要的深拷贝带来的性能开销，C++11 引入了移动语义。理解并实现移动构造函数和移动赋值运算符是现代 C++ 编程的重要技能。
-   **容量增长策略**：当 `vector` 需要扩容时，它通常会以固定的倍数（例如 1.5 倍或 2 倍）增长容量，而不是每次只增加一个元素所需的内存。这样可以减少频繁的内存重新分配，提高效率。
-   **异常安全**：考虑在内存分配失败时（例如 `new` 抛出 `std::bad_alloc`）如何保证 `vector` 处于一致状态。例如，在 `reallocate` 中捕获异常。
-   **RAII (Resource Acquisition Is Initialization)**：`std::vector` 是 RAII 的一个典型例子。内存的分配和释放都由 `vector` 类自动管理，用户无需手动操作，从而避免了内存泄漏和悬空指针等问题。
-   **迭代器失效**：理解 `vector` 在什么操作下会导致迭代器失效。例如，当 `vector` 重新分配内存时，所有指向旧内存的迭代器都会失效。

---

**应对面试建议**

-   **从核心功能开始**：面试时，如果时间有限，先实现最核心的功能，如构造函数、析构函数、`push_back` 和 `operator[]`。
-   **逐步完善**：在核心功能实现后，再逐步添加拷贝构造、赋值运算符、`reserve`、`at` 等。
-   **清晰的注释和解释**：在代码中添加清晰的注释，并能够向面试官解释你每个设计决策的理由。
-   **讨论边界情况和异常处理**：主动讨论你的实现如何处理空 `vector`、越界访问、内存分配失败等边界情况和异常。
-   **优化思路**：讨论如何优化性能，例如使用移动语义，以及为什么选择特定的容量增长策略。
-   **提问**：如果面试官允许，可以问一些关于 `std::vector` 实现的细节问题，表明你对这个话题有深入的思考。