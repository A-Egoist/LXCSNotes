# 自己动手实现shared_ptr智能指针

## 核心职责

*   不考虑删除器和空间配置器
*   不考虑弱引用
*   考虑引用计数的线程安全
*   提出测试案例



shared_ptr 难度等级：

1.   单线程 shared_ptr
2.   互斥锁 shared_ptr
3.   默认内存序原子变量 shared_ptr
4.   考虑内存序优化原子变量 shared_ptr



## 接口需求

成员变量

*   指向管理的对象 `T* ptr_`
*   原子引用计数 `std::atomic<std::size_t>* ref_count`。这是强引用计数。



数据成员细节：

*   空的 `shared_ptr` 大小为 16 字节，与在 64 位情况下的 `std::shared_ptr` 对齐
*   `std::atomic<std::size_t>*` 引用计数



接口：

1.   构造函数。不带参数和带参数的版本
2.   析构函数
3.   拷贝构造函数
4.   拷贝赋值运算符
5.   移动构造函数
6.   移动赋值运算符
7.   运算符 `*` 和 `->`
8.   引用计数、原始指针、重置指针



接口细节：

*   有参构造函数需要 `explicit` 修饰
*   拷贝构造函数和拷贝赋值运算符函数需要 `const T&` 常引用
*   移动构造函数和移动赋值运算符函数需要 `noexcept` 修饰
*   只读接口用 `const` 修饰



内存序细节：

*   `fetch_add` 采用 `std::memory_order_relaxed`
    *   在引用计数减少到零之前的所有操作，与引用计数减少到零之后的操作空间不存在竞态。
*   `fetch_sub` 采用 `std::memory_order_acq_rel`
*   `load` 采用 `std::memory_order_acquire`



其他细节：

*   空的 `std::shared_ptr` 的大小为 16 字节（在64位），我们自己实现的 `shared_ptr` 要和其对齐。
*   使用 `explicit` 防止隐式类型转换，防止出现 `shared_ptr<int> sp = new int(20);`
*   原子操作来控制引用计数，引用计数使用指针类型，确保所有的 `shared_ptr` 能够共享堆上的资源。
*   原子操作中的内存序参数
*   移动构造函数和移动赋值运算符推荐加上 `noexcept`
*   函数后面加 `const` 的作用



线程安全

*   原子操作
    *   熟悉内存序。什么是内存序，什么是内存屏障。
    *   不熟悉内存序
*   互斥锁



原子操作：

*   原子性
*   顺序性



## 代码实现

### 基本功能

使用原子操作来确保引用计数的线程安全，但是没有设置内存序来进一步优化。

*   `ref_count_->fetch_sub(1)` 的作用是原子地将引用计数减 1，并返回减 1 之前的旧值。
*   `ref_count_->fetch_add(1)` 的作用是原子地将引用计数加 1
*   `ref_count_->load()` 的作用是原子地获得引用计数

```cpp
#pragma once

#include <atomic>

template <typename T>
class shared_ptr {
private:
    T* ptr_;  // 管理的原始指针
    std::atomic<std::size_t>* ref_count_;  // 引用计数

    // 释放资源
    void release() {
        // 先检查引用计数对象是否存在，防止空指针解引用
        // 然后，原子地将引用计数减1并获取旧值
        // 如果旧值为1，说明这是最后一个引用，需要释放内存
        if (ref_count_ && ref_count_->fetch_sub(1) == 1) {
            delete ptr_;
            delete ref_count_;
        }
    }
public:
    // 默认构造函数
    shared_ptr() : ptr_(nullptr), ref_count_(nullptr) {}

    // 构造函数
    // 使用 explicit 关键字防止隐式转换，shared_ptr<int> ptr = new int(10); 的形式不允许出现
    explicit shared_ptr(T* p) : ptr_(p), ref_count_(p == nullptr ? nullptr : new std::atomic<std::size_t>(1)) {}

    // 析构函数
    ~shared_ptr() {
        release();
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ref_count_) {
            ref_count_->fetch_add(1);  // 引用计数增加，不需要强内存序
        }
    }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other) {
        // 自赋值
        if (this == &other) return *this;

        release();
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        if (ref_count_) {
            ref_count_->fetch_add(1);  // 引用计数增加
        }

        return *this;
    }

    // 移动构造函数
    shared_ptr(shared_ptr&& other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    // 移动赋值运算符
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        // 自赋值
        if (this == &other) return *this;

        release();  // 释放旧资源
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;

        return *this;
    }

    // 解引用运算符
    T& operator*() const {
        return *ptr_;
    }

    // 箭头运算符
    T* operator->() const {
        return ptr_;
    }

    // 获取引用计数
    std::size_t use_count() const {
        return ref_count_ == nullptr ? 0 : ref_count_->load();
    }

    // 获取原始指针
    T* get() const {
        return ptr_;
    }

    void reset(T* p = nullptr) {
        release();
        ptr_ = p;
        ref_count_ = p == nullptr ? nullptr : new std::atomic<std::size_t>(1);
    }
};
```

