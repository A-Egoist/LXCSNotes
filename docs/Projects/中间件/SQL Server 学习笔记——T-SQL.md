# SQL学习笔记
## SQL概述
SQL按其功能可以分为三大部分：
<font color=green size=5 >数据定义</font>功能、<font color=green size=5 >数据操纵</font>功能和<font color=green size=5 >数据控制</font>功能
DDL、DML、DCL

SQL功能|命令动词
--|--
数据定义|CREATE、ALTER、DROP
数据操纵|SELECT、INSERT、UPDATE、DELETE
数据控制|GRANT、REVOKE

## SQL数据定义
在SQL Server中，我们点击“新建查询”，在弹出的窗口中键入sql语言
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347217.png)

#### 创建数据库
基本格式：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347137.png)
样例：

```sql
CREATE DATABASE Demo
ON
(NAME=Demo_data,--主文件名称
FILENAME='D:\Test\Demo_data.mdf',--主文件的绝对路径
SIZE=1,--主文件的大小
MAXSIZE=10,--最大值
FILEGROWTH=1--数值型增长方式 
--FILEGROWTH=10%--百分比增长
)
LOG ON
(NAME=Demo_log,--日志文件名称
FILENAME='D:\Test\Demo_log.ldf',--日志文件的绝对路径
SIZE=1,--日志文件的大小
MAXSIZE=10,--最大值
FILEGROWTH=1--数值型增长方式 
)
```
效果：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347307.png)
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347701.png)

#### 修改数据库
修改数据库名：
```sql
ALTER DATABASE Demo
MODIFY NAME=New_Demo
```
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347089.png)
修改文件名：

```sql
ALTER DATABASE New_Demo MODIFY FILE(NAME=Demo_data,NEWNAME=Demo)
```
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347750.png)

添加新文件：
```sql
ALTER DATABASE New_Demo
ADD FILE
(NAME = Demo_ndf,
FILENAME = 'D:\Test\Demo_ndf.ndf',
SIZE = 5MB,
MAXSIZE = 10MB,
FILEGROWTH = 1MB
)
```
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347984.png)
添加日志文件

```sql
ALTER DATABASE New_Demo
ADD LOG FILE
(NAME = Demo_new_log,
FILENAME = 'D:\Test\Demo_new_log.ldf',
SIZE = 1MB,
MAXSIZE = 10MB,
FILEGROWTH = 1MB
)
```
#### 删除数据库
```sql
DROP DATABASE 数据库1[,数据库2，数据库3]--可以同时删除多个数据库
--但是用sql语句删除数据库的时候不会有确认信息，所以请小心使用
```
#### 创建基本表
定义基本表的一般格式：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347204.png)
<font color=red size=6>warning</font>
在SQL Server 建立新建查询的时候注意手动选择数据库
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347558.png)
样例：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347090.png)
根据上图所示内容，我们可以创建一个Student表：

```sql
CREATE TABLE Student
(
Sno char(7),
Sname char(10),
Ssex char(2),
Sage tinyint,
Sdept char(20)
)
```
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347254.png)
在上面的例子中，我们创建表格的时候没有确立约束条件。
一个表的约束条件分为两类：<font color=blue size=5>列级约束条件</font>和<font color=blue size=5>表级约束条件</font>。

##### 列级约束条件
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347699.png)
```sql
Sname char(7) NOT NULL--取值非空
Sage tinyint DEFAULT 18--默认值约束
Sno char(7) UNIQUE--限制列取值不重复
Sdept char(20) CHECK(Sdept='CS' OR Sdept='IS')--限制列的取值范围
Sno char(7) PRIMARY KEY--指定本列为主码
Sdept char(20) FOREIGN KEY (Sdept) REFERENCES SC(Sdept)--外码约束
```
##### 表级约束条件
UNIQUE表级约束：
```sql
UNIQUE(Sno,Sname)--表示(Sno,Sname)这样的组合不允许重复
--但是在Sno或Sname的列中可以重复
```
PRIMARY表级约束：
```sql
PRIMARY KEY(Sno)--和在Sno进行列定义相同
PRIMARY KEY(Sno,Sname)--以(Sno,Sname)这样的组合作为表的主码
```
##### 实例
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347336.png)
```sql
CREATE TABLE Student
(
Sno char(7) PRIMARY KEY,
Sname char(10) NOT NULL,
Ssex char(2) CHECK(Ssex='男' OR Ssex='女'),
Sage tinyint CHECK(Sage>=15 AND Sage<=45),
Sdept char(20) DEFAULT '计算机系'
)
```
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347812.png)

