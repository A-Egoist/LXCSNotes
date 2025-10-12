# Tlias 智能学习辅助系统

![image-20251011225006084](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112250087.png)

## 一、部门管理

![image-20251011225028692](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112250640.png)



### 1、准备工作

#### 1.1、开发规范

##### 前后端分离开发

早期开发模式——前后端混合开发

![image-20251012084922154](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120849133.png)

![image-20251012085532294](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120855112.png)



##### Restful风格

![image-20251012090117539](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120901469.png)

![image-20251012090155743](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120901525.png)

![image-20251012090228286](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120902182.png)



接口测试工具：

![image-20251012090406790](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120904563.png)

![image-20251012090534264](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120905160.png)

![image-20251012090903242](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120909417.png)



#### 1.2、工程搭建

>   环境准备：
>
>   1.   MySQL
>        1.   下载地址：https://dev.mysql.com/downloads/windows/installer/8.0.html；
>        2.   安装教程：https://heuqqdmbyk.feishu.cn/wiki/ZRSFwACsRiBD2NkV7bmcrJhInme
>        3.   初始化
>   2.   DataGrip
>        1.   下载地址：https://www.jetbrains.com/datagrip/download/?section=windows
>        2.   安装教程：https://heuqqdmbyk.feishu.cn/wiki/FAa3wj0nYi4xGBksbFuchBK8nhe
>        3.   连接数据库
>   3.   IDEA 中配置 SQL 提示：https://heuqqdmbyk.feishu.cn/wiki/WgPdwfw7PiWSd5knBiYcWE1aneM
>   4.   配置 MyBatis 日志输出：https://heuqqdmbyk.feishu.cn/wiki/WgPdwfw7PiWSd5knBiYcWE1aneM
>   5.   Apifox：https://app.apifox.com/main/teams/3878880?tab=project

![image-20251012091207995](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120912910.png)

![image-20251012091238784](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510120912773.png)



1.   创建空项目
     ![image-20251012111113167](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121111492.png)
2.   检查项目的 JDK 版本
     ![image-20251012111131215](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121111847.png)
3.   检查 Maven 路径
     ![image-20251012111207475](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121112644.png)
4.   修改字符集为 `UTF-8`
     ![image-20251012111310678](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121113996.png)
5.   创建 Module，选择为 SpringBoot
     ![image-20251012111555905](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121115027.png)
     ![image-20251012111640935](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121116024.png)
6.   创建完成



:bulb: 在数据库中，字段、表名的命名规范，多个单词之间使用 `_` 分隔，比如 `update_time`

:bulb: 在 Java 中，实体类中属性的命名规范，采用驼峰命名法，比如 `updateTime`



### 2、查询部门

#### 2.1、接口开发

![image-20251012121841754](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121218326.png)

![image-20251012132620402](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121326160.png)

![image-20251012132752286](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121327288.png)

![image-20251012155340626](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121553434.png)

![image-20251012155905175](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121559071.png)



#### 2.2、前后端联调测试

![image-20251012160422512](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121604511.png)

![image-20251012160726005](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121607909.png)

>   :bulb: ​正则表达式

![image-20251012161116186](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121611021.png)

![image-20251012161252344](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121612059.png)



### 3、删除部门

![image-20251012161419671](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121614500.png)

![image-20251012164302151](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121643971.png)



#### 简单参数接收-方式一

![image-20251012162446949](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121624708.png)



#### 简单参数接收-方式二

![image-20251012162942466](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121629353.png)



#### 简单参数接收-方式三

![image-20251012163121659](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121631452.png)



#### 代码实现

![image-20251012164433121](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121644331.png)



### 4、新增部门

![image-20251012173537945](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121735018.png)

![image-20251012173952213](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121739001.png)

![image-20251012174631453](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121746506.png)

![image-20251012175424265](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121754236.png)



### 5、修改部门

![image-20251012180226868](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121802721.png)

#### 5.1、查询回显

![image-20251012180318320](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121803123.png)

![image-20251012180604037](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121806925.png)

:bulb: 路径参数​

![image-20251012181219983](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121812864.png)

![image-20251012181744925](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121817637.png)![image-20251012181905620](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121819609.png)



#### 5.2、修改数据

![image-20251012190717931](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121907883.png)

![image-20251012191808154](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121918099.png)