### 使用内存序

使用内存序优化，对于 `ref_count_->fetch_add(1)`、`ref_count_->fetch_sub(1)`、`ref_count_->load()`，可以通过指定其使用的内存序来优化：

具体来说：

*   `ref_count_->fetch_add(1, std::memory_order_relaxed)`</br>
    `std::memory_order_relaxed` 是最宽松的内存序。它只保证原子操作本身的原子性，不提供任何跨线程的同步保证。对于引用计数增加操作，这通常是足够的。这是因为 `fetch_add` 只是简单地增加一个计数，不需要保证任何其他内存操作的可见性。当一个线程增加引用计数时，其他线程并不关心这个操作是否立即可见，只要最终能保证计数是正确的就行。这能最大限度地提高性能。

*   `ref_count_->fetch_sub(1, std::memory_order_acq_rel)`</br>
    `std::memory_order_acq_rel` 是一种更严格的内存序，结合了“**获取（acquire）**”和“**释放（release）**”语义。

    *   **释放（Release）语义**：`shared_ptr` 在增加引用计数（`fetch_add`）时，会使用 `release` 语义。这确保了在 `fetch_add` 之前对对象的**所有修改**，在其他线程通过 `acquire` 操作看到 `fetch_add` 之后，都是可见的。
    *   **获取（Acquire）语义**：`shared_ptr` 在减少引用计数（`fetch_sub`）时，如果发现引用计数为 0，会使用 `acquire` 语义。这确保了在 `fetch_sub` 之后，当前线程能看到所有其他线程在先前 `release` 内存序下对该对象进行的修改。
    *   **为什么需要？** 假设线程 A 正在使用 `shared_ptr` 并修改其指向的对象。当线程 A 结束对对象的修改并让 `shared_ptr` 离开作用域时，它的 `fetch_sub` 操作会使用 `acquire` 语义。这保证了在 `delete ptr_` 之前，线程 A 能够看到所有先前对该对象进行的修改，从而避免了“**在修改完成前就销毁对象**”的危险。

*   `ref_count_->load(std::memory_order_acquire)`</br>

    `std::shared_ptr::use_count()` 在读取引用计数时，通常会使用 `std::memory_order_acquire`。这能确保在读取引用计数值的同时，也看到了所有之前对该对象进行的修改。这对于调试非常重要，因为你能确保看到的引用计数值是最新的。

添加内存序之后的完整代码为：

