# 自己动手实现weak_ptr智能指针

## 核心职责

`std::weak_ptr` 是 C++11 标准库中的智能指针，它用于打破  `std::shared_ptr` 的循环引用问题，并提供一种非拥有型的对共享资源的访问方式（观察模式）。`std::weak_ptr` 不会增加对象的引用计数(`shared_count_`)，因此不会阻止观察对象被销毁。它主要用于观察 `std::shared_ptr` 管理的对象，但不控制对象的生命周期。我们需要维护一个指向 `shared_ptr` 对象的弱引用，并能够从中获取原始的 `shared_ptr`。这涉及到引用计数(`shared_count_`)和弱引用计数(`weak_count_`)的管理。

观察性访问：允许观察一个对象而不阻止它的销毁，如果观察对象已被销毁，`weak_ptr` 应该返回一个空的 `shared_ptr`。

`std::shared_ptr` 中有两个指针，一个是管理的原始指针，一个是指向控制块的指针。控制块中有三个指针，1）管理的原始指针；2）引用计数指针；3）弱引用计数指针。



### `std::shared_ptr` 的高级特性，别名构造

允许创建一个新的 `shared_ptr`，它共享另一个 `shared_ptr` 的所有权（即引用计数），但指向其管理对象内部的子对象或成员。它可以避免内存冗余（无需为子对象单独分配所有权，减少额外控制块开销）。

