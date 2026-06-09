# 苍穹外卖-Day07

## 课程内容

- 缓存菜品
- 缓存套餐
- 添加购物车
- 查看购物车
- 清空购物车



功能实现：**缓存商品**、**购物车**

**效果图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281810529.png" alt="image-20221208175444066" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281810421.png" alt="image-20221208175454987" style="zoom:50%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281810278.png" alt="image-20221208175533325" style="zoom:50%;" />



## 1. 缓存菜品

### 1.1 问题说明

用户端小程序展示的菜品数据都是通过查询数据库获得，如果用户端访问量比较大，数据库访问压力随之增大。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281811008.png" alt="image-20221208180228667" style="zoom:80%;" /> 

**结果：**系统响应慢、用户体验差



### 1.2 实现思路

通过 Redis 来缓存菜品数据，减少数据库查询操作。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281811881.png" alt="image-20221208180818572" style="zoom:80%;" /> 

**缓存逻辑分析：**

- 每个分类下的菜品保存一份缓存数据
- 数据库中菜品数据有变更时清理缓存数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281811599.png" alt="image-20221208181007639" style="zoom:67%;" /> 



### 1.3 代码开发

**修改用户端接口 DishController 的 list 方法，加入缓存处理逻辑：**

```java
	@Autowired
    private RedisTemplate redisTemplate;
	/**
     * 根据分类 id 查询菜品
     */
    @GetMapping("/list")
    @ApiOperation(value = "根据分类 id 查询菜品")
    public Result<List<DishVO>> list(Long categoryId) {
        // 构造 redis 中的 key，跪着：dish_分类id
        String key = "dish_" + categoryId;

        // 查询 redis 中是否存在菜品数据
        List<DishVO> list = (List<DishVO>) redisTemplate.opsForValue().get(key);
        if (list != null && !list.isEmpty()) {
            // 如果存在，直接返回，无需查询数据库
            return Result.success(list);
        }

        Dish dish = new Dish();
        dish.setCategoryId(categoryId);
        // 设置为启售中的菜品
        dish.setStatus(StatusConstant.ENABLE);

        // 如果不存在，查询数据库，将查询到的数据放入 redis 中
        list = dishService.listWithFlavor(dish);
        redisTemplate.opsForValue().set(key, list);

        return Result.success(list);
    }
```

为了保证**数据库**和 **Redis** 中的数据保持一致，修改**管理端接口 DishController** 的相关方法，加入清理缓存逻辑。

需要改造的方法：

- 新增菜品
- 修改菜品
- 批量删除菜品
- 起售、停售菜品

**抽取清理缓存的方法：**

在管理端 DishController 中添加

```java
	@Autowired
    private RedisTemplate redisTemplate;
	/**
     * 清理缓存数据
     */
    private void cleanCache(String pattern){
        Set keys = redisTemplate.keys(pattern);
        redisTemplate.delete(keys);
    }
```

**调用清理缓存的方法，保证数据一致性：**

**1). 新增菜品优化**

```java
	/**
     * 新增菜品
     */
    @PostMapping
    @ApiOperation("新增菜品")
    public Result save(@RequestBody DishDTO dishDTO) {
        log.info("新增菜品：{}", dishDTO);
        dishService.saveWithFlavor(dishDTO);

        //清理缓存数据
        String key = "dish_" + dishDTO.getCategoryId();
        cleanCache(key);
        return Result.success();
    }
```

**2). 菜品批量删除优化**

```java
	/**
     * 菜品批量删除
     */
    @DeleteMapping
    @ApiOperation("菜品批量删除")
    public Result delete(@RequestParam List<Long> ids) {
        log.info("菜品批量删除：{}", ids);
        dishService.deleteBatch(ids);

        //将所有的菜品缓存数据清理掉，所有以dish_开头的key
        cleanCache("dish_*");

        return Result.success();
    }
```

**3). 修改菜品优化**

```java
	/**
     * 修改菜品
     */
    @PutMapping
    @ApiOperation("修改菜品")
    public Result update(@RequestBody DishDTO dishDTO) {
        log.info("修改菜品：{}", dishDTO);
        dishService.updateWithFlavor(dishDTO);

        //将所有的菜品缓存数据清理掉，所有以dish_开头的key
        cleanCache("dish_*");

        return Result.success();
    }
```

