# SpringBoot 基础

## SpringBoot 项目配置文件

项目中原有的 `application.properties` 文件存在配置臃肿、层级结构不清晰的问题：

![image-20251011223412063](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112234614.png)

### 使用 properties、yml 和 yaml 配置文件配置

SpringBoot 支持三种格式的配置文件：`.properties`、`.yml`、`.yaml`

![image-20251029155957954](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291559766.png)

:bulb: 其中优先级为：`.properties` > `.yml` > `.yaml`

但是 properties 格式存在配置臃肿和层级结构不清晰的问题：

![image-20251011223713883](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112237742.png)

:bulb: 配置文件的格式选择：`yml` > `properties`，其中在 `yaml` 和 `yml` 两者中，后者在项目中更常用。

:warning: `yml` 配置文件中以 0 开头的值表示八进制，如果想表示其本身含义，需要使用 `''` 引起来。

![image-20251011224002894](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112240823.png)

#### 练习

将 `application.properties` 配置文件修改为 `application.yml` 配置文件：

![image-20251011224028690](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112240499.png)



### 使用 Java 系统属性和命令行参数配置

![image-20251029160436500](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291604348.png)

:bulb: 总的优先级：`命令行参数` > `Java系统属性` > `.properties` > `.yml` > `.yaml`

![image-20251029160841585](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510291608434.png)

:bulb: ​单个 `-` 开始的参数表示 `Java系统属性`，两个 `--` 开始的参数表示 `命令行参数`。



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

