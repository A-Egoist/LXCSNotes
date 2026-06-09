# 苍穹外卖-Day09

## 课程内容

1.   实现用户端历史订单模块
2.   实现商家端订单管理模块
3.   优化用户下单功能



## 1. 用户端历史订单模块

### 1.1 查询历史订单

#### 产品原型

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606051844569.png" alt="image-20221128092537535" style="zoom: 67%;" />



#### 业务规则

- 分页查询历史订单
- 可以根据订单状态查询
- 展示订单数据时，需要展示的数据包括：下单时间、订单状态、订单金额、订单明细（商品名称、图片）

#### 接口设计

参见接口文档

![image-20221128103222657](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606051945366.png)

#### 代码实现

`user/OrderController.java`

```java
    /**
     * 历史订单查询
     * @param status   订单状态 1待付款 2待接单 3已接单 4派送中 5已完成 6已取消
     */
    @GetMapping("/historyOrders")
    @ApiOperation(value = "历史订单查询")
    public Result<PageResult> page(int page, int pageSize, Integer status) {
        log.info("历史订单查询：{}, {}, {}", page, pageSize, status);
        PageResult pageResult = orderService.pageQuery4User(page, pageSize, status);
        return Result.success(pageResult);
    }
```

`OrderService.java`

```java
    /**
     * 用户端订单分页查询
     */
    PageResult pageQuery4User(int page, int pageSize, Integer status);
```

`OrderServiceImpl.java`

```java
    /**
     * 用户端订单分页查询
     */
    public PageResult pageQuery4User(int pageNum, int pageSize, Integer status) {
        // 设置分页
        PageHelper.startPage(pageNum, pageSize);

        OrdersPageQueryDTO ordersPageQueryDTO = new OrdersPageQueryDTO();
        ordersPageQueryDTO.setUserId(BaseContext.getCurrentId());
        ordersPageQueryDTO.setStatus(status);

        // 分页条件查询
        Page<Orders> page = orderMapper.pageQuery(ordersPageQueryDTO);
        ArrayList<OrderVO> list = new ArrayList<>();

        // 查询订单明细，并封装到 OrderVO 进行响应
        if (page != null && page.getTotal() > 0) {
            for (Orders orders : page) {
                // 获取订单 id
                Long orderId = orders.getId();
                // 查询订单明细
                List<OrderDetail> orderDetails = orderDetailMapper.getByOrderId(orderId);
                // 构造返回对象
                OrderVO orderVO = new OrderVO();
                BeanUtils.copyProperties(orders, orderVO);
                orderVO.setOrderDetailList(orderDetails);
                list.add(orderVO);
            }
        }

        return new PageResult(page.getTotal(), list);
    }
```

`OrderMapper.java`

```java
    /**
     * 分页条件查询，并按照下单时间排序
     */
    Page<Orders> pageQuery(OrdersPageQueryDTO ordersPageQueryDTO);
```

`OrderMapper.xml`

```xml
    <select id="pageQuery" resultType="com.sky.entity.Orders">
        select * from orders
        <where>
            <if test="number != null and number != ''">
                and number like concat('%', #{number}, '%')
            </if>
            <if test="phone != null and phone != ''">
                and phone like concat('%', #{phone}, '%')
            </if>
            <if test="userId != null">
                and user_id = #{userId}
            </if>
            <if test="status != null">
                and status = #{status}
            </if>
            <if test="beginTime != null">
                and order_time &gt;= #{beginTime}
            </if>
            <if test="endTime != null">
                and order_time &lt;= #{endTime}
            </if>
        </where>
        order by order_time desc
    </select>
```

`OrderDetailMapper.java`

```java
    /**
     * 根据订单 id 查询订单明细
     */
    @Select("select * from order_detail where order_id = #{orderId}")
    List<OrderDetail> getByOrderId(Long orderId);
```