**4). 菜品起售停售优化**

```java
	/**
     * 菜品起售停售
     */
    @PostMapping("/status/{status}")
    @ApiOperation("菜品起售停售")
    public Result<String> startOrStop(@PathVariable Integer status, Long id) {
        dishService.startOrStop(status, id);

        //将所有的菜品缓存数据清理掉，所有以dish_开头的key
        cleanCache("dish_*");

        return Result.success();
    }
```



### 1.4 功能测试

可以通过如下方式进行测试：

- 查看控制台 sql
- 前后端联调
- 查看 Redis 中的缓存数据

以**加入缓存**、**菜品修改**两个功能测试为例，通过前后端联调方式，查看控制台 sql 的打印和 Redis 中的缓存数据变化。



**1) 加入缓存**

当第一次查询某个分类的菜品时，会从数据为中进行查询，同时将查询的结果存储到 Redis 中，在后绪的访问，若查询相同分类的菜品时，直接从 Redis 缓存中查询，不再查询数据库。

**登录小程序：**选择蜀味牛蛙 (id = 17)

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281812125.png" alt="image-20221210174656770" style="zoom:50%;" /> 

**查看控制台 sql：**有查询语句，说明是从数据库中进行查询

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281812317.png" alt="image-20221210174839028" style="zoom:50%;" /> 

**查看 Redis 中的缓存数据：**说明缓存成功

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281812512.png" alt="image-20221210175055282" style="zoom:50%;" /> 

**再次访问：**选择蜀味牛蛙 (id = 17)

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281812802.png" alt="image-20221210175438411" style="zoom:50%;" /> 

说明是从 Redis 中查询的数据。



**2) 菜品修改**

当在后台修改菜品数据时，为了保证 Redis 缓存中的数据和数据库中的数据时刻保持一致，当修改后，需要清空对应的缓存数据。用户再次访问时，还是先从数据库中查询，同时再把查询的结果存储到 Redis 中，这样，就能保证缓存和数据库的数据保持一致。

**进入后台：**修改蜀味牛蛙分类下的任意一个菜品，当前分类的菜品数据已在 Redis 中缓存

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281812234.png" alt="image-20221210180624453" style="zoom:50%;" /> 

**修改：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281812499.png" alt="image-20221210180900924" style="zoom:50%;" /> 

**查看 Redis 中的缓存数据：**说明修改时，已清空缓存

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604281812015.png" alt="image-20221210181142408" style="zoom:50%;" /> 

用户再次访问同一个菜品分类时，需要先查询数据库，再把结果同步到 Redis 中，保证了两者数据一致性。

其它功能测试步骤基本一致，自已测试即可。



## 2. 缓存套餐

### 2.1 Spring Cache

#### 2.1.1 介绍

Spring Cache 是一个框架，实现了基于注解的缓存功能，只需要简单地加一个注解，就能实现缓存功能。

Spring Cache 提供了一层抽象，底层可以切换不同的缓存实现，例如：

- EHCache
- Caffeine
- Redis（常用）

**起步依赖：**

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-cache</artifactId>  		            		       	 <version>2.7.3</version> 
</dependency>
```



#### 2.1.2 常用注解

在 SpringCache 中提供了很多缓存操作的注解，常见的是以下的几个：

| **注解**       | **说明**                                                     |
| -------------- | ------------------------------------------------------------ |
| @EnableCaching | 开启缓存注解功能，通常加在**启动类**上                       |
| @Cacheable     | 在方法执行前先查询缓存中是否有数据，如果有数据，则直接返回缓存数据；如果没有缓存数据，调用方法并将方法返回值放到缓存中 |
| @CachePut      | 将方法的返回值**放到缓存中**                                 |
| @CacheEvict    | 将一条或多条数据从缓存中**删除**                             |

在 SpringBoot 项目中，使用缓存技术只需在项目中导入相关缓存技术的依赖包，并在启动类上使用 @EnableCaching 开启缓存支持即可。

例如，使用 Redis 作为缓存技术，只需要导入 Spring data Redis 的 maven 坐标即可。



#### 2.1.3 入门案例

**1). 环境准备**

**导入基础工程：**底层已使用 Redis 缓存实现

基础环境的代码，在我们今天的资料中已经准备好了， 大家只需要将这个工程导入进来就可以了。导入进来的工程结构如下： 

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241847731.png" alt="image-20221210183942040" style="zoom:50%;" /> 

**数据库准备:**

创建名为 spring_cache_demo 数据库，将 springcachedemo.sql 脚本直接导入数据库中。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241959624.png" alt="image-20221210184346304" style="zoom:80%;" /> 

**引导类上加 @EnableCaching:**

```java
package com.itheima;

