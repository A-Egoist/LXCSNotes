# 苍穹外卖-Day04

## 实战目标

完成套餐管理模块所有业务功能，包括：

- 新增套餐
- 套餐分页查询
- 删除套餐
- 修改套餐
- 起售停售套餐



要求：

1. 根据产品原型进行需求分析，分析出业务规则
2. 设计接口
3. 梳理表之间的关系（分类表、菜品表、套餐表、口味表、套餐菜品关系表）
4. 根据接口设计进行代码实现
5. 分别通过 swagger 接口文档和前后端联调进行功能测试



## 1. 新增套餐

### 1.1 需求分析和设计

产品原型：

![image-20221018135930842](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604151146143.png)

![image-20260415114709580](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604151147842.png)

业务规则：

- 套餐名称唯一
- 套餐必须属于某个分类
- 套餐必须包含菜品
- 名称、分类、价格、图片为必填项
- 添加菜品窗口需要根据分类类型来展示菜品
- 新增的套餐默认为停售状态

接口设计（共涉及到4个接口）：

- 根据类型查询分类（已完成）
- 根据分类 id 查询菜品
- 图片上传（已完成）
- 新增套餐



### 1.2 根据分类 id 查询菜品

在”新增套餐“功能页面，需要通过“添加菜品”功能选择菜品，所以需要先实现一个根据菜品分类查询所有菜品信息的功能，需要保证查询到的菜品都为启售状态。

#### 接口信息

![image-20260415115456746](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604151154973.png)

#### 代码实现

`DishController.java`

```java
    /**
     * 根据分类 id 查询菜品
     */
    @GetMapping("/list")
    public Result<List<Dish>> list(Long categoryId) {
        log.info("根据分类 id 查询菜品：{}", categoryId);
        List<Dish> dishes = dishService.list(categoryId);
        return Result.success(dishes);
    }
```

`DishService.java`

```java
    /**
     * 根据分类 id 查询菜品
     */
    List<Dish> list(Long categoryId);
```

`DishServiceImpl.java`

```java
    /**
     * 根据分类 id 查询菜品
     */
    public List<Dish> list(Long categoryId) {
        // 根据分类 id 查询在售的菜品
        Dish dish = Dish.builder().categoryId(categoryId).status(StatusConstant.ENABLE).build();
        return dishMapper.list(dish);
    }
```

`DishMapper.java`

```java
    /**
     * 根据分类 id 查询在售菜品
     */
    List<Dish> list(Dish dish);
```

`DishMapper.xml`

```xml
    <select id="list" resultType="com.sky.entity.Dish">
        select * from dish
        <where>
            <if test="name != null">and name like concat('%', #{name}, '%')</if>
            <if test="categoryId != null">and category_id = #{categoryId}</if>
            <if test="status != null">and status = #{status}</if>
        </where>
        order by create_time desc
    </select>
```



### 1.3 新增套餐

#### 接口信息

![image-20260415124213046](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604151242963.png)

在 Controller 中使用 SetmealDTO 接收参数，SetmealDTO 中包含 Setmeal 和 setmealDishes 的信息，所以需要修改数据库中的两个表格（`setmeal` 和 `setmeal_dish`）。首先需要从 setmealDTO 中获取 setmeal 的信息，插入到 `setmeal` 表中。然后从 setmealDTO 中获取 setmealDishes 数组，并且设置数组中的每一个 setmealDish 的 setmealId，再将完整的 setmealDishes 批量插入到 `setmeal_dish` 表中。

在这个过程中，setmealId 需要通过**主键回显**获取。

#### 代码实现

`SetmealController.java`

