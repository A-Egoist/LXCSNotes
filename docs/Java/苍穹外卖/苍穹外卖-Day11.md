# 苍穹外卖-Day11

## 课程内容

- Apache ECharts
- 营业额统计
- 用户统计
- 订单统计
- 销量排名Top10



功能实现：**数据统计**

**数据统计效果图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081357280.png" alt="image-20230101152725417" style="zoom:80%;" /> 



## 1. Apache ECharts

### 1.1 介绍

Apache ECharts 是一款基于 Javascript 的数据可视化图表库，提供直观，生动，可交互，可个性化定制的数据可视化图表。
官网地址：https://echarts.apache.org/zh/index.html

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081357116.png" alt="image-20230101153041348" style="zoom:50%;" /> 



**常见效果展示：**

1). 柱形图

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081357377.png" alt="image-20230101153748714" style="zoom:50%;" /> 



2). 饼形图

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081357751.png" alt="image-20230101153230868" style="zoom:50%;" /> 



3). 折线图

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081357298.png" alt="image-20230101153824086" style="zoom:50%;" /> 



**总结：**不管是哪种形式的图形，最本质的东西实际上是数据，它其实是对数据的一种可视化展示。



### 1.2 入门案例

Apache Echarts官方提供的快速入门：https://echarts.apache.org/handbook/zh/get-started/

**效果展示：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081357392.png" alt="image-20230101155524477" style="zoom:50%;" /> 



**实现步骤：**

1). 引入echarts.js 文件(当天资料已提供)

2). 为 ECharts 准备一个设置宽高的 DOM

3). 初始化echarts实例

4). 指定图表的配置项和数据

5). 使用指定的配置项和数据显示图表



**代码开发：**

```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <title>ECharts</title>
    <!-- 引入刚刚下载的 ECharts 文件 -->
    <script src="echarts.js"></script>
  </head>
  <body>
    <!-- 为 ECharts 准备一个定义了宽高的 DOM -->
    <div id="main" style="width: 600px;height:400px;"></div>
    <script type="text/javascript">
      // 基于准备好的dom，初始化echarts实例
      var myChart = echarts.init(document.getElementById('main'));

      // 指定图表的配置项和数据
      var option = {
        title: {
          text: 'ECharts 入门示例'
        },
        tooltip: {},
        legend: {
          data: ['销量']
        },
        xAxis: {
          data: ['衬衫', '羊毛衫', '雪纺衫', '裤子', '高跟鞋', '袜子']
        },
        yAxis: {},
        series: [
          {
            name: '销量',
            type: 'bar',
            data: [5, 20, 36, 10, 10, 20]
          }
        ]
      };

      // 使用刚指定的配置项和数据显示图表。
      myChart.setOption(option);
    </script>
  </body>
</html>
```



**测试：**(当天资料中已提供)

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081357014.png" alt="image-20230101160244104" style="zoom:50%;" /> 

使用浏览器方式打开即可。



**总结：**使用Echarts，重点在于研究当前图表所需的数据格式。通常是需要后端提供符合格式要求的动态数据，然后响应给前端来展示图表。



## 2. 营业额统计

### 2.1 需求分析和设计

#### 2.1.1 产品原型

营业额统计是基于折现图来展现，并且按照天来展示的。实际上，就是某一个时间范围之内的每一天的营业额。同时，不管光标放在哪个点上，那么它就会把具体的数值展示出来。并且还需要注意日期并不是固定写死的，是由上边时间选择器来决定。比如选择是近7天、或者是近30日，或者是本周，就会把相应这个时间段之内的每一天日期通过横坐标展示。

**原型图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081408789.png" alt="image-20230101160747433" style="zoom:50%;" /> 



**业务规则：**

- 营业额指订单状态为已完成的订单金额合计
- 基于可视化报表的折线图展示营业额数据，X轴为日期，Y轴为营业额
- 根据时间选择区间，展示每天的营业额数据



#### 2.1.2 接口设计

通过上述原型图，设计出对应的接口。



<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081408668.png" alt="image-20230101160801758" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081408361.png" alt="image-20230101160812029" style="zoom:50%;" /> 



