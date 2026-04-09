# Web 基础知识

基础架构知识：

![image-20251008221345904](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082214789.png)

## SpringBoot Web 入门

Spring 官网：https://spring.io/

![image-20251008223410843](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082234258.png)

![image-20251008223433386](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082234323.png)

![image-20251008223500860](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082235846.png)

![image-20251008223541630](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082235571.png)

### 入门程序

![image-20251009204618215](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092046681.png)

![image-20251009210854195](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092108085.png)

1、创建 SpringBoot 工程，勾选 web 开发依赖

![image-20251009205119307](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092051712.png)

![image-20251009205235133](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092052284.png)

基于 SpringBoot 官方网站所创建的多有的 SpringBoot 项目都有这样一个**父工程**。

![image-20251009205633530](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092056093.png)



2、定义请求处理类 HelloController，定义请求处理方法

`HelloController.java`

```java
package top.amonologue;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController // 表示当前类是一个请求处理类
public class HelloController {

    @RequestMapping("/hello")
    public String hello(String name) {
        System.out.println("name: " + name);
        return "Hello " + name + "!";
    }
}

```



3、用 Debug 模式运行启动类

![image-20251009211248261](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092112434.png)



运行结果：

![image-20251009210816363](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092108904.png)



常见问题：

![image-20251009211449142](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092114131.png)



### 入门程序剖析

spring-boot-starter-web 通过依赖配置将 Tomcat 内嵌进来：

![image-20251009213104044](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092131314.png)

![image-20251009213148403](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092131356.png)



## HTTP 协议

![image-20251009214219956](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092142980.png)

### HTTP-请求协议

![image-20251009214856293](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092148175.png)

常见请求头和请求体的含义：

![image-20251009214741369](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092147033.png)

请求头按照 `key: value` 的格式

![image-20251009214947743](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510092149874.png)



![image-20251010164420381](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101644810.png)

```java
package top.amonologue;

import jakarta.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RequestController {
    @RequestMapping("/request")
    public String request(HttpServletRequest request) {
        // 1. 获取请求方式
        var method = request.getMethod();
        System.out.println("method: " + method);

        // 2. 获取请求路径
        var url = request.getRequestURL().toString();  // 资源的完整路径
        System.out.println("url: " + url);

        var uri = request.getRequestURI();  // 资源的访问路径
        System.out.println("uri: " + uri);

        // 3. 获取获取请求协议
        var protocol = request.getProtocol();
        System.out.println("protocol: " + protocol);

        // 4. 获取请求参数
        var name = request.getParameter("name");
        var age = request.getParameter("age");
        System.out.println("name: " + name + " age: " + age);

        // 5. 获取请求头
        var accept = request.getHeader("accept");
        System.out.println("accept: " + accept);

        return  "OK";
    }
}

```

在浏览器中访问 `http://127.0.0.1:8080/request?name=Amonologue&age=24`，控制台的结果：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101655944.png" alt="image-20251010165519089" style="zoom: 67%;" />



### HTTP-响应协议

![image-20251010170412474](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101704266.png)

![image-20251010170307652](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101703086.png)

![image-20251010170237111](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101702958.png)

状态码大全：https://cloud.tencent.com/developer/chapter/13553



![image-20251010170519616](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101705246.png)

![image-20251010194849716](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101948691.png)

![image-20251010195017887](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101950896.png)



## SpringBootWeb 案例