#### 功能测试

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606051841729.png" alt="image-20260605184105309" style="zoom: 40%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606051846165.png" alt="image-20260605184545008" style="zoom:40%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606051846429.png" alt="image-20260605184607868" style="zoom:40%;" />



### 1.2 查询订单详情

#### 产品原型

![image-20221128102144294](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606051944086.png)

#### 接口设计

参见接口文档

![image-20221128142142811](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606051945624.png)

#### 代码实现

`user/OrderController.java`

```java
    /**
     * 查询订单详情
     */
    @GetMapping("/orderDetail/{id}")
    @ApiOperation(value = "查询订单详情")
    public Result<OrderVO> details(@PathVariable Long id) {
        log.info("查询订单详情，订单 id：{}", id);
        OrderVO orderVO = orderService.details(id);
        return Result.success(orderVO);
    }
```

`OrderService.java`

```java
    /**
     * 查询订单详情
     */
    OrderVO details(Long id);
```

`OrderServiceImpl.java`

```java
    /**
     * 查询订单详情
     */
    public OrderVO details(Long id) {
        // 根据订单 id 查询订单
        Orders orders = orderMapper.getById(id);

        // 查询该订单对应的菜品和套餐明细
        List<OrderDetail> orderDetailList = orderDetailMapper.getByOrderId(orders.getId());

        // 将该订单及其详情封装到 OrderVO 中并返回
        OrderVO orderVO = new OrderVO();
        BeanUtils.copyProperties(orders, orderVO);
        orderVO.setOrderDetailList(orderDetailList);

        return orderVO;
    }
```

`OrderMapper.java`

```java
    /**
     * 根据订单 id 查询订单
     */
    @Select("select * from orders where id = #{id}")
    Orders getById(Long id);
```

#### 功能测试

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606052004818.png" alt="image-20260605200408131" style="zoom:40%;" />



### 1.3 取消订单

#### 产品原型

![image-20221128145444268](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606052142466.png)

#### 业务规则

- 待支付和待接单状态下，用户可直接取消订单
- 商家已接单状态下，用户取消订单需电话沟通商家
- 派送中状态下，用户取消订单需电话沟通商家
- 如果在待接单状态下取消订单，需要给用户退款
- 取消订单后需要将订单状态修改为“已取消”

#### 接口设计

参见接口文档

![image-20221128164410852](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606052142862.png)

#### 代码实现

`user/OrderController.java`

```java
    /**
     * 用户取消订单
     */
    @PutMapping("/cancel/{id}")
    @ApiOperation(value = "用户取消订单")
    public Result cancel(@PathVariable Long id) throws Exception {
        log.info("用户取消订单，订单 id：{}", id);
        orderService.userCancelById(id);
        return Result.success();
    }
```

`OrderService.java`

```java
    /**
     * 用户取消订单
     */
    void userCancelById(Long id) throws Exception;
```

`OrderServiceImpl.java`

```java
    /**
     * 用户取消订单
     */
    public void userCancelById(Long id) throws Exception {
        // 根据 id 查询订单，ordersDB 只读
        Orders ordersDB = orderMapper.getById(id);

        // 校验订单是否存在
        if (ordersDB == null) {
            throw new OrderBusinessException(MessageConstant.ORDER_NOT_FOUND);
        }

        // 订单状态：1 表示待付款、2 表示待接单、3 表示已接单、4 表示派送中、5 表示已完成、6 表示已取消
        if (ordersDB.getStatus() > 2) {
            // 状态 3、4、5 需要联系商家，让商家取消订单，用户无法直接取消这类订单
            throw new OrderBusinessException(MessageConstant.ORDER_STATUS_ERROR);
        }

        Orders orders = new Orders();  // orders 只封装需要更新的字段，避免数据覆盖和数据混乱
        orders.setId(ordersDB.getId());

        // 订单处于待接单状态下取消，需要进行退款
        if (ordersDB.getStatus().equals(Orders.TO_BE_CONFIRMED)) {
            // 调用微信支付退款接口
            // weChatPayUtil.refund(
            //         ordersDB.getNumber(),  // 商户订单号
            //         ordersDB.getNumber(),  // 商户退款订单号
            //         new BigDecimal(0.01),  // 退款金额，单位 CNY
            //         new BigDecimal(0.01)  // 退款金额
            // );

            // 支付状态修改为 退款
            orders.setPayStatus(Orders.REFUND);
        }

        // 更新订单状态、取消原因、取消时间
        orders.setStatus(Orders.CANCELLED);
        orders.setCancelReason("用户取消");
        orders.setCancelTime(LocalDateTime.now());
        orderMapper.update(orders);
    }
```

