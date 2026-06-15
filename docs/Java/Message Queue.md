# Message Queue

Message Queue (MQ)，消息队列，即异步调用中的 Broker



## MQ 基础

什么是同步通讯？什么是异步通讯？



### 同步调用

同步调用的优势：

*   时效性强，等待到结果后才返回



同步调用的问题：

*   拓展性差
*   性能下降
*   级联失败



异步调用的优势：

-   耦合度更低
-   性能更好
-   业务拓展性强
-   故障隔离，避免级联失败



异步通信也并非完美无缺，它存在下列缺点：

-   完全依赖于Broker的可靠性、安全性和性能
-   架构复杂，后期维护和调试麻烦



### 异步调用

三个角色：

-   消息发送者：投递消息的人，就是原来的调用方
-   消息Broker：管理、暂存、转发消息，你可以把它理解成微信服务器
-   消息接收者：接收和处理消息的人，就是原来的服务提供方









### 技术选型

几种常见MQ的对比：

|            | RabbitMQ                | ActiveMQ                       | RocketMQ   | Kafka      |
| ---------- | ----------------------- | ------------------------------ | ---------- | ---------- |
| 公司/社区  | Rabbit                  | Apache                         | 阿里       | Apache     |
| 开发语言   | Erlang                  | Java                           | Java       | Scala&Java |
| 协议支持   | AMQP，XMPP，SMTP，STOMP | OpenWire,STOMP，REST,XMPP,AMQP | 自定义协议 | 自定义协议 |
| 可用性     | 高                      | 一般                           | 高         | 高         |
| 单机吞吐量 | 一般                    | 差                             | 高         | 非常高     |
| 消息延迟   | 微秒级                  | 毫秒级                         | 毫秒级     | 毫秒以内   |
| 消息可靠性 | 高                      | 一般                           | 高         | 一般       |

追求可用性：Kafka、 RocketMQ 、RabbitMQ

追求可靠性：RabbitMQ、RocketMQ

追求吞吐能力：RocketMQ、Kafka

追求消息低延迟：RabbitMQ、Kafka



## RabbitMQ





## SpringAMQP

将来我们开发业务功能的时候，肯定不会在控制台收发消息，而是应该基于编程的方式。由于`RabbitMQ`采用了AMQP协议，因此它具备跨语言的特性。任何语言只要遵循AMQP协议收发消息，都可以与`RabbitMQ`交互。并且`RabbitMQ`官方也提供了各种不同语言的客户端。

但是，RabbitMQ官方提供的Java客户端编码相对复杂，一般生产环境下我们更多会结合Spring来使用。而Spring的官方刚好基于RabbitMQ提供了这样一套消息收发的模板工具：SpringAMQP。并且还基于SpringBoot对其实现了自动装配，使用起来非常方便。









## 业务改造