![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347040.png)
```sql
CREATE TABLE Course
(
Cno char(10),
Cname char(20) NOT NULL,
Ccredit tinyint CHECK(Ccredit>0),
Semester tinyint CHECK(Semester>0),
Period int CHECK(Period>0),
PRIMARY KEY(Cno)
)
```
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347760.png)

![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347504.png)
```sql
CREATE TABLE SC
(
Sno char(7) NOT NULL,
Cno char(10) NOT NULL,
Grade tinyint,
CHECK(Grade>=0 AND Grade <=100),
PRIMARY KEY(Sno,Cno),
FOREIGN KEY(Sno) REFERENCES Student(Sno),
FOREIGN KEY(Cno) REFERENCES Course(Cno)
)
```
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347750.png)

#### 修改基本表
在定义完表之后，我们还可能需要修改表的结构，修改表的方法如下：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347221.png)

```sql
--在SC表中添加XKLB列--添加新列
ALTER TABLE SC
ADD XKLB char(4)
--将XKLB的类型改为char(6)--修改列定义
ALTER TABLE SC
ALTER COLUMN XKLB char(6)
--删除Course表的Period列--删除列
ALTER TABLE Course
DROP COLUMN Period
```
约束添加：
```sql
--添加主码约束
ALTER TABLE SC
ADD CONSTRAINT PK_SC PRIMARY KEY(Sno)--ADD CONSTRAINT 约束名 PRIMARY KEY(列名)
ADD CONSTRAINT PK_SC PRIMARY KEY(Sno,Cno)--表级约束

--添加唯一性约束
ALTER TABLE Course
ADD CONSTRAINT UK_C UNIQUE(Cno)--ADD CONSTRAINT 约束名 UNIQUE(列名[,列名1,列名2···])

--添加外键约束
ALTER TABLE SC
ADD CONSTRAINT FK_SC FOREIGN KEY(Sno) REFERENCES Student(Sno)--ADD CONSTRAINT 约束名FOREIGN KEY(列名) REFERENCES 引用表名(列名)

--添加默认值约束
ALTER TABLE SC
ADD CONSTRAINT DF_SC DEFAULT 1 FOR Grade--ADD CONSTRAINT 约束名 DEFAULT 默认值 FOR 列名

--添加检查约束
ALTER TABLE Student
ADD CONSTRAINT CK_S CHECK(Sage>15 AND Sage<45)--ADD CONSTRAINT 约束名 CHECK(约束表达式)
```
#### 删除基本表
```sql
DROP TABLE 表1[,表2,表3]
DROP TABLE Student
```
## SQL数据操纵
#### 数据查询
查询语句是数据库使用中最基本和最重要的语句之一，其功能是从数据中检索满足条件的数据。
数据来源可以是一张表、多张表或者视图。
查询结果是关系。
语句格式：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062347408.png)

##### 简单查询
```sql
--查询指定列
SELECT Sno,Sname FROM Student
--查询所有列
SELECT * FROM Student
--查询经过计算的列
SELECT Sname,2020-Sage FROM Student--第二列列名为空
```
##### 改变列标题
①：`列名 | 表达式 [AS] 列别名`
②：`列别名 = 列名 | 表达式`
```sql
SELECT Sname 姓名,2020-Sage AS 出身年份 FROM Student
```
 ##### 选择表中若干行