>   :question: ​为什么要创建两个 Orders 对象 ordersDB 和 orders？这样做有什么意义？
>
>   ordersDB = 查出来的旧数据（只用来判断）
>
>   orders = 要更新的新数据（只装修改项）
>
>   只传需要更新的字段，是最安全、最标准的更新方式



#### 功能测试

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606052214706.png" alt="image-20260605221422358" style="zoom:40%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606052214721.png" alt="image-20260605221441030" style="zoom:40%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606052215320.png" alt="image-20260605221511091" style="zoom:40%;" />



### 1.4 再来一单

#### 产品原型

![image-20221128173238656](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061100422.png)

#### 业务规则

*   再来一单就是将原订单中的商品重新加入到购物车中

#### 接口设计

参见接口文档

![image-20221128173350467](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061100261.png)

#### 代码实现

`user/OrderController.java`

```java
    /**
     * 再来一单
     */
    @PostMapping("/repetition/{id}")
    @ApiOperation(value = "再来一单")
    public Result repetition(@PathVariable Long id) {
        log.info("再来一单，订单 id：{}", id);
        orderService.repetition(id);
        return Result.success();
    }
```

`OrderService.java`

```java
    /**
     * 再来一单
     */
    void repetition(Long id);
```

`OrderServiceImpl.java`

```java
    /**
     * 再来一单
     */
    public void repetition(Long id) {
        // 获取当前用户 userId
        Long userId = BaseContext.getCurrentId();

        // 根据订单 id 查询订单详情
        List<OrderDetail> orderDetailList = orderDetailMapper.getByOrderId(id);

        // 将订单详情转换为购物车对象
        List<ShoppingCart> shoppingCartList = orderDetailList.stream().map(x -> {
            ShoppingCart shoppingCart = new ShoppingCart();

            // 将原订单详情里面的菜品信息重新复制到购物车对象中
            BeanUtils.copyProperties(x, shoppingCart, "id");
            shoppingCart.setUserId(userId);
            shoppingCart.setCreateTime(LocalDateTime.now());

            return shoppingCart;
        }).collect(Collectors.toList());

        // 将购物车对象批量添加到数据库
        shoppingCartMapper.insertBatch(shoppingCartList);
    }
```

>   :warning: 重点理解如何将订单详情转换为购物车对象，其中 `.stream()`、`.map()`、`.collect()` 的作用分别是什么
>
>   :warning: 将原订单详情中的菜品信息复制到购物车对象中的时候，需要排除 `id` 这个属性

`ShoppingCartMapper.java`

```java
    /**
     * 批量插入购物车数据
     */
    void insertBatch(List<ShoppingCart> shoppingCartList);
```

`ShoppingCartMapper.xml`

```xml
    <insert id="insertBatch" parameterType="list">
        insert into shopping_cart (name, image, user_id, dish_id, setmeal_id, dish_flavor, amount, create_time)
        values
        <foreach collection="shoppingCartList" item="sc" separator=",">
            (#{sc.name}, #{sc.image}, #{sc.userId}, #{sc.dishId}, #{sc.setmealId}, #{sc.dishFlavor}, #{sc.amount}, #{sc.createTime})
        </foreach>
    </insert>
```



#### 功能测试

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061114150.png" alt="image-20260606111408808" style="zoom:40%;" /><img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061114759.png" alt="image-20260606111436390" style="zoom:40%;" />