```java
package com.sky.controller.admin;

import com.sky.dto.SetmealDTO;
import com.sky.result.Result;
import com.sky.service.SetmealService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

/**
 * 套餐管理
 */
@RestController
@RequestMapping("/admin/setmeal")
@Slf4j
@Api("套餐相关接口")
public class SetmealController {

    @Autowired
    private SetmealService setmealService;

    /**
     * 新增套餐
     */
    @PostMapping
    @ApiOperation(value = "新增套餐")
    public Result addSetmeal(@RequestBody SetmealDTO setmealDTO) {
        log.info("新增套餐：{}", setmealDTO);
        setmealService.addSetmeal(setmealDTO);
        return Result.success();
    }
}
```

`SetmealService.java`

```java
package com.sky.service;

import com.sky.dto.SetmealDTO;

public interface SetmealService {
    /**
     * 新增套餐
     */
    void addSetmeal(SetmealDTO setmealDTO);
}
```

`SetmealServiceImpl.java`

```java
package com.sky.service.impl;

import com.sky.dto.SetmealDTO;
import com.sky.entity.Setmeal;
import com.sky.entity.SetmealDish;
import com.sky.mapper.SetmealDishMapper;
import com.sky.mapper.SetmealMapper;
import com.sky.service.SetmealService;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class SetmealServiceImpl implements SetmealService {

    @Autowired
    private SetmealMapper setmealMapper;
    @Autowired
    private SetmealDishMapper setmealDishMapper;

    /**
     * 新增套餐
     */
    @Transactional
    public void addSetmeal(SetmealDTO setmealDTO) {
        // 向 setmeal 表中增加套餐
        Setmeal setmeal = new Setmeal();
        BeanUtils.copyProperties(setmealDTO, setmeal);
        setmealMapper.insert(setmeal);  // 需要获取插入后的 id

        // 获取 insert 生成的主键值
        Long setmealId = setmeal.getId();

        // 增加 setmeal_dish 表中增加套餐中的菜品信息
        List<SetmealDish> setmealDishes = setmealDTO.getSetmealDishes();
        if (setmealDishes != null && !setmealDishes.isEmpty()) {
            setmealDishes.forEach(setmealDish -> {
                setmealDish.setSetmealId(setmealId);
            });
            // 批量插入
            setmealDishMapper.insertBatch(setmealDishes);
        }
    }
}
```

`SetmealMapper.java`

```java
    /**
     * 插入套餐数据
     */
    @AutoFill(value = OperationType.INSERT)
    void insert(Setmeal setmeal);
```

`SetmealMapper.xml`

```xml
    <insert id="insert" useGeneratedKeys="true" keyProperty="id">
        insert into setmeal (category_id, name, price, status, description, image, create_time, update_time, create_user, update_user)
        values (#{categoryId}, #{name}, #{price}, #{status}, #{description}, #{image}, #{createTime}, #{updateTime}, #{createUser}, #{updateUser})
    </insert>
```

:warning: 需要设置**主键回显**

`SetmealDishMapper.java`

```java
    /**
     * 批量插入套餐菜品数据
     */
    void insertBatch(List<SetmealDish> setmealDishes);
```

`SetmealDishMapper.xml`

```xml
    <insert id="insertBatch">
        insert into setmeal_dish (setmeal_id, dish_id, name, price, copies) values
        <foreach collection="setmealDishes" item="setmealDish" separator=",">
            (#{setmealDish.setmealId}, #{setmealDish.dishId}, #{setmealDish.name}, #{setmealDish.price}, #{setmealDish.copies})
        </foreach>
    </insert>
```



## 2. 套餐分页查询

这个功能和菜品管理类似，按照相同的方式实现就行。

Controller 接收参数使用 `SetmealPageQueryDTO`，Mapper 的返回结果使用 `Page<SetmealVO>` 泛型。

`SetmealController.java`

```java
    /**
     * 套餐分页查询
     */
    @GetMapping("/page")
    @ApiOperation(value = "套餐分页查询")
    public Result<PageResult> page(SetmealPageQueryDTO setmealPageQueryDTO) {
        log.info("套餐分页查询：{}", setmealPageQueryDTO);
        PageResult pageResult = setmealService.pageQuery(setmealPageQueryDTO);
        return Result.success(pageResult);
    }
```