import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cache.annotation.EnableCaching;

@Slf4j
@SpringBootApplication
@EnableCaching//开启缓存注解功能
public class CacheDemoApplication {
    public static void main(String[] args) {
        SpringApplication.run(CacheDemoApplication.class,args);
        log.info("项目启动成功...");
    }
}
```



**2). @CachePut 注解**

**@CachePut 说明：** 

​	作用: 将方法返回值，放入缓存

​	value: 缓存的名称, 每个缓存名称下面可以有很多 key

​	key: 缓存的 key  ----------> 支持 Spring 的表达式语言 SPEL 语法



**在 save 方法上加注解 @CachePut**

当前 UserController 的 save 方法是用来保存用户信息的，我们希望在该用户信息保存到数据库的同时，也往缓存中缓存一份数据，我们可以在 save 方法上加上注解 @CachePut，用法如下：

```java
	/**
	* CachePut：将方法返回值放入缓存
	* value：缓存的名称，每个缓存名称下面可以有多个key
	* key：缓存的key
	*/
	@PostMapping
    @CachePut(value = "userCache", key = "#user.id")//key的生成：userCache::1
    public User save(@RequestBody User user){
        userMapper.insert(user);
        return user;
    }
```

**说明：**key 的写法如下

`#user.id`：`#user` 指的是方法形参的名称，id 指的是 user 的 id 属性 , 也就是使用 user 的 id 属性作为 key；

`#result.id`：`#result` 代表方法返回值，该表达式代表以返回对象的 id 属性作为 key；

`#p0.id`：`#p0` 指的是方法中的第一个参数，id 指的是第一个参数的 id 属性,也就是使用第一个参数的 id 属性作为 key；

`#a0.id`：`#a0` 指的是方法中的第一个参数，id 指的是第一个参数的 id 属性，也就是使用第一个参数的 id 属性作为 key；

`#root.args[0].idl`：`#root.args[0]` 指的是方法中的第一个参数，id 指的是第一个参数的 id 属性，也就是使用第一个参数的 id 属性作为 key；

**启动服务，通过 swagger 接口文档测试，访问 UserController 的 save() 方法**

因为 id 是自增，所以不需要设置 id 属性

 <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241849868.png" alt="image-20221210191702887" style="zoom:50%;" /> 

**查看 user 表中的数据**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241849555.png" alt="image-20221210192325931" style="zoom: 67%;" /> 

**查看 Redis 中的数据**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241850806.png" alt="image-20221210192418204" style="zoom:50%;" /> 



**3). @Cacheable 注解**

**@Cacheable 说明:**

​	作用: 在方法执行前，spring 先查看缓存中是否有数据，如果有数据，则直接返回缓存数据；若没有数据，调用方法并将方法返回值放到缓存中

​	value: 缓存的名称，每个缓存名称下面可以有多个 key

​	key: 缓存的 key  ----------> 支持 Spring 的表达式语言 SPEL 语法



 **在 getById 上加注解 @Cacheable**

```java
	/**
	* Cacheable：在方法执行前 spring 先查看缓存中是否有数据，如果有数据，则直接返回缓存数据；若没有数据，*调用方法并将方法返回值放到缓存中
	* value：缓存的名称，每个缓存名称下面可以有多个 key
	* key：缓存的 key
	*/
	@GetMapping
    @Cacheable(cacheNames = "userCache",key="#id")
    public User getById(Long id){
        User user = userMapper.getById(id);
        return user;
    }
```