## 2. 商家端订单管理模块

### 2.1 订单搜索

#### 产品原型

![image-20221129092023177](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061829989.png)

![image-20221129114035570](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061829195.png)

![image-20221129114054664](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061829957.png)

![image-20221129114116492](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061829770.png)

![image-20221129114132956](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061830829.png)

![image-20221129114151055](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061830312.png)



#### 业务规则

- 输入订单号/手机号进行搜索，支持模糊搜索
- 根据订单状态进行筛选
- 下单时间进行时间筛选
- 搜索内容为空，提示未找到相关订单
- 搜索结果页，展示包含搜索关键词的内容
- 分页展示搜索到的订单数据



#### 接口设计

参见接口文档



#### 代码实现

`admin/OrderController.java`

```java
package com.sky.controller.admin;

import com.sky.dto.OrdersPageQueryDTO;
import com.sky.result.PageResult;
import com.sky.result.Result;
import com.sky.service.OrderService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController("adminOrderController")
@RequestMapping("/admin/order")
@Slf4j
@Api(tags = "管理端-订单管理接口")
public class OrderController {

    @Autowired
    private OrderService orderService;

    /**
     * 订单搜索
     */
    @GetMapping("/conditionSearch")
    @ApiOperation(value = "订单搜索")
    public Result<PageResult> conditionSearch(OrdersPageQueryDTO ordersPageQueryDTO) {
        log.info("订单搜索：{}", ordersPageQueryDTO);
        PageResult pageResult = orderService.conditionSearch(ordersPageQueryDTO);
        return Result.success(pageResult);
    }
}
```

`OrderService.java`

```java
    /**
     * 订单搜索
     */
    PageResult conditionSearch(OrdersPageQueryDTO ordersPageQueryDTO);
```

`OrderServiceImpl.java`

```java
    /**
     * 订单搜索
     */
    public PageResult conditionSearch(OrdersPageQueryDTO ordersPageQueryDTO) {
        // 设置分页
        PageHelper.startPage(ordersPageQueryDTO.getPage(), ordersPageQueryDTO.getPageSize());

        Page<Orders> page = orderMapper.pageQuery(ordersPageQueryDTO);

        // 部分订单状态，需要额外返回订单菜品信息，将 Orders 转换为 OrderVO
        List<OrderVO> orderVOList = getOrderVOList(page);

        return new PageResult(page.getTotal(), orderVOList);
    }

    private List<OrderVO> getOrderVOList(Page<Orders> page) {
        // 返回订单菜品信息，自定义 OrderVO 响应结果
        List<OrderVO> orderVOList = new ArrayList<>();

        List<Orders> ordersList = page.getResult();
        if (ordersList != null && !ordersList.isEmpty()) {
            for (Orders orders : ordersList) {
                // 将共同字段复制到 OrderVO 对象
                OrderVO orderVO = new OrderVO();
                BeanUtils.copyProperties(orders, orderVO);

                // 将订单菜品信息封装到 orderVO 中并添加到 OrderVOList 中
                String orderDishes = getOrderDishesStr(orders);
                orderVO.setOrderDishes(orderDishes);
                orderVOList.add(orderVO);
            }
        }
        return orderVOList;
    }

    /**
     * 根据订单 id 获取菜品信息字符串
     */
    private String getOrderDishesStr(Orders orders) {
        // 查询订单菜品详情（订单中的菜品及其数量）
        List<OrderDetail> orderDetailList = orderDetailMapper.getByOrderId(orders.getId());

        // 将每一条订单菜品信息拼接为字符串（格式：宫保鸡丁*3;鱼香肉丝*2）
        List<String> orderDishList = orderDetailList.stream().map(x -> {
            String orderDish = x.getName() + "*" + x.getNumber() + ";";
            return orderDish;
        }).collect(Collectors.toList());

        // 将该订单对应的所有菜品信息拼接在一起
        return String.join("", orderDishList);
    }
```

