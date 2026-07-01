# Redis 基础

>   Redis --> 键值数据库 --> NoSQL --> 非关系型数据库
>
>   Mysql --> 关系型数据库



## Redis 安装

在 WSL2 安装 Redis，修改设置并运行

```bash
# 安装
sudo apt install redis-server -y
# 修改配置
sudo vim /etc/redis/redis.conf
```

修改三处：

1.  `supervised no` → `supervised systemd`
2.  `bind 127.0.0.1` 注释掉（前面加 #），下一行增加 `bind 0.0.0.0`
3.  添加密码：`requirepass 123456`（自定义）

```bash
# 重启服务
sudo service redis-server restart
# 开机启动
sudo systemctl enable redis-server
```

测试联通

```bash
redis-cli
AUTH 123456
ping # 返回PONG即成功
```



## Redis-CLI 常用命令

*   KEYS: 不建议在生产环境中使用
*   DEL: 删除 key
*   EXISTS: 判断 key 是否存在
*   EXPIRE: 给一个 key 设置有效期，有效期到期时该 key 会被自动删除
*   TTL: 查看一个 key 的剩余有效期

通过 `help [command]` 查看一个命令的具体用法



### String 类型



### Hash 类型



### List 类型



### Set 类型



### SortedSet 类型

 



## Redis 客户端

常用的两种客户端：

1.   Jedis
2.   SpringDataRedis



## Jedis





## Spring Data Redis

SpringData 是 Spring 中数据操作的模块，包括对各种数据库的集成，其中对 Redis 的集成模块就叫做 SpringDataRedis，官网地址：https://spring.io/projects/spring-data-redis

![image-20260617180803569](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606171808879.png)



SpringBoot 已经提供了对 SpringDataRedis 的支持，使用非常简单：

1.   引入依赖

     ```xml
     <dependency>
         <groupId>org.springframework.boot</groupId>
         <artifactId>spring-boot-starter-data-redis</artifactId>
     </dependency>
     ```

     

2.   配置文件

     ```yaml
     spring:
       profiles:
         active: dev
       data:
         redis:
           host: ${spring.data.redis.password}
           port: ${spring.data.redis.password}
           password: ${spring.data.redis.password}
           lettuce:
             pool:
               enabled: true
               max-active: 8
               max-idle: 8
               min-idle: 0
               max-wait: 1000ms
     ```

     

3.   注入 RedisTemplate

     ```java
     @Autowired
     private RedisTemplate redisTemplate;
     ```

     

4.   编写测试

     ```java
     @SpringBootTest
     class RedisDemoApplicationTests {
     
         @Autowired
         private RedisTemplate redisTemplate;
     
         @Test
         void testString() {
             // 插入一条 String 类型数据
             redisTemplate.opsForValue().set("name", "amonologue");
             // 读取一条 String 类型数据
             Object name = redisTemplate.opsForValue().get("name");
             System.out.println("name = " + name);
         }
     }
     ```





### 自定义 Redis Serializer

:warning: 使用 RedisTemplate 操作 Redis 的时候，存入的数据会被默认序列化器（JDK 序列化，JdkSerializationRedisSerializer）处理。

![image-20260617205825551](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606172058634.png)

想要所见即所得，需要改变序列化方式。

RedisTemplate 的序列化器 Serializer 的几种实现

![image-20260617210247241](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606172102309.png)

一般使用 StringRedisSerializer 和 GenericJackson2JsonRedisSerializer



#### 使用 StringRedisSerializer 的情况

>   :warning: 无法自动实现序列化和反序列化，需要手动完成对象的序列化和反序列化

只处理**字符串**，底层直接 `String.getBytes(StandardCharsets.UTF_8)`，无复杂转换。

-   特点：
    -   只支持 String 类型，key/value 必须是字符串
    -   Redis 中存储明文，客户端直接可读，无乱码
    -   性能极高，无反射、无 JSON 解析开销
-   限制：**不能直接序列化 Java 对象**，对象需要手动转 JSON 字符串存入
-   依赖：无额外第三方包



#### 使用 GenericJackson2JsonRedisSerializer 的情况

