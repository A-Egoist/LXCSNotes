# 苍穹外卖-Day03

## 课程内容

- 公共字段自动填充
- 新增菜品
- 菜品分页查询
- 删除菜品
- 修改菜品



**功能实现：**菜品管理

**菜品管理效果图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604111050491.png" alt="image-20221121142133307" style="zoom:50%;" /> 





## 1. 公共字段自动填充

### 1.1 问题分析

在上一章节我们已经完成了后台系统的**员工管理功能**和**菜品分类功能**的开发，在**新增员工**或者**新增菜品分类**时需要设置创建时间、创建人、修改时间、修改人等字段，在**编辑员工**或者**编辑菜品分类**时需要设置修改时间、修改人等字段。这些字段属于公共字段，也就是也就是在我们的系统中很多表中都会有这些字段，如下：

| **序号** | **字段名**  | **含义**  | **数据类型** |
| -------- | ----------- | --------- | ------------ |
| 1        | create_time | 创建时间  | datetime     |
| 2        | create_user | 创建人 id | bigint       |
| 3        | update_time | 修改时间  | datetime     |
| 4        | update_user | 修改人 id | bigint       |

而针对于这些字段，我们的赋值方式为： 

1). 在新增数据时，将 createTime、updateTime 设置为当前时间，createUser、updateUser 设置为当前登录用户 id。
<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604111055729.png" alt="image-20260411105517876" style="zoom: 67%;" />

2). 在更新数据时，将 updateTime 设置为当前时间，updateUser 设置为当前登录用户 id。
<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604111055677.png" alt="image-20260411105538193" style="zoom:67%;" />



如果都按照上述的操作方式来处理这些公共字段，需要在每一个业务方法中进行操作，编码相对冗余、繁琐，那能不能对于这些公共字段在某个地方统一处理，来简化开发呢？

**答案是可以的，我们使用 AOP 切面编程，实现功能增强，来完成公共字段自动填充功能。**



### 1.2 实现思路

在实现公共字段自动填充，也就是在插入或者更新的时候为指定字段赋予指定的值，使用它的好处就是可以统一对这些字段进行处理，避免了重复代码。在上述的问题分析中，我们提到有四个公共字段，需要在新增/更新中进行赋值操作, 具体情况如下: 

| **序号** | **字段名**  | **含义** | **数据类型** | **操作类型**   |
| -------- | ----------- | -------- | ------------ | -------------- |
| 1        | create_time | 创建时间 | datetime     | insert         |
| 2        | create_user | 创建人id | bigint       | insert         |
| 3        | update_time | 修改时间 | datetime     | insert、update |
| 4        | update_user | 修改人id | bigint       | insert、update |



**实现步骤：**

1). 自定义注解 AutoFill，用于标识需要进行公共字段自动填充的方法

2). 自定义切面类 AutoFillAspect，**统一拦截**加入了 AutoFill 注解的方法，通过**反射**为公共字段赋值

3). 在 Mapper 的方法上加入 AutoFill 注解



若要实现上述步骤，需掌握以下知识(之前课程内容都学过)

**技术点：**枚举、注解、AOP、反射

>   枚举：用于标识当前操作的类型
>
>   反射：为公共字段赋值



### 1.3 代码开发

按照上一小节分析的实现步骤依次实现，共三步。

#### 1.3.1 步骤一

**自定义注解 AutoFill**              

进入到 sky-server 模块，创建 com.sky.annotation 包。

```java
package com.sky.annotation;

import com.sky.enumeration.OperationType;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * 自定义注解，用于标识某个方法需要进行功能字段自动填充处理
 */
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface AutoFill {
    // 数据库操作类型：UPDATE 和 INSERT
    OperationType value();
}
```

其中 OperationType 已在 sky-common 模块中定义

```java
package com.sky.enumeration;

/**
 * 数据库操作类型
 */
public enum OperationType {

    /**
     * 更新操作
     */
    UPDATE,

    /**
     * 插入操作
     */
    INSERT
}
```



#### 1.3.2 步骤二

**自定义切面 AutoFillAspect**

在 sky-server 模块，创建 com.sky.aspect 包。

