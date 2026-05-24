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





