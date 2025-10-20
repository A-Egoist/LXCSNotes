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

### 列表查询

那接下来，我们要来完成的是员工列表的列表查询功能实现。 具体的需求如下：

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141104933.png)

在查询员工列表数据时，既需要查询 员工的基本信息，还需要查询员工所属的部门名称，所以这里呢，会涉及到多表查询的操作。

而且，在查询员工列表数据时，既要考虑搜索栏中的查询条件，还要考虑对查询的结果进行分页处理。

那么接下来，我们在实现这个功能时，将会分为三个部分来逐一实现：

-   准备工作
-   分页查询
-   条件分页查询



#### 准备工作

1.   创建员工管理相关表结构：数据库表 emp、emp_expr
2.   准备实体类 Emp、EmpExpr
3.   准备三层架构的基本代码结构：EmpController、EmpService/EmpServiceImpl、EmpMapper



#### 分页查询

![image-20251014120908364](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141209244.png)

##### 原始方式

![image-20251014121757402](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141217492.png)

![image-20251014134516068](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510141345134.png)

##### PageHelper分页插件

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



#### 条件分页查询

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



##### 优化1：封装请求参数

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



##### 优化2：动态SQL

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

![image-20251015175756725](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510151758789.png)



### 新增员工

![image-20251015181129742](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510151811563.png)

在新增员工的时候，在表单中，我们既要录入员工的基本信息，又要录入员工的工作经历信息。 员工基本信息，对应的表结构是 emp表，员工工作经历信息，对应的表结构是 emp_expr 表，所以这里我们要操作两张表，往两张表中保存数据。

 

#### 准备工作

新增员工所涉及的两条 SQL 语句：

```sql
-- 新增员工
-- 保存员工的基本信息 - emp
INSERT INTO emp(username, name, gender, phone, job, salary, image, entry_date, dept_id, create_time, update_time)
VALUES('linpingzhi', '林平之', 1, '18809091234', 1, 8000, '1.jpg', '2022-09-18', 1, '2025-10-01 00:00:00', '2025-10-01 00:00:00');

-- 批量保存员工的工作经历信息 - emp_expr
INSERT INTO emp_expr(emp_id, begin, end, company, job) VALUES(37, '2012-07-01', '2019-03-03', '百度科技股份有限公司', 'java开发'), (37, '2019-03-15', '2023-03-01', '阿里巴巴科技股份有限公司', '架构师')
```



#### 思路分析

![image-20251015191836239](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510151918353.png)

![image-20251015192947777](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510151929639.png)

![image-20251015193901325](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510151939190.png)



使用 MyBatis 实现动态 SQL：