**注意：**具体返回数据一般由前端来决定，前端展示图表，具体折现图对应数据是什么格式，是有固定的要求的。
所以说，后端需要去适应前端，它需要什么格式的数据，我们就给它返回什么格式的数据。



### 2.2 代码开发

#### 2.2.1 VO设计

**根据接口定义设计对应的VO：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081408678.png" alt="image-20230101164058056" style="zoom:50%;" /> 

在sky-pojo模块，TurnoverReportVO.java已定义

```java
package com.sky.vo;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class TurnoverReportVO implements Serializable {

    //日期，以逗号分隔，例如：2022-10-01,2022-10-02,2022-10-03
    private String dateList;

    //营业额，以逗号分隔，例如：406.0,1520.0,75.0
    private String turnoverList;

}
```



#### 2.2.2 Controller层

**根据接口定义创建ReportController：**

```java
package com.sky.controller.admin;

import com.sky.result.Result;
import com.sky.service.ReportService;
import com.sky.vo.TurnoverReportVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.time.LocalDate;

@RestController
@RequestMapping("/admin/report")
@Slf4j
@Api(tags = "统计报表相关接口")
public class ReportController {

    @Autowired
    private ReportService reportService;

    /**
     * 营业额统计
     * @return
     */
    @GetMapping("/turnoverStatistics")
    @ApiOperation(value = "营业额统计")
    public Result<TurnoverReportVO> turnoverStatistics(@DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate begin,
                                                       @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate end) {
        log.info("营业额统计：{}，{}", begin, end);
        TurnoverReportVO turnoverReportVO = reportService.getTurnover(begin, end);
        return Result.success(turnoverReportVO);
    }
}
```



#### 2.2.3 Service层接口

**创建ReportService接口，声明getTurnover方法：**

```java
package com.sky.service;

import com.sky.vo.TurnoverReportVO;

import java.time.LocalDate;

public interface ReportService {

    /**
     * 营业额统计
     */
    TurnoverReportVO getTurnover(LocalDate begin, LocalDate end);
}
```



#### 2.2.4 Service层实现类

**创建ReportServiceImpl实现类，实现getTurnover方法:**

```java
package com.sky.service.impl;

import com.sky.entity.Orders;
import com.sky.mapper.OrderMapper;
import com.sky.service.ReportService;
import com.sky.vo.TurnoverReportVO;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Service
@Slf4j
public class ReportServiceImpl implements ReportService {

    @Autowired
    private OrderMapper orderMapper;

    /**
     * 营业额统计
     */
    public TurnoverReportVO getTurnover(LocalDate begin, LocalDate end) {
        // 构造日期 list
        List<LocalDate> dateList = new ArrayList();
        dateList.add(begin);
        while (!end.equals(begin)) {
            begin = begin.plusDays(1);
            dateList.add(begin);
        }

        // 构造营业额 list
        List<Double> turnoverList = new ArrayList<>();
        for (LocalDate date : dateList) {
            LocalDateTime beginTime = LocalDateTime.of(date, LocalTime.MIN);
            LocalDateTime endTime = LocalDateTime.of(date, LocalTime.MAX);

            Map map = new HashMap();
            map.put("status", Orders.COMPLETED);
            map.put("begin", beginTime);
            map.put("end", endTime);

            Double turnover = orderMapper.sumTurnover(map);
            turnover = turnover == null ? 0.0 : turnover;

            turnoverList.add(turnover);
        }

        // 返回封装结果
        return TurnoverReportVO.builder()
                .dateList(StringUtils.join(dateList, ","))
                .turnoverList(StringUtils.join(turnoverList, ","))
                .build();
    }
}
```



#### 2.2.5 Mapper层

**在OrderMapper接口声明sumByMap方法：**

```java
    /**
     * 根据 map 中的 begin、end、status 等条件统计营业额
     */
    Double sumTurnover(Map map);
```

**在OrderMapper.xml文件中编写动态SQL：**

```xml
    <select id="sumTurnover" resultType="java.lang.Double">
        select sum(amount) from orders
        <where>
            <if test="begin != null">
                and order_time &gt;= #{begin}
            </if>
            <if test="end != null">
                and order_time &lt;= #{end}
            </if>
            <if test="status != null">
                and status = #{status}
            </if>
        </where>
    </select>
```