**重启服务，通过 swagger 接口文档测试，访问 UserController 的 getById() 方法**

第一次访问，会请求我们 controller 的方法，查询数据库。后面再查询相同的 id，就直接从 Redis 中查询数据，不用再查询数据库了，就说明缓存生效了。

提前在 redis 中手动删除掉 id=1 的用户数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241851473.png" alt="image-20221210193834150" style="zoom:50%;" /> 

**查看控制台 sql 语句：**说明从数据库查询的用户数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241851454.png" alt="image-20221210193948896" style="zoom: 67%;" /> 

**查看 Redis 中的缓存数据：**说明已成功缓存

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241851846.png" alt="image-20221210194112334" style="zoom:50%;" /> 

再次查询相同 id 的数据时，直接从 redis 中直接获取，不再查询数据库。



**4). @CacheEvict 注解**

**@CacheEvict 说明：** 

​	作用: 清理指定缓存

​	value: 缓存的名称，每个缓存名称下面可以有多个 key

​	key: 缓存的 key  ----------> 支持 Spring 的表达式语言 SPEL 语法



**在 delete 方法上加注解 @CacheEvict**

```java
	@DeleteMapping
    @CacheEvict(cacheNames = "userCache",key = "#id")//删除某个key对应的缓存数据
    public void deleteById(Long id){
        userMapper.deleteById(id);
    }

	@DeleteMapping("/delAll")
    @CacheEvict(cacheNames = "userCache",allEntries = true)//删除userCache下所有的缓存数据
    public void deleteAll(){
        userMapper.deleteAll();
    }
```

**重启服务，通过 swagger 接口文档测试，访问 UserController 的 deleteAll() 方法**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241852908.png" alt="image-20221210195254874" style="zoom:50%;" /> 

**查看 user 表：**数据清空

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241852586.png" alt="image-20221210195332101" style="zoom:80%;" /> 

**查询 Redis 缓存数据**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605241852391.png" alt="image-20221210195500014" style="zoom:50%;" /> 



### 2.2 实现思路

**实现步骤：**

1). 导入 Spring Cache 和 Redis 相关 maven 坐标

2). 在启动类上加入 @EnableCaching 注解，开启缓存注解功能

3). 在用户端接口 SetmealController 的 list 方法上加入 @Cacheable 注解

4). 在管理端接口 SetmealController 的 save、delete、update、startOrStop 等方法上加入 CacheEvict 注解



### 2.3 代码开发

按照上述实现步骤：

**1). 导入 Spring Cache 和 Redis 相关 maven 坐标(已实现)**

```xml
<dependency>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>

<dependency>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-starter-cache</artifactId>
</dependency>
```



**2). 在启动类上加入 @EnableCaching 注解，开启缓存注解功能**

```java
package com.sky;

import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.transaction.annotation.EnableTransactionManagement;

@SpringBootApplication
@EnableTransactionManagement //开启注解方式的事务管理
@Slf4j
@EnableCaching
public class SkyApplication {
    public static void main(String[] args) {
        SpringApplication.run(SkyApplication.class, args);
        log.info("server started");
    }
}
```



**3). 在用户端接口 SetmealController 的 list 方法上加入 @Cacheable 注解**

```java
	/**
     * 条件查询
     *
     * @param categoryId
     * @return
     */
    @GetMapping("/list")
    @ApiOperation("根据分类id查询套餐")
    @Cacheable(cacheNames = "setmealCache",key = "#categoryId") //key: setmealCache::100
    public Result<List<Setmeal>> list(Long categoryId) {
        Setmeal setmeal = new Setmeal();
        setmeal.setCategoryId(categoryId);
        setmeal.setStatus(StatusConstant.ENABLE);

        List<Setmeal> list = setmealService.list(setmeal);
        return Result.success(list);
    }
```



**4). 在管理端接口 SetmealController 的 save、delete、update、startOrStop 等方法上加入 CacheEvict 注解**

