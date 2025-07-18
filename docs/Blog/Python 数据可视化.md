# Python 数据可视化

```python
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
```

## Numpy 基础

```python
ndarray_a = np.array([1, 2, 3, 4])
ndarray_b = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])
```

### 基础操作

1. 索引

   ```python
   ndarray_a[1]  # 2
   ndarray_b[1][2]  # 7
   ndarray_a[-1]  # 4
   ndarray_b[1][-3]  # 6
   ```

2. 切片

   ```python
   ndarray_a[1:-1]  # array([2, 3])
   ndarray_b[:1, 1:-1]  # array([2, 3])
   ndarray_b[:, 1:-1]  # array([[2, 3],
                       #        [6, 7]])
   ```

3. 分割

   [np.split](https://numpy.org/doc/stable/reference/generated/numpy.split.html)

   [np.hsplit](https://numpy.org/doc/stable/reference/generated/numpy.hsplit.html)

   [np.vsplit](https://numpy.org/doc/stable/reference/generated/numpy.vsplit.html)

4. 迭代

   [numpy.nditer](https://numpy.org/doc/stable/reference/generated/numpy.nditer.html)

   [numpy.ndenumerate](https://numpy.org/doc/stable/reference/generated/numpy.ndenumerate.html)

### 高级操作

1. 过滤（可用于数据清洗）

   1. ```python
      ndarray_a[ndarray_a > 2]  # array([3, 4])
      ndarray_b[ndarray_b > 2]  # array([3, 4, 5, 6, 7, 8])
      ```

   2. [np.extract](https://numpy.org/doc/stable/reference/generated/numpy.extract.html)
   3. [np.where](https://numpy.org/doc/stable/reference/generated/numpy.where.html)

   

2. 排序

   1. [np.sort](https://numpy.org/doc/stable/reference/generated/numpy.sort.html)

      ```python
      np.sort([2, 5, 1, 0, 9, 2, 5, 3, 6])  # array([0, 1, 2, 2, 3, 5, 5, 6, 9])
      np.sort([2, 5, 1, 0, 9, 2, 5, 3, 6])[::-1]  # array([9, 6, 5, 5, 3, 2, 2, 1, 0])
      ```

      

   2. [np.argsort](https://numpy.org/doc/stable/reference/generated/numpy.argsort.html)

      

3. 组合

   

4. 重构

   1. ndarray.reshape(shape)
   
      ```python
      ndarray_a.reshape(1, 4)  # array([[1, 2, 3, 4]])
      ndarray_a.reshape(4, 1)  # array([[1],
                               #        [2],
                               #        [3],
                               #        [4]])
      ndarray_a.reshape(2, -1)  # array([[1, 2],
                                #        [3, 4]])
      ```
   
      

## Pandas 基础

> Pandas 的主要数据结构是 Series （一维数据）与 DataFrame （二维数据），这两种数据结构足以处理
> 金融、统计、社会科学、工程等领域里的大多数典型用例。

### DataFrame 

DataFrame 是一个表格型的数据结构

* 含有一组有序的列，每列可以是不同的值类型（数值、字符串、布尔型值）。

* 既有行索引也有列索引。它可以被看做由 Series 组成的字典（共同用一个行索引）

  ![image-20220525104654476](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350367.png)

* Pandas Series 类似表格中的一个列

  ![image-20220525104642062](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350727.png)

### Series

* Pandas Series 类似表格中的一个列（ column ），类似于一维数组，可以保存任何数据类型。

* Series 由索引（ index ）和列组成

* 可以从 .csv 文件、 Excel 电子表格或 SQL 数据库中加载数据集，即可创建 Series

* Series 也包含了多种创建方式

  * Numpy 数组

    ```python
    ndarray = np.array([1, 2, 3])
    series = pd.Series(ndarray)
    print(series)
    ```

  * 列表

    ```python
    plist = ['p', 'y', 't', 'h', 'o', 'n']
    series = pd.Series(plist)
    print(series)
    ```

### 索引

```python
df = pd.read_csv('./iris.csv')
```

![image-20220525112034879](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350718.png)

* 列索引

  * df['category']，返回一个 Series

    ![image-20220525112216071](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350714.png)

  * df[['category']]，返回一个 DataFrame

    ![image-20220525112648273](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350468.png)

* 行索引

  * df.loc[]，行索引
  * df.iloc[]，整数行号索引



### Pandas 高级操作

* 过滤

  ![image-20220525113327411](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350278.png)

* 排序

## Matplotlib 基础

### Matplotlib 介绍

* 每个图表封装于 Figure 对象中，即可视化的顶层容器
* Python 对象可控制 Axes 、刻度线、图例、标题、文本框、网格和许多其他对象
* Figure
  * 最外层容器并用作绘图的画布，进而可在其
    中绘制多个图表。
  * 不仅加载 Axes 对象，还可对 Title 进行配置
* Axes
  * 是实际的图表或子图表
  * 包括 x 轴和 y 轴、spine 和图例

![image-20220525113552483](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350591.png)

Figure 和 Axes

* Figure 想象成一张纸（一般被称之为画布）
* Axes 代表的则是纸中的一片区域（当然可以有多个区域，这是后续要说到的 subplots）

![image-20220525113603338](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350106.png)

### 函数式编程和面向对象编程

1. 函数式编程(plt)

   ```python
   plt.figure()
   plt.plot([1, 2, 3], [4, 5, 6])
   plt.show()
   ```

   ![image-1](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350362.png)

   函数式编程方式，先生成一个 Figure 画布，然后在这个画布上隐式生成一个画图区域进行画图。

   

2. 面向对象编程(ax)

   ```python
   fig, ax = plt.subplots()
   ax.plot([1, 2, 3], [4, 5, 6])
   plt.show()
   ```

   ![image-2](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350405.png)

   面向对象编程方式，同时生成了 Figure 和 axes 两个对象，然后用 ax 对象在其区域内进行绘图。



![image-20220525114521468](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350211.png)

### Matplotlib 中的格式化字符串

* 颜色

  ![image-20220525114610828](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350309.png)

* 标记

  ![image-20220525114628264](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350139.png)

* 线条样式

  ![image-20220525114643473](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062350127.png)
