# 字节跳动-tac-客户端

## 二面

>   飞书妙记：https://swpu.feishu.cn/minutes/obcn3s6mo95i1m85h4djn6c6

1.   自我介绍

2.   这些项目中（自我介绍提到的项目）你觉得最有挑战的是哪一个？

3.   你能不能介绍一下他的业务背景，他要完成什么样的业务目标，然后你在里面碰到的难点和你的解决方案

4.   有没有人反馈过这个软件存在故障之类的问题？如何去解决以保证程序的稳定？

5.   讲一讲你在第二段实习中值得分享的事情？在这个过程中有碰到什么紧急的事情吧？如何解决的。

6.   场景题1：

     >   假设你有一个主任务，有三个子任务 a、b、 c，它们需要统计每个区域的故障率，a 线程执行 a 任务， a 任务它需要统计 a 区域中正常设备的数量，或者说设备的故障率。然后b 任务统计 b 区域的，c 任务统计 c 区域的，然后主任务需要收集 a、b、c 三个区域的最终结果，然后计算一个整体的这个故障率，然后返回给用户。你如果用你熟悉的语言，你会用什么样的模型或者什么样的技术手段去解决这个问题？

7.   场景题1，追问：主线程怎么确保所有的事情都执行完了？

8.   场景题1，追问：还有个问题，就是说如果有一个子线程特别慢，或者它出现故障了，它把整个系统拖慢了。你的主线程，还有这些子线程，它们资源都释放不了，这种情况下怎么处理？

9.   场景题1，追问：超时停止，ok，那主线程怎么知道子线程超时了？

10.   场景题1，追问：好，这个任务变复杂了，它可能不是三个子任务，不是三个区域，大概有可能有 100 个区域，有 100 个任务需要去做。你会创建 100 个子线程吗？

11.   场景题1，追问：那这个核心线程数应该怎么计算？设置多少是合适的？

12.   场景题1，追问：那如果你一开始给个经验值的话，你会怎么给？

13.   场景题2：

      >   还有一个设计题，就是我有一个订单库，或者有一个订有 1, 000 万个订单，然后，嗯，这里面有 1% 到 2% 的订单可能会超时，然后我们在超时之前需要给用户发一个提醒。举个例子，就比如说一个订单它两小时就超时了，嗯，我们在一小时 59 分的时候需要去给用户发一个短信或者啥的，或者是站内信之类的，然后怎么去设计怎么运用自己学过的这个数据结构，还有中位数或者是一些模型都可以，然后来解决这个问题，就只需要解决触发就行，后面的发送短信这些就可以忽略掉。

14.   场景题2，追问：但这个东西有多大呢？因为你如果是总量 1, 000 万的订单，嗯，那就假设你增量的订单大概是百分之 10% 左右，是吧？那你这个订单就是在你的订单大概有 10% 左右，你这里面要放 100 万的数据吗？

15.   场景题2，追问：你可以计算一下，就是你内存放不放得下，假设就是有 100 万个 100 万订单。

16.   你自己对自己的职业规划大概是什么样子，然后以及假设你最终来到团队以后，你对自己的预期什么样子？

17.   你觉得自己最大的优势和最大的劣势是什么？

