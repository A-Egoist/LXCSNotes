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





