```java
package com.sky.aspect;

/**
 * 自定义切面，实现公共字段自动填充处理逻辑
 */
@Aspect
@Component
@Slf4j
public class AutoFillAspect {

    /**
     * 切入点
     */
    @Pointcut("execution(* com.sky.mapper.*.*(..)) && @annotation(com.sky.annotation.AutoFill)")
    public void autoFillPointCut(){}

    /**
     * 前置通知，在通知中进行公共字段的赋值
     */
    @Before("autoFillPointCut()")
    public void autoFill(JoinPoint joinPoint){
        /////////////////////重要////////////////////////////////////
        // 可先进行调试，是否能进入该方法 提前在 mapper 方法添加 AutoFill 注解
        log.info("开始进行公共字段自动填充...");
    }
}
```

**完善自定义切面 AutoFillAspect 的 autoFill 方法**

```java
package com.sky.aspect;

import com.sky.annotation.AutoFill;
import com.sky.constant.AutoFillConstant;
import com.sky.context.BaseContext;
import com.sky.enumeration.OperationType;
import lombok.extern.slf4j.Slf4j;
import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.aspectj.lang.reflect.MethodSignature;
import org.springframework.stereotype.Component;
import java.lang.reflect.Method;
import java.time.LocalDateTime;

/**
 * 自定义切面，实现公共字段自动填充处理逻辑
 */
@Aspect
@Component
@Slf4j
public class AutoFillAspect {

    /**
     * 切入点
     */
    @Pointcut("execution(* com.sky.mapper.*.*(..)) && @annotation(com.sky.annotation.AutoFill)")
    public void autoFillPointCut(){}

    /**
     * 前置通知，在通知中进行公共字段的赋值
     */
    @Before("autoFillPointCut()")
    public void autoFill(JoinPoint joinPoint){
        log.info("开始进行公共字段自动填充...");

        // 获取到当前被拦截的方法上的数据库操作类型
        MethodSignature signature = (MethodSignature) joinPoint.getSignature();  // 方法签名对象
        AutoFill autoFill = signature.getMethod().getAnnotation(AutoFill.class);  // 获得方法上的注解对象
        OperationType operationType = autoFill.value();  // 获得数据库操作类型

        // 获取到当前被拦截的方法的参数--实体对象
        Object[] args = joinPoint.getArgs();
        if(args == null || args.length == 0){
            return;
        }

        Object entity = args[0];

        // 准备赋值的数据
        LocalDateTime now = LocalDateTime.now();
        Long currentId = BaseContext.getCurrentId();

        // 根据当前不同的操作类型，为对应的属性通过反射来赋值
        if(operationType == OperationType.INSERT){
            // 为4个公共字段赋值
            try {
                Method setCreateTime = entity.getClass().getDeclaredMethod(AutoFillConstant.SET_CREATE_TIME, LocalDateTime.class);
                Method setCreateUser = entity.getClass().getDeclaredMethod(AutoFillConstant.SET_CREATE_USER, Long.class);
                Method setUpdateTime = entity.getClass().getDeclaredMethod(AutoFillConstant.SET_UPDATE_TIME, LocalDateTime.class);
                Method setUpdateUser = entity.getClass().getDeclaredMethod(AutoFillConstant.SET_UPDATE_USER, Long.class);

                // 通过反射为对象属性赋值
                setCreateTime.invoke(entity,now);
                setCreateUser.invoke(entity,currentId);
                setUpdateTime.invoke(entity,now);
                setUpdateUser.invoke(entity,currentId);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }else if(operationType == OperationType.UPDATE){
            // 为 2 个公共字段赋值
            try {
                Method setUpdateTime = entity.getClass().getDeclaredMethod(AutoFillConstant.SET_UPDATE_TIME, LocalDateTime.class);
                Method setUpdateUser = entity.getClass().getDeclaredMethod(AutoFillConstant.SET_UPDATE_USER, Long.class);

                // 通过反射为对象属性赋值
                setUpdateTime.invoke(entity,now);
                setUpdateUser.invoke(entity,currentId);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
```



#### 1.3.3 步骤三

**在 Mapper 接口的方法上加入 AutoFill 注解**

以 **CategoryMapper** 为例，分别在新增和修改方法添加 @AutoFill() 注解，也需要 **EmployeeMapper** 做相同操作

