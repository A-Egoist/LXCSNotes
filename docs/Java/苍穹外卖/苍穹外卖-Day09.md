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

```java
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

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试







## 2. 商家端订单管理模块

### 2.1 订单搜索

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试

### 2.2 各个状态的订单数量统计

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试

### 2.3 查询订单详情

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试

### 2.4 接单

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试

### 2.5 拒单

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试

### 2.6 取消订单

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试

### 2.7 派送订单

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试

### 2.8 完成订单

#### 产品原型

#### 业务规则

#### 接口设计

#### 代码实现

#### 功能测试



## 3. 优化用户下单功能

实现功能：校验收货地址是否超出配送范围