#### 功能测试

![image-20260606194334152](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061943816.png)

![image-20260606194350569](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061943110.png)



### 2.2 各个状态的订单数量统计

#### 产品原型

![image-20221129095804419](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606061949960.png)



#### 接口设计

参见接口文档

#### 代码实现

`admin/OrderController.java`

```java
    /**
     * 各个状态的订单数量统计
     */
    @GetMapping("/statistics")
    @ApiOperation(value = "各个状态的订单数量统计")
    public Result<OrderStatisticsVO> statistics() {
        log.info("各个状态的订单数量统计");
        OrderStatisticsVO orderStatisticsVO = orderService.statistics();
        return Result.success(orderStatisticsVO);
    }
```

`OrderService.java`

```java
    /**
     * 各个状态的订单数量统计
     */
    OrderStatisticsVO statistics();
```

`OrderServiceImpl.java`

```java
    /**
     * 各个状态的订单数量统计
     * @return
     */
    public OrderStatisticsVO statistics() {
        // 根据状态，分别查询出待接单、待派送、派送中的订单数量
        Integer toBeConfirmed = orderMapper.countStatus(Orders.TO_BE_CONFIRMED);
        Integer confirmed = orderMapper.countStatus(Orders.CONFIRMED);
        Integer deliveryInProgress = orderMapper.countStatus(Orders.DELIVERY_IN_PROGRESS);

        // 将查询出的数据封装到 orderStatisticsVO 中响应
        OrderStatisticsVO orderStatisticsVO = new OrderStatisticsVO();
        orderStatisticsVO.setToBeConfirmed(toBeConfirmed);
        orderStatisticsVO.setConfirmed(confirmed);
        orderStatisticsVO.setDeliveryInProgress(deliveryInProgress);

        return orderStatisticsVO;
    }
```

`OrderMapper.java`

```java
    /**
     * 根据状态统计订单数量
     */
    @Select("select count(id) from orders where status = #{status}")
    Integer countStatus(Integer status);
```

#### 功能测试

![image-20260606200321001](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062003196.png)



### 2.3 查询订单详情

#### 产品原型

![image-20221129101712084](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062057940.png)

#### 业务规则

- 订单详情页面需要展示订单基本信息（状态、订单号、下单时间、收货人、电话、收货地址、金额等）
- 订单详情页面需要展示订单明细数据（商品名称、数量、单价）

#### 接口设计

参见接口文档

#### 代码实现

`OrderController.java`

```java
    /**
     * 查询订单详情
     */
    @GetMapping("/details/{id}")
    @ApiOperation(value = "查询订单详情")
    public Result<OrderVO> details(@PathVariable Long id) {
        log.info("查询订单详情：{}", id);
        OrderVO orderVO = orderService.details(id);
        return Result.success(orderVO);
    }
```



#### 功能测试

![image-20260606210147973](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062101483.png)



### 2.4 接单

#### 产品原型

![image-20221129105142623](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062104573.png)

![image-20221129105116285](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062104779.png)

#### 业务规则

*   商家接单其实就是将订单的状态修改为“已接单”

#### 接口设计

参见接口文档

#### 代码实现

`admin/OrderController.java`

```java
    /**
     * 接单
     */
    @PutMapping("/confirm")
    @ApiOperation(value = "接单")
    public Result confirm(@RequestBody OrdersConfirmDTO ordersConfirmDTO) {
        log.info("接单：{}", ordersConfirmDTO);
        orderService.confirm(ordersConfirmDTO);
        return Result.success();
    }
```

`OrderService.java`

```java
    /**
     * 接单
     */
    void confirm(OrdersConfirmDTO ordersConfirmDTO);
```

`OrderServiceImpl.java`

