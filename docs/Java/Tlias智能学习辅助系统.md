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
     *   Dao (Mapper)：数据访问。使用 MyBatis 实现，所以这一部分可以改为 Mapper。
5.   和前端进行数据交互的数据均封装为 JSON 格式，使用 `@RequestBody` 注解以在数据传输前自动地将 Java 对象转换为 JSON 格式
6.   使用 Apifox 来模拟各种请求
7.   后端代码的具体实现部分使用面向接口编程的方式，利用多态、IOC、DI 等机制
8.   日志使用 `Slf4j` （底层还是 `Logback`）



## 二、员工管理

那接下来，我们要来完成的是员工列表的查询功能实现。 具体的需求如下：

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141104933.png)

在查询员工列表数据时，既需要查询 员工的基本信息，还需要查询员工所属的部门名称，所以这里呢，会涉及到多表查询的操作。

而且，在查询员工列表数据时，既要考虑搜索栏中的查询条件，还要考虑对查询的结果进行分页处理。

那么接下来，我们在实现这个功能时，将会分为三个部分来逐一实现：

-   准备工作
-   分页查询
-   条件分页查询



### 准备工作

1.   创建员工管理相关表结构：数据库表 emp、emp_expr
2.   准备实体类 Emp、EmpExpr
3.   准备三层架构的基本代码结构：EmpController、EmpService/EmpServiceImpl、EmpMapper



### 分页查询

![image-20251014120908364](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141209244.png)

#### 原始方式

![image-20251014121757402](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141217492.png)

![image-20251014134516068](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141345134.png)

#### PageHelper分页插件

 ![image-20251014170842669](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141708586.png)

![image-20251014170942525](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141709422.png)

在 `pom.xml` 文件中引入依赖：

```xml
<!--分页插件PageHelper-->
<dependency>
    <groupId>com.github.pagehelper</groupId>
    <artifactId>pagehelper-spring-boot-starter</artifactId>
    <version>1.4.7</version>
</dependency>
```

在 `EmpMapper.java` 中定义接口的查询方法（无需考虑分页）

```java
/**
 * 查询所有的员工及其对应的部门名称
 */
@Select("select e.*, d.name deptName from emp as e left join dept as d on e.dept_id = d.id")
public List<Emp> list();
```

在 `EmpServiceImpl.java` 中实现分页查询

```java
@Override
public PageResult page(Integer page, Integer pageSize) {
    //1. 设置分页参数
    PageHelper.startPage(page,pageSize);

    //2. 执行查询
    List<Emp> empList = empMapper.list();
    Page<Emp> p = (Page<Emp>) empList;

    //3. 封装结果
    return new PageResult(p.getTotal(), p.getResult());
}
```

![image-20251014180337180](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141803391.png)

:bulb: `PageHelper` 将原来的两次 SQL 操作替换为一次 SQL 操作。

![image-20251014180720214](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141807281.png)



:warning: PageHelper 实现分页查询时，SQL 语句的结尾不能加分号

:warning: PageHelper 只会对紧跟在其后的第一条 SQL 语句进行分页处理​



### 条件分页查询

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141914612.png)

通过员工管理的页面原型我们可以看到，员工列表页面的查询，不仅仅需要考虑分页，还需要考虑查询条件。 分页查询我们已经实现了，接下来，我们需要考虑在分页查询的基础上，再加上查询条件。

我们看到页面原型及需求中描述，搜索栏的搜索条件有三个，分别是：

-   姓名：模糊匹配
-   性别：精确匹配
-   入职日期：范围匹配

![image-20251014202203197](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510142022634.png)



:warning: ​在预编译的 SQL 中，不能够把 `#{}` 放到单引号中，比如：

```java
@Select("SELECT e.*, d.name deptName FROM emp e LEFT JOIN dept d ON e.dept_id = d.id WHERE e.name like '%#{name}%' AND e.gender = #{gender} AND e.entry_date BETWEEN #{begin} AND #{end} ORDER BY e.update_time DESC LIMIT #{start}, #{pageSize}")
    public List<Emp> conditionalQuery(Integer start, Integer pageSize, String name, Integer gender, LocalDate begin, LocalDate end);
```

应该使用 `CONCAT()` 来解决：

```java
@Select("SELECT e.*, d.name deptName FROM emp e LEFT JOIN dept d ON e.dept_id = d.id WHERE e.name like CONCAT('%', #{name}, '%') AND e.gender = #{gender} AND e.entry_date BETWEEN #{begin} AND #{end} ORDER BY e.update_time DESC LIMIT #{start}, #{pageSize}")
    public List<Emp> conditionalQuery(Integer start, Integer pageSize, String name, Integer gender, LocalDate begin, LocalDate end);
```

![image-20251014214802580](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510142148421.png)



#### 优化1：封装请求参数

在上述分页条件查询中，请求参数比较多，有6个，如下所示：

-   请求参数：/emps?name=张&gender=1&begin=2007-09-01&end=2022-09-01&page=1&pageSize=10

那我们在 Controller 层方法中，接收请求参数的时候，直接在 Controller 方法中声明这样6个参数即可，这样做，功能可以实现，但是不方便维护和管理。

所以，可以将所有的参数封装为一个实体类，来管理这几个参数，不过要保证前段传递的请求参数和实体类的属性名是一样的。

```java
package top.amonologue.pojo;

import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;

@Data
public class EmpQueryParam {
    private Integer page = 1;  // 当前页码
    private Integer pageSize = 10;  // 每页记录数
    private String name;  // 员工姓名
    private Integer gender;  // 员工性别
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate begin;  // 入职日期
    @DateTimeFormat(pattern = "yyyy-MM-dd")
    private LocalDate end;  // 离职日期
}
```

然后将涉及到的 Controller、Service 和 Mapper 的参数替换为这个实体类。



#### 优化2：动态SQL

通过注解的方式实现的 Mapper 不利于动态的 SQL 实现。我们可以通过 MyBatis 中的动态 SQL 来实现不同的 SQL 语句。

**所谓动态SQL，指的就是随着用户的输入或外部的条件的变化而变化的SQL语句。**

具体的 `EmpMapper.xml` 文件的内容：

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "https://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="top.amonologue.mapper.EmpMapper">
    <select id="conditionalQuery" resultType="top.amonologue.pojo.EmpQueryParam">
        SELECT e.*, d.name deptName FROM emp e LEFT JOIN dept d ON e.dept_id = d.id
        <where>
            <if test="name != null and name != ''">
                e.name like CONCAT('%', #{name}, '%')
            </if>
            <if test="gender != null">
                AND e.gender = #{gender}
            </if>
            <if test="begin != null and end != null">
                AND e.entry_date BETWEEN #{begin} AND #{end}
            </if>
        </where>
        ORDER BY e.update_time DESC LIMIT #{start}, #{pageSize}
    </select>
</mapper>
```

:warning: 在不额外设置的情况下，MyBatis 的 Mapper 类要和对应的 XML 文件<mark>同包同名</mark>.

在这里呢，我们用到了两个动态SQL的标签：`<if>`  `<where>`。 这两个标签的具体作用如下：

*   `<if>`：判断条件是否成立，如果条件为true，则拼接SQL。

*   `<where>`：根据查询条件，来生成where关键字，并会自动去除条件前面多余的and或or。

![image-20251014231032852](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510142310779.png)