`SetmealService.java`

```java
    /**
     * 套餐分页查询
     */
    PageResult pageQuery(SetmealPageQueryDTO setmealPageQueryDTO);
```

`SetmealServiceImpl.java`

```java
    /**
     * 套餐分页查询
     */
    public PageResult pageQuery(SetmealPageQueryDTO setmealPageQueryDTO) {
        PageHelper.startPage(setmealPageQueryDTO.getPage(), setmealPageQueryDTO.getPageSize());
        Page<SetmealVO> page = setmealMapper.pageQuery(setmealPageQueryDTO);
        return new PageResult(page.getTotal(), page.getResult());
    }
```

`SetmealMapper.java`

```java
    /**
     * 套餐分页查询
     */
    Page<SetmealVO> pageQuery(SetmealPageQueryDTO setmealPageQueryDTO);
```

`SetmealMapper.xml`

```xml
    <select id="pageQuery" resultType="com.sky.vo.SetmealVO">
        select s.*, c.name as category_name from setmeal s left outer join category c on s.category_id = c.id
        <where>
            <if test="name != null">and s.name like concat('%', #{name}, '%')</if>
            <if test="categoryId != null">and s.category_id = #{categoryId}</if>
            <if test="status != null">and s.status = #{status}</if>
        </where>
        order by s.create_time desc
    </select>
```



## 3. 删除套餐

实际上是实现批量删除套餐，将删除单个套餐视为批量删除套餐的特殊形式。

所以需要明确哪些情况下不能够删除套餐：启售的套餐不能够删除。



`SetmealController.java`

```java
    /**
     * 批量删除套餐
     */
    @DeleteMapping
    @ApiOperation(value = "批量删除套餐")
    public Result deleteBatch(@RequestParam List<Long> ids) {
        log.info("批量删除套餐：{}", ids);
        setmealService.deleteBatch(ids);
        return Result.success();
    }
```

:question: 为什么可以使用 `(@RequestParam List<Long> ids)` 来接收 String 类型且用 `,` 分隔的 ids？实现原理是什么？在常规的方式应该是使用 `(String ids)` 来接收 Query 参数，然后再手动分隔得到 `List<Long> ids`。

这是因为 `Spring MVC` 内置了 Converter（转换器），可以实现这种自动转换。

`SetmealService.java`

```java
    /**
     * 批量删除套餐
     */
    void deleteBatch(List<Long> ids);
```

`SetmealServiceImpl.java`

```java
    /**
     * 批量删除套餐
     */
    @Transactional
    public void deleteBatch(List<Long> ids) {
        // 先检查所有需要删除的套餐中，是否存在启售的套餐，如果存在，则都不能删除
        for (Long id : ids) {
            Setmeal setmeal = setmealMapper.getById(id);
            if (setmeal.getStatus() == StatusConstant.ENABLE) {
                throw new DeletionNotAllowedException(MessageConstant.SETMEAL_ON_SALE);
            }
        }

        // 批量删除 setmeal 表中的套餐数据
        setmealMapper.deleteByIds(ids);

        // 批量删除 setmeal_dish 表中的套餐菜品关系数据
        setmealDishMapper.deleteByIds(ids);
    }
```

`SetmealMapper.java`

```java
    /**
     * 根据 id 查询套餐
     */
    @Select("select * from setmeal where id = #{id}")
    Setmeal getById(Long id);

    /**
     * 根据 id 批量删除套餐
     */
    void deleteByIds(List<Long> ids);
```

`SetmealMapper.xml`

```java
    <delete id="deleteByIds">
        delete from setmeal where id in
        <foreach collection="ids" item="id" separator="," open="(" close=")">
            #{id}
        </foreach>
    </delete>
```

`SetmealDishMapper.java`

```java
    /**
     * 根据 id 批量删除套餐菜品关系数据
     */
    void deleteByIds(List<Long> setmealIds);
```