```cpp
#pragma once

#include <atomic>

template <typename T>
class shared_ptr {
private:
    T* ptr_;  // 管理的原始指针
    std::atomic<std::size_t>* ref_count_;  // 引用计数

    // 释放资源
    void release() {
        if (ref_count_ && ref_count_->fetch_sub(1, std::memory_order_acq_rel) == 1) {
            delete ptr_;
            delete ref_count_;
        }
    }
public:
    // 默认构造函数
    shared_ptr() : ptr_(nullptr), ref_count_(nullptr) {}

    // 构造函数
    // 使用 explicit 关键字防止隐式转换，shared_ptr<int> ptr = new int(10); 的形式不允许出现
    explicit shared_ptr(T* p) : ptr_(p), ref_count_(p == nullptr ? nullptr : new std::atomic<std::size_t>(1)) {}

    // 析构函数
    ~shared_ptr() {
        release();
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        if (ref_count_) {
            ref_count_->fetch_add(1, std::memory_order_relaxed);  // 引用计数增加，不需要强内存序
        }
    }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other) {
        // 自赋值
        if (this == &other) return *this;

        release();
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        if (ref_count_) {
            ref_count_->fetch_add(1, std::memory_order_relaxed);  // 引用计数增加
        }

        return *this;
    }

    // 移动构造函数
    shared_ptr(shared_ptr&& other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
    }

    // 移动赋值运算符
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        // 自赋值
        if (this == &other) return *this;

        release();  // 释放旧资源
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;

        return *this;
    }

    // 解引用运算符
    T& operator*() const {
        return *ptr_;
    }

    // 箭头运算符
    T* operator->() const {
        return ptr_;
    }

    // 获取引用计数
    std::size_t use_count() const {
        return ref_count_ == nullptr ? 0 : ref_count_->load(std::memory_order_acquire);
    }

    // 获取原始指针
    T* get() const {
        return ptr_;
    }

    void reset(T* p = nullptr) {
        release();
        ptr_ = p;
        ref_count_ = p == nullptr ? nullptr : new std::atomic<std::size_t>(1);
    }
};
```



### 互斥锁实现引用计数

使用互斥锁（Mutex）同样可以实现引用计数的线程安全，但是通常比原子操作性能差，因为互斥锁涉及操作系统级别的上下文切换和线程调度开销。

以下是使用互斥锁来重写  `shared_ptr` 的代码：

```cpp
#pragma once

#include <mutex>

template <typename T>
class shared_ptr {
private:
    T* ptr_;  // 管理的原始指针
    std::size_t* ref_count_;  // 引用计数
    std::mutex* mtx_;  // 使用互斥锁来保证引用计数的线程安全

    // 释放资源
    void release() {
        if (ref_count_) {
            std::lock_guard<std::mutex> lock(*mtx_);
            -- (*ref_count_);
            if (*ref_count_ == 0) {
                // 如果是最后一个引用
                delete ptr_;
                delete ref_count_;
                delete mtx_;  // 同样需要释放互斥锁的内存
            }
        }
    }
public:
    // 默认构造函数
    shared_ptr() : ptr_(nullptr), ref_count_(nullptr), mtx_(nullptr) {}

    // 构造函数
    explicit shared_ptr(T* p) : ptr_(p) {
        if (p == nullptr) {
            ref_count_ = nullptr;
            mtx_ = nullptr;
        } else {
            ref_count_ = new std::size_t(1);
            mtx_ = new std::mutex();
        }
    }

    // 析构函数
    ~shared_ptr() {
        release();
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) : ptr_(other.ptr_), ref_count_(other.ref_count_), mtx_(other.mtx_) {
        if (ref_count_) {
            std::lock_guard<std::mutex> lock(*mtx_);
            ++ (*ref_count_);
        }
    }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other) {
        // 自赋值
        if (this == &other) return *this;

        release();
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        mtx_ = other.mtx_;
        if (ref_count_) {
            std::lock_guard<std::mutex> lock(*mtx_);
            ++ (*ref_count_);
        }

        return *this;
    }

    // 移动构造函数
    shared_ptr(shared_ptr&& other) noexcept : ptr_(other.ptr_), ref_count_(other.ref_count_), mtx_(other.mtx_) {
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
        other.mtx_ = nullptr;
    }

    // 移动赋值运算符
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        // 自赋值
        if (this == &other) return *this;

        release();  // 释放旧资源
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        mtx_ = other.mtx_;
        other.ptr_ = nullptr;
        other.ref_count_ = nullptr;
        other.mtx_ = nullptr;

        return *this;
    }

    // 解引用运算符
    T& operator*() const {
        return *ptr_;
    }

    // 箭头运算符
    T* operator->() const {
        return ptr_;
    }

    // 获取引用计数
    std::size_t use_count() const {
        int count = 0;
        if (ref_count_ != nullptr) {
            std::lock_guard<std::mutex> lock(*mtx_);
            count = *ref_count_;
        }
        return count;
    }

    // 获取原始指针
    T* get() const {
        return ptr_;
    }

    void reset(T* p = nullptr) {
        release();
        ptr_ = p;
        if (p == nullptr) {
            ref_count_ = nullptr;
            mtx_ = nullptr;
        } else {
            ref_count_ = new std::size_t(1);
            mtx_ = new std::mutex();
        }
    }
};
```



