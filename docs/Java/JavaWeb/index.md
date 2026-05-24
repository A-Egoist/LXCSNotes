# JavaWeb

## Web前端基础

HTML-CSS 基础：[HTML-CSS](./HTML-CSS.md)

JavaScript 基础：[JS](./JS.md)

Vue3 基础：[Vue3](./Vue3.md)

Ajax/Axios 基础：[Ajax](./Ajax.md)

![image-20251007220942335](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072209913.png)



## Web后端基础

Maven 基础：[Maven](../Maven.md)

Web 基础知识 + SpringBoot 基础：[Web基础知识](./Web基础知识.md)

SpringBoot 基础：[SpringBoot基础](./SpringBoot基础.md)

MySQL：[MySQL](../MySQL.md)

JDBC：[JDBC](./JDBC.md)

MyBatis：[MyBatis](./MyBatis.md)

![image-20251011224542139](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112245515.png)



## Web 后端实战

**Tlias 智能学习辅助系统**

Tlias 案例：[Tlias智能学习辅助系统](./Tlias智能学习辅助系统.md)



**Web 后端开发总结**

![image-20260409102317880](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091023619.png)

三层架构模型

*   Controller 层负责接收请求，接收到请求之后会调用 Service 层，最终给前端响应数据
*   Service 层负责具体的业务逻辑处理，调用 Dao 层，然后将结果返回给 Controller 层
*   Dao 层负责数据访问操作，负责数据的增删改查，操作数据库，将数据库的操作结果返回给 Service 层

![image-20260409102956287](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091029555.png)

使用过滤器和拦截器拦截前端发起的请求做一些统一的处理。过滤器和拦截器都可以拦截前端发起的请求，但是过滤器的拦截范围更大。拦截器是 Spring 提供的，只能够拦截 Spring 中的资源。

![image-20251101113428194](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011134247.png)

为了解决 Controller、Service、Dao 这三层代码之间的耦合，引入 Spring 中的控制反转（IOC）和依赖注入（DI）。此外，引入了 AOP 面向切面编程的编程思想，将公共逻辑抽取到 AOP 中，制作成一个通知，从而简化开发。

*   Cookie、Session：传统 Java Web 程序中提供的会话跟踪技术
*   JWT：现在企业项目开发当中用的比较多的会话跟踪技术
*   阿里云 OSS：对象存储解决方案
*   Mybatis：持久层框架，用于简化对数据库的访问操作

![image-20260409103721571](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091037992.png)

SpringBoot 相当于是项目的底座，通过 SpringBoot 可以快速构建一个 Spring 的应用。SpringBoot 并不是用来替代 Spring framework 的，而是用于简化 Spring framework。

`全局异常处理`和`拦截器`是 Spring framework 对于 web 所提供的功能。而这一部分功能加上`接收请求`、`响应数据`其实就是 Spring MVC 框架中提供的功能。

:bulb: 在 Spring 家族中并没有一个框架叫做 Spring MVC，Spring MVC 就是 Spring 中的一部分，只不过行业统一将 Spring 中对于 Web 应用开发的支持部分叫做 Spring MVC。

>   MVC 是模型（Model）、视图（View）、控制器（Controller）的缩写，其核心思想是通过将业务逻辑、数据、显示分离来组织代码。

![image-20251101113719469](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011137421.png)

:bulb: **SSM** 就是指 **SpringMVC**、**Spring framework**、**MyBatis​**

在企业项目开发中，在基于 SSM 进行开发的时候，都是基于 Spring Boot 这个底座进行开发的。



## Web 前端实战

Vue3：[Vue3](./Vue3.md)

ElementPlus：[ElementPlus](./ElementPlus.md)



## Web 项目部署

![image-20251104182055633](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511041820510.png)

### Linux

#### 前端项目部署





#### 后端项目部署





### Docker





## 项目思考