`SetmealDishMapper.xml`

```java
    <delete id="deleteByIds">
        delete from setmeal_dish where setmeal_id in
        <foreach collection="setmealIds" item="setmealId" separator="," open="(" close=")">
            #{setmealId}
        </foreach>
    </delete>
```



## 4. 修改套餐

修改套餐要实现两个功能：

1.   套餐信息的回显，即根据套餐 id 查询套餐信息
2.   修改后套餐数据的保存

### 根据套餐  id 查询套餐信息



`SetmealController.java`

```java
    /**
     * 根据 id 查询套餐
     */
    @GetMapping("/{id}")
    @ApiOperation(value = "根据 id 查询套餐")
    public Result<SetmealVO> queryById(@PathVariable Long id) {
        log.info("根据 id 查询套餐：{}", id);
        SetmealVO setmealVO = setmealService.queryByIdWithDish(id);
        return Result.success(setmealVO);
    }
```

`SetmealService.java`

```java
    /**
     * 根据 id 查询套餐和菜品
     */
    SetmealVO queryByIdWithDish(Long id);
```

`SetmealServiceImpl.java`

```java
    /**
     * 根据 id 查询套餐和菜品
     */
    public SetmealVO queryByIdWithDish(Long id) {
        // 根据套餐 id 查询套餐数据
        Setmeal setmeal = setmealMapper.getById(id);

        // 根据套餐 id 查询套餐菜品关系数据
        List<SetmealDish> setmealDishes = setmealDishMapper.getSetmealDishesById(id);

        // 将数据封装到 VO
        SetmealVO setmealVO = new SetmealVO();
        BeanUtils.copyProperties(setmeal, setmealVO);
        setmealVO.setSetmealDishes(setmealDishes);

        return setmealVO;
    }
```

`SetmealMapper.java`

```java
    /**
     * 根据套餐 id 查询套餐数据
     */
    @Select("select * from setmeal where id = #{id}")
    Setmeal getById(Long id);
```

`SetmealDishMapper.java`

```java
    /**
     * 根据套餐 id 查询套餐菜品关系数据
     */
    @Select("select * from setmeal_dish where setmeal_id = #{setmealId}")
    List<SetmealDish> getSetmealDishesById(Long setmealId);
```



### 套餐数据保存

套餐数据的修改分为三步：

1.   修改套餐的基本数据，需要修改 `setmeal` 表
2.   删除与套餐与菜品的关系数据，需要修改 `setmeal_dish` 表
3.   重新插入套餐与菜品的关系数据，需要修改 `setmeal_dish` 表

`SetmealController.java`

```java
    /**
     * 修改套餐
     */
    @PutMapping
    @ApiOperation(value = "修改套餐")
    public Result update(@RequestBody SetmealDTO setmealDTO) {
        log.info("修改套餐：{}", setmealDTO);
        setmealService.update(setmealDTO);
        return Result.success();
    }
```

`SetmealService.java`

```java
    /**
     * 修改套餐
     */
    void update(SetmealDTO setmealDTO);
```

`SetmealServiceImpl.java`

```java
    /**
     * 修改套餐
     */
    @Transactional
    public void update(SetmealDTO setmealDTO) {
        // 修改套餐基本数据
        Setmeal setmeal = new Setmeal();
        BeanUtils.copyProperties(setmealDTO, setmeal);
        setmealMapper.update(setmeal);

        Long setmealId = setmealDTO.getId();

        // 修改套餐和菜品的关系数据，先删除旧的套餐和菜品的关系数据，然后新增套餐和菜品的关系数据
        setmealDishMapper.deleteById(setmealId);
        List<SetmealDish> setmealDishes = setmealDTO.getSetmealDishes();
        if (setmealDishes != null && !setmealDishes.isEmpty()) {
            setmealDishes.forEach(setmealDish -> {
                setmealDish.setSetmealId(setmealId);
            });
            // 向 setmeal_dish 表中插入 n 条套餐和菜品的关系数据
            setmealDishMapper.insertBatch(setmealDishes);
        }
    }
```

