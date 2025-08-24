# 自己动手实现shared_ptr智能指针

## 核心职责

*   不考虑删除器和空间配置器
*   不考虑弱引用
*   考虑引用计数的线程安全
*   提出测试案例



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





空的 `std::shared_ptr` 的大小为 16 字节（在64位），我们自己实现的 `shared_ptr` 要和其对齐。

使用 `explicit` 防止隐式类型转换，防止出现 `shared_ptr<int> sp = new int(20);`



原子操作来控制引用计数，引用计数使用指针类型，确保所有的 `shared_ptr` 能够共享堆上的资源。

原子操作中的内存序参数



移动构造函数和移动赋值运算符推荐加上 `noexcept`



函数后面加 `const` 的作用



线程安全

*   原子操作
    *   熟悉内存序。什么是内存序，什么是内存屏障。
    *   不熟悉内存序
*   互斥锁



原子操作：

*   原子性
*   顺序性
*   



## 代码实现



## 参考资料

[1] [字节跳动C++二面：手撕shared_ptr，源码分享。](https://www.bilibili.com/video/BV1eHwPewE4E)