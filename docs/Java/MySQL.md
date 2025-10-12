# MySQL

![image-20251011110920673](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111109684.png)

![image-20251011111043179](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111110111.png)

## MySQL 概述

### 安装

![image-20251011111653759](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111116015.png)

[MySQL安装文档](https://heuqqdmbyk.feishu.cn/wiki/ZRSFwACsRiBD2NkV7bmcrJhInme)

![image-20251011111841255](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111118178.png)

![image-20251011111859746](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111119579.png)



### 数据模型

![image-20251011112037037](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111120947.png)

![image-20251011112153342](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111121079.png)



## SQL 语句

![image-20251011112400204](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111124244.png)

![image-20251011113313753](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111133176.png)

![image-20251011113344102](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111133044.png)



### DDL(Data Definition Language)

![image-20251011112718927](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111127801.png)

![image-20251011173521074](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111735011.png)

![image-20251011173600140](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111736093.png)

:bulb: ​在定义主键的时候指定关键字 `auto_increment` 可以实现主键自增的效果。

一个字段可以添加多个约束，多个约束之间使用空格分开



**数据类型**

MySQL 中的数据类型有很多，主要分为三类：数值类型、字符串类型、日期时间类型。

数值类型的选取原则：在满足业务需求的前提下，尽可能选择占用磁盘空间小的数据类型。

此外，数值类型还区分有符号（`signed`）和无符号（`unsigned`）。

![image-20251011180109056](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111801980.png)



**案例**

![image-20251011180148519](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111801548.png)

![image-20251011180216888](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111802853.png)

创建表的时候，一般有三个默认字段：

*   id 主键
*   create_time 创建时间
*   update_time 修改时间



![image-20251011180943246](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111809870.png)



### DML(Data Manipulation Language)

![image-20251011181241516](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111812441.png)

![image-20251011181410757](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111814656.png)

![image-20251011181437503](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111814652.png)

![image-20251011181528521](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111815388.png)



### DQL(Data Query Language)

![image-20251011181647311](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111816106.png)

![image-20251011181735344](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111817120.png)

#### 基本查询

![image-20251011181847382](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111818324.png)

#### 条件查询

![image-20251011181944933](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111819692.png)

:bulb: 模糊匹配中的通配符：

*   `%` 任意个字符
*   `_` 一个字符

#### 分组查询

![image-20251011182256140](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111822897.png)

![image-20251011182412574](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111824677.png)

![image-20251011182554418](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111825876.png)

DQL 语句中 where 和 having 的区别：

*   执行时机不同（where -> group by -> having）
*   判断条件不同（having 后可以用聚合函数，where 不可以）

[MySQL-SQL-DQL-分组查询](https://www.bilibili.com/video/BV1yGydYEE3H?spm_id_from=333.788.player.switch&vd_source=f4cc25a44af6631d6f4db023b3bb88e4&p=60)

#### 排序查询

![image-20251011182842131](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111828016.png)

#### 分页查询

![image-20251011182946963](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510111829724.png)

MySQL 中的分页查询（分页查询是方言，不同数据库的分页查询方式不同）：

*   语法：`limit 起始索引,每页展示记录数`
*   注意：项目开发中，前端传递过来的是页码，需要转换为起始索引
*   公式：（页码-1） * 每页展示记录数



## 多表关系

### 一对多（多对一）

![image-20251012220535465](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510122205417.png)





### 一对一







### 多对多





### 案例





## 多表设计



## 多表查询



## 事务