>   [MSVC 和 libstdc++ 的 shared_ptr 实现中为什么保存了两个原始指针？](https://www.zhihu.com/question/278401255/answer/1939298854)
>
>   shared_ptr 的 MSVC 和 gcc 实现里，有两个变量指向原始指针：一个在 shared_ptr 里，一个在控制块中。
>
>   为什么需要两个指针？是否可以只保留后者，为什么？



### shared_ptr 的循环引用问题

问题：当两个对象互相持有对方的 shared_ptr 时，引用计数永远不会归零。

如下代码所示，有两个类 `A` 和 `B`，创建两个实例并让他们相互引用，当 `a` 和 `b` 离开作用域时，它们的引用计数会减 1，但不会变为 0：

*   `a` 离开作用域，`a` 的引用计数从 2 变为 1，因为 `b->a_ptr` 仍然指向它；
*   `b` 离开作用域，`b` 的引用计数从 2 变为 1，因为 `a->b_ptr` 仍然指向它。

由于 `a` 和 `b` 的引用计数永远不会变为 0，它们所管理的内存将永远不会被释放，这就会导致**内存泄露**。

```cpp
#include <iostream>
#include <memory>

class B;

class A {
public:
    std::shared_ptr<B> b_ptr;
};

class B {
public:
    std::shared_ptr<A> a_ptr;
};

int main() {
    {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();
    
        a->b_ptr = b;
        b->a_ptr = a;
    
        std::cout << "a.use_count() = " << a.use_count() << '\n';
        std::cout << "b.use_count() = " << b.use_count() << '\n';
    }

    return 0;
}
```

解决：将其中一个指针改为 weak_ptr，它不会增加引用计数。

```cpp
#include <iostream>
#include <memory>

class B;

class A {
public:
    std::shared_ptr<B> b_ptr;
};

class B {
public:
    std::weak_ptr<A> a_ptr;  // 使用 weak_ptr
};

int main() {
    {
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();
    
        a->b_ptr = b;
        b->a_ptr = a;  // a 的引用计数仍然为 1，弱引用计数为 1
    
        std::cout << "a.use_count() = " << a.use_count() << '\n';
        std::cout << "b.use_count() = " << b.use_count() << '\n';
    }

    return 0;
}
```

`std::weak_ptr` 是一种弱引用，它不会增加对象的引用计数(`shared_count_`)，它只是一种“观察者”，可以安全的访问被 `shared_ptr` 管理的对象，但不会阻止该对象被销毁。

将类 `B` 中的 `std::shared_ptr` 替换为 `std::weak_ptr` 已解决循环引用的问题。当 `a` 和 `b` 离开作用域时：

*   `a` 离开作用域，`a` 的引用计数从 1 变为 0，当引用计数变为 0 时，`a` 所管理的内存被释放。
*   `b` 离开作用域，`b` 的引用计数从 2 变为 1，因为 `a->b_ptr` 仍然指向它。但是 `a` 已经被销毁，所以当 `a->b_ptr` 离开作用域被重置时，`b` 的引用计数从 1 变为 0，然后 `b` 的内存也会被释放。



### 何时使用 weak_ptr

当观察对象但不拥有所有权时。





### 实现要点

1.   为什么需要两个引用计数？</br>

     引用计数用来记录有多少个 `shared_ptr` 共享对象所有权；
     弱引用计数用来记录有多少个 `weak_ptr` 观察该对象。

2.   为什么 `shared_ptr` 只有一个 `control_block<T>* cb_`，而不加一个 `T* ptr_`？
     不考虑实现别名构造，`control_block` 里面的 `ptr_`，在 gcc 中就是指代拥有指针，而 `T* ptr_` 是存储指针。

3.   什么时候删除对象，什么时候删除控制块？
     强引用计数为 0 时删除对象，引用计数和弱引用计数都为 0 时删除控制块。

4.   为什么 `weak_ptr::lock` 方法需要循环？
     防止对象已被销毁时还返回有效指针。多线程下，可能有线程正在销毁最后一个 `shared_ptr`，而此时另一个线程调用 `weak_ptr::lock`。如果直接判断引用计数大于 0 就加 1，可能在判断和加 1 之间对象已被销毁，导致悬垂指针。



gcc 中实现的 `shared_ptr` 的内存结构：

![image-20250826170909237](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508261709396.png)



自己实现的 `shared_ptr` 的内存结构：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508261709892.png" alt="image-20250826170945083" style="zoom: 50%;" />

## 接口需求

`weak_ptr` 主要是配合 `shared_ptr` 使用，所以 `weak_ptr` 模板类的成员方法不多，常用的有：

*   默认构造函数
*   析构函数，析构时弱引用计数(`weak_count_`)减 1，如果弱引用计数为 0 且引用计数(`shared_count_`)为 0，则删除控制块
*   拷贝构造函数、移动构造函数、拷贝赋值运算符函数，移动赋值运算符函数
*   提供从 `shared_ptr` 构造和赋值的拷贝构造函数和拷贝赋值运算符函数
*   use_count()，返回引用计数(`shared_count_`)
*   reset()，将当前 `weak_ptr` 重置为空指针
*   expired()，判断当前 `weak_ptr` 观察的对象是否到期
*   lock()，如果当前观察对象已经过期，返回一个空的 `shared_ptr`，否则返回有效的 `shared_ptr` 并且对应的引用计数加 1

对应的，需要在 `shared_ptr` 中提供从 `weak_ptr` 构造 `shared_ptr` 对象的构造函数，还需要提供从 `cb_` 构造 `shared_ptr` 对象的构造函数。



## 代码实现

### 控制块

```cpp
template <typename T>
struct control_block {
    std::atomic<std::size_t> shared_count_;  // 强引用计数
    std::atomic<std::size_t> weak_count_;  // 弱引用计数
    T* ptr_;  // 管理的原始指针
    
    control_block(T* p, std::size_t shared_init, std::size_t weak_init) : ptr_(p), shared_count_(shared_init), weak_count_(weak_init) {}
};
```



### `shared_ptr` 类

```cpp
template <typename T>
class shared_ptr {
private:
    template <typename U>
    friend class weak_ptr;

    control_block<T>* cb_;

    // 私有构造函数，供(weak_ptr::lock()使用) 
    explicit shared_ptr(control_block<T>* block) : cb_(block) {}

public:
    shared_ptr() noexcept : cb_(nullptr) {}

    explicit shared_ptr(T* p) {
        if (p) {
            cb_ = new control_block(p, 1, 0);  // 强引用 = 1，弱引用 = 0
        } else {
            cb_ = nullptr;
        }
    }
    
    // 析构函数
    ~shared_ptr() {
        if (cb_ == nullptr) return;

        // 原子减少强引用计数
        std::size_t old_shared_count = cb_->shared_count_.fetch_sub(1, std::memory_order_acq_rel);
        if (old_shared_count == 1) {
            delete cb_->ptr_;  // 释放控制块中的 ptr_
            cb_->ptr_ = nullptr;  // 标记 control_block 中的 ptr_ 已释放

            // 如果弱引用为 0，立即删除控制块
            if (cb_->weak_count_.load(std::memory_order_acquire) == 0) {
                delete cb_;
            }
        }
        cb_ = nullptr;
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) noexcept : cb_(other.cb_) {
        if (cb_) {
            cb_->shared_count_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 移动构造函数
    shared_ptr(shared_ptr&& other) noexcept : cb_(other.cb_) {
        other.cb_ = nullptr;
    }

    // 从 weak_ptr 中构造
    explicit shared_ptr(const weak_ptr<T>& wp) {
        cb_ = wp.cb_;
        if (cb_ != nullptr) {
            std::size_t current_count = cb_->shared_count_.load(std::memory_order_acquire);
            do {
                if (current_count == 0) {
                    throw std::bad_weak_ptr();  // 如果 weak_ptr 已过期
                }
            } while (!cb_->shared_count_.compare_exchange_weak(current_count, current_count + 1, std::memory_order_acq_rel, std::memory_order_acquire));
        }
    }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other) noexcept {
        // 自赋值
        if (this != &other) {
            shared_ptr temp(other);  // 使用临时对象交换
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 移动赋值运算符
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            shared_ptr temp(std::move(other));
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 解引用运算符
    T& operator*() const noexcept {
        return *cb_->ptr_;
    }

    // 箭头运算符
    T* operator->() const noexcept {
        return cb_->ptr_;
    }

    // get() 获取原始指针
    T* get() const noexcept {
        return cb_ == nullptr ? nullptr : cb_->ptr_;
    }

    // use_count() 获得强引用计数
    std::size_t use_count() const noexcept {
        return cb_ == nullptr ? 0 : cb_->shared_count_.load(std::memory_order_acquire);
    }

    // reset() 重置
    void reset(T* p = nullptr) {
        shared_ptr temp(p);  // 创建一个新的 shared_ptr
        std::swap(cb_, temp.cb_);  // 交换当前对象和临时对象
    }

    // 检查是否为空
    explicit operator bool() const noexcept {
        return cb_ != nullptr && cb_->ptr_ != nullptr;
    }
};
```



### `weak_ptr` 类

```cpp
template <typename T>
class weak_ptr {
private:
    template <typename U>
    friend class shared_ptr;

    control_block<T>* cb_;

public:
    weak_ptr() noexcept : cb_(nullptr) {}

    // 析构函数
    ~weak_ptr() {
        if (cb_ == nullptr) return;

        // 原子引用减少弱引用计数
        std::size_t old_weak_count = cb_->weak_count_.fetch_sub(1, std::memory_order_acq_rel);
        // 最后一个 weak_ptr
        if (old_weak_count == 1) {
            // 若对象已释放(强引用为0)，删除控制块
            if (cb_->shared_count_.load(std::memory_order_acquire) == 0) {
                delete cb_;
            }
        }
        cb_ = nullptr;
    }

    // 拷贝构造函数
    weak_ptr(const weak_ptr& other) noexcept : cb_(other.cb_) {
        if (cb_ != nullptr) {
            cb_->weak_count_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 移动构造函数
    weak_ptr(weak_ptr&& other) noexcept : cb_(other.cb_) {
        other.cb_ = nullptr;
    }

    // 拷贝赋值运算符
    weak_ptr& operator=(const weak_ptr& other) {
        if (this != &other) {
            weak_ptr temp(other);
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 移动赋值运算符
    weak_ptr& operator=(weak_ptr&& other) {
        if (this != &other) {
            weak_ptr temp(std::move(other));
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& sp) noexcept : cb_(sp.cb_) {
        if (cb_ != nullptr) {
            cb_->weak_count_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 从 share_ptr 赋值
    weak_ptr& operator=(const shared_ptr<T>& sp) {
        weak_ptr temp(sp);
        std::swap(cb_, temp.cb_);
        return *this;
    }

    // use_count() 返回强引用计数
    std::size_t use_count() const noexcept{
        return cb_ == nullptr ? 0 : cb_->shared_count_.load(std::memory_order_acquire);
    }

    // reset()
    void reset() noexcept {
        weak_ptr temp;
        std::swap(cb_, temp.cb_);
    }

    // 检查对象是否到期
    bool expired() const noexcept {
        return !cb_ || cb_->shared_count_.load(std::memory_order_acquire) == 0;
    }

    // 安全获取 shared_ptr，lock()
    shared_ptr<T> lock() const noexcept {
        // 快路径判断
        if (expired()) {
            return shared_ptr<T>();
        }

        // 慢路径判断
        std::size_t current_count = cb_->shared_count_.load(std::memory_order_acquire);  // Q: 为什么不需要判断 cb_ 是否为空？ A: 因为当前 weak_ptr 共享了控制块，所以控制块的弱引用计数肯定大于0，所以控制块存在。
        do {
            if (current_count == 0) {
                return shared_ptr<T>();  // 对象已经释放
            }
        } while (!cb_->shared_count_.compare_exchange_weak(current_count, current_count + 1, std::memory_order_acq_rel, std::memory_order_acquire));
        // 第一内存序时成功的情况下使用的内存序，第二个内存序是失败的情况下使用的内存序

        return shared_ptr<T>(cb_);
    }
};
```



### 完整代码

```cpp
#pragma once

#include <atomic>
#include <stdexcept>

template <typename T>
struct control_block {
    std::atomic<std::size_t> shared_count_;  // 强引用计数
    std::atomic<std::size_t> weak_count_;  // 弱引用计数
    T* ptr_;  // 管理的原始指针
    
    control_block(T* p, std::size_t shared_init, std::size_t weak_init) : ptr_(p), shared_count_(shared_init), weak_count_(weak_init) {}
};

template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
private:
    template <typename U>
    friend class weak_ptr;

    control_block<T>* cb_;  // 为什么需要使用 cotrol_block<T> 来作为类型名，而不能使用 control_block ？

    // 私有构造函数，供(weak_ptr::lock()使用) 
    explicit shared_ptr(control_block<T>* block) : cb_(block) {}

public:
    shared_ptr() noexcept : cb_(nullptr) {}

    explicit shared_ptr(T* p) {
        if (p) {
            cb_ = new control_block(p, 1, 0);  // 强引用 = 1，弱引用 = 0
        } else {
            cb_ = nullptr;
        }
    }
    
    // 析构函数
    ~shared_ptr() {
        if (cb_ == nullptr) return;

        // 原子减少强引用计数
        std::size_t old_shared_count = cb_->shared_count_.fetch_sub(1, std::memory_order_acq_rel);
        if (old_shared_count == 1) {
            delete cb_->ptr_;  // 释放控制块中的 ptr_
            cb_->ptr_ = nullptr;  // 标记 control_block 中的 ptr_ 已释放

            // 如果弱引用为 0，立即删除控制块
            if (cb_->weak_count_.load(std::memory_order_acquire) == 0) {
                delete cb_;
            }
        }
        cb_ = nullptr;
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) noexcept : cb_(other.cb_) {
        if (cb_) {
            cb_->shared_count_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 移动构造函数
    shared_ptr(shared_ptr&& other) noexcept : cb_(other.cb_) {
        other.cb_ = nullptr;
    }

    // 从 weak_ptr 中构造
    explicit shared_ptr(const weak_ptr<T>& wp) {
        cb_ = wp.cb_;
        if (cb_ != nullptr) {
            std::size_t current_count = cb_->shared_count_.load(std::memory_order_acquire);
            do {
                if (current_count == 0) {
                    throw std::bad_weak_ptr();  // 如果 weak_ptr 已过期
                }
            } while (!cb_->shared_count_.compare_exchange_weak(current_count, current_count + 1, std::memory_order_acq_rel, std::memory_order_acquire));
        }
    }

    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other) noexcept {
        // 自赋值
        if (this != &other) {
            shared_ptr temp(other);  // 使用临时对象交换
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 移动赋值运算符
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            shared_ptr temp(std::move(other));
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 解引用运算符
    T& operator*() const noexcept {
        return *cb_->ptr_;
    }

    // 箭头运算符
    T* operator->() const noexcept {
        return cb_->ptr_;
    }

    // get() 获取原始指针
    T* get() const noexcept {
        return cb_ == nullptr ? nullptr : cb_->ptr_;
    }

    // use_count() 获得强引用计数
    std::size_t use_count() const noexcept {
        return cb_ == nullptr ? 0 : cb_->shared_count_.load(std::memory_order_acquire);
    }

    // reset() 重置
    void reset(T* p = nullptr) {
        shared_ptr temp(p);  // 创建一个新的 shared_ptr
        std::swap(cb_, temp.cb_);  // 交换当前对象和临时对象
    }

    // 检查是否为空
    explicit operator bool() const noexcept {
        return cb_ != nullptr && cb_->ptr_ != nullptr;
    }
};

template <typename T>
class weak_ptr {
private:
    template <typename U>
    friend class shared_ptr;

    control_block<T>* cb_;

public:
    weak_ptr() noexcept : cb_(nullptr) {}

    // 析构函数
    ~weak_ptr() {
        if (cb_ == nullptr) return;

        // 原子引用减少弱引用计数
        std::size_t old_weak_count = cb_->weak_count_.fetch_sub(1, std::memory_order_acq_rel);
        // 最后一个 weak_ptr
        if (old_weak_count == 1) {
            // 若对象已释放(强引用为0)，删除控制块
            if (cb_->shared_count_.load(std::memory_order_acquire) == 0) {
                delete cb_;
            }
        }
        cb_ = nullptr;
    }

    // 拷贝构造函数
    weak_ptr(const weak_ptr& other) noexcept : cb_(other.cb_) {
        if (cb_ != nullptr) {
            cb_->weak_count_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 移动构造函数
    weak_ptr(weak_ptr&& other) noexcept : cb_(other.cb_) {
        other.cb_ = nullptr;
    }

    // 拷贝赋值运算符
    weak_ptr& operator=(const weak_ptr& other) {
        if (this != &other) {
            weak_ptr temp(other);
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 移动赋值运算符
    weak_ptr& operator=(weak_ptr&& other) {
        if (this != &other) {
            weak_ptr temp(std::move(other));
            std::swap(cb_, temp.cb_);
        }
        return *this;
    }

    // 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& sp) noexcept : cb_(sp.cb_) {
        if (cb_ != nullptr) {
            cb_->weak_count_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 从 share_ptr 赋值
    weak_ptr& operator=(const shared_ptr<T>& sp) {
        weak_ptr temp(sp);
        std::swap(cb_, temp.cb_);
        return *this;
    }

    // use_count() 返回强引用计数
    std::size_t use_count() const noexcept{
        return cb_ == nullptr ? 0 : cb_->shared_count_.load(std::memory_order_acquire);
    }

    // reset()
    void reset() noexcept {
        weak_ptr temp;
        std::swap(cb_, temp.cb_);
    }

    // 检查对象是否到期
    bool expired() const noexcept {
        return !cb_ || cb_->shared_count_.load(std::memory_order_acquire) == 0;
    }

    // 安全获取 shared_ptr，lock()
    shared_ptr<T> lock() const noexcept {
        // 快路径判断
        if (expired()) {
            return shared_ptr<T>();
        }

        // 慢路径判断
        std::size_t current_count = cb_->shared_count_.load(std::memory_order_acquire);  // Q: 为什么不需要判断 cb_ 是否为空？ A: 因为当前 weak_ptr 共享了控制块，所以控制块的弱引用计数肯定大于0，所以控制块存在。
        do {
            if (current_count == 0) {
                return shared_ptr<T>();  // 对象已经释放
            }
        } while (!cb_->shared_count_.compare_exchange_weak(current_count, current_count + 1, std::memory_order_acq_rel, std::memory_order_acquire));
        // 第一内存序时成功的情况下使用的内存序，第二个内存序是失败的情况下使用的内存序

        return shared_ptr<T>(cb_);
    }
};
```



## 测试代码

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <memory> // 为了与标准库做对比
#include "MyWeakPtr001.h"

// 用于追踪对象生命周期的类
struct TestObject {
    static std::atomic<int> creation_count;
    static std::atomic<int> deletion_count;
    int id;

    TestObject(int i) : id(i) {
        creation_count++;
        std::cout << "TestObject(" << id << ") created. Total: " << creation_count << std::endl;
    }
    ~TestObject() {
        deletion_count++;
        std::cout << "TestObject(" << id << ") destroyed. Total: " << deletion_count << std::endl;
    }
};
std::atomic<int> TestObject::creation_count = 0;
std::atomic<int> TestObject::deletion_count = 0;

void print_status(const shared_ptr<TestObject>& sp, const std::string& name) {
    std::cout << "--- Status of " << name << " ---" << std::endl;
    std::cout << name << " is " << (sp.get() ? "not null" : "null") << std::endl;
    if (sp.get()) {
        std::cout << "Value: " << (*sp).id << std::endl;
        std::cout << "shared_count: " << sp.use_count() << std::endl;
        std::cout << "Pointer address: " << sp.get() << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}

void print_weak_status(const weak_ptr<TestObject>& wp, const std::string& name) {
    std::cout << "--- Status of weak_ptr " << name << " ---" << std::endl;
    std::cout << name << " is " << (wp.expired() ? "expired" : "not expired") << std::endl;
    shared_ptr<TestObject> sp = wp.lock();
    if (sp) {
        std::cout << "Successfully locked. Shared count: " << sp.use_count() << std::endl;
    } else {
        std::cout << "Failed to lock. Object has been destroyed." << std::endl;
    }
    std::cout << "----------------------" << std::endl;
}

// 模拟多线程竞争
void shared_ptr_thread_func(shared_ptr<TestObject> sp) {
    for (int i = 0; i < 10000; ++i) {
        shared_ptr<TestObject> temp = sp;
        shared_ptr<TestObject> temp2 = temp;
    }
}

int main() {
    std::cout << "--- Single-threaded Test ---" << std::endl;

    // 1. 基本 shared_ptr 和 weak_ptr 构造
    shared_ptr<TestObject> sp1(new TestObject(100));
    weak_ptr<TestObject> wp1 = sp1;

    print_status(sp1, "sp1");
    print_weak_status(wp1, "wp1");
    assert(sp1.use_count() == 1);

    // 2. 拷贝构造 shared_ptr
    shared_ptr<TestObject> sp2 = sp1;
    assert(sp1.use_count() == 2);
    print_status(sp2, "sp2");

    // 3. 释放一个 shared_ptr
    sp2.reset();
    assert(sp1.use_count() == 1);
    print_status(sp1, "sp1 after sp2 reset");

    // 4. weak_ptr 失去控制对象
    {
        shared_ptr<TestObject> sp3(new TestObject(200));
        weak_ptr<TestObject> wp2 = sp3;
        print_weak_status(wp2, "wp2 before sp3 destroy");
    } // sp3 离开作用域，TestObject(200) 被销毁，但控制块仍然存在

    std::cout << "After sp3 destroyed, TestObject(200) is gone, but wp2 is still alive." << std::endl;
    print_weak_status(wp1, "wp1 (unaffected)");
    // 5. weak_ptr 已过期，lock() 失败
    {
        weak_ptr<TestObject> wp2;
        wp2 = wp1; // weak_ptr 拷贝赋值
        assert(wp1.lock().get() == sp1.get());
    } // wp2 销毁

    // 6. 验证循环引用问题
    std::cout << "--- Circular Reference Test ---" << std::endl;
    struct Node {
        shared_ptr<Node> next;
        weak_ptr<Node> prev;
        ~Node() { std::cout << "Node destroyed." << std::endl; }
    };

    shared_ptr<Node> n1 = shared_ptr<Node>(new Node());
    shared_ptr<Node> n2 = shared_ptr<Node>(new Node());
    
    n1->next = n2;  // 
    n2->prev = n1;  // 使用 weak_ptr 避免循环引用

    // std::cout << n1.use_count() << std::endl;
    // std::cout << n2.use_count() << std::endl;
    assert(n1.use_count() == 1);
    assert(n2.use_count() == 2);

    // 7. 多线程测试 (验证线程安全)
    std::cout << "--- Multi-threaded Test ---" << std::endl;
    shared_ptr<TestObject> thread_sp(new TestObject(300));
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(shared_ptr_thread_func, thread_sp);
    }
    for (auto& t : threads) {
        t.join();
    }
    print_status(thread_sp, "thread_sp after multi-threaded operations");
    assert(thread_sp.use_count() == 1);

    // Final cleanup check
    sp1.reset();
    thread_sp.reset();
    std::cout << "Final creation count: " << TestObject::creation_count << ", Final deletion count: " << TestObject::deletion_count << std::endl;
    assert(TestObject::creation_count == TestObject::deletion_count);

    return 0;
}
```



## 总结

### 手撕 `weak_ptr` 的两个关键点

#### 1 `weak_ptr` 和 `shared_ptr` 的析构函数

`weak_ptr` 和 `shared_ptr` 的析构函数必须协同工作，以确保内存安全。它们需要解决两个问题：何时释放原始对象 (`ptr_` 指向的对象) 和何时释放控制块。目前采用的策略是：

*   在 `~shared_ptr()` 中，先将引用计数减 1，如果引用计数减为 0，表明当前 `shared_ptr` 是最后一个 `shared_ptr`，此时应该释放其管理的对象。然后再看此时控制块中弱引用计数是否为 0，若为 0，则应该删除控制块。
*   在 `~weak_ptr()` 中，现将弱引用计数减 1，如果弱引用计数减为 0，表明当前 `weak_ptr` 是最后一个 `weak_ptr`，此时再看 `shared_ptr` 是否为 0，若为 0，则应该删除控制块。

这样可以保证原始对象 `ptr_` 由最后一个 `shared_ptr` 销毁，而控制块则由最后一个智能指针销毁。



#### 2 `weak_ptr` 中的 `lock()` 函数

`lock()` 函数用于返回当前 `weak_ptr` 观察的 `shared_ptr` 对象，并将引用计数加 1，如果观察的对象已过期，返回一个空的 `shared_ptr`。在实现过程中需要原子且线程安全地获取对应的 `shared_ptr`。为了保证在**尝试增加引用计数时，确保原始对象没有被其他线程销毁**。所以使用了 `compare_exchange_weak(current_count, current_count + 1, memory_order_acq_rel, memory_order_acquire)`。

为什么使用 `compare_exchange_weak`？假设线程 A 在执行 `lock()`，它读取 `shared_count_` 为 1，就在它准备增加引用计数时，线程 B 销毁了最后一个 `shared_ptr`，将 `shared_count_` 减为 0，并销毁了原始对象。如果 `lock()` 没有使用原子操作，线程 A 可能会在对象被销毁后增加一个过时的引用计数，然后返回一个指向已销毁对象的 `shared_ptr`，导致悬空指针。

而 `compare_exchange_weak` 提供了**原子性的“读取-修改-写入”**操作：

1.  它读取 `shared_count_`。
2.  检查读取到的值是否等于 `current_count`。
3.  如果是，则将 `shared_count_` 原子性地更新为 `current_count + 1`，并返回 `true`。
4.  如果不是（说明在读取后有其他线程修改了它），则不做任何操作，并返回 `false`。

这个循环确保了，`lock()` 只会在成功将引用计数从一个**有效值**增加时才返回一个 `shared_ptr`。如果它发现 `shared_count_` 已经为 0，它会安全地退出并返回空指针，从而杜绝了悬空指针的使用。



### `lock()` 的另一种实现

```cpp
// 另一种 lock() 实现
shared_ptr<T> lock() const noexcept {
    try {
        return shared_ptr<T>(*this); // 调用 shared_ptr(const weak_ptr<T>& wp)
    } catch (const std::bad_weak_ptr&) {
        return shared_ptr<T>();
    }
}
```

在这种设计中，`shared_ptr(const weak_ptr<T>& wp)` 构造函数才是所有复杂逻辑的真正封装者。

```cpp
// 从 weak_ptr 中构造
explicit shared_ptr(const weak_ptr<T>& wp) {
    cb_ = wp.cb_;
    if (cb_ != nullptr) {
        std::size_t current_count = cb_->shared_count_.load(std::memory_order_acquire);
        do {
            if (current_count == 0) {
                throw std::bad_weak_ptr();  // 如果 weak_ptr 已过期
            }
        } while (!cb_->shared_count_.compare_exchange_weak(current_count, current_count + 1, std::memory_order_acq_rel, std::memory_order_acquire));
    }
}
```



### `friend` 关键字

友元函数

友元类



### valgrind 定位内存泄露

>   [Linux内存泄露定位1：valgrind篇](https://mp.weixin.qq.com/s/dWbqNIA4pLWs4pd53Gaq8A)

使用方法：

```bash
valgrind --leak-check=full ./main
```

检测结果：

```text
==52600== Memcheck, a memory error detector
==52600== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==52600== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==52600== Command: ./main
==52600==
--- Single-threaded Test ---
TestObject(100) created. Total: 1
--- Status of sp1 ---
sp1 is not null
Value: 100
shared_count: 1
Pointer address: 0x4e214c0
----------------------
--- Status of weak_ptr wp1 ---
wp1 is not expired
Successfully locked. Shared count: 2
----------------------
--- Status of sp2 ---
sp2 is not null
Value: 100
shared_count: 2
Pointer address: 0x4e214c0
----------------------
--- Status of sp1 after sp2 reset ---
sp1 after sp2 reset is not null
Value: 100
shared_count: 1
Pointer address: 0x4e214c0
----------------------
TestObject(200) created. Total: 2
--- Status of weak_ptr wp2 before sp3 destroy ---
wp2 before sp3 destroy is not expired
Successfully locked. Shared count: 2
----------------------
TestObject(200) destroyed. Total: 1
After sp3 destroyed, TestObject(200) is gone, but wp2 is still alive.
--- Status of weak_ptr wp1 (unaffected) ---
wp1 (unaffected) is not expired
Successfully locked. Shared count: 2
----------------------
--- Circular Reference Test ---
--- Multi-threaded Test ---
TestObject(300) created. Total: 3
--- Status of thread_sp after multi-threaded operations ---
thread_sp after multi-threaded operations is not null
Value: 300
shared_count: 1
Pointer address: 0x4e218a0
----------------------
TestObject(100) destroyed. Total: 2
TestObject(300) destroyed. Total: 3
Final creation count: 3, Final deletion count: 3
Node destroyed.
Node destroyed.
==52600== Invalid write of size 8
==52600==    at 0x10B6F9: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:48)
==52600==    by 0x10B35B: main (test_MyWeakPtr.cpp:133)
==52600==  Address 0x4e217a0 is 16 bytes inside a block of size 24 free'd
==52600==    at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52600==    by 0x10B884: weak_ptr<main::Node>::~weak_ptr() (MyWeakPtr001.h:155)
==52600==    by 0x10AA04: main::Node::~Node() (test_MyWeakPtr.cpp:99)
==52600==    by 0x10B6E4: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:47)
==52600==    by 0x10AA10: main::Node::~Node() (test_MyWeakPtr.cpp:99)
==52600==    by 0x10B6E4: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:47)
==52600==    by 0x10B35B: main (test_MyWeakPtr.cpp:133)
==52600==  Block was alloc'd at
==52600==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52600==    by 0x10B8E3: shared_ptr<main::Node>::shared_ptr(main::Node*) (MyWeakPtr001.h:34)
==52600==    by 0x10AF67: main (test_MyWeakPtr.cpp:102)
==52600==
==52600== Invalid read of size 8
==52600==    at 0x10B767: load (atomic_base.h:505)
==52600==    by 0x10B767: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:51)
==52600==    by 0x10B35B: main (test_MyWeakPtr.cpp:133)
==52600==  Address 0x4e21798 is 8 bytes inside a block of size 24 free'd
==52600==    at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52600==    by 0x10B884: weak_ptr<main::Node>::~weak_ptr() (MyWeakPtr001.h:155)
==52600==    by 0x10AA04: main::Node::~Node() (test_MyWeakPtr.cpp:99)
==52600==    by 0x10B6E4: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:47)
==52600==    by 0x10AA10: main::Node::~Node() (test_MyWeakPtr.cpp:99)
==52600==    by 0x10B6E4: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:47)
==52600==    by 0x10B35B: main (test_MyWeakPtr.cpp:133)
==52600==  Block was alloc'd at
==52600==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52600==    by 0x10B8E3: shared_ptr<main::Node>::shared_ptr(main::Node*) (MyWeakPtr001.h:34)
==52600==    by 0x10AF67: main (test_MyWeakPtr.cpp:102)
==52600==
==52600== Invalid free() / delete / delete[] / realloc()
==52600==    at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52600==    by 0x10B78D: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:52)
==52600==    by 0x10B35B: main (test_MyWeakPtr.cpp:133)
==52600==  Address 0x4e21790 is 0 bytes inside a block of size 24 free'd
==52600==    at 0x484A61D: operator delete(void*, unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52600==    by 0x10B884: weak_ptr<main::Node>::~weak_ptr() (MyWeakPtr001.h:155)
==52600==    by 0x10AA04: main::Node::~Node() (test_MyWeakPtr.cpp:99)
==52600==    by 0x10B6E4: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:47)
==52600==    by 0x10AA10: main::Node::~Node() (test_MyWeakPtr.cpp:99)
==52600==    by 0x10B6E4: shared_ptr<main::Node>::~shared_ptr() (MyWeakPtr001.h:47)
==52600==    by 0x10B35B: main (test_MyWeakPtr.cpp:133)
==52600==  Block was alloc'd at
==52600==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52600==    by 0x10B8E3: shared_ptr<main::Node>::shared_ptr(main::Node*) (MyWeakPtr001.h:34)
==52600==    by 0x10AF67: main (test_MyWeakPtr.cpp:102)
==52600==
==52600==
==52600== HEAP SUMMARY:
==52600==     in use at exit: 0 bytes in 0 blocks
==52600==   total heap usage: 41 allocs, 42 frees, 78,546 bytes allocated
==52600==
==52600== All heap blocks were freed -- no leaks are possible
==52600==
==52600== For lists of detected and suppressed errors, rerun with: -s
==52600== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
```



### Google Test

使用 Google Test 测试手搓 `shared_ptr` 和 `weak_ptr` 的效果。





## 参考资料

[1] [某量化C++实习二面：手撕weak_ptr，文档源码分享~【码农Mark】](https://www.bilibili.com/video/BV1BBKHztEvE)

[2] 

