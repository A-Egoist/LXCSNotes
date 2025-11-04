# SpringBoot 原理

## 配置优先级

![image-20251029155957954](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291559766.png)

SpringBoot 支持三种格式的配置文件：`.properties`、`.yml`、`.yaml`

:bulb: 其中优先级为：`.properties` > `.yml` > `.yaml`

:bulb: 但是推荐使用 `.yml` 格式的配置文件

![image-20251029160436500](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291604348.png)

:bulb: 总的优先级：`命令行参数` > `Java系统属性` > `.properties` > `.yml` > `.yaml`

![image-20251029160841585](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291608434.png)

:bulb: ​单个 `-` 开始的参数表示 `Java系统属性`，两个 `--` 开始的参数表示 `命令行参数`。



## Bean 管理

### Bean 的作用域

Bean 的默认作用域 `singleton`：默认单例的 Bean 是在项目启动时创建的，创建完毕后会将该 Bean 存入 IOC 容器中。

`@Lazy` 注解：延迟初始化，将单例对象的初始化延迟到第一次使用的时候，再来创建这个 bean，即懒汉模式。

`@Scope("prototype")` 注解：非单例的，多例的

![image-20251029175758697](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291757472.png)

![image-20251029180139100](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291801942.png)

![image-20251029180312338](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291803025.png)

:bulb: ​Bean 的默认名字是类名首字母小写。



### 第三方 Bean



![image-20251029182621366](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291826289.png)

:warning: 通过 `@Bean` 注解的 Bean 的名称默认就是方法名。

:bulb: ​推荐使用一个单独的配置类来管理第三方 Bean

![image-20251029182810877](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291828769.png)



## SpringBoot 原理

### 起步依赖

起步依赖的原理：Maven 的依赖传递



### 自动配置

![image-20251029185629423](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291856253.png)

#### 实现方案

**自动配置实现方案一**：`@Component` + `@ComponentScan`

组件扫描，通过 `@ComponentScan` 设置扫描的包

![image-20251029190635911](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291906939.png)



**自动配置实现方案二**：

```java
// @Import(TokenParser.class)  // 普通类
// @Import(HeaderConfig.class)  // 配置类
// @Import(MyImportSelector.class)  // ImportSelector 接口实现类 - 批量导入

// @EnableHeaderConfig  // 导入第三方库提供的注解，第三方库在这个注解内部实现了 @Import 注解
```

![image-20251030220025746](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510302203307.png)



#### 源码跟踪

![image-20251030222159525](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510302222462.png)

![image-20251030222555450](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510302225603.png)



:warning:

>   Bean、IOC 容器、自动注入



`@Conditional` 注解的作用

![image-20251031151108361](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510311511269.png)

![image-20251031151316015](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510311513354.png)

![image-20251031151514276](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510311515115.png)



#### 自定义 starter

![image-20251031184542560](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510311845525.png)

![image-20251031205237981](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510312052764.png)

https://www.bilibili.com/video/BV1yGydYEE3H/?p=147