### 2.3 功能测试

可以通过如下方式进行测试：

- 接口文档测试
- 前后端联调测试

启动服务器，启动nginx，直接采用前后端联调测试。

进入数据统计模块

**1). 查看近7日营业额统计**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081505102.png" alt="image-20230101172807757" style="zoom:50%;" /> 

进入开发者模式，查看返回数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081505200.png" alt="image-20230101173031357" style="zoom:80%;" /> 



**2). 查看近30日营业额统计**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081505951.png" alt="image-20230101173201667" style="zoom:50%;" /> 

进入开发者模式，查看返回数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081505209.png" alt="image-20230101173304127" style="zoom:80%;" /> 

也可通过断点方式启动，查看每步执行情况。



## 3. 用户统计

### 3.1 需求分析和设计

#### 3.1.1 产品原型

所谓用户统计，实际上统计的是用户的数量。通过折线图来展示，上面这根蓝色线代表的是用户总量，下边这根绿色线代表的是新增用户数量，是具体到每一天。所以说用户统计主要统计**两个数据**，一个是**总的用户数量**，另外一个是**新增用户数量**。

**原型图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081513629.png" alt="image-20230102213727736" style="zoom:50%;" /> 

**业务规则：**

- 基于可视化报表的折线图展示用户数据，X轴为日期，Y轴为用户数
- 根据时间选择区间，展示每天的用户总量和新增用户量数据



#### 3.1.2 接口设计

根据上述原型图设计接口。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081513913.png" alt="image-20230102213809414" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081513863.png" alt="image-20230102213818334" style="zoom:50%;" /> 



### 3.2 代码开发

#### 3.2.1 VO设计

**根据用户统计接口的返回结果设计VO：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081807051.png" alt="image-20230102211004237" style="zoom:50%;" /> 

在sky-pojo模块，UserReportVO.java已定义

```java
package com.sky.vo;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.io.Serializable;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class UserReportVO implements Serializable {

    //日期，以逗号分隔，例如：2022-10-01,2022-10-02,2022-10-03
    private String dateList;

    //用户总量，以逗号分隔，例如：200,210,220
    private String totalUserList;

    //新增用户，以逗号分隔，例如：20,21,10
    private String newUserList;

}
```



#### 3.2.2 Controller层

**根据接口定义，在ReportController中创建userStatistics方法：**

```java
    /**
     * 用户统计
     */
    @GetMapping("/userStatistics")
    @ApiOperation(value = "用户统计")
    public Result<UserReportVO> userStatistics(@DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate begin,
                                               @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate end) {
        log.info("用户统计：{}，{}", begin, end);
        UserReportVO userReportVO = reportService.getUserStatistics(begin, end);
        return Result.success(userReportVO);
    }
```



#### 3.2.3 Service层接口

**在ReportService接口中声明getUserStatistics方法：**

```java
    /**
     * 统计指定时间区间内的用户数据
     */
    UserReportVO getUserStatistics(LocalDate begin, LocalDate end);
```



#### 3.2.4 Service层实现类

**在ReportServiceImpl实现类中实现getUserStatistics方法：**

```java
    /**
     * 统计指定时间区间内的用户数据
     */
    public UserReportVO getUserStatistics(LocalDate begin, LocalDate end) {
        // 构造日期 list
        List<LocalDate> dateList = new ArrayList();
        dateList.add(begin);
        while (!end.equals(begin)) {
            begin = begin.plusDays(1);
            dateList.add(begin);
        }

        // 构造每天用户总量 list
        List<Integer> totalUserList = new ArrayList<>();
        // 构造每天新增用户 list
        List<Integer> newUserList = new ArrayList<>();

        for (LocalDate date : dateList) {
            LocalDateTime beginTime = LocalDateTime.of(date, LocalTime.MIN);
            LocalDateTime endTime = LocalDateTime.of(date, LocalTime.MAX);

            Map map = new HashMap();
            map.put("end", endTime);
            Integer totalUser = userMapper.countUser(map);
            map.put("begin", beginTime);
            Integer newUser = userMapper.countUser(map);

            totalUserList.add(totalUser);
            newUserList.add(newUser);
        }

        // 返回封装结果
        return UserReportVO.builder()
                .dateList(StringUtils.join(dateList, ","))
                .totalUserList(StringUtils.join(totalUserList, ","))
                .newUserList(StringUtils.join(newUserList, ","))
                .build();
    }
```