`SetmealMapper.java`

```java
    /**
     * 更新套餐数据
     */
    @AutoFill(value = OperationType.UPDATE)
    void update(Setmeal setmeal);
```

`SetmealMapper.xml`

```xml
    <update id="update">
        update setmeal
        <set>
            <if test="categoryId != null">category_id = #{categoryId},</if>
            <if test="name != null">name = #{name},</if>
            <if test="price != null">price = #{price},</if>
            <if test="status != null">status = #{status},</if>
            <if test="description != null">description = #{description},</if>
            <if test="image != null">image = #{image},</if>
            <if test="updateTime != null">update_time = #{updateTime},</if>
            <if test="updateUser != null">update_user = #{updateUser},</if>
        </set>
        where id = #{id}
    </update>
```

`SetmealDishMapper.java`

```java
    /**
     * 根据 id 删除套餐菜品关系数据
     */
    @Delete("delete from setmeal_dish where setmeal_id = #{setmealId}")
    void deleteById(Long setmealId);

    /**
     * 批量插入套餐菜品数据
     */
    void insertBatch(List<SetmealDish> setmealDishes);
```

`SetmealDishMapper.xml`

```xml
    <insert id="insertBatch">
        insert into setmeal_dish (setmeal_id, dish_id, name, price, copies) values
        <foreach collection="setmealDishes" item="setmealDish" separator=",">
            (#{setmealDish.setmealId}, #{setmealDish.dishId}, #{setmealDish.name}, #{setmealDish.price}, #{setmealDish.copies})
        </foreach>
    </insert>
```



## 5. 启售或停售套餐

业务规则：

- 可以对状态为启售的套餐进行停售操作，可以对状态为停售的套餐进行起售操作
- 启售的套餐可以展示在用户端，停售的套餐不能展示在用户端
- 启售套餐时，如果套餐内包含停售的菜品，则不能启售



`SetmealController.java`

```java
    /**
     * 套餐启售或停售
     */
    @PostMapping("/status/{status}")
    public Result EnableOrDisable(@PathVariable Integer status, @RequestParam Long id) {
        log.info("套餐启售或停售：{}", status);
        setmealService.EnableOrDisable(id, status);
        return Result.success();
    }
```

`SetmealService.java`

```java
    /**
     * 套餐启售或停售
     */
    void EnableOrDisable(Long id, Integer status);
```

`SetmealServiceImpl.java`

```java
    /**
     * 套餐启售或停售
     */
    public void EnableOrDisable(Long id, Integer status) {
        // 启售套餐
        if (status == StatusConstant.ENABLE) {
            // 先判断套餐中的菜品是否存在停售的菜品
            List<Dish> dishes = dishMapper.getDishBySetmealId(id);
            dishes.forEach(dish -> {
                // 如果存在停售的菜品，抛出启售失败异常
                if (dish.getStatus() == StatusConstant.DISABLE) {
                    throw new SetmealEnableFailedException(MessageConstant.SETMEAL_ENABLE_FAILED);
                }
            });
        }

        // 停售套餐、启售套餐（套餐中没有停售菜品）
        Setmeal setmeal = Setmeal.builder().id(id).status(status).build();
        setmealMapper.update(setmeal);
    }
```

:warning: 需要分情况讨论：

*   如果套餐在启售状态，则可以直接修改为停售状态。
*   如果套餐在停售状态，在修改为启售状态之前，需要判断套餐内的所有菜品均为启售状态。

`DishMapper.java`

```java
    /**
     * 根据套餐 id 查询菜品
     */
    @Select("select d.* from dish d left join setmeal_dish sd on d.id = sd.dish_id where sd.setmeal_id = #{setmealId}")
    List<Dish> getDishBySetmealId(Long setmealId);
```