:warning:（通用 JSON 序列化，项目主流）

通用 JSON 序列化，**自动识别任意 POJO 类型**，无需指定实体 Class。

序列化时会额外存入 `@class` 字段记录对象全类名，反序列化自动实例化对应实体。

-   优点：
    1.  任意 Java 对象直接序列化，统一一套序列化器适配所有 POJO
    2.  Redis 存储标准 JSON 字符串，可视化友好
    3.  支持自定义 ObjectMapper（日期格式化、忽略未知字段、枚举转换等）
-   缺点：
    1.  序列化 JSON 多携带 `@class` 字段，少量冗余
    
        >   为了在反序列化的时候知道对象的类型，JSON 序列化器会将类的 Class 类型写入 json 结果中，存入 Redis，会带来额外的内存开销。
    2.  需要 jackson-databind 依赖
-   适用：绝大多数业务场景，缓存 POJO、Map、List 等复杂对象



#### 自定义序列化的实现方式

![image-20260617232621781](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606172326690.png)

:warning: 注意 SpringBoot 版本，SpringBoot 4.x 不支持以上操作，需要按照如下方式设置：

```java
@Configuration
public class RedisConfig {

    @Bean
    public RedisTemplate<String, Object> redisTemplate(RedisConnectionFactory redisConnectionFactory) {
        // 创建 RedisTemplate 对象
        RedisTemplate<String, Object> template = new RedisTemplate();
        // 设置连接工厂
        template.setConnectionFactory(redisConnectionFactory);
        // 设置 Key 的序列化
        template.setKeySerializer(RedisSerializer.string());
        template.setHashKeySerializer(RedisSerializer.string());
        // 设置 Value 的序列化
        GenericJacksonJsonRedisSerializer serializer = GenericJacksonJsonRedisSerializer.builder()
                        .enableUnsafeDefaultTyping().build();
        template.setValueSerializer(serializer);
        template.setHashValueSerializer(serializer);
        // 返回
        return template;
    }
}
```



### 手动实现序列化和反序列化

使用 StringRedisTemplate，并且手动实现序列化和反序列化。

```java
package com.egoist.redisdemo;

import com.egoist.redisdemo.redis.config.redis.pojo.User;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.core.StringRedisTemplate;
import tools.jackson.databind.ObjectMapper;

@SpringBootTest
class RedisStringTests {

    @Autowired
    private StringRedisTemplate stringRedisTemplate;

    @Test
    void testString() {
        // 插入一条 String 类型数据
        stringRedisTemplate.opsForValue().set("name", "Zhang");
        // 读取一条 String 类型数据
        Object name = stringRedisTemplate.opsForValue().get("name");
        System.out.println("name = " + name);
    }

    private static final ObjectMapper mapper = new ObjectMapper();

    @Test
    void testSaveUser() {
        // 创建对象
        User user = new User("egoist", 21);
        // 手动序列化
        String json = mapper.writeValueAsString(user);
        // 写入数据
        stringRedisTemplate.opsForValue().set("user:100", json);
        // 获取数据
        String jsonUser = stringRedisTemplate.opsForValue().get("user:100");
        // 手动反序列化
        User userGet = mapper.readValue(jsonUser, User.class);
        System.out.println("user = " + userGet);
    }
}
```



### 两种实践方案

方案一：

1.   自定义 RedisTemplate
2.   修改 RedisTemplate 的序列化器为 GenericJackson2JsonRedisSerializer

方案二：

1.   使用 StringRedisTemplate
2.   写入 Redis 时，手动把对象序列化为 JSON
3.   读取 Redis 时，手动把读取到的 JSON 反序列化为对象



## 参考资料

[1] [day10-Redis面试篇](https://my.feishu.cn/wiki/Jck7w4GBSia4sukQn1vc9s3anMf)

[2] [【黑马程序员Redis入门到实战教程，深度透析redis底层原理+redis分布式锁+企业解决方案+黑马点评实战项目】](https://www.bilibili.com/video/BV1cr4y1671t/?p=21&share_source=copy_web&vd_source=b5ed364998fc1b958c57abd6dbda38e3)