#### 3.2.5 Mapper层

**在UserMapper接口中声明countByMap方法：**

```java
    /**
     * 统计指定时间区间内的用户数量
     */
    Integer countUser(Map map);
```

**在UserMapper.xml文件中编写动态SQL：**

```java
    <select id="countUser" resultType="java.lang.Integer">
        select count(id) from user
        <where>
            <if test="begin != null">
                and create_time &gt;= #{begin}
            </if>
            <if test="end != null">
                and create_time &lt;= #{end}
            </if>
        </where>
    </select>
```



### 3.3 功能测试

可以通过如下方式进行测试：

- 接口文档测试
- 前后端联调测试

进入数据统计模块

**1). 查看近7日用户统计**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081809180.png" alt="image-20230107191339668" style="zoom:50%;" /> 

进入开发者模式，查看返回数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081809129.png" alt="image-20230107191532175" style="zoom:50%;" /> 



**2). 查看近30日用户统计**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081809813.png" alt="image-20230107191613369" style="zoom:50%;" /> 

进入开发者模式，查看返回数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081809223.png" alt="image-20230107191707568" style="zoom:50%;" /> 

也可通过断点方式启动，查看每步执行情况。



## 4. 订单统计

### 4.1 需求分析和设计

#### 4.1.1 产品原型

订单统计通过一个折现图来展现，折线图上有两根线，这根蓝色的线代表的是订单总数，而下边这根绿色的线代表的是有效订单数，指的就是状态是已完成的订单就属于有效订单，分别反映的是每一天的数据。上面还有3个数字，分别是订单总数、有效订单、订单完成率，它指的是整个时间区间之内总的数据。

**原型图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081832679.png" alt="image-20230107192859270" style="zoom:50%;" /> 

**业务规则：**

- 有效订单指状态为 “已完成” 的订单
- 基于可视化报表的折线图展示订单数据，X轴为日期，Y轴为订单数量
- 根据时间选择区间，展示每天的订单总数和有效订单数
- 展示所选时间区间内的有效订单数、总订单数、订单完成率，订单完成率 = 有效订单数 / 总订单数 * 100%



#### 4.1.2 接口设计

根据上述原型图设计接口。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081832220.png" alt="image-20230107192942872" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081832510.png" alt="image-20230107192952958" style="zoom:50%;" /> 



### 4.2 代码开发

#### 4.2.1 VO设计

**根据订单统计接口的返回结果设计VO：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081832503.png" alt="image-20230107195325915" style="zoom:50%;" /> 

在sky-pojo模块，OrderReportVO.java已定义

```java
package com.sky.vo;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.io.Serializable;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class OrderReportVO implements Serializable {

    //日期，以逗号分隔，例如：2022-10-01,2022-10-02,2022-10-03
    private String dateList;

    //每日订单数，以逗号分隔，例如：260,210,215
    private String orderCountList;

    //每日有效订单数，以逗号分隔，例如：20,21,10
    private String validOrderCountList;

    //订单总数
    private Integer totalOrderCount;

    //有效订单数
    private Integer validOrderCount;

    //订单完成率
    private Double orderCompletionRate;

}
```



#### 4.2.2 Controller层

**在ReportController中根据订单统计接口创建orderStatistics方法：**

```java
    /**
     * 订单统计
     */
    @GetMapping("/ordersStatistics")
    @ApiOperation(value = "订单统计")
    public Result<OrderReportVO> ordersStatistics(@DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate begin,
                                                  @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate end) {
        log.info("订单统计：{}，{}", begin, end);
        OrderReportVO orderReportVO = reportService.getOrdersStatistics(begin, end);
        return Result.success(orderReportVO);
    }
```



#### 4.2.3 Service层接口

**在ReportService接口中声明getOrderStatistics方法：**

```java
    /**
     * 统计指定时间区间内的订单数据
     */
    OrderReportVO getOrdersStatistics(LocalDate begin, LocalDate end);
```