```java
	/**
     * 新增套餐
     *
     * @param setmealDTO
     * @return
     */
    @PostMapping
    @ApiOperation("新增套餐")
    @CacheEvict(cacheNames = "setmealCache",key = "#setmealDTO.categoryId")//key: setmealCache::100
    public Result save(@RequestBody SetmealDTO setmealDTO) {
        setmealService.saveWithDish(setmealDTO);
        return Result.success();
    }
	/**
     * 批量删除套餐
     *
     * @param ids
     * @return
     */
    @DeleteMapping
    @ApiOperation("批量删除套餐")
    @CacheEvict(cacheNames = "setmealCache",allEntries = true)
    public Result delete(@RequestParam List<Long> ids) {
        setmealService.deleteBatch(ids);
        return Result.success();
    }
	/**
     * 修改套餐
     *
     * @param setmealDTO
     * @return
     */
    @PutMapping
    @ApiOperation("修改套餐")
    @CacheEvict(cacheNames = "setmealCache",allEntries = true)
    public Result update(@RequestBody SetmealDTO setmealDTO) {
        setmealService.update(setmealDTO);
        return Result.success();
    }

    /**
     * 套餐起售停售
     *
     * @param status
     * @param id
     * @return
     */
    @PostMapping("/status/{status}")
    @ApiOperation("套餐起售停售")
    @CacheEvict(cacheNames = "setmealCache",allEntries = true)
    public Result startOrStop(@PathVariable Integer status, Long id) {
        setmealService.startOrStop(status, id);
        return Result.success();
    }
```



### 2.4 功能测试

通过前后端联调方式来进行测试，同时观察 redis 中缓存的套餐数据。和**缓存菜品**功能测试基本一致，不再赘述。



## 3. 添加购物车

### 3.1 需求分析和设计

#### 3.1.1 产品原型

用户可以将菜品或者套餐添加到购物车。对于菜品来说，如果设置了口味信息，则需要选择规格后才能加入购物车；对于套餐来说，可以直接点击 <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605281838293.png" alt="image-20210813181916235" style="zoom: 67%;" /> 将当前套餐加入购物车。在购物车中可以修改菜品和套餐的数量，也可以清空购物车。

**效果图：**

 <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605281838659.png" alt="image-20221210203822817" style="zoom:50%;" /> 



#### 3.1.2 接口设计

通过上述原型图，设计出对应的添加购物车接口。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605281838220.png" alt="image-20221208184342490" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605281838855.png" alt="image-20221208184354291" style="zoom:50%;" />

**说明：**添加购物车时，有可能添加菜品，也有可能添加套餐。故传入参数要么是菜品 id，要么是套餐 id。



#### 3.1.3 表设计

用户的购物车数据，也是需要保存在数据库中的，购物车对应的数据表为 shopping_cart 表，具体表结构如下：

| **字段名**  | **数据类型**  | **说明**     | **备注** |
| ----------- | ------------- | ------------ | -------- |
| id          | bigint        | 主键         | 自增     |
| name        | varchar(32)   | 商品名称     | 冗余字段 |
| image       | varchar(255)  | 商品图片路径 | 冗余字段 |
| user_id     | bigint        | 用户id       | 逻辑外键 |
| dish_id     | bigint        | 菜品id       | 逻辑外键 |
| setmeal_id  | bigint        | 套餐id       | 逻辑外键 |
| dish_flavor | varchar(50)   | 菜品口味     |          |
| number      | int           | 商品数量     |          |
| amount      | decimal(10,2) | 商品单价     | 冗余字段 |
| create_time | datetime      | 创建时间     |          |

**说明：** 

- 购物车数据是关联用户的，在表结构中，我们需要记录，每一个用户的购物车数据是哪些
- 菜品列表展示出来的既有套餐，又有菜品，如果用户选择的是套餐，就保存套餐 ID(setmeal_id)，如果用户选择的是菜品，就保存菜品 ID(dish_id)
- 对同一个菜品/套餐，如果选择多份不需要添加多条记录，增加数量 number 即可



### 3.2 代码开发

#### 3.2.1 DTO 设计

**根据添加购物车接口的参数设计 DTO：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605281839142.png" alt="image-20221208184938195" style="zoom:50%;" /> 

在 sky-pojo 模块，ShoppingCartDTO.java 已定义