```java
package com.sky.mapper;

@Mapper
public interface CategoryMapper {
    /**
     * 插入数据
     * @param category
     */
    @Insert("insert into category(type, name, sort, status, create_time, update_time, create_user, update_user)" +
            " VALUES" +
            " (#{type}, #{name}, #{sort}, #{status}, #{createTime}, #{updateTime}, #{createUser}, #{updateUser})")
    @AutoFill(value = OperationType.INSERT)
    void insert(Category category);
    /**
     * 根据 id 修改分类
     * @param category
     */
    @AutoFill(value = OperationType.UPDATE)
    void update(Category category);

}
```

**同时**，将业务层为公共字段赋值的代码注释掉。

1). 将员工管理的新增和编辑方法中的公共字段赋值的代码注释。

2). 将菜品分类管理的新增和修改方法中的公共字段赋值的代码注释。



### 1.4 功能测试

以**新增菜品分类**为例，进行测试

**启动项目和 Nginx**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131137020.png" alt="image-20221121154642757" style="zoom:50%;" /> 

**查看控制台**

通过观察控制台输出的 SQL 来确定公共字段填充是否完成

![image-20221121154841887](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131137903.png)

**查看表**

category 表中数据

![image-20221121155104152](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131137959.png)

其中 create_time，update_time，create_user，update_user 字段都已完成自动填充。

由于使用 admin(id=1) 用户登录进行菜品添加操作，故 create_user，update_user 都为 1。



## 2. 新增菜品

### 2.1 需求分析与设计

#### 2.1.1 产品原型

后台系统中可以管理菜品信息，通过**新增功能**来添加一个新的菜品，在添加菜品时需要选择当前菜品所属的菜品分类，并且需要上传菜品图片。

**新增菜品原型：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131823793.png" alt="image-20221121164131337" style="zoom: 50%;" /> 

当填写完表单信息，点击"保存"按钮后，会提交该表单的数据到服务端，在服务端中需要接受数据，然后将数据保存至数据库中。



**业务规则：**

- 菜品名称必须是唯一的
- 菜品必须属于某个分类下，不能单独存在
- 新增菜品时可以根据情况选择菜品的口味
- 每个菜品必须对应一张图片



#### 2.1.2 接口设计

根据上述原型图先**粗粒度**设计接口，共包含 3 个接口。

**接口设计：**

- 根据类型查询分类（已完成）
- 文件上传
- 新增菜品



接下来**细粒度**分析每个接口，明确每个接口的请求方式、请求路径、传入参数和返回值。

**1. 根据类型查询分类**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131826939.png" alt="image-20221121165033612" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131826656.png" alt="image-20221121165043619" style="zoom:50%;" />

**2. 文件上传**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131826977.png" alt="image-20221121165201319" style="zoom:50%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131826639.png" alt="image-20221121165215634" style="zoom:50%;" />

>   Content-Type: multipart/form-data 是通过浏览器进行文件上传的固定的一种请求头



**3. 新增菜品**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131826265.png" alt="image-20221121165254961" style="zoom: 50%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131826993.png" alt="image-20221121165308394" style="zoom: 50%;" /><img src="D:/Projects/1、黑马程序员Java项目《苍穹外卖》企业级开发实战/讲义/day03/assets/image-20221121165322687.png" alt="image-20221121165322687" style="zoom: 50%;" />



#### 2.1.3 表设计

通过原型图进行分析：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131837002.png" alt="image-20221121165917874" style="zoom:50%;" /> 

新增菜品，其实就是将新增页面录入的菜品信息插入到 dish 表，如果添加了口味做法，还需要向 dish_flavor 表插入数据。所以在新增菜品时，涉及到两个表：

| 表名        | 说明       |
| ----------- | ---------- |
| dish        | 菜品表     |
| dish_flavor | 菜品口味表 |



**1). 菜品表:dish**

| **字段名**  | **数据类型**  | **说明**     | **备注**    |
| ----------- | ------------- | ------------ | ----------- |
| id          | bigint        | 主键         | 自增        |
| name        | varchar(32)   | 菜品名称     | 唯一        |
| category_id | bigint        | 分类id       | 逻辑外键    |
| price       | decimal(10,2) | 菜品价格     |             |
| image       | varchar(255)  | 图片路径     |             |
| description | varchar(255)  | 菜品描述     |             |
| status      | int           | 售卖状态     | 1起售 0停售 |
| create_time | datetime      | 创建时间     |             |
| update_time | datetime      | 最后修改时间 |             |
| create_user | bigint        | 创建人id     |             |
| update_user | bigint        | 最后修改人id |             |

