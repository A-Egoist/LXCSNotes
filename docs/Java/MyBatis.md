# MyBatis

## 入门程序

MyBatis 官网：https://mybatis.org/mybatis-3/zh_CN/index.html

![image-20251011200509936](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112005911.png)

![image-20251011200142632](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112001479.png)

![image-20251011200752210](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112007099.png)

设置 `application.properties` 的字符集为 `UTF-8`：

![image-20251011201048346](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112010336.png)



### 辅助配置-配置 SQL 提示

![image-20251011213531944](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112135000.png)

![image-20251011213601900](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112136883.png)



### 辅助配置-配置 MyBatis 的日志输出

![image-20251011213738295](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112137254.png)



## JDBC VS MyBatis

![image-20251011214523098](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112145977.png)



## 数据库连接池

![image-20251011215041186](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112150037.png)

![image-20251011215340032](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112153958.png)

![image-20251011215428117](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112154368.png)



## 增删改查操作

### 删除用户

![image-20251011215853777](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112158122.png)

![image-20251011220131309](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112201316.png)



### 新增用户

![image-20251011220521033](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112205990.png)



### 修改用户

![image-20251011220625072](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112206980.png)



### 查询用户

![image-20251011221528285](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112215221.png)

:bulb: ​`@Param` 注解的使用场景：

*   如果接口方法形参中，需要传递多个参数，需要通过 `@Param` 注解为参数起名字；
*   在基于 SpringBoot 官方骨架创建的 SpringBoot 项目中，该注解可以省略；



## XML 映射配置

![image-20251011221938175](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112219143.png)



![image-20251011222227529](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112222396.png)

![image-20251011222849370](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510112228314.png)

