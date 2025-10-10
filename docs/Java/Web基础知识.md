# Web基础知识

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

![image-20251010165519089](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510101655944.png)



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



### 分层解耦

![image-20251010224246056](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102242269.png)

![image-20251010224611208](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102246316.png)

![image-20251010224820152](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102248043.png)



### IOC & DI 入门

![image-20251010225018434](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102250289.png)

1.   给对应的类加上 `@Component` 注解
2.   给成员变量加上 `@Atowired` 注解

![image-20251010225543458](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102255334.png)



### IOC 详解

![image-20251010230354209](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102303261.png)

在声明 Bean 的时候指定 Bean 的名字：`@Repository("userDao")`

![image-20251010230654349](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102306143.png)



### DI 详解

![image-20251010231600023](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102316080.png)

:bulb: ​Bean 的默认名字是类名的首字母小写。

![image-20251010232124196](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102321227.png)

![image-20251010232224189](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510102322014.png)