**2). 菜品口味表:dish_flavor**

| **字段名** | **数据类型** | **说明** | **备注** |
| ---------- | ------------ | -------- | -------- |
| id         | bigint       | 主键     | 自增     |
| dish_id    | bigint       | 菜品id   | 逻辑外键 |
| name       | varchar(32)  | 口味名称 |          |
| value      | varchar(255) | 口味值   |          |

:question: 为什么要设置**逻辑外键**，而不是直接在数据库中设置为外键？



### 2.2 代码开发

#### 2.2.1 文件上传实现

因为在新增菜品时，需要上传菜品对应的图片(文件)，包括后绪其它功能也会使用到文件上传，故要实现通用的文件上传接口。

文件上传，是指将本地图片、视频、音频等文件上传到服务器上，可以供其他用户浏览或下载的过程。文件上传在项目中应用非常广泛，我们经常发抖音、发朋友圈都用到了文件上传功能。

实现文件上传服务，需要有存储的支持，那么我们的解决方案将以下几种：

1. 直接将图片保存到服务的硬盘（springmvc 中的文件上传）
    1. 优点：开发便捷，成本低
    2. 缺点：扩容困难
2. 使用分布式文件系统进行存储
    1. 优点：容易实现扩容
    2. 缺点：开发复杂度稍大（有成熟的产品可以使用，比如：FastDFS，MinIO）
3. 使用第三方的存储服务（例如 OSS）
    1. 优点：开发简单，拥有强大功能，免维护
    2. 缺点：付费

在本项目选用阿里云的 OSS 服务进行文件存储。（前面课程已学习过阿里云 OSS，不再赘述）

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604131857504.png" alt="image-20221121174942235" style="zoom:67%;" /> 

**实现步骤：**

**1). 定义 OSS 相关配置**

在 sky-server 模块

application-dev.yml

```yaml
sky:
  alioss:
    endpoint: oss-cn-hangzhou.aliyuncs.com
    access-key-id: XXXXXX
    access-key-secret: XXXXXX
    bucket-name: sky-take-out
```

application.yml

```yaml
spring:
  profiles:
    active: dev  # 设置环境
sky:
  alioss:
    endpoint: ${sky.alioss.endpoint}
    access-key-id: ${sky.alioss.access-key-id}
    access-key-secret: ${sky.alioss.access-key-secret}
    bucket-name: ${sky.alioss.bucket-name}
```



**2). 读取 OSS 配置**

在 sky-common 模块中，已定义

```java
package com.sky.properties;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Component
@ConfigurationProperties(prefix = "sky.alioss")
@Data
public class AliOssProperties {

    private String endpoint;
    private String accessKeyId;
    private String accessKeySecret;
    private String bucketName;

}
```



**3). 生成 OSS 工具类对象**

在 sky-server 模块

```java
package com.sky.config;

import com.sky.properties.AliOssProperties;
import com.sky.utils.AliOssUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.autoconfigure.condition.ConditionalOnMissingBean;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * 配置类，用于创建 AliOssUtil 对象
 */
@Configuration
@Slf4j
public class OssConfiguration {

    @Bean
    @ConditionalOnMissingBean
    public AliOssUtil aliOssUtil(AliOssProperties aliOssProperties){
        log.info("开始创建阿里云文件上传工具类对象：{}",aliOssProperties);
        return new AliOssUtil(aliOssProperties.getEndpoint(),
                aliOssProperties.getAccessKeyId(),
                aliOssProperties.getAccessKeySecret(),
                aliOssProperties.getBucketName());
    }
}
```

其中，AliOssUtil.java 已在 sky-common 模块中定义

