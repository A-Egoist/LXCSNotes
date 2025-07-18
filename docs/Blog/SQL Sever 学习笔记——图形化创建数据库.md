# SQL Sever Management Studio基础
## 启动连接到数据库服务器
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062345502.png)
连接服务器之后可以看到界面的左侧如图所示：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062345024.png)
展开数据库选项卡后，可以看到已经存在的数据库：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062345825.png)

## 创建数据库
右键单击“数据库”选项，选择“新建数据库”选项：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062345642.png)
我们根据需求依次修改“常规”、“选项”、“文件组”等信息。

### SQL Server 数据库种类及文件
在上面新建数据库的过程中，我们需要对数据库文件进行命名，在此之前我们就需要了解到数据库文件的种类。
文件分为两种，分别是数据文件(.mdf | .ndf)和日志文件(.ldf)，其中.mdf文件是主数据文件，一个数据库中有且仅有一个.mdf文件；.ndf是辅助数据文件，一个数据库中可以有零个或多个；.ldf是日志文件，其用于存放对数据库的操作记录，一个数据库可以包含一个或多个。
### 数据库文件组
1）<font color=red size=4 >主文件组</font>。包含主数据文件和未指明组的其他文件。
2）<font color=red size=4 >次文件组</font>。也称用户自定义文件组，是由用户首次创建或修改数据库时自定义的。其目的在于数据分配，以提高数据库的读写效率。
3）<font color=red size=4 >默认文件组</font>。各数据库都有一个被指定的默认文件组。若在数据库创建对象时没有指定其所属的文件组时，则将分配给默认文件组。
### 创建表
在我们创建好数据库之后，我们就可以可以根据关系在数据库中创建表了，步骤如下：
首先我们打开我们创建好的数据库：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346093.png)
然后，我们右键单击“表”，选择“新建”，再选择“表”，结果如图所示：
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346365.png)

#### 创建属性
在创建好表之后，我们就可以根据表结构来创建对应的属性，以及设置一些基本的要求。如：选择数据类型，选择字符型长度，是否允许NULL值
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346945.png)
在设计好这些基本的要求后，我们可以选择保存，并对表进行命名。
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346542.png)
如果想在保存之后再次修改表格内容并保存，我们需要修改设置：
点击左上角的“工具”，选择“选项”，按照图中的指示，找到“阻止保存要求重新创建表的更改”，取消前面的“√”
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346083.png)

#### 约束条件
1）主键约束
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346334.png)
2）默认值约束
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346645.png)
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346677.png)
3）NULL约束
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346170.png)

4）唯一性约束
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346313.png)
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346884.png)

5）检查约束
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346247.png)
根据需求填写约束表达式
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346899.png)

6）外键约束
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346302.png)
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346855.png)

### 修改表
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346431.png)
右键单击需要修改的表，再选择“设计”选项，就可以按照之前的步骤对表进行修改。

### 删除表
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346475.png)
右键单击需要删除的表，选择“删除”选项，在确认之后就可以对表进行删除操作。

## 修改数据库
选择需要修改的数据库，右键单击选择“属性”，即可对数据库做出修改。
![在这里插入图片描述](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062346731.png)

## 删除数据库
选择需要删除的数据库，右键单击选择“删除”，在确认后即可删除数据库。