18.   笔试：[200. 岛屿数量](https://leetcode.cn/problems/number-of-islands/)

19.   反问1：可能会接触到什么方向的业务？

20.   反问2：进来之后使用的技术栈大概有哪些？



## 一面

>   飞书妙记：https://swpu.feishu.cn/minutes/obcnyur97p89x5ccp5z6vw35



1.   自我介绍
2.   项目
3.   C++ 中指针和引用的区别是什么？
4.   C++ 中为什么会引入右值和移动语义？
5.   平时你自己写类的时候，你什么时候你会为这个类实现拷贝构造函数或者移动构造函数？
6.   为什么要去实现拷贝构造函数和移动构造函数
7.   这个与深拷贝和浅拷贝的关系
8.   函数调用约定了解吗？
9.   函数的调用过程了解吗？
10.   函数调用过程中的堆栈的过程了解吗
11.   说一下共享指针的特性和实现原理
12.   share from this 是什么？了解这个机制吗？
13.   说一说你对数组和链表这两种最基础的数据结构的认识，访问方式，内存布局，适用场景
14.   如果你要实现一个队列，在底层你会选择哪一个作为它的数据结构？
15.   如何遍历二叉树，如果将二叉树的内容遍历出来
16.   进程和线程有什么区别
17.   你了解进程的内存布局吗
18.   栈的扩展方向是怎么样的？你觉得为什么要这么设计？栈空间一般大概是多少？
19.   一台电脑到底能够创建多少个进程，一个进程最多能够创建多少线程？
20.   TCP 和 UDP 的区别
21.   TCP 的握手过程是怎么样的？
22.   在网络 I/O 模型中，select 和 epoll 的区别是什么？
23.   在调用了 select 或者 epoll 函数之后，当收到客户端的连接请求之后，到 select 或者 epoll 函数返回之后，这中间他们做了什么？要从这里深入了解 select 和 epoll 的具体区别，比如说涉及到用户空间和内核空间的切换，并不是在所有场景下 epoll 的性能都比 select 高。
24.   你有什么职业规划吗？
25.   你平时都是通过什么样的范式或者途径来提升自己的技术能力和视野？
26.   在你了解的项目中，或者你在网上看到的项目中，能举一两个你印象比较深刻的吗？
27.   考一个多线程编程的一个最常见的模型，多消费者多生产者模型。

```cpp
#include <chrono>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <string>
#include <atomic>

class BlockingQueue {
public:
    BlockingQueue(int max_size) : MAX_SIZE_(max_size) {}
    
    ~BlockingQueue() {

    }

    bool push(int value) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_producter_.wait(lock, [&]() { return queue_.size() < MAX_SIZE_ || is_stop_; });
        if (is_stop_.load() == true) {
            return false;
        }
        queue_.push(value);
        cv_consumer_.notify_one();
        return true;
    }

    bool pop(int& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_consumer_.wait(lock, [&]() { return !queue_.empty() || is_stop_; });
        if (is_stop_.load() == true) {
            return false;
        }
        value = queue_.front();
        queue_.pop();
        cv_producter_.notify_one();
        return true;
    }

    void stop() {
        is_stop_ = true;

        cv_consumer_.notify_all();
        cv_producter_.notify_all();
    }

private:
    std::queue<int> queue_;
    int MAX_SIZE_;
    // bool is_stop_;
    std::atomic<bool> is_stop_{false};
    std::mutex mutex_;
    std::condition_variable cv_consumer_;
    std::condition_variable cv_producter_;
};

BlockingQueue blocking_queue(16);


void worker_producter(std::string name, int value) {
    while (true) {
        std::cout << "Producter: name = " << name << ", value = " << value << "\n";
        if (!blocking_queue.push(value)) {
            break;
        }
        
    }
}

void worker_consumer(std::string name) {
    while (true) {
        int value;
        if (blocking_queue.pop(value)) {
            std::cout << "Consumer: name = " << name << ", value = " << value << "\n";
        } else {
            break;
        }
    }
}

int main() {
    std::thread t1(worker_producter, "1", 1);
    std::thread t2(worker_producter, "2", 2);
    std::thread t3(worker_consumer, "3");
    std::thread t4(worker_consumer, "4");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    blocking_queue.stop();
    
    if (t1.joinable()) {
        t1.join();
    }
    if (t2.joinable()) {
        t2.join();
    }
    if (t3.joinable()) {
        t3.join();
    }
    if (t4.joinable()) {
        t4.join();
    }

    return 0;
}
```

------反问环节------

28.   前面的面试中，你也提到了我对底层的了解不够深入，我想问一下这方面我可以从哪些方面来提升？

      >   你是最值得学习的对象。其实不是网上的各种开源库，什么哪个博客的这些什么项目，其实不是。所以你最想，如果你想提高你的技术，就是最，你最应该学习的是标准库。
      >
      >   对，标准库的源码像什么 share 的 PTR 这些，然后什么 Vector 的这些链表，这些扩容，以及这个你像一些 Hashmap 这些底层的实现，还有一些为什么？就是还有一些那个什么，那个叫个什么。
      >
      >   还有就是一些类的一些内存管理，就是比如说我要去对这个类就是了解这个类的一些内存的布局这些，还有就是刚才说的进程线程操作，那是操作系统相关的，就是他们的一些函数的调用，就是我不同的函数编译出来的汇编大概长什么样子，这些就是其实还是要去更多的去打基础，你把这些东西学到了，如果你能很熟练的，就像刚才这个生产者消费者模式多。其实就是一个多线程编程的，你能够写得很熟练的话，那么你在写业务代码的时候，也你就是其实你只需要熟悉一下业务就行了。
      >
      >   你写一个类，比如说你可以尝试自己去写一个 string 类，嗯，你就自己写，还有就是 c 加的这个容器的迭代器，你自己去实现一个迭代器，你可以先尝试自己去思考怎么写，但是你不去参考别人的代码，你先自己思考，你要去实现一个容器，实现一个迭代器，你怎么写？
      >
      >   嗯，这些都是就是我们编程中间随时都要用到的东西，如果你知道他内部怎么写的，那你使用它那就是降维打击了，你更加不会因为什么我不了解，然后就使用就会出问题这种。嗯，好，你底层的会写，你能实现一个迭代器，你能实现一个容器，那么你在一些，你在封装一些更高级的什么什么消息队列这些，那就更加不是问题了。

29.   如果就是能够进来的话，有没有什么培养体系之类的？

      >   培养体系的话我们是每个人会分配一个mentor，然后有专门的人带，但是不是一对一的，可能是一对多的这种，然后公司也有很多的这个，特别是大公司也有很多的这个资料这些，然后也有各种学习群，这些就是只要你愿意学习，其实学习的提升的方式有很多。



## 参考资料