```java
package com.sky.dto;

import lombok.Data;
import java.io.Serializable;

@Data
public class ShoppingCartDTO implements Serializable {

    private Long dishId;
    private Long setmealId;
    private String dishFlavor;
}
```



#### 3.2.2 Controller 层

**根据添加购物车接口创建 ShoppingCartController：**

```java
package com.sky.controller.user;

import com.sky.dto.ShoppingCartDTO;
import com.sky.result.Result;
import com.sky.service.ShoppingCartService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/user/shoppingCart")
@Slf4j
@Api(tags = "C端购物车接口")
public class ShoppingCartController {

    @Autowired
    private ShoppingCartService shoppingCartService;

    /**
     * 添加购物车
     */
    @PostMapping("/add")
    @ApiOperation(value = "添加购物车")
    public Result add(@RequestBody ShoppingCartDTO shoppingCartDTO) {
        log.info("添加购物车：{}", shoppingCartDTO);
        shoppingCartService.addShoppingCart(shoppingCartDTO);
        return Result.success();
    }
}
```



#### 3.2.3 Service 层接口

**创建 ShoppingCartService 接口：**

```java
package com.sky.service;

import com.sky.dto.ShoppingCartDTO;

public interface ShoppingCartService {

    /**
     * 添加购物车
     */
    void addShoppingCart(ShoppingCartDTO shoppingCartDTO);
}
```



#### 3.2.4 Service 层实现类

**创建 ShoppingCartServiceImpl 实现类，并实现 add 方法：**

```java
package com.sky.service.impl;

import com.sky.context.BaseContext;
import com.sky.dto.ShoppingCartDTO;
import com.sky.entity.Dish;
import com.sky.entity.Setmeal;
import com.sky.entity.ShoppingCart;
import com.sky.mapper.DishMapper;
import com.sky.mapper.SetmealMapper;
import com.sky.mapper.ShoppingCartMapper;
import com.sky.service.ShoppingCartService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;

@Service
@Slf4j
public class ShoppingCartServiceImpl implements ShoppingCartService {

    @Autowired
    private ShoppingCartMapper shoppingCartMapper;
    @Autowired
    private DishMapper dishMapper;
    @Autowired
    private SetmealMapper setmealMapper;

    /**
     * 添加购物车
     */
    public void addShoppingCart(ShoppingCartDTO shoppingCartDTO) {
        // 判断当前加入购物车中的商品是否已经存在
        // select * from shopping_cart where user_id = ? and setmeal_id = ?
        // select * from shopping_cart where user_id = ? and dish_id = ? and dish_flavor = ?
        ShoppingCart shoppingCart = new ShoppingCart();
        BeanUtils.copyProperties(shoppingCartDTO, shoppingCart);
        Long userId = BaseContext.getCurrentId();
        shoppingCart.setUserId(userId);

        List<ShoppingCart> list = shoppingCartMapper.list(shoppingCart);

        // 如果已经存在，数量加一
        if (list != null && !list.isEmpty()) {
            ShoppingCart cart = list.get(0);
            cart.setNumber(cart.getNumber() + 1);
            shoppingCartMapper.updateNumberById(cart);
        } else {
            // 如果不存在，插入一条购物车数据
            // 判断添加的是菜品还是套餐
            Long dishId = shoppingCartDTO.getDishId();
            if (dishId != null) {
                // 添加的是菜品
                Dish dish = dishMapper.getById(dishId);
                shoppingCart.setName(dish.getName());
                shoppingCart.setImage(dish.getImage());
                shoppingCart.setAmount((dish.getPrice()));
            } else {
                // 添加的是套餐
                Long setmealId = shoppingCartDTO.getSetmealId();
                Setmeal setmeal = setmealMapper.getById(setmealId);
                shoppingCart.setName(setmeal.getName());
                shoppingCart.setImage(setmeal.getImage());
                shoppingCart.setAmount((setmeal.getPrice()));
            }
            shoppingCart.setNumber(1);
            shoppingCart.setCreateTime(LocalDateTime.now());
            shoppingCartMapper.insert(shoppingCart);
        }
    }
}
```



#### 3.2.5 Mapper 层

**创建 ShoppingCartMapper 接口:**

