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

外键约束

物理外键与逻辑外键



### 一对一

一对一关系表在实际开发中应用起来比较简单，通常是用来做单表的拆分，也就是将一张大表拆分成两张小表，将大表中的一些基础字段放在一张表当中，将其他的字段放在另外一张表当中，以此来提高数据的操作效率。

一对一的应用场景： 用户表(基本信息+身份信息)

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510131933819.png)

-   基本信息：用户的ID、姓名、性别、手机号、学历
-   身份信息：民族、生日、身份证号、身份证签发机关，身份证的有效期(开始时间、结束时间)

如果在业务系统当中，对用户的基本信息查询频率特别的高，但是对于用户的身份信息查询频率很低，此时出于提高查询效率的考虑，我就可以将这张大表拆分成两张小表，第一张表存放的是用户的基本信息，而第二张表存放的就是用户的身份信息。他们两者之间一对一的关系，一个用户只能对应一个身份证，而一个身份证也只能关联一个用户。

那么在数据库层面怎么去体现上述两者之间是一对一的关系呢？

其实一对一我们可以看成一种特殊的一对多。一对多我们是怎么设计表关系的？是不是在多的一方添加外键。同样我们也可以通过外键来体现一对一之间的关系，我们只需要在任意一方来添加一个外键就可以了。

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510131933089.png)

SQL脚本：

```SQL
-- 用户基本信息表
create table tb_user(
    id int unsigned  primary key auto_increment comment 'ID',
    name varchar(10) not null comment '姓名',
    gender tinyint unsigned not null comment '性别, 1 男  2 女',
    phone char(11) comment '手机号',
    degree varchar(10) comment '学历'
) comment '用户基本信息表';
-- 测试数据
insert into tb_user values (1,'白眉鹰王',1,'18812340001','初中'),
                        (2,'青翼蝠王',1,'18812340002','大专'),
                        (3,'金毛狮王',1,'18812340003','初中'),
                        (4,'紫衫龙王',2,'18812340004','硕士');

-- 用户身份信息表
create table tb_user_card(
    id int unsigned  primary key auto_increment comment 'ID',
    nationality varchar(10) not null comment '民族',
    birthday date not null comment '生日',
    idcard char(18) not null comment '身份证号',
    issued varchar(20) not null comment '签发机关',
    expire_begin date not null comment '有效期限-开始',
    expire_end date comment '有效期限-结束',
    user_id int unsigned not null unique comment '用户ID',
    constraint fk_user_id foreign key (user_id) references tb_user(id)
) comment '用户身份信息表';
-- 测试数据
insert into tb_user_card values (1,'汉','1960-11-06','100000100000100001','朝阳区公安局','2000-06-10',null,1),
        (2,'汉','1971-11-06','100000100000100002','静安区公安局','2005-06-10','2025-06-10',2),
        (3,'汉','1963-11-06','100000100000100003','昌平区公安局','2006-06-10',null,3),
        (4,'回','1980-11-06','100000100000100004','海淀区公安局','2008-06-10','2028-06-10',4);
```

:bulb: **一对一 ：在任意一方加入外键，关联另外一方的主键，并且设置外键为唯一的(UNIQUE)**



### 多对多

多对多的关系在开发中属于也比较常见的。比如：学生和老师的关系，一个学生可以有多个授课老师，一个授课老师也可以有多个学生。在比如：学生和课程的关系，一个学生可以选修多门课程，一个课程也可以供多个学生选修。

案例：学生与课程的关系

-   关系：一个学生可以选修多门课程，一门课程也可以供多个学生选择
-   实现关系：建立第三张中间表，中间表至少包含两个外键，分别关联两方主键

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510131934334.png)

SQL脚本：