[Web基础-SpringBootWeb案例](https://www.bilibili.com/video/BV1yGydYEE3H?spm_id_from=333.788.player.switch&vd_source=f4cc25a44af6631d6f4db023b3bb88e4&p=46)

![image-20251010201555841](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102015785.png)

![image-20251010201648667](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102016591.png)



## 分层解耦

### 三层架构

![image-20251010210448747](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102104840.png)

![image-20251010210748014](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102107973.png)

面向接口的编程方式，先声明结构，然后在 `impl/` 文件夹中实现接口。并且在调用具体的实现的时候使用多态的方式调用：

![image-20251010214650885](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102146093.png)

![image-20251010215050836](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102150776.png)

![image-20251010223720379](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102237344.png)

![image-20251010223905859](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102239757.png)



### 什么是分层解耦

![image-20251010224246056](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102242269.png)

![image-20251010224611208](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102246316.png)

![image-20251010224820152](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102248043.png)



### 什么是 IoC

IoC （Inversion of Control ）即控制反转。它是一种思想不是一个技术实现。描述的是：Java 开发领域对象的创建以及管理的问题。

例如：现有类 A 依赖于类 B

-   **传统的开发方式** ：往往是在类 A 中手动通过 new 关键字来 new 一个 B 的对象出来
-   **使用 IoC 思想的开发方式** ：不通过 new 关键字来创建对象，而是通过 IoC 容器(Spring 框架) 来帮助我们实例化对象。我们需要哪个对象，直接从 IoC 容器里面去取即可。

从以上两种开发方式的对比来看：我们 “丧失了一个权力” (创建、管理对象的权力)，从而也得到了一个好处（不用再考虑对象的创建、管理等一系列的事情）

**为什么叫控制反转?**

-   **控制** ：指的是对象创建（实例化、管理）的权力
-   **反转** ：控制权交给外部环境（IoC 容器）

![IoC 图解](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091114082.png)



### IOC 解决了什么问题

IoC 的思想就是两方之间不互相依赖，由第三方容器来管理相关资源。这样有什么好处呢？

1.  对象之间的耦合度或者说依赖程度降低；
2.  资源变的容易管理；比如你用 Spring 容器提供的话很容易就可以实现一个单例。

例如：现有一个针对 User 的操作，利用 Service 和 Dao 两层结构进行开发

在没有使用 IoC 思想的情况下，Service 层想要使用 Dao 层的具体实现的话，需要通过 new 关键字在`UserServiceImpl` 中手动 new 出 `IUserDao` 的具体实现类 `UserDaoImpl`（不能直接 new 接口类）。

很完美，这种方式也是可以实现的，但是我们想象一下如下场景：

开发过程中突然接到一个新的需求，针对 `IUserDao` 接口开发出另一个具体实现类。因为 Server 层依赖了 `IUserDao` 的具体实现，所以我们需要修改 `UserServiceImpl` 中 new 的对象。如果只有一个类引用了 `IUserDao` 的具体实现，可能觉得还好，修改起来也不是很费力气，但是如果有许许多多的地方都引用了 `IUserDao` 的具体实现的话，一旦需要更换 `IUserDao`  的实现方式，那修改起来将会非常的头疼。

![IoC&Aop-ioc-illustration-dao-service](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091115549.png)

使用 IoC 的思想，我们将对象的控制权（创建、管理）交由 IoC 容器去管理，我们在使用的时候直接向 IoC 容器 “要” 就可以了

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604091115333.png)



### IOC & DI 入门

![image-20251010225018434](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102250289.png)

1.   在 Service 层和 Dao 层的**实现类**上添加 `@Component` 注解，交给 IoC 容器管理
2.   给 Controller 层和 Service 层的**成员变量**加上 `@Autowired` 注解，注入运行时所依赖的对象

![image-20251010225543458](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102255334.png)



#### IOC 使用详解

![image-20251010230354209](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102303261.png)

通过注解将某个对象交给 IoC 容器管理，IoC 容器管理的对象被称为 Bean（Spring Bean）。

在声明 Bean 的时候可以指定 Bean 的名字：`@Repository("userDao")`

![image-20251010230654349](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102306143.png)

IoC：把对象的创建、管理交给 Spring 容器，不再自己 new，通过 `@Service`、`@Controller`、`@Component` 实现。



#### DI 使用详解

![image-20251010231600023](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102316080.png)

DI：由 Spring 自动把容器中的对象赋值给需要的成员变量，通过 `@Autowired` 实现。

:bulb: ​Bean 的默认名字是类名的首字母小写。

![image-20251010232124196](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102321227.png)



## Spring Bean

简单来说，Bean 代指的就是那些被 IoC 容器所管理的对象。

