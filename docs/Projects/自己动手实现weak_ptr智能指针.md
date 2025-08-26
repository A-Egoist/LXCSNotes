# 自己动手实现weak_ptr智能指针

## 核心职责

`std::shared_ptr` 中有两个指针，一个是管理的原始指针，一个是指向控制块的指针。控制块中有三个指针，1）管理的原始指针；2）引用计数指针；3）弱引用计数指针。



### `std::shared_ptr` 的高级特性，别名构造

允许创建一个新的 `shared_ptr`，它共享另一个 `shared_ptr` 的所有权（即引用计数），但指向其管理对象内部的子对象或成员。它可以避免内存冗余（无需为子对象单独分配所有权，减少额外控制块开销）。

>   [MSVC 和 libstdc++ 的 shared_ptr 实现中为什么保存了两个原始指针？](https://www.zhihu.com/question/278401255/answer/1939298854)
>
>   shared_ptr 的 MSVC 和 gcc 实现里，有两个变量指向原始指针：一个在 shared_ptr 里，一个在控制块中。
>
>   为什么需要两个指针？是否可以只保留后者，为什么？





friend 关键字的作用，友元函数和友元类。



Google Test



### shared_ptr 的循环引用问题

问题：当两个对象互相持有对方的 shared_ptr 时，引用计数永远不会归零。

```cpp
class B;
class A {
public:
    shared_ptr<B> b_ptr;
};
class B {
public:
    shared_ptr<A> a_ptr;
};
```

解决：将其中一个指针改为 weak_ptr，它不会增加引用计数。

```cpp
class B;
class A {
public:
    shared_ptr<B> b_ptr;
};
class B {
public:
    shared_ptr<A> a_ptr;
}
```





### 何时使用 weak_ptr

当观察对象但不拥有所有权时。





### 实现要点

1.   为什么需要两个引用计数？</br>

     强引用计数用来记录有多少个 `shared_ptr` 共享对象所有权；
     弱引用计数用来记录有多少个 `weak_ptr` 观察该对象。

2.   为什么 `shared_ptr` 只有一个 `control_block<T>* cb_`，而不加一个 `T* ptr_`？
     不考虑实现别名构造，`control_block` 里面的 `ptr_`，在 gcc 中就是指代拥有指针，而 `T* ptr_` 是存储指针。

3.   什么时候删除对象，什么时候删除控制块？
     强引用计数为 0 时删除对象，强引用计数和弱引用计数都为 0 时删除控制块。

4.   为什么 `weak_ptr::lock` 方法需要循环？
     防止对象已被销毁时还返回有效指针。多线程下，可能有线程正在销毁最后一个 `shared_ptr`，而此时另一个线程调用 `weak_ptr::lock`。如果直接判断引用计数大于 0 就加 1，可能在判断和加 1 之间对象已被销毁，导致悬垂指针。



gcc 中实现的 `shared_ptr` 的内存结构：

![image-20250826170909237](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508261709396.png)



自己实现的 `shared_ptr` 的内存结构：

![image-20250826170945083](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202508261709892.png)

## 接口需求



## 代码实现

### 基本功能

```cpp
#pragma once

#include <atomic>
#include <stdexcept>

template <typename T>
struct control_block {
    std::atomic<std::size_t>* shared_count_;  // 强引用计数
    std::atomic<std::size_t>* weak_count_;  // 弱引用计数
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
        std::size_t old_shared_count = cb_->shared_count_->fetch_sub(1, std::memory_order_acq_rel);
        if (old_shared_count == 1) {
            delete cb_->ptr_;  // 释放控制块中的 ptr_
            cb_->ptr_ = nullptr;  // 标记 control_block 中的 ptr_ 已释放

            // 如果弱引用为 0，立即删除控制块
            if (cb_->weak_count_->load(std::memory_order_acquire)) {
                delete cb_;
            }
        }
        cb_ = nullptr;  // 清空控制块指针
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) noexcept : cb_(other.cb_) {
        if (cb_) {
            cb_->shared_count_->fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 移动构造函数
    shared_ptr(shared_ptr&& other) noexcept : cb_(other.cb_) {
        other.cb_ = nullptr;
    }

    // 从 weak_ptr 中构造
    explicit shared_ptr(const weak_ptr<T>& wp) : cb_(wp.cb_) {
        if (cb_ != nullptr) {
            std::size_t current_count = cb_->shared_count_->load(std::memory_order_acquire);
            do {
                if (current_count == 0) {
                    throw std::bad_weak_ptr();  // 如果 weak_ptr 已过期
                }
            } while (!cb_->shared_count_->compare_exchange_weak(current_count, current_count + 1, std::memory_order_acq_rel, std::memory_order_acquire));
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
        return cb_ == nullptr ? 0 : cb_->shared_count_->load(std::memory_order_acquire);
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
        std::size_t old_weak_count = cb_->weak_count_->fetch_sub(1, std::memory_order_acq_rel);
        // 最后一个 weak_ptr
        if (old_weak_count == 1) {
            // 若对象已释放(强引用为0)，删除控制块
            if (cb_->shared_count_->load(std::memory_order_acquire) == 0) {
                delete cb_;
            }
        }
        cb_ = nullptr;
    }

    // 拷贝构造函数
    weak_ptr(const weak_ptr& other) noexcept : cb_(other.cb_) {
        if (cb_ != nullptr) {
            cb_->weak_count_->fetch_add(1, std::memory_order_relaxed);
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
            std::move(cb_, temp.cb_);
        }
        return *this;
    }

    // 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& sp) noexcept : cb_(sp.cb_) {
        if (cb_ != nullptr) {
            cb_->weak_count_->fetch_add(1, std::memory_order_relaxed);
        }
    }

    // 从 share_ptr 赋值
    weak_ptr& operator=(const shared_ptr<T>& sp) {
        weak_ptr temp(sp);
        std::swap(cb_, temp.cb_);
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

    // get()
    T* get() const noexcept{
        return cb_ == nullptr ? nullptr : cb_->ptr_;
    }

    // use_count()
    std::size_t use_count() const noexcept{
        return cb_ == nullptr ? 0 : cb_->weak_count_->load(std::memory_order_acquire);
    }

    // reset()
    void reset(T& p = nullptr) noexcept {
        weak_ptr temp(p);
        std::swap(cb_, temp.cb_);
    }

    // bool() 重载
    explicit operator bool() const noexcept {
        return cb_ != nullptr && cb_->ptr_ != nullptr;
    }

    // 检查对象是否有效

    // 安全获取 shared_ptr，lock()
};
```





## 测试代码



## 使用技巧



## 参考资料

[1] [某量化C++实习二面：手撕weak_ptr，文档源码分享~【码农Mark】](https://www.bilibili.com/video/BV1BBKHztEvE)

[2] 