#### 4.2.4 Service层实现类

**在ReportServiceImpl实现类中实现getOrderStatistics方法：**

```java
    /**
     * 统计指定时间区间内的订单数据
     */
    public OrderReportVO getOrdersStatistics(LocalDate begin, LocalDate end) {
        // 构造日期 list
        List<LocalDate> dateList = new ArrayList();
        dateList.add(begin);
        while (!end.equals(begin)) {
            begin = begin.plusDays(1);
            dateList.add(begin);
        }

        // 构造每天总订单数 list
        List<Integer> orderCountList = new ArrayList<>();
        // 构造每天有效订单数 list
        List<Integer> validOrderCountList = new ArrayList<>();

        for (LocalDate date : dateList) {
            LocalDateTime beginTime = LocalDateTime.of(date, LocalTime.MIN);
            LocalDateTime endTime = LocalDateTime.of(date, LocalTime.MAX);

            Map map = new HashMap();
            map.put("begin", beginTime);
            map.put("end", endTime);
            Integer orderCount = orderMapper.countByMap(map);
            map.put("status", Orders.COMPLETED);
            Integer validOrderCount = orderMapper.countByMap(map);

            orderCountList.add(orderCount);
            validOrderCountList.add(validOrderCount);
        }

        // 计算时间区间内的总订单数量
        Integer totalOrderCount = orderCountList.stream().reduce(Integer::sum).get();
        // 计算时间区间内的有效订单数量
        Integer validOrderCount = validOrderCountList.stream().reduce(Integer::sum).get();
        // 订单完成率
        Double orderCompletionRate = 0.0;
        if (totalOrderCount != 0) {
            orderCompletionRate = validOrderCount * 1.0 / totalOrderCount;
        }

        return OrderReportVO.builder()
                .dateList(StringUtils.join(dateList, ","))
                .orderCountList(StringUtils.join(orderCountList, ","))
                .validOrderCountList(StringUtils.join(validOrderCountList, ","))
                .totalOrderCount(totalOrderCount)
                .validOrderCount(validOrderCount)
                .orderCompletionRate(orderCompletionRate)
                .build();
    }
```



#### 4.2.5 Mapper层

**在OrderMapper接口中声明countByMap方法：**

```java
    /**
     * 根据 map 中的 begin、end、status 等条件统计订单数据
     */
    Integer countByMap(Map map);
```

**在OrderMapper.xml文件中编写动态SQL：**

```java
    <select id="countByMap" resultType="java.lang.Integer">
        select count(id) from orders
        <where>
            <if test="begin != null">
                and order_time &gt;= #{begin}
            </if>
            <if test="end != null">
                and order_time &lt;= #{end}
            </if>
            <if test="status != null">
                and status = #{status}
            </if>
        </where>
    </select>
```



### 4.3 功能测试

可以通过如下方式进行测试：

- 接口文档测试
- 前后端联调

重启服务，直接采用前后端联调测试。

进入数据统计模块

**1). 查看近7日订单统计**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081849650.png" alt="image-20230107202854533" style="zoom:50%;" /> 

进入开发者模式，查看返回数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081849031.png" alt="image-20230107202953128" style="zoom:50%;" /> 



**2). 查看近30日订单统计**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081849853.png" alt="image-20230107203025165" style="zoom:50%;" /> 

进入开发者模式，查看返回数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606081849312.png" alt="image-20230107203127308" style="zoom:50%;" /> 

也可通过断点方式启动，查看每步执行情况。



## 5. 销量排名Top10

### 5.1 需求分析和设计

#### 5.1.1 产品原型

所谓销量排名，销量指的是商品销售的数量。项目当中的商品主要包含两类：一个是**套餐**，一个是**菜品**，所以销量排名其实指的就是菜品和套餐销售的数量排名。通过柱形图来展示销量排名，这些销量是按照降序来排列，并且只需要统计销量排名前十的商品。

**原型图：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606082013030.png" alt="image-20230107203622747" style="zoom:50%;" /> 

**业务规则：**

- 根据时间选择区间，展示销量前10的商品（包括菜品和套餐）
- 基于可视化报表的柱状图降序展示商品销量
- 此处的销量为商品销售的份数



