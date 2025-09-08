# WebServer

## 项目说明

本项目是基于 TinyWebServer 实现的一个 C++ WebServer 项目，目的是用一个更实际的项目来提升自己的 C++ Coding 能力。

项目的架构图如下所示：

![image-20250626150831128](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506261508970.png)

### 阻塞队列

使用生产者-消费者模式实现阻塞队列，支持优雅退出，这是 Log 类和线程池的基础。

使用两个条件变量，将生产者和消费者的等待分开：

*   生产者只关心队列是否已满。当队列满了，它就在 `cond_productor_`上等待；
*   消费者只关心队列是否为空。当队列为空，它就在 `cond_consumer_` 上等待；

这样，当一个消费者取走一个任务后，队列不再是满的，所以它应该唤醒生产者。

同样，当一个生产者放入一个任务后，队列不再是空的，所以它应该唤醒消费者。

这样分离确保了需要唤醒消费者的时候不会虚假唤醒生产者。

```cpp
#pragma once
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_productor_;  // 生产者条件变量
    std::condition_variable cond_consumer_;  // 消费者条件变量
    size_t max_size_;
    std::atomic<bool> is_closed_{false};  // 控制队列是否在没有任务的时候阻塞，当为 true 时，pop 操作不再等待，而是立即返回，用于优雅退出。

public:
    BlockingQueue(size_t max_size = 10000): max_size_(max_size) {}

    // 优雅的关闭队列
    void close() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            is_closed_.store(true);
        }
        // 唤醒所有的生产者和消费者，让它们检查 is_closed_ 状态并退出
        cond_productor_.notify_all();
        cond_consumer_.notify_all();
    }

    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_productor_.wait(lock, [this]() { return queue_.size() < max_size_ || is_closed_.load(); });
        // 判断是什么原因唤醒
        if (is_closed_.load()) {
            // 如果是应为队列关闭唤醒，则不再写入
            return;
        }
        queue_.push(value);
        cond_consumer_.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_consumer_.wait(lock, [this]() { return !queue_.empty() || is_closed_.load(); });
        // 判断什么原因唤醒
        if (is_closed_.load()) {
            // 如果是因为队列关闭唤醒，则不再弹出任务
            return false;
        }
        value = queue_.front();
        queue_.pop();
        cond_productor_.notify_one();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }
};
```



### Logger 类设计

使用单例模式(懒汉模式)实现 Logger 类，支持异步和同步操作：

*   同步模式：调用 `log()` 函数加锁写入内容。`log_mutex_` 是同步模式下的互斥锁。
*   异步模式：将消息推入队列，用一个子线程专门负责从队列中读取消息并写入日志文件。

将 `BlockingQueue` 队列设计在堆上，便于在 init 中动态创建。

引入原子标记位 `is_initialized_` 用于标志 Logger 类是否实例化，保证线程安全。

在使用时，需要先通过 `Logger::getInstance().init("logs/running.log", true);` 初始化，然后通过 `Logger::getInstance().log("INFO", "Server started");` 写入内容，在 `main()` 函数退出前通过调用 `Logger::getInstance().stop();` 保证数据的完整性和优雅退出。

此外，使用宏定义实现 Logger 类的四种快速调用方式：

*   `LOG_INFO(msg)`
*   `LOG_DEBUG(msg)`
*   `LOG_WARNING(msg)`
*   `LOG_ERROR(msg)`

`log.hpp`

```cpp
#pragma once

#include <string>
#include <fstream>
#include <thread>
#include <atomic>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>
#include "webserver/utils/block_queue.hpp"

#define LOG_INFO(msg) Logger::getInstance().log("INFO", msg)
#define LOG_DEBUG(msg) Logger::getInstance().log("DEBUG", msg)
#define LOG_WARNING(msg) Logger::getInstance().log("WARNING", msg)
#define LOG_ERROR(msg) Logger::getInstance().log("ERROR", msg)

class Logger {
private:
    Logger();
    ~Logger();
    void writeLog();

    std::ofstream log_file_;
    BlockingQueue<std::string>* queue_;
    std::thread write_thread_;
    std::atomic<bool> is_initialized_{false};  // 标志是否初始化，用于线程安全
    bool async_;
    std::mutex log_mutex_;

public:
    static Logger& getInstance();
    void init(const std::string& filename, bool async = true, int max_queue_size = 10000);
    void log(const std::string& level, const std::string& message);
    void stop();
};
```

