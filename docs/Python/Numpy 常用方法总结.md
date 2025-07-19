## Numpy库入门

### 简介

#### 1、Numpy家族

![](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062351385.png)

#### 2、Numpy是数据处理与分析、科学计算的基础

![](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062351361.png)

上面展示的就是几个深度依赖Numpy库的有名的工具模块

#### 3、关于更多的Numpy基本概念可以参考下面这篇博客

[NumPy入门讲座（1）：基本概念](https://blog.csdn.net/xufive/article/details/103567312)

### 创建数组

#### 概述：ndarray数组的创建方法

| 函数                 | 说明                                                      |
| -------------------- | --------------------------------------------------------- |
| np.array(list/tuple) | 直接从python中的列表、元组的类型创建ndarray数组           |
| np.arange(n)         | 类似pytho的内置range()函数，返回ndarray类型，元素从0道n-1 |
| np.ones(shape)       | 根据shape生成一个全1数组，shape是元组类型                 |
| np.zeros(shape)      | 根据shape生成一个全0数组，shape是元组类型                 |
| np.full(shape,val)   | 根据shape生成一个数组，每个元素都是val                    |
| np.eye(n)            | 创建一个正方形的n*n单位矩阵，主对角线为1，其余为0         |
| np.ones_like(a)      | 根据数组a的形状生成一个全1数组                            |
| np.zeros_like(a)     | 根据数组a的形状生成一个全0数组                            |
| np.full_like(a,val)  | 根据数组a的形状生成一个数组，每个元素值都是val            |
| np.linspace()        | 根据起止数据等间距地填充数据，形成数组                    |
| np.concatenate()     | 将两个或多个数组合并成一个新的数组                        |

[NumPy入门讲座（2）：创建数组](https://blog.csdn.net/xufive/article/details/103575481)这篇博客的博主将**ndarray**数组的创建分为了四个部分，如图所示：![](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062351000.png)

### 操作数组

#### 1、索引和切片

在一维的情况下其实ndarray数组和python的列表操作相差不大，但是对于多位操作，Numpy数组比python的列表灵活得多，假设有一栋2层楼，每层楼内的房间都是3行4列，那我们可以用一个三维数组来保存每个房间的居住人数。

```python
>>> a = np.arange(24).reshape(2,3,4)    # 2层3行4列
>>> a
array([[[ 0,  1,  2,  3],
        [ 4,  5,  6,  7],
        [ 8,  9, 10, 11]],

       [[12, 13, 14, 15],
        [16, 17, 18, 19],
        [20, 21, 22, 23]]])
>>> a[1][2][3]                          # 虽然可以这样
23
>>> a[1,2,3]                            # 但这才是规范的用法
23
>>> a[:,0,0]                            # 所有楼层的第1排第1列
array([ 0, 12])
>>> a[0,:,:]                            # 1楼的所有房间，等价与a[0]或a[0,...]
array([[ 0,  1,  2,  3],
       [ 4,  5,  6,  7],
       [ 8,  9, 10, 11]])
>>> a[:,:,1:3]                          # 所有楼层所有排的第2到4列
array([[[ 1,  2],
        [ 5,  6],
        [ 9, 10]],

       [[13, 14],
        [17, 18],
        [21, 22]]])
>>> a[1,:,-1]                           # 2层每一排的最后一个房间
array([15, 19, 23])
```