```java
    /**
     * 接单
     */
    public void confirm(OrdersConfirmDTO ordersConfirmDTO) {
        // 将订单的状态修改为“已接单”
        Orders orders = Orders.builder()
                .id(ordersConfirmDTO.getId())
                .status(Orders.CONFIRMED)
                .build();
        orderMapper.update(orders);
    }
```

#### 功能测试

![image-20260606213139568](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062131573.png)

### 2.5 拒单

#### 产品原型

![image-20221129110358976](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062131022.png)

![image-20221129110428390](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062131451.png)

#### 业务规则

- 商家拒单其实就是将订单状态修改为“已取消”
- 只有订单处于“待接单”状态时可以执行拒单操作
- 商家拒单时需要指定拒单原因
- 商家拒单时，如果用户已经完成了支付，需要为用户退款



#### 接口设计

参见接口文档

#### 代码实现

`admin/OrderController.java`

```java
    /**
     * 拒单
     */
    @PutMapping("/rejection")
    @ApiOperation(value = "拒单")
    public Result rejection(@RequestBody OrdersRejectionDTO ordersRejectionDTO) throws Exception {
        log.info("拒单：{}", ordersRejectionDTO);
        orderService.rejection(ordersRejectionDTO);
        return Result.success();
    }
```

`OrderService.java`

```java
    /**
     * 拒单
     */
    void rejection(OrdersRejectionDTO ordersRejectionDTO) throws Exception;
```

`OrderServiceImpl.java`

```java
    /**
     * 拒单
     */
    public void rejection(OrdersRejectionDTO ordersRejectionDTO) throws Exception {
        // 根据 id 查询订单信息，只读
        Orders ordersDB = orderMapper.getById(ordersRejectionDTO.getId());

        // 订单只有存在且状态为 2（待接单）才可以拒单
        if (ordersDB == null || !ordersDB.getStatus().equals(Orders.TO_BE_CONFIRMED)) {
            throw new OrderBusinessException(MessageConstant.ORDER_STATUS_ERROR);
        }

        // 获取支付状态
        Integer payStatus = ordersDB.getPayStatus();
        if (payStatus == Orders.PAID) {
            // 如果用户已付款，需要退款
            // String refund = weChatPayUtil.refund(
            //         ordersDB.getNumber(),
            //         ordersDB.getNumber(),
            //         new BigDecimal(0.01),
            //         new BigDecimal(0.01)
            // );
            // log.info("申请退款：{}", refund);
            log.info("申请退款");
        }

        // 拒单需要退款，根据订单 id 更新订单状态、拒单原因、取消时间
        Orders orders = new Orders();
        orders.setId(ordersDB.getId());
        orders.setStatus(Orders.CANCELLED);
        orders.setRejectionReason(ordersRejectionDTO.getRejectionReason());
        orders.setCancelTime(LocalDateTime.now());

        // 更新数据库
        orderMapper.update(orders);
    }
```

#### 功能测试

![image-20260606215642081](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062157071.png)

![image-20260606215651651](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062157344.png)

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062157649.png" alt="image-20260606215702468" style="zoom:50%;" />

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606062157390.png" alt="image-20260606215723536" style="zoom:50%;" />



### 2.6 取消订单

#### 产品原型

![image-20221129111402099](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070001065.png)

#### 业务规则

- 取消订单其实就是将订单状态修改为“已取消”
- 商家取消订单时需要指定取消原因
- 商家取消订单时，如果用户已经完成了支付，需要为用户退款

#### 接口设计

参见接口文档

#### 代码实现

`admin/OrderController.java`

```java
    /**
     * 取消订单
     */
    @PutMapping("/cancel")
    @ApiOperation(value = "取消订单")
    public Result cancel(@RequestBody OrdersCancelDTO ordersCancelDTO) throws Exception {
        log.info("取消订单：{}", ordersCancelDTO);
        orderService.adminCancel(ordersCancelDTO);
        return Result.success();
    }
```

`OrderService.java`

```java
    /**
     * 商家取消订单
     */
    void adminCancel(OrdersCancelDTO ordersCancelDTO) throws Exception;
```