`log.cpp`

```cpp
#include "webserver/utils/log.hpp"

Logger::Logger() : queue_(nullptr), async_(true) {}

Logger::~Logger() {
    stop();
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::init(const std::string& filename, bool async, int max_queue_size) {
    std::cout << "Logger 开始初始化\n";
    bool expected = false;
    if (!is_initialized_.compare_exchange_strong(expected, true)) {
        return;  // 已经初始化，直接返回
    }

    async_ = async;
    // 打开文件，使用 std::ios::ate 模式，定位到文件末尾
    // 这样每次写入时都不需要重新打开文件
    log_file_.open(filename, std::ios::ate);
    if (!log_file_.is_open()) {
        std::cerr << "Cannot open log file: " << filename << "\n";
        exit(1);
    }

    if (async_) {
        queue_ = new BlockingQueue<std::string>(max_queue_size);
        write_thread_ = std::thread(&Logger::writeLog, this);
    }

    std::cout << "Logger 初始化完成\n";
}

/* level: ["INFO", "DEBUG", "WARNING", "ERROR"] */
void Logger::log(const std::string& level, const std::string& message) {
    if (!is_initialized_.load()) {
        return;  // 如果没有初始化直接返回
    }

    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&now_c), "%F %T") << "]\t" << "[" << level << "]\t" << message << "\n";
    std::string msg = ss.str();

    if (async_) {
        // 异步模式下，将消息推入队列
        queue_->push(msg);
    } else {
        // 同步模式下，直接加锁写入
        std::lock_guard<std::mutex> lock(log_mutex_);
        log_file_ << msg;
        log_file_.flush();
    }
}

void Logger::stop() {
    bool expected = true;
    if (!is_initialized_.compare_exchange_strong(expected, false)) {
        // 未初始化或者已经在关闭过程中
        return;
    }

    if (async_ && queue_ != nullptr) {
        // 1. 关闭队列，组织新的日志写入，并唤醒所有消费者
        queue_->close();

        // 2. 等待日志写入线程结束
        if (write_thread_.joinable()) {
            write_thread_.join();
        }

        // 3. 释放队列内存
        delete queue_;
        queue_ = nullptr;
    }

    if (log_file_.is_open()) {
        log_file_.close();
    }
}

void Logger::writeLog() {
    std::string msg;

    // 只要成功从队列中取出消息就写入文件
    while (queue_->pop(msg)) {
        log_file_ << msg;
        log_file_.flush();  // 可能存在瓶颈，后期优化
    }
}
```



### EpollServer 类

`epoll_server.hpp`

```cpp
#pragma once

#include <sys/epoll.h>
#include <functional>
#include <unordered_map>

// 回调函数类型定义
// 当有新连接或数据可读时，EpollServer会调用这些函数
using EventCallback = std::function<void(int)>;

class EpollServer {
private:
    int port_;
    int listen_fd_;
    int epoll_fd_;  // epoll 实例

    void initSocket();

    EventCallback connection_callback_;
    EventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback close_callback_;

public:
    EpollServer(int port);
    ~EpollServer();

    void run();

    // 注册回调函数
    void setConnectionCallback(EventCallback callback);
    void setReadCallback(EventCallback callback);
    void setWriteCallback(EventCallback callback);
    void setCloseCallback(EventCallback callback);

    // 供外部调用的 Epoll 相关接口
    void addFd(int fd, uint32_t events);
    void updateFd(int fd, uint32_t events);
    void removeFd(int fd);
};
```

`epoll_server.cpp`

