# C++ 项目实战



## 一、从零开始实现 C++ TinyWebServer 全过程记录

详见：[从零开始实现 C++ TinyWebServer](./从零开始实现 C++ TinyWebServer.md)

[Github](https://github.com/A-Egoist/WebServer)

### 项目说明



### Function

-   利用 IO 复用技术 Epoll 与线程池实现多线程的 Reactor 高并发模型；
-   利用正则与状态机解析 HTTP 请求报文，实现处理静态资源的请求；
-   利用标准库容器封装 char，实现自动增长的缓冲区；
-   基于小根堆实现的定时器，关闭超时的非活动连接；
-   利用单例模式与阻塞队列实现异步的日志系统，记录服务器运行状态；
-   利用 RAII 机制实现了数据库连接池，减少数据库连接建立与关闭的开销，同时实现了用户注册登录功能。
-   增加 logsys, threadpool 测试单元 (todo: timer, sqlconnpool, httprequest, httpresponse)



### 运行和测试

1.   编译并运行 WebServer：
     ```bash
     make
     ./bin/server
     ```

2.   日志、线程池测试：
     ```bash
     cd test
     make
     ./test
     ```

3.   服务器压力测试：
     ```bash
     cd webbench-1.5
     make
     ./webbench -c 1000 -t 5 http://127.0.0.1:1316/
     ```

     ![image-20250615221756266](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506152218864.png)
     
     ==55688 / 30s = 1856.27 QPS==
     
     ![image-20250621195226672](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506211952765.png)
     
     ==12789 / 5s = 2557.8 QPS==



## 二、自己动手实现 vector 容器

详见：[自己动手实现vector容器](./自己动手实现vector容器.md)

### 项目说明



## 三、自己动手实现 unique_ptr

详见：[自己动手实现unique_ptr智能指针](./自己动手实现unique_ptr智能指针.md)

### 项目说明



## 四、自己动手实现 shared_ptr

详见：[自己动手实现shared_ptr智能指针](./自己动手实现shared_ptr智能指针.md)

### 项目说明



## 五、自己动手实现 weak_ptr

详见：[自己动手实现weak_ptr智能指针](./自己动手实现weak_ptr智能指针.md)

### 项目说明



## 六、自己动手实现 string 容器

### 项目说明



## 七、基于 Boost 库的搜索引擎

[【C++综合项目】——基于Boost库的搜索引擎（手把手讲解，小白一看就会！！）](https://xas-sunny.blog.csdn.net/article/details/140881214)



## 八、手撕线程池

[华为海思C++一面：手撕线程池~源码分享](https://www.bilibili.com/video/BV1Rbwhe3Euh)





## 九、手撕 LRU Cache

[字节、米哈游、百度面经：手撕LRUCache](https://www.bilibili.com/video/BV1Hx4y1s7He)





## 十、环形缓冲区

环形缓冲区设计

环形缓冲区、循环缓冲区、环形队列、循环队列

[C++环形缓冲区设计与实现：从原理到应用的全方位解析](https://zhuanlan.zhihu.com/p/649214928)



## 可选项目

[1] [研究生为了摸鱼，做了个导师识别系统？](https://www.bilibili.com/video/BV1qEtpz2EFP?spm_id_from=333.1245.0.0)

[2] [【开源】你独自一个人做了个什么东西？AI驱动的Galgame？](https://www.bilibili.com/video/BV1v48tzYEfi?spm_id_from=333.1245.0.0)

[3] [【C/C++项目】跳跃小游戏！思路讲解+代码实现，C语言游戏功能案例，一个视频学会如何做出角色跳跃！](https://www.bilibili.com/video/BV1nje8zXEMz?spm_id_from=333.1245.0.0)

[4] [【C语言/C++】植物大战僵尸！零基础如何做独立游戏？用C语言做出第一个属于自己的游戏](https://www.bilibili.com/video/BV1BM8JzCErF?spm_id_from=333.1245.0.0)

[5] [【C语言/C++】万能抢票器！演唱会，火车票，秒抢，试试就知道有多厉害！！！！](https://www.bilibili.com/video/BV1GURqYMEeW?spm_id_from=333.1245.0.0)

[6] [【QT项目实战】qt桌面小宠物！想要拥有一个自己开发的桌面小宠物吗？程序员手把手教你怎么做！](https://www.bilibili.com/video/BV1g24y1N7zJ?spm_id_from=333.1245.0.0)

[7] [【C语言/C++】自制桌面宠物！软萌可撩，简单有趣又好玩，让桌面瞬间重获新生！](https://www.bilibili.com/video/BV1LUTjzgEjP?spm_id_from=333.1245.0.0)

[8] [一人团队开发了个游戏](https://www.bilibili.com/video/BV1fa7HzQEjZ?spm_id_from=333.1245.0.0)

[9] [纯Qt5复刻QQ聊天项目分享（覆盖数据库，TCP网络编程，文件IO）](https://www.bilibili.com/video/BV1sut4zuECU?spm_id_from=333.1245.0.0)

[10] [C++ 全栈聊天项目(40) 多线程文件传输](https://www.bilibili.com/video/BV13xXWYZE7C?spm_id_from=333.1245.0.0)

[11] [c++手撕transformer 1](https://www.bilibili.com/video/BV1as7azMEW1?spm_id_from=333.1245.0.0)

[12] [Google TL系统设计 - 支付系统](https://www.bilibili.com/video/BV1i43GzkEYW?spm_id_from=333.1245.0.0)

[13] [C++ 全栈聊天项目(54) 断点续传实现细节](https://www.bilibili.com/video/BV1bTbAzjEEY?spm_id_from=333.1245.0.0)

[14] 

[15] 







## 参考资料

[1] 小彭老师推荐：[参考资料与项目推荐](https://parallel101.github.io/cppguidebook/recommend/)

[2]  [代码随想录知识星球](https://www.programmercarl.com/other/kstar.html)

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506191156865.png" alt="image-20250619115555160" style="zoom: 67%;" />

[3] [C++校招项目防雷同之：高性能RPC框架-支持json/protobuf等多种序列化方式](https://www.bilibili.com/video/BV176Niz8ENj?spm_id_from=333.1245.0.0)

[4] [你知道C++ Linux校招简历项目有多雷同吗？别再写muduo网络库、webserver了](https://www.bilibili.com/video/BV1mJTtzZEpk?spm_id_from=333.1245.0.0)

[5] [【C++】从零搭建聊天服务器（面试加分必备实战项目）](https://www.bilibili.com/video/BV1sE4m1d7Mp?spm_id_from=333.1245.0.0)

[6] [C++项目要做到什么程度才可以校招-以实际项目和腾讯招聘要求讲解](https://www.bilibili.com/video/BV16BJ6z7EFD?spm_id_from=333.1245.0.0)

[7]

[8]

[9]

[10]