![image-20251012191853466](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121918277.png)



#### 5.3、@RequestMapping

![image-20251012192123523](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121921402.png)

![image-20251012192357501](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121923359.png)



### 6、日志技术

![image-20251012192539359](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121925279.png)

![image-20251012192703614](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121927496.png)

![image-20251012192954366](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121929200.png)



#### 6.1、Logback 快速入门

![image-20251012193211697](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121932517.png)



#### 6.2、Logback 配置文件详解

![image-20251012194954654](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121949825.png)

:bulb: ​个人用日志配置

`logback.xml`

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<configuration>
    <!-- 控制台输出 -->
    <appender name="STDOUT" class="ch.qos.logback.core.ConsoleAppender">
        <encoder class="ch.qos.logback.classic.encoder.PatternLayoutEncoder">
            <!-- 格式化输出：%d 表示日期，%thread 表示线程名，%-5level表示级别从左显示5个字符宽度，%msg表示日志消息，%n表示换行符 -->
            <pattern>%d{yyyy-MM-dd HH:mm:ss.SSS} [%thread] %-5level %logger{50}-%msg%n</pattern>
        </encoder>
    </appender>

    <!-- 按照每天生成日志文件 -->
    <appender name="FILE" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <rollingPolicy class="ch.qos.logback.core.rolling.SizeAndTimeBasedRollingPolicy">
            <!-- 日志文件输出的文件名, %i表示序号 -->
            <!-- <FileNamePattern>D:/tlias-%d{yyyy-MM-dd}-%i.log</FileNamePattern> -->
            <FileNamePattern>D:/Projects/Java_tutorial/Tlias/logs/tlias-%d{yyyy-MM-dd}-%i.log</FileNamePattern>
            <!-- 最多保留的历史日志文件数量 -->
            <MaxHistory>30</MaxHistory>
            <!-- 最大文件大小，超过这个大小会触发滚动到新文件，默认为 10MB -->
            <maxFileSize>10MB</maxFileSize>
        </rollingPolicy>

        <encoder class="ch.qos.logback.classic.encoder.PatternLayoutEncoder">
            <!-- 格式化输出：%d 表示日期，%thread 表示线程名，%-5level表示级别从左显示5个字符宽度，%msg表示日志消息，%n表示换行符 -->
            <pattern>%d{yyyy-MM-dd HH:mm:ss.SSS} [%thread] %-5level %logger{50}-%msg%n</pattern>
        </encoder>
    </appender>

    <!-- 日志输出级别 -->
    <root level="INFO">
         <!-- 输出到控制台 -->
        <appender-ref ref="STDOUT" />
        <!-- 输出到文件 -->
         <appender-ref ref="FILE" />
    </root>

</configuration>
```



#### 6.3、Logback 日志级别

![image-20251012195231161](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121952176.png)



#### 6.4、案例

![image-20251012195328809](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510121953771.png)

在实际项目中，声明 `Logger` 实例的方式有两种：

1.   在类中声明：
     ```java
     private static final Logger log = LoggerFactory.getLogger(DeptController.class);  // 固定的代码
     ```

2.   在类外使用 `lombok` 提供的注解 `@Slf4j`，这样生成的 `Logger` 实例名称为 `log`

![image-20251012200329937](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510122003005.png)



### 7、个人总结

前后端分离项目的后端部分的开发流程：

1.   需求分析
2.   根据需求设计接口文档，接口文档的设计参考：https://heuqqdmbyk.feishu.cn/wiki/GyZVwpRf6ir89qkKtFqc0HlTnhg
3.   实现数据库以及 SQL 请求
4.   使用 SpringBoot 的 Java 后端按照三层架构的方式实现，具体来说将后端部分分为：
     *   Controller：接收请求、响应请求
     *   Service：业务逻辑处理
     *   Dao：数据访问。使用 MyBatis 实现，所以这一部分可以改为 Mapper。
5.   和前端进行数据交互的数据均封装为 JSON 格式，使用 `@RequestBody` 注解以在数据传输前自动地将 Java 对象转换为 JSON 格式
6.   使用 Apifox 来模拟各种请求
7.   后端代码的具体实现部分使用面向接口编程的方式，利用多态、IOC、DI 等机制
8.   日志使用 `Slf4j` （底层还是 `Logback`）



## 二、员工管理