`OrderServiceImpl.java`

```java
    /**
     * 商家取消订单
     */
    public void adminCancel(OrdersCancelDTO ordersCancelDTO) throws Exception {
        // 根据订单 id 查询订单，只读
        Orders ordersDB = orderMapper.getById(ordersCancelDTO.getId());

        // 获取支付状态
        Integer payStatus = ordersDB.getPayStatus();
        if (payStatus == Orders.PAID) {
            // 如果用户已支付，需要退款
            // String refund = weChatPayUtil.refund(
            //         ordersDB.getNumber(),
            //         ordersDB.getNumber(),
            //         new BigDecimal(0.01),
            //         new BigDecimal(0.01)
            // );
            // log.info("申请退款：{}", refund);
            log.info("申请退款");
        }

        // 管理端取消订单需要退款，根据订单 id 更新订单状态、取消原因、取消时间
        Orders orders = new Orders();
        orders.setId(ordersCancelDTO.getId());
        orders.setStatus(Orders.CANCELLED);
        orders.setCancelReason(ordersCancelDTO.getCancelReason());
        orders.setCancelTime(LocalDateTime.now());

        // 更新数据库
        orderMapper.update(orders);
    }
```

#### 功能测试

![image-20260607000852713](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070009580.png)

![image-20260607000913080](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070009409.png)

![image-20260607000928397](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070009471.png)



### 2.7 派送订单

#### 产品原型

![image-20221129113257201](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070012143.png)

#### 业务规则

- 派送订单其实就是将订单状态修改为“派送中”
- 只有状态为“待派送”的订单可以执行派送订单操作

#### 接口设计

参见接口文档

#### 代码实现

`admin/OrderController.java`

```java
    /**
     * 派送订单
     */
    @PutMapping("/delivery/{id}")
    @ApiOperation(value = "派送订单")
    public Result delivery(@PathVariable Long id) throws Exception {
        log.info("派送订单：{}", id);
        orderService.delivery(id);
        return Result.success();
    }
```

`OrderService.java`

```java
    /**
     * 派送订单
     */
    void delivery(Long id);
```

`OrderServiceImpl.java`

```java
    /**
     * 派送订单
     */
    public void delivery(Long id) {
        // 根据订单 id 查询订单，只读
        Orders ordersDB = orderMapper.getById(id);

        // 校验订单是否存在，且状态为“已接单”
        if (ordersDB == null || !ordersDB.getStatus().equals(Orders.CONFIRMED)) {
            throw new OrderBusinessException(MessageConstant.ORDER_STATUS_ERROR);
        }

        // 根据订单 id 更新订单状态
        Orders orders = new Orders();
        orders.setId(id);
        orders.setStatus(Orders.DELIVERY_IN_PROGRESS);

        // 更新数据库
        orderMapper.update(orders);
    }
```

#### 功能测试

![image-20260607002200316](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070022205.png)

![image-20260607002212469](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070022405.png)

![image-20260607002221294](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070022448.png)



### 2.8 完成订单

#### 产品原型

![image-20221129112554051](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070024412.png)

#### 业务规则

- 完成订单其实就是将订单状态修改为“已完成”
- 只有状态为“派送中”的订单可以执行订单完成操作

#### 接口设计

参见接口文档

#### 代码实现

`admin/OrderController.java`

```java
    /**
     * 完成订单
     */
    @PutMapping("/complete/{id}")
    @ApiOperation(value = "完成订单")
    public Result complete(@PathVariable Long id) throws Exception {
        log.info("完成订单");
        orderService.complete(id);
        return Result.success();
    }
```

`OrderService.java`

```java
    /**
     * 完成订单
     */
    void complete(Long id);
```

`OrderServiceImpl.java`