```sql
SELECT Sno FROM SC
--等价于
SELECT ALL Sno FROM SC
--在SELECT中缺省则为ALL
--DISTINCT关键字可以去重
SELECT DISTINCT Sno FROM SC
```
##### `WHERE`用于查询满足条件的元组
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062348540.png)
```sql
--比较
SELECT Sname FROM Student WHERE Sdept='IS'
SELECT Sname,Sage FROM Student WHERE Sage<20
SELECT Sname,Sage FROM Student WHERE NOT Sage>=20
--范围
SELECT Sname FROM Student WHERE Sage BETWEEN 20 AND 23
SELECT Sname FROM Student WHERE Sage>=20 AND Sage<=23
SELECT Sname FROM Student WHERE Sage NOT BETWEEN 20 AND 23
SELECT Sname FROM Student WHERE Sage<20 OR Sage>23
--集合
SELECT Sname FROM Student WHERE Sdept IN('IS','MA','CS')
SELECT Sname FROM Student WHERE Sdept NOT IN('IS','MA','CS')
```
##### 字符串匹配
在字符匹配中有四种通配符：
`_`：匹配任意一个字符
`%`：匹配0个或多个字符
`[]`：匹配`[]`中的任意一个字符
`[^]`：不匹配`[]`中的任意一个字符
```sql
SELECT * FROM Student WHERE Sno LIKE '200215121'
SELECT * FROM Student WHERE Sname LIKE '王%'
SELECT * FROM Student WHERE Sname LIKE '[张刘李]%'
SELECT * FROM Student WHERE Sno LIKE '%[^235]'
SELECT * FROM Student WHERE Sno NOT LIKE '%[235]'
```
##### 涉及空值的查询
空值(`NULL`)在数据库中有特殊的含义，代表不确定的值
判断某个值是否为`NULL`，只能用专门的判断`NULL`值的子句来完成`IS NULL`、`IS NOT NULL`
```sql
SELECT Sno FROM SC WHERE Grade IS NULL
SELECT Sno FROM SC WHERE Grade IS NOT NULL
```
##### 多重条件查询
运用`AND`和`OR`俩简介查询多个查询条件
其中`AND`的优先级高于`OR`
```sql
SELECT Sname FROM Student WHERE Sdept='IS' AND Sage<20
```
##### `ORDER BY`
`ORDER BY <列名> [ASC | DESC][,<列名>···]`
可以按一个或多个属性列排序
`ASC`：升序、`DESC`降序、缺省值为升序
当排序列含空值时：
`ASC`：排序列为空值的元组最先显示
`DESC`：排序列为空值的元组最后显示
```sql
SELECT Sno,Grade FROM SC WHERE Cno='3' ORDER BY Grade DESC
```
##### TOP限制结果集
```sql
SELECT TOP 3 Sname,Sage,Sdept FROM Student ORDER BY Sage DESC
```
##### 聚集函数
聚集函数也称为集合函数或聚合函数、计算函数，其作用是对一组值进行计算并返回一个单值。SQL提供的聚合函数有：
`COUNT(*)`：统计表中元组个数
`COUNT(<列名>)`：统计本列列值个数
`SUM(<列名>)`：计算列值综合
`AVG(<列名>)`：计算列值平均值
`MAX(<列名>)`：求列值最大值
`MIN(<列名>)`：求列值最小值
除`COUNT(*)`外，其他函数在计算过程中均忽略`NULL`值
```sql
SELECT COUNT(*) 总人数 FROM Student
SELECT COUNT(Sno) 选课人数 FROM SC
SELECT SUM(Grade) 总成绩 FROM SC WHERE Sno='95122'
SELECT AVG(Grade) 平均成绩 FROM SC WHERE Cno='C01'
SELECT MAX(Grade) 最高分 FROM SC WHERE Cno='C01'
SELECT MIN(Grade) 最低分 FROM SC WHERE Cno='C01'
```
<font color=red>聚合函数不能出现在WHERE子句中</font>

##### `GROUP BY`
`GROUP BY`可将计算控制在组一级，分组的目的是细化计算函数的作用对象
分组语句位置在`WHERE`子句的后边，一般形式为：
`GROUP BY <分组依据列>`
`[HAVING <组过滤条件>]`

```sql
SELECT Cno 课程号,COUNT(Sno) 选课人数 FROM SC GROUP BY Cno
SELECT Sno 学号,COUNT(Cno) 选课门数,AVG(Grade) 平均成绩 
FROM SC GROUP BY Sno
```

<font size=6 color=blue>暂时只学到了这里，之后再更新o(╥﹏╥)o</font>
##### 其他
#### 数据更改
## SQL数据控制