```java
package com.sky.utils;

import com.aliyun.oss.ClientException;
import com.aliyun.oss.OSS;
import com.aliyun.oss.OSSClientBuilder;
import com.aliyun.oss.OSSException;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;
import java.io.ByteArrayInputStream;

@Data
@AllArgsConstructor
@Slf4j
public class AliOssUtil {

    private String endpoint;
    private String accessKeyId;
    private String accessKeySecret;
    private String bucketName;

    /**
     * 文件上传
     */
    public String upload(byte[] bytes, String objectName) {

        // 创建 OSSClient 实例
        OSS ossClient = new OSSClientBuilder().build(endpoint, accessKeyId, accessKeySecret);

        try {
            // 创建 PutObject 请求
            ossClient.putObject(bucketName, objectName, new ByteArrayInputStream(bytes));
        } catch (OSSException oe) {
            System.out.println("Caught an OSSException, which means your request made it to OSS, "
                    + "but was rejected with an error response for some reason.");
            System.out.println("Error Message:" + oe.getErrorMessage());
            System.out.println("Error Code:" + oe.getErrorCode());
            System.out.println("Request ID:" + oe.getRequestId());
            System.out.println("Host ID:" + oe.getHostId());
        } catch (ClientException ce) {
            System.out.println("Caught an ClientException, which means the client encountered "
                    + "a serious internal problem while trying to communicate with OSS, "
                    + "such as not being able to access the network.");
            System.out.println("Error Message:" + ce.getMessage());
        } finally {
            if (ossClient != null) {
                ossClient.shutdown();
            }
        }

        //文件访问路径规则 https://BucketName.Endpoint/ObjectName
        StringBuilder stringBuilder = new StringBuilder("https://");
        stringBuilder
                .append(bucketName)
                .append(".")
                .append(endpoint)
                .append("/")
                .append(objectName);

        log.info("文件上传到:{}", stringBuilder.toString());

        return stringBuilder.toString();
    }
}
```



**4). 定义文件上传接口**

在 sky-server 模块中定义接口

```java
package com.sky.controller.admin;

import com.sky.result.Result;
import com.sky.utils.AliOssUtil;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.UUID;

/**
 * 通用接口
 */
@RestController
@RequestMapping("/admin/common")
@Api(tags = "通用接口")
@Slf4j
public class CommonController {

    @Autowired
    private AliOssUtil aliOssUtil;

    /**
     * 文件上传
     */
    @PostMapping("/upload")
    @ApiOperation(value = "文件上传")
    public Result<String> upload(MultipartFile file) {
        log.info("文件上传：{}", file);

        try {
            // 获取原始文件名
            String originalFilename = file.getOriginalFilename();
            // 获取原始文件后缀
            String extension = originalFilename.substring(originalFilename.lastIndexOf("."));
            // 构造新文件名称
            String objectName = UUID.randomUUID().toString() + extension;
            // 获取文件的请求路径
            String filePath = aliOssUtil.upload(file.getBytes(), objectName);
            return Result.success(filePath);
        } catch (IOException e) {
            log.error("文件上传失败：{}", e);
        }

        return null;
    }
}
```



#### 2.2.2 新增菜品实现

**1). 设计 DTO 类**

在 sky-pojo 模块中

```java
package com.sky.dto;

import com.sky.entity.DishFlavor;
import lombok.Data;
import java.io.Serializable;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

@Data
public class DishDTO implements Serializable {

    private Long id;
    //菜品名称
    private String name;
    //菜品分类id
    private Long categoryId;
    //菜品价格
    private BigDecimal price;
    //图片
    private String image;
    //描述信息
    private String description;
    //0 停售 1 起售
    private Integer status;
    //口味
    private List<DishFlavor> flavors = new ArrayList<>();
}
```



**2). Controller 层**

进入到 sky-server 模块

```java
package com.sky.controller.admin;

import com.sky.dto.DishDTO;
import com.sky.dto.DishPageQueryDTO;
import com.sky.entity.Dish;
import com.sky.result.PageResult;
import com.sky.result.Result;
import com.sky.service.DishService;
import com.sky.vo.DishVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import java.util.List;
import java.util.Set;

/**
 * 菜品管理
 */
@RestController
@RequestMapping("/admin/dish")
@Api(tags = "菜品相关接口")
@Slf4j
public class DishController {

    @Autowired
    private DishService dishService;

    /**
     * 新增菜品
     */
    @PostMapping
    @ApiOperation("新增菜品")
    public Result save(@RequestBody DishDTO dishDTO) {
        log.info("新增菜品：{}", dishDTO);
        dishService.saveWithFlavor(dishDTO);//后绪步骤开发
        return Result.success();
    }
}
```