### 拷贝并交换(copy-and-swap)

使用拷贝并交换(copy-and-swap)模式优化原子操作和互斥量中的拷贝赋值运算符，因为 `std::swap()` 是原子的。

#### 原子操作

原来的写法：

```cpp
shared_ptr& operator=(const shared_ptr& other) {
    // 自赋值
    if (this == &other) return *this;

    release();
    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    if (ref_count_) {
        ref_count_->fetch_add(1, std::memory_order_relaxed);  // 引用计数增加
    }

    return *this;
}
```

使用拷贝并交换模式优化：

```cpp
shared_ptr& operator=(shared_ptr other) {  // 按值传递参数
    std::swap(ptr_, other.ptr_);
    std::swap(ref_count_, other.ref_count_);

    return *this;
}
```

使用按值传递参数，在源对象传递参数后，会首先调用拷贝构造函数得到拷贝对象 `other`，在 `other` 中其 `ptr_` 和源对象的 `ptr_` 相同，`ref_count_` 比源对象的 `ref_count_` 增加 1。然后再使用原子交换，将 `other` 和 `this` 中的新旧资源进行交换。交换完成后，`other` 中是旧资源，`this` 中是新资源，在 `other` 离开作用域之后，它的析构函数会被调用，安全地释放它所持有的旧资源。





#### 互斥量

原来的写法：

```cpp
shared_ptr& operator=(const shared_ptr& other) {
    // 自赋值
    if (this == &other) return *this;

    release();
    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    mtx_ = other.mtx_;
    if (ref_count_) {
        std::lock_guard<std::mutex> lock(*mtx_);
        ++ (*ref_count_);
    }

    return *this;
}
```

使用拷贝并交换模式优化：

```cpp
shared_ptr& operator=(shared_ptr other) {  // 按值传递参数
	std::swap(ptr_, other.ptr_);
    std::swap(ref_count_, other.ref_count_);
    std::swap(mtx_, other.mtx_);

    return *this;
}
```



## 测试代码

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include "MySharedPtr.h"

struct TestObject {
    static std::atomic<int> creation_count;
    static std::atomic<int> deletion_count;

    int value;

    TestObject(int val) : value(val) {
        creation_count++;
        std::cout << "TestObject(" << value << ") created. Total: " << creation_count << std::endl;
    }

    ~TestObject() {
        deletion_count++;
        std::cout << "TestObject(" << value << ") destroyed. Total: " << deletion_count << std::endl;
    }
};

std::atomic<int> TestObject::creation_count = 0;
std::atomic<int> TestObject::deletion_count = 0;

void print_status(const shared_ptr<TestObject>& ptr, const std::string& name) {
    std::cout << "--- Status of " << name << " ---" << std::endl;
    std::cout << name << " is " << (ptr.get() ? "not null" : "null") << std::endl;
    if (ptr.get()) {
        std::cout << "Value: " << (*ptr).value << std::endl;
        std::cout << "use_count: " << ptr.use_count() << std::endl;
        std::cout << "Pointer address: " << ptr.get() << std::endl;
    }
    std::cout << "----------------------" << std::endl << std::endl;
}

// 多线程测试函数
void thread_func(shared_ptr<TestObject> sp, int thread_id) {
    for (int i = 0; i < 10000; ++i) {
        // 在循环中进行拷贝和赋值，模拟多线程竞争
        shared_ptr<TestObject> temp = sp;
        shared_ptr<TestObject> temp2;
        temp2 = temp;
    }
    // 线程结束，sp 离开作用域，引用计数减少
    std::cout << "Thread " << thread_id << " finished." << std::endl;
}