`EmpExprMapper.xml`

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "https://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="top.amonologue.mapper.EmpExprMapper">
    <select id="saveExprBatch">
        INSERT INTO emp_expr(emp_id, begin, end, company, job) VALUES
        <foreach collection="empExprList" item="empExpr" separator=", ">
            (#{empExpr.empId}, #{empExpr.begin}, #{empExpr.end}, #{empExpr.company}, #{empExpr.job})
        </foreach>
    </select>
</mapper>
```

![image-20251015202123955](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510152021075.png)



### 事务管理

MySQL 的事务管理原理详见：[MySQL](./MySQL.md)

![image-20251015223850897](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510152238527.png)

![image-20251015224421214](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510152244151.png)

![image-20251015225008237](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510152250917.png)

![image-20251015225154583](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510152251509.png)

![image-20251015225423945](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510152254797.png)

![image-20251015225524112](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510152255220.png)



### 文件上传

文件上传，是指将本地图片、视频、音频等文件上传到服务器，供其他用户浏览或下载的过程。

文件上传在项目中应用非常广泛，我们经常发微博、发微信朋友圈都用到了文件上传功能。

![image](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510160808535.png)

>   在我们的案例中，在新增员工的时候，要上传员工的头像，此时就会涉及到文件上传的功能。在进行文件上传时，我们点击加号或者是点击图片，就可以选择手机或者是电脑本地的图片文件了。当我们选择了某一个图片文件之后，这个文件就会上传到服务器，从而完成文件上传的操作。



#### 本地上传

![image-20251016081004420](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510160810390.png)

![image-20251016085004438](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510160850168.png)



#### 阿里云OSS

![image-20251016085316349](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510160853382.png)

![image-20251016085352210](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510160853164.png)

![image-20251016085455490](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510160854332.png)

![image-20251016090719804](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510160907769.png)

1.   本地配置阿里云 OSS 访问凭证：以管理员方式打开 cmd，然后分别执行如下命令：
     ```bash
     # 设置 KEY_ID 和 KEY_SECRET
     setx OSS_ACCESS_KEY_ID "YOUR_ACCESS_KEY_ID"
     setx OSS_ACCESS_KEY_SECRET "YOUR_ACCESS_KEY_SECRET"
     
     # 运行如下命令检查环境变量是否生效
     echo %OSS_ACCESS_KEY_ID%
     echo %OSS_ACCESS_KEY_SECRET%
     ```

2.   `pom.xml` 中配置相关依赖，参考官方文档：https://help.aliyun.com/zh/oss/developer-reference/oss-java-sdk/?spm=a2c4g.11186623.help-menu-31815.d_20_2_1.3a7a6e96J3uo2o#6c7270d006fv0

3.   配置完阿里云 OSS 之后，需要重启 IDEA 以加载访问凭证



![image-20251016112717647](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161127579.png)

1.   引入阿里云 OSS 文件上传工具类（由官方的示例代码改造而来）
2.   上传文件接口开发



![image-20251016115422750](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161154647.png)



#### 功能优化1

在刚才我们制作的AliyunOSS操作的工具类中，我们直接将 endpoint、bucketName参数直接在java文件中写死了。如下所示：

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161212123.png)

如果后续，项目要部署到测试环境、上生产环境，我们需要来修改这两个参数。 而如果开发一个大型项目，所有用到的技术涉及到的这些个参数全部写死在java代码中，是非常不便于维护和管理的。 



那么对于这些容易变动的参数，我们可以将其配置在配置文件中，然后通过 `@Value` 注解来注解外部配置的属性。如下所示：

![img](https://heuqqdmbyk.feishu.cn/space/api/box/stream/download/asynccode/?code=ZGRjMWE1ZTI0M2M4NDgxYzBjMzc2NjBkYjg0ZTYxZDJfa2t3Y1NVc0YyeG9mb1JoSEhidUNSNFFOeHlsWjRSNXFfVG9rZW46TmdkSGJxT2x2b0V5RVV4dEE5TWM4NzVobkJnXzE3NjA1ODc5Nzc6MTc2MDU5MTU3N19WNA)

具体实现代码如下：

`application.yml`

```YAML
#阿里云OSS
aliyun:
  oss:
    endpoint: https://oss-cn-chengdu.aliyuncs.com
    bucketName: amonologue-image-bed
    region: cn-chengdu
    dir: tlias
```

`AliyunOSSOperator.java`

```java
@Value("${aliyun.oss.endpoint}")
private String endpoint;
@Value("${aliyun.oss.bucketName}")
private String bucketName;
@Value("${aliyun.oss.region}")
private String region;
@Value("${aliyun.oss.dir}")
private String dir;
```



:bulb: 注解、运行时注入



#### 功能优化2

如果只有一两个属性需要注入，而且不需要考虑复用性，使用`@Value`注解就可以了。

但是使用@Value注解注入配置文件的配置项，如果配置项多，注入繁琐，不便于维护管理 和 复用。如下所示:

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161220692.png)

那么有没有一种方式可以简化这些配置参数的注入呢？答案是肯定有，在Spring中给我们提供了一种简化方式，可以直接将**配置文件**中配置项的值**自动注入**到对象的属性中。



Spring 提供的简化方式套路：

1). 需要创建一个实现类，且实体类中的属性名和配置文件当中key的名字必须要一致

​     比如：配置文件当中叫endpoint，实体类当中的属性也得叫endpoint，另外实体类当中的属性还需要提供 getter / setter方法

2). 需要将实体类交给Spring的IOC容器管理，成为IOC容器当中的bean对象

3). 在实体类上添加`@ConfigurationProperties`注解，并通过perfect属性来指定配置参数项的前缀

![img](https://heuqqdmbyk.feishu.cn/space/api/box/stream/download/asynccode/?code=NzhmOWZjOTE5ZjlmNTZhY2QwN2VhZWUxMmU0NzQzMjhfR3pZWHd3QWFRSURaWVl4d0ZKQzZKOVBEQzhDZ0MwZkFfVG9rZW46REdNTGJBSVg1b2dBdDd4QVUyUmNzM2dsblVjXzE3NjA1ODg0OTk6MTc2MDU5MjA5OV9WNA)

**具体实现步骤:**

1). 定义实体类AliyunOSSProperties ，并交给IOC容器管理

```Java
package top.amonologue.utils;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Data
@Component
@ConfigurationProperties(prefix = "aliyun.oss")
public class AliyunOSSProperties {
    private String endpoint;
    private String bucketName;
    private String region;
    private String dir;
}

```

2). 修改AliyunOSSOperator

```java
package top.amonologue.utils;

import com.aliyun.oss.*;
import com.aliyun.oss.common.auth.CredentialsProviderFactory;
import com.aliyun.oss.common.auth.EnvironmentVariableCredentialsProvider;
import com.aliyun.oss.common.comm.SignVersion;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import java.io.ByteArrayInputStream;
import java.util.UUID;

@Component
public class AliyunOSSOperator {

    @Autowired
    private AliyunOSSProperties aliyunOSSProperties;

    public String upload(byte[] content, String originalFilename) throws Exception {
        String endpoint = aliyunOSSProperties.getEndpoint();
        String bucketName = aliyunOSSProperties.getBucketName();
        String region = aliyunOSSProperties.getRegion();
        String dir = aliyunOSSProperties.getDir();

        // 从环境变量中获取访问凭证。运行本代码示例之前，请确保已设置环境变量OSS_ACCESS_KEY_ID和OSS_ACCESS_KEY_SECRET。
        EnvironmentVariableCredentialsProvider credentialsProvider = CredentialsProviderFactory.newEnvironmentVariableCredentialsProvider();

        // 填写Object完整路径，例如202406/1.png。Object完整路径中不能包含Bucket名称。
        //生成一个新的不重复的文件名
        String newFileName = UUID.randomUUID() + originalFilename.substring(originalFilename.lastIndexOf("."));
        String objectName = dir + "/" + newFileName;

        // 创建OSSClient实例。
        ClientBuilderConfiguration clientBuilderConfiguration = new ClientBuilderConfiguration();
        clientBuilderConfiguration.setSignatureVersion(SignVersion.V4);
        OSS ossClient = OSSClientBuilder.create()
                .endpoint(endpoint)
                .credentialsProvider(credentialsProvider)
                .clientConfiguration(clientBuilderConfiguration)
                .region(region)
                .build();

        try {
            ossClient.putObject(bucketName, objectName, new ByteArrayInputStream(content));
        } finally {
            ossClient.shutdown();
        }

        return endpoint.split("//")[0] + "//" + bucketName + "." + endpoint.split("//")[1] + "/" + objectName;
    }

}
```

![image-20251016124814000](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161248941.png)



### 删除员工

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161302821.png)



![image-20251016131644457](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161316359.png)

![image-20251016132129334](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161321298.png)



### 修改员工

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510161950602.png)

在进行修改员工信息的时候，我们首先先要根据员工的ID查询员工的详细信息用于页面回显展示，然后用户修改员工数据之后，点击保存按钮，就可以将修改的数据提交到服务端，保存到数据库。 具体操作为：

1.   根据ID查询员工信息
2.   保存修改的员工信息



#### 查询回调

我们可以先通过一条SQL语句，查询出指定员工的基本信息，及其员工的工作经历信息。SQL如下：

```SQL
-- 查询指定员工的基本信息
SELECT e.*, ee.id ee_id, ee.begin ee_begin, ee.end ee_end, ee.company ee_company, ee.job ee_job FROM emp e LEFT JOIN emp_expr ee ON e.id = ee.emp_id WHERE e.id = 30;
```

具体的实现思路如下：

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510162037289.png)

因为这个 SQL 查询结果有可能返回多条数据（用户有多段经历），但是使用 MyBatis 的 `resultType` 实现的自动封装我们只能接收到一条返回数据，所以我们需要使用 `resultMap` 来实现手动封装：

```xml
    <!-- 自定义结果集 ResultMap -->
    <resultMap id="empResultMap" type="top.amonologue.pojo.Emp">
        <id column="id" property="id" />
        <result column="username" property="username" />
        <result column="password" property="password" />
        <result column="name" property="name" />
        <result column="gender" property="gender" />
        <result column="phone" property="phone" />
        <result column="job" property="job" />
        <result column="salary" property="salary" />
        <result column="image" property="image" />
        <result column="entry_date" property="entryDate" />
        <result column="dept_id" property="deptId" />
        <result column="create_time" property="createTime" />
        <result column="update_time" property="updateTime" />

        <!-- 封装exprList -->
        <collection property="exprList" ofType="top.amonologue.pojo.EmpExpr">
            <id column="ee_id" property="id"/>
            <result column="ee_company" property="company"/>
            <result column="ee_job" property="job"/>
            <result column="ee_begin" property="begin"/>
            <result column="ee_end" property="end"/>
            <result column="ee_empid" property="empId"/>
        </collection>
    </resultMap>

    <select id="getInfoById" resultMap="empResultMap">
        SELECT e.*, ee.id ee_id, ee.begin ee_begin, ee.end ee_end, ee.company ee_company, ee.job ee_job
        FROM emp e LEFT JOIN emp_expr ee ON e.id = ee.emp_id
        WHERE e.id = #{id}
    </select>
```

在 `resultMap` 中，`column` 对应数据库中的字段，`property` 对应 Java 中的属性。

![image-20251017130038406](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171300379.png)

![image-20251017130103971](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171301822.png)



#### 修改员工

思路：

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171311185.png)

![image-20251017140316855](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171403961.png)



请求数据样例（接口文档中给出的数据有问题）：

```json
{
    "id": 2,
    "username": "zhangwuji",
    "password": "123456",
    "name": "张无忌",
    "gender": 1,
    "image": "https://web-framework.oss-cn-hangzhou.aliyuncs.com/2022-09-02-00-27-53B.jpg",
    "job": 2,
    "salary": 8000,
    "phone": 13399090239,
    "entryDate": "2015-01-01",
    "deptId": 2,
    "updateTime": "2022-09-02T00:29:04",
    "exprList": [
      {
        "begin": "2012-07-01",
        "end": "2015-06-20",
        "company": "中软国际股份有限公司",
        "job": "java开发"
      },
      {
        "begin": "2015-07-01",
        "end": "2019-03-03",
        "company": "百度科技股份有限公司",
        "job": "java开发"
      },
      {
        "begin": "2019-03-15",
        "end": "2023-03-01",
        "company": "阿里巴巴科技股份有限公司",
        "job": "架构师"
      }
    ]
  }
```



`EmpMapper.xml`

```xml
    <select id="updateById">
        UPDATE emp
        <set>
            <if test="username != null and username != ''">username = #{username},</if>
            <if test="password != null and password != ''">password = #{password},</if>
            <if test="name != null and name != ''">name = #{name},</if>
            <if test="gender != null">gender = #{gender},</if>
            <if test="image != null and image != ''">image = #{image},</if>
            <if test="job != null">job = #{job},</if>
            <if test="salary != null">salary = #{salary},</if>
            <if test="phone != null and phone != ''">phone = #{phone},</if>
            <if test="entryDate != null">entry_date = #{entryDate},</if>
            <if test="deptId != null">dept_id = #{deptId},</if>
            <if test="updateTime != null">update_time = #{updateTime},</if>
        </set>
        WHERE id = #{id};
    </select>
```



### 异常处理

#### 问题分析

当我们在修改部门数据的时候，如果输入一个在数据库表中已经存在的手机号，点击保存按钮之后，前端提示了错误信息，但是返回的结果并不是统一的响应结果，而是框架默认返回的错误结果 。

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171844233.png)

状态码为500，表示服务器端异常，我们打开idea，来看一下，服务器端出了什么问题。

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171844091.png)

上述错误信息的含义是，`emp`员工表的`phone`手机号字段的值重复了，因为在数据库表`emp`中已经有了`13309090027`这个手机号了，我们之前设计这张表时，为`phone`字段建议了唯一约束，所以该字段的值是不能重复的。

而当我们再将该员工的手机号也设置为 `13309090027`，就违反了唯一约束，此时就会报错。



我们来看一下出现异常之后，最终服务端给前端响应回来的数据长什么样。

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171844084.png)

响应回来的数据是一个JSON格式的数据。但这种JSON格式的数据还是我们开发规范当中所提到的统一响应结果Result吗？显然并不是。由于返回的数据不符合开发规范，所以前端并不能解析出响应的JSON数据 。

接下来我们需要思考的是出现异常之后，当前案例项目的异常是怎么处理的？ 答案：没有做任何的异常处理

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171844404.png" alt="img" style="zoom:50%;" />

当我们没有做任何的异常处理时，我们三层架构处理异常的方案：

-   Mapper接口在操作数据库的时候出错了，此时异常会往上抛(谁调用Mapper就抛给谁)，会抛给service。 
-   service 中也存在异常了，会抛给controller。
-   而在controller当中，我们也没有做任何的异常处理，所以最终异常会再往上抛。最终抛给框架之后，框架就会返回一个JSON格式的数据，里面封装的就是错误的信息，但是框架返回的JSON格式的数据并不符合我们的开发规范。



使用 `try-catch` 的方式抛出异常：

![image-20251017185108424](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510171851653.png)

使用 SpringBoot 提供的全局异常处理器处理异常：

![image-20251017222248375](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510172222184.png)

:bulb: 定义一个全局异常处理器需要使用到两个注解：`@RestControllerAdvice` 和 `@Exceptionhandler`

`top.amonologue.exception.GlobalExceptionHandler.java`：

```java
package top.amonologue.exception;

import lombok.extern.slf4j.Slf4j;
import org.springframework.dao.DuplicateKeyException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import top.amonologue.pojo.Result;

@Slf4j
@RestControllerAdvice
public class GlobalExceptionHandler {
    @ExceptionHandler
    public Result handleException(Exception e) {
        log.error(e.getMessage());
        return Result.error(e.getMessage());
    }

    /**
     * 处理 DuplicateKeyException
     */
    @ExceptionHandler
    public Result handleDuplicateKeyException(DuplicateKeyException e) {
        log.error("DuplicateKeyException");
        String message = e.getMessage();
        int i = message.indexOf("Duplicate entry");
        String errMsg = message.substring(i);
        String[] arr = errMsg.split(" ");

        return Result.error(arr[2] + " 已存在");
    }
}

```

当在 `GlobalExceptionHandler` 类中存在多个 `@ExceptionHandler` 注解的类方法，会根据接收的参数，按照继承树从低到高的方式匹配。



### 员工信息统计

使用 Echarts 来展示报表：https://echarts.apache.org/zh/index.html

![image-20251017231204364](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510172312305.png)

#### 职位统计

![image-20251017231557299](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510172315181.png)

![image-20251018104409652](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181044716.png)

![image-20251018104514718](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181045579.png)



#### 性别统计

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181108183.png" alt="img" style="zoom:50%;" />

对于这类的图形报表，服务端要做的，就是为其提供数据即可。 我们可以通过官方的示例，看到提供的数据就是一个json格式的数据。

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181108859.png)

![image-20251018111415994](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181114901.png)

![image-20251018111513374](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181115251.png)

![image-20251018111534059](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181115882.png)



## 三、班级管理



## 四、学员管理

![image-20251018123219306](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181232222.png)

![image-20251018123235224](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181232073.png)

![image-20251018123253811](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181232887.png)

![image-20251018123330677](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181233450.png)

[项目实战-需求说明](https://www.bilibili.com/video/BV1yGydYEE3H?spm_id_from=333.788.player.switch&vd_source=f4cc25a44af6631d6f4db023b3bb88e4&p=119)





## 五、登录认证

### 登录功能

![image-20251018124401950](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181244738.png)

:bulb: ​定义一个实体类用于封装登录结果

![image-20251018130239230](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181302049.png)

:bulb: ​Mapper 中的方法名不用跟业务挂钩，尽量做到见名知意。

![image-20251018171737767](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181717694.png)



### 登录校验

所谓登录校验，指的是我们在服务器端接收到浏览器发送过来的请求之后，首先我们要对请求进行校验。先要校验一下用户登录了没有，如果用户已经登录了，就直接执行对应的业务操作就可以了；如果用户没有登录，此时就不允许他执行相关的业务操作，直接给前端响应一个错误的结果，最终跳转到登录页面，要求他登录成功之后，再来访问对应的数据。



#### 思路

了解完什么是登录校验之后，接下来我们分析一下登录校验大概的实现思路。

首先我们在宏观上先有一个认知：

前面在讲解HTTP协议的时候，我们提到HTTP协议是无状态协议。什么又是无状态的协议？

所谓无状态，指的是每一次请求都是独立的，下一次请求并不会携带上一次请求的数据。而浏览器与服务器之间进行交互，基于HTTP协议也就意味着现在我们通过浏览器来访问了登陆这个接口，实现了登陆的操作，接下来我们在执行其他业务操作时，服务器也并不知道这个员工到底登陆了没有。因为HTTP协议是无状态的，两次请求之间是独立的，所以是无法判断这个员工到底登陆了没有。

![image-20251018190204826](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510181902300.png)

那应该怎么来实现登录校验的操作呢？具体的实现思路可以分为两部分：

1.  在员工登录成功后，需要将用户登录成功的信息存起来，记录用户已经登录成功的标记。
2.  在浏览器发起请求时，需要在服务端进行统一拦截，拦截后进行登录校验。



#### 会话技术

**会话**：在用户打开浏览器第一次访问服务器的时候，这个会话就建立了，直到有任何一方断开连接，此时会话就结束了。在一次会话当中，是可以包含多次请求和响应的。

**会话跟踪**：一种维护浏览器状态的方法，服务器需要识别多次请求是否来自于同一浏览器，以便在同一次会话的多次请求间共享数据。

**会话跟踪方案**：

1.  Cookie（客户端会话跟踪技术）：数据存储在客户端浏览器当中
2.  Session（服务端会话跟踪技术）：数据存储在储在服务端
3.  令牌技术



**Cookie**

![image-20251018200402669](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182004580.png)



**Session**

![image-20251018203939444](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182039414.png)



**令牌**

![image-20251018204347200](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182043038.png)



:bulb: 针对于这三种方案，现在企业开发当中使用的最多的就是第三种令牌技术进行会话跟踪。而前面的这两种传统的方案，现在企业项目开发当中已经很少使用了。



#### JWT 令牌

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182046813.png)

JWT令牌最典型的应用场景就是登录认证：

1.  在浏览器发起请求来执行登录操作，此时会访问登录的接口，如果登录成功之后，我们需要生成一个  令牌，将生成的 JWT 令牌返回给前端。
2.  前端拿到 JWT 令牌之后，会将 JWT 令牌存储起来。在后续的每一次请求中都会将 JWT 令牌携带到服务端。
3.  服务端统一拦截请求之后，先来判断一下这次请求有没有把令牌带过来，如果没有带过来，直接拒绝访问，如果带过来了，还要校验一下令牌是否是有效。如果有效，就直接放行进行请求的处理。

在 JWT 登录认证的场景中我们发现，整个流程当中涉及到两步操作：

1.  在登录成功之后，要生成令牌。
2.  每一次请求当中，要接收令牌并对令牌进行校验。



![image-20251018222711474](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182227475.png)

![image-20251018222804622](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182228569.png)

![image-20251018222836953](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182228732.png)

![image-20251018223912542](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510182239433.png)



**案例**

JWT 令牌的生成和校验的基本操作我们已经学习完了，接下来我们就需要在案例当中通过 JWT 令牌技术来跟踪会话。具体的思路我们前面已经分析过了，主要就是两步操作：

1.  生成令牌
    1.  在登录成功之后来生成一个 JWT 令牌，并且把这个令牌直接返回给前端
2.  校验令牌
    1.  拦截前端请求，从请求中获取到令牌，对令牌进行解析校验

那我们首先来完成：登录成功之后生成 JWT 令牌，并且把令牌返回给前端。

:bulb: JWT 令牌存储在浏览器的本地存储空间 `localstorage` 中了。 `localstorage` 是浏览器的本地存储，在移动端也是支持的。



#### 过滤器 Filter

通过浏览器的开发者工具，我们可以看到在后续的请求当中，都会在请求头中携带JWT令牌到服务端，而服务端需要统一拦截所有的请求，从而判断是否携带的有合法的JWT令牌。

那怎么样来统一拦截到所有的请求校验令牌的有效性呢？这里我们会学习两种解决方案：

1.  Filter过滤器
2.  Interceptor拦截器

我们首先来学习过滤器Filter。



**快速入门**

![image-20251019101849911](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191018915.png)

![image-20251019102114148](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191021807.png)

![image-20251019103359376](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191034195.png)



**登录校验 Filter**

![image-20251019105438677](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191054565.png)



**令牌校验流程**

我们要完成登录校验，主要是利用Filter过滤器实现，而Filter过滤器的流程步骤：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191056385.png" alt="img" style="zoom: 67%;" />

基于上面的业务流程，我们分析出具体的操作步骤：

1.  获取请求url
2.  判断请求url中是否包含login，如果包含，说明是登录操作，放行
3.  获取请求头中的令牌（token）
4.  判断令牌是否存在，如果不存在，响应 401
5.  解析token，如果解析失败，响应 401
6.  放行



**详解(执行流程、拦截路径、过滤器链)**

![image-20251019110912074](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191109928.png)

![image-20251019111111237](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191111072.png)

:warning: 在目录拦截部分，`/emps/*` 中的 `/*` 可以有也可以没有。也就是说 `/emps/*` 可以拦截请求路径 `/emps` 及其子路径。

![image-20251019111416969](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191114885.png)

![image-20251019111523793](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191115658.png)



#### 拦截器 Interceptor

![image-20251019111815253](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191118260.png)



**快速入门**

![image-20251019112143719](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191121775.png)

![image-20251019112807153](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191128136.png)



**令牌校验 Interceptor**

![image-20251019112855369](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191128204.png)



**详解(拦截路径、执行流程)**

![image-20251019124832793](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191248673.png)

![image-20251019125322016](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191253949.png)

![image-20251019125344521](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510191253288.png)



## 六、Spring AOP

![image-20251020102414388](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510201024207.png)

![image-20251020102331947](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510201023818.png)



### AOP 基础

![image-20251020102638074](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510201027275.png)

![image-20251020103939429](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510201039805.png)

:bulb: ​侵入式和非侵入式

![image-20251020104521172](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510201045194.png)





### AOP 进阶









### AOP 案例

