```java
    /**
     * 完成订单
     */
    public void complete(Long id) {
        // 根据订单 id 查询订单信息，只读
        Orders ordersDB = orderMapper.getById(id);

        // 校验订单是否存在，且状态为“派送中”
        if (ordersDB == null || !ordersDB.getStatus().equals(Orders.DELIVERY_IN_PROGRESS)) {
            throw new OrderBusinessException(MessageConstant.ORDER_STATUS_ERROR);
        }

        // 根据订单 id 更新订单状态
        Orders orders = new Orders();
        orders.setId(id);
        orders.setStatus(Orders.COMPLETED);
        orders.setDeliveryTime(LocalDateTime.now());

        // 更新数据库
        orderMapper.update(orders);
    }
```



#### 功能测试

![image-20260607003251215](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070033036.png)

![image-20260607003306373](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070033981.png)

![image-20260607003314897](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606070033007.png)



## 3. 优化用户下单功能

实现功能：校验收货地址是否超出配送范围

### 环境准备

1、登录百度地图开放平台，进入控制台，创建应用，获取 AK

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606071016933.png" alt="image-20260607101622772" style="zoom:50%;" />

### 代码实现

`application.yml`

```yml
sky:
  shop:
    address: ${sky.shop.address}
  baidu:
    ak: ${sky.baidu.ak}
```

`OrderServiceImpl.java`

首先注入数据：

```java
    @Value("${sky.shop.address}")
    private String shopAddress;
    @Value("${sky.baidu.ak}")
    private String baiduAK;
```

然后添加一个校验方法：

```java
    /**
     * 检查用户的收获地址是否超出配送范围
     */
    private void checkOutOfRange(String address) {
        Map map = new HashMap();
        map.put("address", shopAddress);
        map.put("output", "json");
        map.put("ak",  baiduAK);

        // 获取店铺的经纬度坐标
        String shopCoordinate = HttpClientUtil.doGet("https://api.map.baidu.com/geocoding/v3", map);
        JSONObject jsonObject = JSONObject.parseObject(shopCoordinate);
        if (!jsonObject.getString("status").equals("0")) {
            throw new OrderBusinessException("店铺地址解析失败");
        }

        // 数据解析
        JSONObject location = jsonObject.getJSONObject("result").getJSONObject("location");
        String lat = location.getString("lat");
        String lng = location.getString("lng");
        // 店铺经纬度坐标
        String shopLngLat = lat + "," + lng;

        // 获取用户的经纬度坐标
        map.put("address", address);
        String userCoordinate = HttpClientUtil.doGet("https://api.map.baidu.com/geocoding/v3", map);

        jsonObject = JSONObject.parseObject(userCoordinate);
        if (!jsonObject.getString("status").equals("0")) {
            throw new OrderBusinessException("收货地址解析失败");
        }

        // 数据解析
        location = jsonObject.getJSONObject("result").getJSONObject("location");
        lat = location.getString("lat");
        lng = location.getString("lng");
        // 用户收货地址经纬度坐标
        String userLngLat = lat + "," + lng;

        map.put("origin", shopLngLat);
        map.put("destination", userLngLat);
        map.put("steps_info", "0");

        // 路线规划
        String json = HttpClientUtil.doGet("https://api.map.baidu.com/directionlite/v1/driving", map);
        jsonObject = JSONObject.parseObject(json);
        if (!jsonObject.getString("status").equals("0")) {
            throw new OrderBusinessException("配送路线规划失败");
        }

        // 数据解析
        JSONObject result = jsonObject.getJSONObject("result");
        JSONArray jsonArray = (JSONArray) result.get("routes");
        Integer distance = (Integer) ((JSONObject) jsonArray.get(0)).get("distance");

        // 如果配送距离超过 5000 米
        if (distance > 5000) {
            throw new OrderBusinessException("超出配送范围");
        }
    }
```

最后在用户下单方法中添加如下代码：

```java
        // 检查用户的收货地址是否超出配送范围
        checkOutOfRange(addressBook.getCityName() + addressBook.getDistrictName() + addressBook.getDetail());
```

![image-20260607104651822](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606071047415.png)