```cpp
#include "webserver/core/epoll_server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "webserver/utils/log.hpp"

constexpr int MAX_EVENTS = 1024;

EpollServer::EpollServer(int port) : port_(port), listen_fd_(-1), epoll_fd_(-1) {
    initSocket();
}

EpollServer::~EpollServer() {
    if (listen_fd_ >= 0) {
        close(listen_fd_);
    }
    if (epoll_fd_ >= 0) {
        close(epoll_fd_);
    }
}

void EpollServer::initSocket() {
    listen_fd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (listen_fd_ == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd_, (sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_fd_, SOMAXCONN) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
        perror("epoll_create failed");
        exit(EXIT_FAILURE);
    }

    addFd(listen_fd_, EPOLLIN | EPOLLET);
    Logger::getInstance().log("INFO", "EpollServer initialized. Listening on port " + std::to_string(port_));
}

void EpollServer::addFd(int fd, uint32_t events) {
    epoll_event event{};
    event.data.fd = fd;
    event.events = events;
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event) == -1) {
        perror("epoll_ctl_add failed");
        Logger::getInstance().log("ERROR", "Failed to add fd " + std::to_string(fd) + " to epoll.");
    }
}

void EpollServer::updateFd(int fd, uint32_t events) {
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = events | EPOLLET | EPOLLONESHOT; // 保持边缘触发和 EPOLLONESHOT
    
    // 使用 EPOLL_CTL_MOD 操作来修改文件描述符的事件
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ev) == -1) {
        // 错误处理，可以打印日志
    }
}

void EpollServer::removeFd(int fd) {
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, nullptr) == -1) {
        perror("epoll_ctl_del failed");
        Logger::getInstance().log("ERROR", "Failed to remove fd " + std::to_string(fd) + " from epoll.");
    }
}

void EpollServer::setConnectionCallback(EventCallback callback) {
    connection_callback_ = std::move(callback);
}

void EpollServer::setReadCallback(EventCallback callback) {
    read_callback_ = std::move(callback);
}

void EpollServer::setWriteCallback(EventCallback callback) {
    write_callback_ = std::move(callback);
}

void EpollServer::setCloseCallback(EventCallback callback) {
    close_callback_ = std::move(callback);
}

void EpollServer::run() {
    epoll_event events[MAX_EVENTS];
    while (true) {
        int nfds = epoll_wait(epoll_fd_, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait failed");
            Logger::getInstance().log("ERROR", "epoll_wait failed, shutting down server.");
            break;
        }

        for (int i = 0; i < nfds; ++i) {
            int fd = events[i].data.fd;
            uint32_t event_type = events[i].events;

            if (fd == listen_fd_) {
                // 处理新连接
                if (connection_callback_) {
                    connection_callback_(listen_fd_);
                }
            } else {
                // 处理错误和断开事件
                if (event_type & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                    if (close_callback_) {
                        close_callback_(fd);
                    }
                }

                // 处理可读事件
                if (event_type & EPOLLIN) {
                    if (read_callback_) {
                        read_callback_(fd);
                    }
                }

                // 处理可写事件
                if (event_type & EPOLLOUT) {
                    if (write_callback_) {
                        write_callback_(fd);
                    }
                }
            }
        }
    }
}
```





### HttpServer 类

`http_server.hpp`

```cpp
#pragma once

#include "webserver/core/epoll_server.hpp"
#include "webserver/http/http_connection.hpp"
#include "webserver/sql/MySQLConnector.hpp"
#include "webserver/pool/ThreadPool.hpp"
#include "webserver/timer/heaptimer.hpp"
#include <unordered_map>
#include <memory>

class HttpServer {
public:
    HttpServer(int port);
    ~HttpServer();

    void run();

private:
    void handleNewConnection(int listen_fd);
    void handleRead(int client_fd);
    void handleWrite(int client_fd);
    void handleClose(int client_fd);

    EpollServer epoll_server_;  // epoll server
    ThreadPool thread_pool_;  // 线程池
    MySQLConnector mysql_connector_;  // sql 连接
    HeapTimer heap_timer_;  // 计时器
    std::unordered_map<int, std::unique_ptr<HTTPConnection>> http_connections_;
};
```



`http_server.cpp`