>   参考资料：[Spring常见面试题总结](https://javaguide.cn/system-design/framework/spring/spring-knowledge-and-questions-summary.html)

### 将一个类声明为 Bean 的注解有哪些?

-   `@Component`：通用的注解，可标注任意类为 `Spring` 组件。如果一个 Bean 不知道属于哪个层，可以使用`@Component` 注解标注。
-   `@Repository` : 对应持久层即 Dao 层，主要用于数据库相关操作。
-   `@Service` : 对应服务层，主要涉及一些复杂的逻辑，需要用到 Dao 层。
-   `@Controller` : 对应 Spring MVC 控制层，主要用于接受用户请求并调用 `Service` 层返回数据给前端页面。



### @Component 和 @Bean 的区别是什么？

*   `@Component` 注解作用于类，而`@Bean`注解作用于方法。
*   `@Component`通常是通过类路径扫描来自动侦测以及自动装配到 Spring 容器中（我们可以使用 `@ComponentScan` 注解定义要扫描的路径从中找出标识了需要装配的类自动装配到 Spring 的 bean 容器中）。`@Bean` 注解通常是我们在标有该注解的方法中定义产生这个 bean,`@Bean`告诉了 Spring 这是某个类的实例，当我需要用它的时候还给我。
*   `@Bean` 注解比 `@Component` 注解的自定义性更强，而且很多地方我们只能通过 `@Bean` 注解来注册 bean。比如当我们引用第三方库中的类需要装配到 `Spring`容器时，则只能通过 `@Bean`来实现。

![image-20251029182621366](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291826289.png)

`@Bean` 注解使用示例：

```java
@Configuration
public class OSSConfig {
    @Bean
    public AliyunOSSOperator aliyunOSSOperator(AliyunOSSProperties ossProperties) {
        return new AliyunOSSOperator(ossProperties);
    }
}
```

:warning: 通过 `@Bean` 注解的 Bean 的名称默认就是方法名。

:bulb: ​推荐使用一个单独的配置类来管理第三方 Bean

![image-20251029182810877](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291828769.png)



### 注入 Bean 的注解有哪些？

Spring 内置的 `@Autowired` 以及 JDK 内置的 `@Resource` 和 `@Inject` 都可以用于注入 Bean。

| Annotation   | Package                            | Source       |
| ------------ | ---------------------------------- | ------------ |
| `@Autowired` | `org.springframework.bean.factory` | Spring 2.5+  |
| `@Resource`  | `javax.annotation`                 | Java JSR-250 |
| `@Inject`    | `javax.inject`                     | Java JSR-330 |

`@Autowired` 和 `@Resource` 使用的比较多一些。

#### @Autowired 和 @Resource 的区别是什么？

**@Autowired**

`@Autowired` 是 Spring 内置的注解，默认注入逻辑为**先按类型（byType）匹配，若存在多个同类型 Bean，则再尝试按名称（byName）筛选**。

具体来说：

1.  优先根据接口 / 类的类型在 Spring 容器中查找匹配的 Bean。若只找到一个符合类型的 Bean，直接注入，无需考虑名称；
2.  若找到多个同类型的 Bean（例如一个接口有多个实现类），则会尝试通过**属性名或参数名**与 Bean 的名称进行匹配（默认 Bean 名称为类名首字母小写，除非通过 `@Bean(name = "...")` 或 `@Component("...")` 显式指定）。

当一个接口存在多个实现类时：

-   若属性名与某个 Bean 的名称一致，则注入该 Bean；
-   若属性名与所有 Bean 名称都不匹配，会抛出 `NoUniqueBeanDefinitionException`，此时需要通过 `@Qualifier` 显式指定要注入的 Bean 名称。

举例说明：

```java
// SmsService 接口有两个实现类：SmsServiceImpl1、SmsServiceImpl2（均被 Spring 管理）

// 报错：byType 匹配到多个 Bean，且属性名 "smsService" 与两个实现类的默认名称（smsServiceImpl1、smsServiceImpl2）都不匹配
@Autowired
private SmsService smsService;

// 正确：属性名 "smsServiceImpl1" 与实现类 SmsServiceImpl1 的默认名称匹配
@Autowired
private SmsService smsServiceImpl1;

// 正确：通过 @Qualifier 显式指定 Bean 名称 "smsServiceImpl1"
@Autowired
@Qualifier(value = "smsServiceImpl1")
private SmsService smsService;
```

实际开发实践中，建议通过 `@Qualifier` 注解来显式指定名称而不是依赖变量的名称。

**@Resource**

`@Resource` 有两个比较重要且日常开发常用的属性：`name`（名称）、`type`（类型）。

```java
public @interface Resource {
    String name() default "";
    Class<?> type() default Object.class;
}
```

如果仅指定 `name` 属性则注入方式为 `byName`，如果仅指定 `type` 属性则注入方式为 `byType`，如果同时指定 `name` 和 `type` 属性（不建议这么做）则注入方式为 `byType` + `byName`。

```java
// 报错，byName 和 byType 都无法匹配到 bean
@Resource
private SmsService smsService;
// 正确注入 SmsServiceImpl1 对象对应的 bean
@Resource
private SmsService smsServiceImpl1;
// 正确注入 SmsServiceImpl1 对象对应的 bean（比较推荐这种方式）
@Resource(name = "smsServiceImpl1")
private SmsService smsService;
```

:bulb: ​考虑到 `@Resource` 的语义更清晰（名称优先），并且是 Java 标准，能减少对 Spring 框架的强耦合，通常**更推荐使用 `@Resource`**，尤其是在需要按名称注入的场景下。而 `@Autowired` 配合构造器注入，在实现依赖注入的不可变性和强制性方面有优势，也是一种非常好的实践。















### Bean 的作用域

Bean 的默认作用域为 `singleton`：默认单例的 Bean 是在项目启动时创建的，创建完毕后会将该 Bean 存入 IOC 容器中。

`@Lazy` 注解：延迟初始化，将单例对象的初始化延迟到第一次使用的时候，再来创建这个 bean，即懒汉模式。

`@Scope("prototype")` 注解：非单例的，多例的

![image-20251029175758697](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291757472.png)

![image-20251029180139100](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291801942.png)

![image-20251029180312338](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291803025.png)

:bulb: ​Bean 的默认名字是类名首字母小写。