```SQL
-- 学生表
create table tb_student(
    id int auto_increment primary key comment '主键ID',
    name varchar(10) comment '姓名',
    no varchar(10) comment '学号'
) comment '学生表';
-- 学生表测试数据
insert into tb_student(name, no) values ('黛绮丝', '2000100101'),
                                        ('谢逊', '2000100102'),
                                        ('殷天正', '2000100103'),
                                        ('韦一笑', '2000100104');

-- 课程表
create table tb_course(
   id int auto_increment primary key comment '主键ID',
   name varchar(10) comment '课程名称'
) comment '课程表';
-- 课程表测试数据
insert into tb_course (name) values ('Java'), ('PHP'), ('MySQL') , ('Hadoop');

-- 学生课程表（中间表）
create table tb_student_course(
   id int auto_increment comment '主键' primary key,
   student_id int not null comment '学生ID',
   course_id  int not null comment '课程ID',
   constraint fk_courseid foreign key (course_id) references tb_course (id),
   constraint fk_studentid foreign key (student_id) references tb_student (id)
)comment '学生课程中间表';

-- 学生课程表测试数据
insert into tb_student_course(student_id, course_id) values (1,1),(1,2),(1,3),(2,2),(2,3),(3,4);
```

:bulb: ​**多对多 ：需要建立一张中间表，中间表中有两个外键字段，分别关联两方的主键。**



## 多表查询

多表查询可以分为：

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510132307568.png)

1.  连接查询
    1.  内连接：相当于查询A、B交集部分数据
    2.  外连接
        -   左外连接：查询左表所有数据(包括两张表交集部分数据)
        -   右外连接：查询右表所有数据(包括两张表交集部分数据)
2.  子查询

### 内连接

内连接查询：查询两表或多表中交集部分数据。

内连接从语法上可以分为：

-   隐式内连接
-   显式内连接

**隐式内连接语法：**

```SQL
select  字段列表   from   表1 , 表2   where  条件 ... ;
```

**显式内连接语法：**

```SQL
select  字段列表   from   表1  [ inner ]  join 表2  on  连接条件 ... ;
```

案例1：查询所有员工的ID，姓名，及所属的部门名称

-    隐式内连接实现

    ```SQL
    select emp.id, emp.name, dept.name from emp , dept where emp.dept_id = dept.id;
    ```

-   显式内连接实现

    ```SQL
    select emp.id, emp.name, dept.name from emp inner join dept on emp.dept_id = dept.id;
    ```

案例2：查询 性别为男, 且工资 高于8000 的员工的ID, 姓名, 及所属的部门名称

-   隐式内连接实现

    ```SQL
    select emp.id, emp.name, dept.name from emp , dept where emp.dept_id = dept.id and emp.gender = 1 and emp.salary > 8000;
    ```

-   显式内连接实现

    ```SQL
    select emp.id, emp.name, dept.name from emp inner join dept on emp.dept_id = dept.id where emp.gender = 1 and emp.salary > 8000;
    ```

:warning: 在多表联查时，我们指定字段时，需要在字段名前面加上表名，来指定具体是哪一张的字段。 如：emp.dept_id



**给表起别名简化书写：**

```SQL
select  字段列表 from 表1 as 别名1 , 表2 as  别名2  where  条件 ... ;

select  字段列表 from 表1 别名1 , 表2  别名2  where  条件 ... ;  -- as 可以省略
```

使用了别名的多表查询：

```SQL
select e.id, e.name, d.name from emp as e , dept as d where e.dept_id = d.id and e.gender = 1 and e.salary > 8000;
```

:warning: ​一旦为表起了别名，就不能再使用表名来指定对应的字段了，此时只能够使用别名来指定字段。



### 外连接

外连接分为两种：左外连接 和 右外连接。

**左外连接语法：**

```SQL
select  字段列表   from   表1  left  [ outer ]  join 表2  on  连接条件 ... ;
```

左外连接相当于查询表1(左表)的所有数据，当然也包含表1和表2交集部分的数据。

**右外连接语法：**

```SQL
select  字段列表   from   表1  right  [ outer ]  join 表2  on  连接条件 ... ;
```

右外连接相当于查询表2(右表)的所有数据，当然也包含表1和表2交集部分的数据。

案例1：查询员工表 所有 员工的姓名, 和对应的部门名称 (左外连接)

```SQL
-- 左外连接：以left join关键字左边的表为主表，查询主表中所有数据，以及和主表匹配的右边表中的数据
select e.name , d.name  from emp as e left join dept as d on e.dept_id = d.id ;
```

案例2：查询部门表 所有 部门的名称, 和对应的员工名称 (右外连接)

```SQL
-- 右外连接：以right join关键字右边的表为主表，查询主表中所有数据，以及和主表匹配的左边表中的数据
select e.name , d.name from emp as e right join dept as d on e.dept_id = d.id;
```