```java
package com.sky.mapper;

import com.sky.entity.ShoppingCart;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Update;

import java.util.List;

@Mapper
public interface ShoppingCartMapper {

    /**
     * 动态条件查询
     */
    List<ShoppingCart> list(ShoppingCart shoppingCart);;

    @Update("update shopping_cart set number = #{number} where id = #{id}")
    void updateNumberById(ShoppingCart shoppingCart);

    /**
     * 插入购物车数据
     */
    @Insert("insert into shopping_cart (name, image, user_id, dish_id, setmeal_id, dish_flavor, number, amount, create_time) " +
            "values (#{name}, #{image}, #{userId}, #{dishId}, #{setmealId}, #{dishFlavor}, #{number}, #{amount}, #{createTime})")
    void insert(ShoppingCart shoppingCart);
}
```

**创建 ShoppingCartMapper.xml：**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd" >
<mapper namespace="com.sky.mapper.ShoppingCartMapper">
    <select id="list" resultType="com.sky.entity.ShoppingCart">
        select * from shopping_cart
        <where>
            <if test="userId != null">and user_id = #{userId}</if>
            <if test="setmealId != null">and setmeal_id = #{setmealId}</if>
            <if test="dishId != null">and dish_id = #{dishId}</if>
            <if test="dishFlavor != null">and dish_flavor = #{dishFlavor}</if>
        </where>
    </select>
</mapper>
```



### 3.3 功能测试

进入小程序，添加菜品

<img src="D:/Projects/1、黑马程序员Java项目《苍穹外卖》企业级开发实战/讲义/day07/assets/image-20221210210338094.png" alt="image-20221210210338094" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605282230133.png" alt="image-20221210210409954" style="zoom:50%;" />

加入购物车，查询数据库

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605282230280.png" alt="image-20221210210643308" style="zoom:80%;" /> 

因为现在没有实现查看购物车功能，所以只能在表中进行查看。

在前后联调时，后台可通断点方式启动，查看运行的每一步。



## 4. 查看购物车

### 4.1 需求分析和设计

#### 4.1.1 产品原型

当用户添加完菜品和套餐后，可进入到购物车中，查看购物中的菜品和套餐。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292149273.png" alt="image-20221208190038058" style="zoom:50%;" /> 



#### 4.1.2 接口设计

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292149490.png" alt="image-20221208190052467" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292149944.png" alt="image-20221208190102904" style="zoom:50%;" />



### 4.2 代码开发

#### 4.2.1 Controller层

**在ShoppingCartController中创建查看购物车的方法：**

```java
    /**
     * 查看购物车
     */
    @GetMapping("/list")
    @ApiOperation(value = "查看购物车")
    public Result<List<ShoppingCart>> list() {
        log.info("查看购物车");
        List<ShoppingCart> list = shoppingCartService.showShoppingCart();
        return Result.success(list);
    }
```



#### 4.2.2 Service层接口

**在ShoppingCartService接口中声明查看购物车的方法：**

```java
    /**
     * 查看购物车
     */
    List<ShoppingCart> showShoppingCart();
```



#### 4.2.3 Service层实现类

**在ShoppingCartServiceImpl中实现查看购物车的方法：**

```java
    /**
     * 查看购物车
     */
    public List<ShoppingCart> showShoppingCart() {
        Long userId = BaseContext.getCurrentId();
        ShoppingCart shoppingCart = ShoppingCart.builder().userId(userId).build();
        List<ShoppingCart> list = shoppingCartMapper.list(shoppingCart);
        return list;
    }
```



### 4.3 功能测试

当进入小程序时，就会发起查看购物车的请求

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292159052.png" alt="image-20221210213347557" style="zoom:50%;" /> 

点击购物车图标

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292159316.png" alt="image-20221210213438878" style="zoom:50%;" /> 

测试成功。



## 5. 清空购物车

### 5.1 需求分析和设计

#### 5.1.1 产品原型

当点击清空按钮时，会把购物车中的数据全部清空。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292201698.png" alt="image-20221210213703715" style="zoom:50%;" /> 



#### 5.1.2 接口设计

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292201893.png" alt="image-20221208191606894" style="zoom:50%;" /> 



### 5.2 代码开发

#### 5.2.1 Controller层

**在ShoppingCartController中创建清空购物车的方法：**

```java
    /**
     * 清空购物车
     */
    @DeleteMapping("/clean")
    @ApiOperation(value = "清空购物车")
    public Result clean() {
        shoppingCartService.cleanShoppingCart();
        return Result.success();
    }