```cpp
#include "webserver/core/http_server.hpp"
#include "webserver/utils/log.hpp"
#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

constexpr int MAX_TIMEOUT = 5000;

HttpServer::HttpServer(int port)
    : epoll_server_(port),
      thread_pool_(10), // 假设线程池大小为10
      heap_timer_(),
      mysql_connector_() {

    // 注册所有回调函数
    epoll_server_.setConnectionCallback(std::bind(&HttpServer::handleNewConnection, this, std::placeholders::_1));
    epoll_server_.setReadCallback(std::bind(&HttpServer::handleRead, this, std::placeholders::_1));
    // epoll_server_.setWriteCallback(std::bind(&HttpServer::handleWrite, this, std::placeholders::_1)); // 暂不实现，读为主
    epoll_server_.setCloseCallback(std::bind(&HttpServer::handleClose, this, std::placeholders::_1));
}

HttpServer::~HttpServer() {
    // 析构函数可以为空，因为成员变量会自动析构
}

void HttpServer::run() {
    // 启动 EpollServer 的事件循环
    epoll_server_.run();
}

void HttpServer::handleNewConnection(int listen_fd) {
    // 持续接收新连接，直至没有新的连接到达（边缘触发）
    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(listen_fd, (sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // 所有新连接都已处理
                break;
            } else {
                perror("accept failed");
                Logger::getInstance().log("ERROR", "Accept failed.");
                break;
            }
        }

        // 创建新的 HTTPConnection 对象并管理
        http_connections_[client_fd] = std::make_unique<HTTPConnection>(client_fd, &mysql_connector_);

        // 添加定时器和事件到 EpollServer
        heap_timer_.addTimer(client_fd, MAX_TIMEOUT);
        epoll_server_.addFd(client_fd, EPOLLIN | EPOLLET);

        Logger::getInstance().log("INFO", "Client[" + std::to_string(client_fd) + "] connected!");
    }
}

void HttpServer::handleRead(int client_fd) {
    // 提交任务到线程池
    thread_pool_.enqueue([this, client_fd] {
        auto it = http_connections_.find(client_fd);
        if (it == http_connections_.end()) {
            // 连接不存在，直接返回
            return;
        }

        HTTPConnection& conn = *(it->second);
        
        // 接收数据
        std::string raw_data;
        bool is_connection_alive = conn.receiveRequest(raw_data);
        if (!is_connection_alive) {
            // 连接已关闭或出错，直接处理关闭
            handleClose(client_fd);
            return;
        }

        // 处理请求并发送响应
        conn.parseRequest(raw_data);
        conn.sendResponse();

        // 根据连接状态更新或关闭
        if (conn.is_keep_alive) {
            heap_timer_.updateTimer(client_fd, MAX_TIMEOUT);
        } else {
            handleClose(client_fd);
        }
    });
}

void HttpServer::handleClose(int client_fd) {
    // 线程安全地移除连接
    auto it = http_connections_.find(client_fd);
    if (it != http_connections_.end()) {
        Logger::getInstance().log("INFO", "Client[" + std::to_string(client_fd) + "] is closed due to timeout or http request.");
        
        // 从 epoll 和定时器中移除
        epoll_server_.removeFd(client_fd);
        heap_timer_.removeTimer(client_fd);
        
        // 关闭 socket
        close(client_fd);

        // 从 map 中移除，unique_ptr 会自动释放内存
        http_connections_.erase(it);
    }
}

// 暂不实现，因为非阻塞写更复杂
void HttpServer::handleWrite(int client_fd) {
    // 这里处理写事件，例如发送大量数据时
}
```



### SQLConnector 类

在之前实现的 `MySQLConnector` 类中，我们全局只使用了一个 `HttpServer` 实例，因此全局只有一个 `MySQLConnector` 实例，但是在多线程高并发的情况下会存在非线程安全问题。







### HeapTimer 类



### ThreadPool 类



### HttpConnection 类




## TODO
### 基本要求
- [x] 连接数据库，存储用户账号和密码
    - [ ] 应该保证 username 不能重复，让 username 成为 key