int main() {
    std::cout << "--- Test shared_ptr (Single-threaded) ---" << std::endl << std::endl;

    // 1. 基本构造、拷贝和析构
    shared_ptr<TestObject> sp1(new TestObject(10));
    print_status(sp1, "sp1");
    assert(sp1.use_count() == 1);

    {
        shared_ptr<TestObject> sp2 = sp1; // 拷贝构造
        print_status(sp2, "sp2");
        assert(sp1.use_count() == 2);
        assert(sp2.use_count() == 2);

        shared_ptr<TestObject> sp3;
        sp3 = sp1; // 拷贝赋值
        print_status(sp3, "sp3");
        assert(sp1.use_count() == 3);
        assert(sp3.use_count() == 3);
    } // sp2 和 sp3 离开作用域，引用计数减到 1

    print_status(sp1, "sp1 after scope exit");
    assert(sp1.use_count() == 1);
    std::cout << "Creation count: " << TestObject::creation_count << ", Deletion count: " << TestObject::deletion_count << std::endl << std::endl;

    // 2. 移动语义
    std::cout << "--- Test Move Semantics ---" << std::endl;
    shared_ptr<TestObject> sp4(new TestObject(20));
    shared_ptr<TestObject> sp5 = std::move(sp4); // 移动构造
    print_status(sp4, "sp4 after move");
    print_status(sp5, "sp5 after move");
    assert(sp4.get() == nullptr);
    assert(sp5.use_count() == 1);
    std::cout << "Move construction test passed." << std::endl << std::endl;
    
    // 3. reset()
    std::cout << "--- Test reset() ---" << std::endl;
    shared_ptr<TestObject> sp6(new TestObject(30));
    print_status(sp6, "sp6 before reset");
    sp6.reset(new TestObject(40)); // 释放旧资源，接管新资源
    print_status(sp6, "sp6 after reset");
    assert(sp6.use_count() == 1);
    std::cout << "reset() test passed." << std::endl << std::endl;

    // 4. 多线程测试
    std::cout << "--- Test shared_ptr (Multi-threaded) ---" << std::endl << std::endl;
    
    // 创建一个 shared_ptr，并让多个线程共享它
    shared_ptr<TestObject> shared_obj(new TestObject(50));
    std::vector<std::thread> threads;
    const int num_threads = 10;
    
    // 启动线程
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(thread_func, shared_obj, i);
    }
    
    // 等待线程结束
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "All threads finished." << std::endl;
    print_status(shared_obj, "shared_obj after all threads finish");
    assert(shared_obj.use_count() == 1);
    std::cout << "Multi-threaded test passed." << std::endl;

    // 主函数结束，shared_obj 离开作用域，最后一次引用计数减少，资源销毁
    return 0;
}
```



## 使用技巧

在手搓 `shared_ptr` 的过程中，逐渐理解到 `std::shared_ptr` 的设计理念、使用方法以及一些细节问题。

Q1: 一个经典的问题，`std::shared_ptr` 是线程安全的吗？

Q2: `std::atomic` 如何使用？

Q3: 什么是内存序，应该如何正确理解并使用内存序？什么是内存屏障？

Q4: 什么是拷贝并交换(copy-and-swap)技巧，为什么只用在拷贝赋值运算符函数中？

Q5: 如何使用互斥量(mutex)保证引用计数的线程安全？

Q6: 为什么使用 `explicit` 关键字显示的定义带参构造函数？

Q7: `fetch_sub()` 的作用是什么？

Q8: 空的 `std::shared_ptr` 的大小是多少字节(在 64 为机器上)？

Q9: 为什么在自己手搓 `unique_ptr` 的时候需要实现 `explicit operator bool()`？其中，为什么使用 `explicit` 关键字？

Q10: 从测试代码中能够学到什么使用 `std::shared_ptr` 的方法？

<mark>TODO</mark>



## 参考资料

[1] [字节跳动C++二面：手撕shared_ptr，源码分享。](https://www.bilibili.com/video/BV1eHwPewE4E)

[2] [【C++ STL】小彭老师带你手搓智能指针：shared_ptr（简介有源码链接）](https://www.bilibili.com/video/BV15eWZeuEsV?spm_id_from=333.1245.0.0)