```



#### 5.2.2 Service层接口

**在ShoppingCartService接口中声明清空购物车的方法：**

```java
    /**
     * 清空购物车
     */
    void cleanShoppingCart();
```



#### 5.2.3 Service层实现类

**在ShoppingCartServiceImpl中实现清空购物车的方法：**

```java
    /**
     * 清空购物车
     */
    public void cleanShoppingCart() {
        Long userId = BaseContext.getCurrentId();
        shoppingCartMapper.deleteByUserId(userId);
    }
```



#### 5.2.4 Mapper层

**在ShoppingCartMapper接口中创建删除购物车数据的方法：**

```java
    /**
     * 根据 userId 删除数据
     */
    @Delete("delete from shopping_cart where user_id = #{userId}")
    void deleteByUserId(Long userId);
```



### 5.3 功能测试

进入到购物车页面

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292208661.png" alt="image-20221210214710863" style="zoom:50%;" /> 

点击清空

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292209080.png" alt="image-20221210214914092" style="zoom:50%;" /> 

查看数据库中的数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202605292209004.png" alt="image-20221210214950261" style="zoom:80%;" /> 

说明当前用户的购物车数据已全部删除。



## 6. 删除购物车中一个商品

### 产品原型

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606071206878.png" alt="image-20220613153609795" style="zoom:67%;" />

### 接口设计

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606071206544.png" alt="image-20220610152629105" style="zoom: 67%;" />

### 数据模型

shopping_cart表：

![image-20220610151810308](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606071207741.png)

### 代码开发

`ShoppingCartController.java`

```java
    /**
     * 删除购物车中一个商品
     */
    @PostMapping("/sub")
    @ApiOperation(value = "删除购物车中一个商品")
    public Result sub(@RequestBody ShoppingCartDTO shoppingCartDTO) {
        log.info("删除购物车中一个商品：{}", shoppingCartDTO);
        shoppingCartService.subShoppingCart(shoppingCartDTO);
        return Result.success();
    }
```

`ShoppingCartService.java`

```java
    /**
     * 删除购物车中一个商品
     */
    void subShoppingCart(ShoppingCartDTO shoppingCartDTO);
```

`ShoppingCartServiceImpl.java`

```java
    /**
     * 删除购物车中一个商品
     */
    public void subShoppingCart(ShoppingCartDTO shoppingCartDTO) {
        // 构建购物车对象
        ShoppingCart shoppingCart = new ShoppingCart();
        BeanUtils.copyProperties(shoppingCartDTO, shoppingCart);
        shoppingCart.setUserId(BaseContext.getCurrentId());

        // 查询当前登录用户的购物车数据
        List<ShoppingCart> list = shoppingCartMapper.list(shoppingCart);
        if (list != null && !list.isEmpty()) {
            ShoppingCart cart = list.get(0);  // 只读
            shoppingCart.setId(cart.getId());

            Integer number = cart.getNumber();
            if (number == 1) {
                // 如果商品在购物车中的数量为 1，则直接删除该条记录
                shoppingCartMapper.deleteById(shoppingCart.getId());
            } else {
                // 如果商品在购物车中的数量大于 1，则数量减 1
                shoppingCart.setNumber(number - 1);
                shoppingCartMapper.updateNumberById(shoppingCart);
            }
        }
    }
```

`ShoppingCartMapper.java`

```java
    /**
     * 根据 id 删除购物车数据
     */
    @Delete("delete from shopping_cart where id = #{id}")
    void deleteById(Long id);
```

### 功能测试

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606071213700.png" alt="image-20260607121344425" style="zoom: 50%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606071214548.png" alt="image-20260607121401962" style="zoom:50%;" /><img src="C:\Users\Amonologue\AppData\Roaming\Typora\typora-user-images\image-20260607121420728.png" alt="image-20260607121420728" style="zoom:50%;" />
