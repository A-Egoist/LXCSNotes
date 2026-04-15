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
5. 分别通过swagger接口文档和前后端联调进行功能测试



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



## 3. 删除套餐



## 4. 修改套餐



## 5. 起售停售套餐