#### 5.1.2 接口设计

根据上述原型图设计接口。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606082013109.png" alt="image-20230107203720606" style="zoom:50%;" /> <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606082013242.png" alt="image-20230107203730681" style="zoom:50%;" /> 



### 5.2 代码开发

#### 5.2.1 VO设计

**根据销量排名接口的返回结果设计VO：**

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606082013134.png" alt="image-20230107204028895" style="zoom:50%;" /> 

在sky-pojo模块，SalesTop10ReportVO.java已定义

```java
package com.sky.vo;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.io.Serializable;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class SalesTop10ReportVO implements Serializable {

    //商品名称列表，以逗号分隔，例如：鱼香肉丝,宫保鸡丁,水煮鱼
    private String nameList;

    //销量列表，以逗号分隔，例如：260,215,200
    private String numberList;

}
```



#### 5.2.2 Controller层

**在ReportController中根据销量排名接口创建top10方法：**

```java
    /**
     * 销量排名 top10 统计
     */
    @GetMapping("/top10")
    @ApiOperation(value = "销量排名 top10 统计")
    public Result<SalesTop10ReportVO> top10(@DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate begin,
                                            @DateTimeFormat(pattern = "yyyy-MM-dd") LocalDate end) {
        log.info("销量排名 top10 统计：{}，{}", begin, end);
        SalesTop10ReportVO salesTop10ReportVO = reportService.getSalesTop10(begin, end);
        log.info("从{}到{}的销量排名统计结果：{}", begin, end, salesTop10ReportVO);
        return Result.success(salesTop10ReportVO);
    }
```



#### 5.2.3 Service层接口

**在ReportService接口中声明getSalesTop10方法：**

```java
    /**
     * 统计指定时间区间内的销量排名 top10
     */
    SalesTop10ReportVO getSalesTop10(LocalDate begin, LocalDate end);
```



#### 5.2.4 Service层实现类

**在ReportServiceImpl实现类中实现getSalesTop10方法：**

```java
    /**
     * 统计指定时间区间内的销量排名 top10
     */
    public SalesTop10ReportVO getSalesTop10(LocalDate begin, LocalDate end) {
        // 转换时间格式
        LocalDateTime beginTime = LocalDateTime.of(begin, LocalTime.MIN);
        LocalDateTime endTime = LocalDateTime.of(end, LocalTime.MAX);
        
        List<GoodsSalesDTO> salesTop10 = orderMapper.getSalesTop10(beginTime, endTime);

        List<String> nameList = salesTop10.stream().map(GoodsSalesDTO::getName).collect(Collectors.toList());
        List<Integer> numberList = salesTop10.stream().map(GoodsSalesDTO::getNumber).collect(Collectors.toList());

        return SalesTop10ReportVO.builder()
                .nameList(StringUtils.join(nameList, ","))
                .numberList(StringUtils.join(numberList, ","))
                .build();
    }
```



#### 5.2.5 Mapper层

**在OrderMapper接口中声明getSalesTop10方法：**

```java
    /**
     * 统计指定时间区间内的销量排名 top10
     */
    List<GoodsSalesDTO> getSalesTop10(LocalDateTime begin, LocalDateTime end);
```

**在OrderMapper.xml文件中编写动态SQL：**

```xml
    <select id="getSalesTop10" resultType="com.sky.dto.GoodsSalesDTO">
        select od.name, sum(od.number) number from order_detail od, orders o
        where od.order_id = o.id and o.status = 5
        <if test="begin != null">
            and o.order_time &gt;= #{begin}
        </if>
        <if test="end != null">
            and o.order_time &lt;= #{end}
        </if>
        group by od.name order by number desc limit 0, 10
    </select>
```



### 5.3 功能测试

可以通过如下方式进行测试：

- 接口文档测试
- 前后端联调

重启服务，直接采用前后端联调测试。

**查看近30日销量排名Top10统计**

若查询的某一段时间没有销量数据，则显示不出效果。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606082013756.png" alt="image-20230107210518821" style="zoom:50%;" /> 

进入开发者模式，查看返回数据

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202606082013292.png" alt="image-20230107210711326" style="zoom:50%;" /> 

也可通过断点方式启动，查看每步执行情况。