案例3：查询工资 高于8000 的 所有员工的姓名, 和对应的部门名称 (左外连接)

```SQL
select e.name , d.name  from emp as e left join dept as d on e.dept_id = d.id where e.salary > 8000;
```

:warning: ​左外连接和右外连接是可以相互替换的，只需要调整连接查询时SQL语句中表的先后顺序就可以了。而我们在日常开发使用时，更偏向于左外连接。



### 子查询

SQL语句中嵌套select语句，称为嵌套查询，又称子查询。

```SQL
SELECT  *  FROM   t1   WHERE  column1 =  ( SELECT  column1  FROM  t2 ... );
```

子查询外部的语句可以是insert / update / delete / select 的任何一个，最常见的是 select。



根据子查询结果的不同分为：

1.  标量子查询（子查询结果为单个值 [一行一列]）
2.  列子查询（子查询结果为一列，但可以是多行）
3.  行子查询（子查询结果为一行，但可以是多列）
4.  表子查询（子查询结果为多行多列[相当于子查询结果是一张表]）

子查询可以书写的位置：

1.  where之后
2.  from之后
3.  select之后

:bulb: 子查询的要点是，先对需求做拆分，明确具体的步骤，然后再逐条编写SQL语句。 最终将多条SQL语句合并为一条。



#### 标量子查询

子查询返回的结果是单个值(数字、字符串、日期等)，最简单的形式，这种子查询称为**标量子查询**。

常用的操作符： =   <>   >    >=    <   <=   

案例1：查询 最早入职 的员工信息

```SQL
-- 1. 查询最早的入职时间
select min(entry_date) from emp;  -- 结果: 2000-01-01

-- 2. 查询入职时间 = 最早入职时间的员工信息
select * from emp where entry_date = '2000-01-01';

-- 3. 合并为一条SQL
select * from emp where entry_date = (select min(entry_date) from emp);
```

案例2：查询在 阮小五 入职之后入职的员工信息

```SQL
-- 1. 查询 "阮小五" 的入职日期
select entry_date from emp where name = '阮小五'; -- 结果: 2015-01-01

-- 2. 根据上述查询到的这个入职日期, 查询在该日期之后入职的员工信息
select * from emp where entry_date > '2015-01-01';

-- 3. 合并SQL为一条SQL
select * from emp where entry_date > (select entry_date from emp where name = '阮小五');
```



#### 列子查询

子查询返回的结果是一列(可以是多行)，这种子查询称为列子查询。

常用的操作符：

| 操作符 | 描述                         |
| ------ | ---------------------------- |
| in     | 在指定的集合范围之内，多选一 |
| not in | 不在指定的集合范围之内       |

案例1：查询 "教研部" 和 "咨询部" 的所有员工信息

```SQL
-- 1. 查询 "教研部" 和 "咨询部" 的部门ID
select id from dept where name = '教研部' or name = '咨询部'; -- 结果: 3,2

-- 2. 根据上面查询出来的部门ID, 查询员工信息
select * from emp where dept_id in(3,2);

-- 3. 合并SQL为一条SQL语句
select * from emp where dept_id in (select id from dept where name = '教研部' or name = '咨询部');
```



#### 行子查询

子查询返回的结果是一行(可以是多列)，这种子查询称为行子查询。

常用的操作符：= 、<> 、IN 、NOT IN

案例1：查询与 "李忠" 的薪资 及 职位都相同的员工信息

```SQL
-- 1. 查询 "李忠" 的薪资和职位
select salary , job from emp where name = '李忠'; -- 结果: 5000, 5

-- 2. 根据上述查询到的薪资和职位 , 查询对应员工的信息
select * from emp where (salary, job) = (5000,5);

-- 3. 将两条SQL合并为一条SQL
select * from emp where (salary, job) = (select salary , job from emp where name = '李忠');
```



#### 表子查询

子查询返回的结果是多行多列，常作为临时表，这种子查询称为**表子查询**。

案例：*获取每个部门中薪资最高的员工信息*

```SQL
-- a. 获取每个部门的最高薪资
select dept_id, max(salary) from emp group by dept_id;

-- b. 查询每个部门中薪资最高的员工信息
select * from emp e , (select dept_id, max(salary) max_sal from emp group by dept_id) a
    where e.dept_id = a.dept_id and e.salary = a.max_sal;
```



## 事务

