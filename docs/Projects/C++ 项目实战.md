# C++ 项目实战



## 一、从零开始实现 C++ TinyWebServer 全过程记录

[Notes](./一、从零开始实现 C++ TinyWebServer 全过程记录.md)

[Github](https://github.com/A-Egoist/WebServer)



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



## 二、





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