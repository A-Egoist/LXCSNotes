# 苍穹外卖



## 启动项目

### step1：启动 MySQL

```cmd
net start mysql
```

### step2：启动前端

运行 `nginx-1.20.2/nginx.exe`

### step3：启动 Redis

```cmd
.\redis-server.exe  .\redis.windows.conf
```

### step4：在 IDEA 中启动项目

### step5：启动 DataGrip

### step6：启动微信开发者工具



## 笔记

[苍穹外卖中的技术总结](./技术总结.md)



## 讲义整理

[苍穹外码-Day01](./苍穹外卖-Day01.md)：项目效果展示、软件开发整体介绍、苍穹外卖项目介绍、开发环境搭建、接口文档介绍、Swagger 介绍

[苍穹外码-Day02](./苍穹外卖-Day02.md)：新增员工、员工分页查询、启用禁用员工账号、编辑员工、导入分类模块功能代码

[苍穹外码-Day03](./苍穹外卖-Day03.md)：菜品相关功能

[苍穹外码-Day04](./苍穹外卖-Day04.md)：套餐相关功能

至此，分类管理、员工管理、菜品管理、套餐管理这四个功能基本完成。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604211727851.png" alt="image-20260421172648033" style="zoom:67%;" />

[苍穹外码-Day05](./苍穹外卖-Day05.md)：Redis

[苍穹外码-Day06](./苍穹外卖-Day06.md)：微信小程序、微信登录

[苍穹外码-Day07](./苍穹外卖-Day07.md)：使用 Redis 缓存菜品数据、使用 Spring Cache 来简化 Redis 的使用、购物车相关功能实现

[苍穹外码-Day08](./苍穹外卖-Day08.md)：地址簿功能实现、用户下单功能实现、微信支付功能了解、

[苍穹外码-Day09](./苍穹外卖-Day09.md)：用户端订单相关操作、商家端订单管理功能实现、校验收货地址是否超出配送范围

[苍穹外码-Day10](./苍穹外卖-Day10.md)：通过 Spring Task 实现定时任务、通过 WebSocket 实现客户端和服务端的全双工通信、实现来单提醒和用户催单功能

[苍穹外码-Day11](./苍穹外卖-Day11.md)：数据统计相关功能实现

[苍穹外码-Day12](./苍穹外卖-Day12.md)：工作台相关接口实现、通过 Apache POI 实现 Excel 文件处理、实现导出数据报表功能、文件输入输出流