**3). Service 层接口**

```java
package com.sky.service;

import com.sky.dto.DishDTO;
import com.sky.entity.Dish;

public interface DishService {

    /**
     * 新增菜品和对应的口味
     */
    public void saveWithFlavor(DishDTO dishDTO);

}
```



**4). Service 层实现类**

```java
package com.sky.service.impl;

import com.sky.dto.DishDTO;
import com.sky.entity.Dish;
import com.sky.entity.DishFlavor;
import com.sky.mapper.DishFlavorMapper;
import com.sky.mapper.DishMapper;
import com.sky.service.DishService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
@Slf4j
public class DishServiceImpl implements DishService {

    @Autowired
    private DishMapper dishMapper;
    @Autowired
    private DishFlavorMapper dishFlavorMapper;
    /**
     * 新增菜品和对应的口味
     */
    @Transactional  // 事务注解，保证数据的一致性，原子性
    public void saveWithFlavor(DishDTO dishDTO) {

        // 向菜品表插入 1 条数据
        Dish dish = new Dish();
        BeanUtils.copyProperties(dishDTO, dish);
        dishMapper.insert(dish);

        // 获取 insert 生成的主键值
        Long dishId = dish.getId();

        // 向口味表插入 n 条数据
        List<DishFlavor> flavors = dishDTO.getFlavors();
        if (flavors != null && !flavors.isEmpty()) {
            flavors.forEach(flavor -> {
                flavor.setDishId(dishId);
            });
            // Mapper 批量插入
            dishFlavorMapper.insertBatch(flavors);
        }

    }
}
```



**5). Mapper 层**

DishMapper.java 中添加

```java
	/**
     * 插入菜品数据
     *
     * @param dish
     */
    @AutoFill(value = OperationType.INSERT)
    void insert(Dish dish);
```

在 /resources/mapper 中创建 DishMapper.xml

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd" >
<mapper namespace="com.sky.mapper.DishMapper">

    <insert id="insert" useGeneratedKeys="true" keyProperty="id">
        insert into dish (name, category_id, price, image, description, create_time, update_time, create_user,update_user, status)
        values (#{name}, #{categoryId}, #{price}, #{image}, #{description}, #{createTime}, #{updateTime}, #{createUser}, #{updateUser}, #{status})
    </insert>
</mapper>

```

DishFlavorMapper.java

```java
package com.sky.mapper;

import com.sky.entity.DishFlavor;
import java.util.List;

@Mapper
public interface DishFlavorMapper {
    /**
     * 批量插入口味数据
     * @param flavors
     */
    void insertBatch(List<DishFlavor> flavors);

}
```

在 /resources/mapper 中创建 DishFlavorMapper.xml

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd" >
<mapper namespace="com.sky.mapper.DishFlavorMapper">
    <insert id="insertBatch">
        insert into dish_flavor (dish_id, name, value) VALUES
        <foreach collection="flavors" item="df" separator=",">
            (#{df.dishId},#{df.name},#{df.value})
        </foreach>
    </insert>
</mapper>
```



### 2.3 功能测试

进入到菜品管理--->新建菜品

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604132142448.png" alt="image-20221121195440804" style="zoom:50%;" /> 

由于没有实现菜品查询功能，所以保存后，暂且在表中查看添加的数据。

dish 表：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604132142621.png" alt="image-20221121195737692" style="zoom:50%;" /> 

dish_flavor 表：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604132142375.png" alt="image-20221121195902555" style="zoom:50%;" /> 

测试成功。



### 2.4 代码提交

注意，由于在 `application-dev.yml` 文件中明文写入了阿里云 OSS 的相关信息，所以从此开始之后的代码提交中，需要忽略掉 `application-dev.yml` 文件。

（1）执行如下命令取消 git 对 `application-dev.yml` 的追踪

```bash
git rm --cached sky-server/src/main/resources/application-dev.yml
```

（2）在 `.gitignore` 文件中添加如下一行

```txt
sky-server/src/main/resources/application-dev.yml
```

（3）提交新的修改