- [x] 完成注册和登录功能，登录成功的用户应该返回 `welcome.html` 界面
- [x] 完成日志功能
- [ ] 完成 TCP 连接池
  
- [x] 完成工作线程池
  
- [x] 完成定时器，关闭非活动连接
    - [x] 目前对 HTTP 请求的响应都带有 `"Connection: close\r\n\r\n"`，这样的频繁的连接、断开连接、再连接的过程非常耗费资源，下一步应该添加定时器以关闭长时间没有使用的连接。
    - [ ] 已经成功添加定时器，但是在压力测试后之后发现，性能大幅度降低，现在需要分析性能降低的原因并解决这个问题。

- [ ] `webbench-1.5` 服务器压力测试
- [ ] 部署到腾讯云

### 额外功能
- [ ] 实现聊天服务器的功能，参考[GitHub](https://github.com/archibate/co_http)，考虑在现有WebServer的基础上增加聊天室的功能
- [ ] 实现音乐播放器的功能



## 运行和测试

编译并运行 WebServer

```bash
mkdir build
cd build
cmake ..
make
./webserver
```

服务器压力测试

```bash
cd webbench-1.5
make
./webbench -c 1000 -t 5 http://127.0.0.1:8080/
```



## 发布版本

### Version 0.8

-   [ ] 解决连接长时间不自动释放的问题
-   [ ] 大文件传输优化
-   [ ] 修改定时器
-   [ ] 



### Version 0.7

[Link]()

TODO:

-   [ ] 重新整理仓库结构，方便拓展
    目标仓库结构为：

    ```bash
    webserver/
    ├── apps/                   # 具体应用实现
    │   ├── blog/               # 博客应用
    │   ├── chat/               # 聊天室应用
    │   ├── game/               # 在线消消乐游戏
    │   └── ...                 # 其他应用
    ├── src/
    │   ├── core/               # 服务器核心组件
    │   │   ├── epoll/          # epoll 封装
    │   │   ├── threadpool/     # 线程池实现
    │   │   ├── timer/          # 定时器管理
    │   │   ├── connection/     # 连接管理
    │   │   └── server.cpp      # 服务器主循环
    │   ├── http/               # HTTP 协议处理
    │   │   ├── request.cpp     # 请求解析
    │   │   ├── response.cpp    # 响应生成
    │   │   ├── router.cpp      # 路由系统
    │   │   └── middleware/     # 中间件系统
    │   ├── database/           # 数据库抽象层
    │   │   ├── mysql/          # MySQL 实现
    │   │   ├── sqlite/         # SQLite 实现（可选）
    │   │   └── db_interface.h  # 统一数据库接口
    │   ├── utils/              # 工具类
    │   │   ├── logger/         # 日志系统
    │   │   ├── config/         # 配置解析
    │   │   ├── buffer/         # 缓冲区管理
    │   │   └── crypto/         # 加密工具
    │   └── api/                # 应用开发接口
    │       ├── application.h   # 应用接口基类
    │       └── plugin.h        # 插件接口
    ├── include/                # 公共头文件
    │   └── webserver/          # 项目头文件命名空间
    ├── third_party/            # 第三方依赖
    ├── tests/                  # 测试套件
    │   ├── unit/               # 单元测试
    │   ├── integration/        # 集成测试
    │   └── benchmark/          # 性能测试
    ├── scripts/                # 实用脚本
    │   ├── deploy/             # 部署脚本
    │   └── build/              # 构建脚本
    ├── config/                 # 配置文件
    │   ├── server.conf         # 服务器配置
    │   └── apps/               # 应用配置
    ├── docs/                   # 项目文档
    ├── resources/              # 静态资源
    │   ├── static/             # 静态文件（CSS/JS/图片）
    │   └── templates/          # HTML 模板
    ├── CMakeLists.txt          # 主构建配置
    ├── Dockerfile              # 容器化支持
    └── .github/                # CI/CD 配置
    ```

-   [ ] 完善此项目，为之后添加博客、在线聊天室、在线消消乐等功能打好基础；

-   [ ] 添加项目笔记；



### Version 0.6

[Link]()

已完成 WebServer 的基础功能，包括：

*   处理 GET 和 POST 请求，返回对应的静态内容；
*   连接 MySQL 数据库，支持用户的注册和登录；
*   加入异步日志系统，有助于调试BUG，定位错误，数据分析；
*   持久连接，将 Connection 设置为 keep-alive，节约 TCP 连接的开销
*   添加 Timer 控制连接时间
*   拓展为多线程 Reactor 模型，添加线程池
*   模块化，将 WebServer 类中对 HTTP 的具体处理放到 `http/` 下
*   `webbench-1.5` 服务器压力测试，完成时间：2025-6-24 11:58:57
    ![image-20250624115946580](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506241159019.png)



### Version 0.5

[Link](https://github.com/A-Egoist/WebServer/tree/b854639c0a7b440c91564d307fa45448d07247a0)

已完成 WebServer 的基础功能，包括：

*   处理 GET 和 POST 请求，返回对应的静态内容；
*   连接 MySQL 数据库，支持用户的注册和登录；
*   加入异步日志系统，有助于调试BUG，定位错误，数据分析；
*   持久连接，将 Connection 设置为 keep-alive，节约 TCP 连接的开销
*   添加 Timer 控制连接时间
*   拓展为多线程 Reactor 模型
*   `webbench-1.5` 服务器压力测试，完成时间：2025-6-23 20:14:17
    ![image-20250623201442703](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506232014356.png)

TODO：

-   [ ] 在添加多线程之后，发现 QPS 有一些下降，需要分析原因



### Version 0.4

[Link](https://github.com/A-Egoist/WebServer/tree/8750b027ba9acd0f8eb961842a216ff6814ecc82)

已完成 WebServer 的基础功能，包括：

*   处理 GET 和 POST 请求，返回对应的静态内容；
*   连接 MySQL 数据库，支持用户的注册和登录；
*   加入异步日志系统，有助于调试BUG，定位错误，数据分析；
*   持久连接，将 Connection 设置为 keep-alive，节约 TCP 连接的开销
*   添加 Timer 控制连接时间
*   `webbench-1.5` 服务器压力测试，完成时间：2025-6-21 19:33:44
    ![image-20250621193406828](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506211934008.png)

测试是否 keep-alive：

```bash
curl -v --http1.1 http://127.0.0.1:8080/ http://127.0.0.1:8080/picture http://127.0.0.1:8080/login http://127.0.0.1:8080/welcome > http11NUL
```

```bash
curl -v --http1.0 http://127.0.0.1:8080/ http://127.0.0.1:8080/picture http://127.0.0.1:8080/login http://127.0.0.1:8080/welcome > http10NUL
```

```bash
curl -v --header "Connection: close" http://127.0.0.1:8080

curl -v --header "Connection: keep-alive" http://127.0.0.1:8080
```



### Version 0.3

[Link](https://github.com/A-Egoist/WebServer/tree/5a25bb874cd17e16a1e446188b69a10c97e098b7)

已完成 WebServer 的基础功能，包括：

*   处理 GET 和 POST 请求，返回对应的静态内容；
*   连接 MySQL 数据库，支持用户的注册和登录；
*   加入异步日志系统，有助于调试BUG，定位错误，数据分析；
*   完成一次 `webbench-1.5` 服务器压力测试，完成时间：2025-6-18 21:20:55
    ![image-20250618212041657](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506182120838.png)

### Version 0.2

[Link](https://github.com/A-Egoist/WebServer/tree/11830bcd8217816af960a1f5e7cb15d7dda5bdcc)

已完成 WebServer 的基础功能，包括：

*   处理 GET 和 POST 请求，返回对应的静态内容；
*   连接 MySQL 数据库，支持用户的注册和登录；

### Version 0.1

[Link](https://github.com/A-Egoist/WebServer/tree/4dbadc7e63c5665b921c8cce4055bf8d54db595f)

已完成 WebServer 的基础功能，包括：

*   处理 GET 和 POST 请求，返回对应的静态内容；

