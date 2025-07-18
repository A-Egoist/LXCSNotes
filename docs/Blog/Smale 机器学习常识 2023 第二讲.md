# Smale 机器学习常识 2023 第二讲

>   主讲人: [闵帆](https://blog.csdn.net/minfanphd)
>
>   时间: 2023.06.20 14:30-15:30
>
>   文字稿: [机器学习常识 3: 分类、回归、聚类](https://blog.csdn.net/minfanphd/article/details/130820544)、[机器学习常识 4: 分类问题的训练与测试](https://blog.csdn.net/minfanphd/article/details/130878062)、[机器学习常识 5: 性能评价指标](https://blog.csdn.net/minfanphd/article/details/130880261)

## 常识 3: 分类、回归、聚类

### 基本概念

**分类**是指将一个样本预测为给定类型之一, 也称为为该样本打标签.

**回归**是指为一个输出为实型值的预测.

**聚类**是指根据样本的属性, 把给定的样本集合划分为若干个子集(簇).

### 扩展概念

**多标签分类**是指类别之间没有互斥性, 比如电影、天气等.



## 常识 4: 分类问题的训练与测试

### 基本概念

数据集划分(split-in-two / split-in- three)

*   训练集(Train)

*   测试集(Test)

*   验证集(Validation)

训练方法

*   监督学习(Supervised Learning)

*   无监督学习(Unsupervised Learning)

*   自监督学习(Self-supervised Learning)

### 训练、测试的不同方案

不同学习方法可能对不同训练数据的适应性不同.

*   多次随机划分训练集于测试集(random splitting).
*   交叉验证(cross validation). 数据集中有 100 条数据, 将其分为 5 份, 即每份 20 条数据. 每次选择其中 4 份(即 80 条数据)进行训练, 其它 1 份(即 20 条数据)进行测试. 这样, 所有的数据都被测试过一次. 这种方案被称为 5 折交叉验证(5 folds cross validation, 5-cv).
*   留一法(leave-one-out).
*   使用训练集进行测试.

### 拟合能力和泛化能力

当测试集和训练集相同时, 考察的是模型的**拟合能力**.

当测试集于训练集不同是, 考察的是模型的**泛化能力**. 提升泛化能力才是机器学习的真正的目的.

模型在训练集效果好, 但是在测试集上效果表现差, 就是产生了**过拟合(over-fitting)**.

**如何防止过拟合, 适当降低拟合能力以获得更好的泛化能力, 是机器学习的核心.**

### 验证集

训练集相当于平时的例题, 直接提供标准答案.

验证集相当于平时的习题/测验题, 做完后可以看标准答案.

测试集相当于高考题, 只知道分数, 不告诉答案.

## 常识 5: 性能评价指标

### 分类问题评价指标

#### F-measure

混淆矩阵

True Positive(TP)

False Positive(FP)

False Negative(FN)

True Negative(TN)

精度(Precision) $P=\frac{TP}{TP+FP}$

召回率(Recall) $R=\frac{TP}{TP+FN}$

准确率(Accuracy) $Acc=\frac{TP+TN}{TP+FN+FP+TN}$

#### 基于实数值预测的评价指标

*   受试者曲线 ROC
*   曲线下面积 AUC

#### 基于序的评价指标

### 回归问题评价指标

平均绝对误差(Mean Absolute Error, MAE)

均方误差(Mean Squared Error, MSE)

均方根误差(Root Mean Squared Error, RMSE)

### 聚类问题评价指标

聚类没有一个可参考的客观标准, 所以评价指标很凌乱.

*   内部评价指标: 紧密度(Compactness)计算每个样本点到它对应的聚类中心的距离, 然后将它们加起来求均值.
*   外部评价指标: 借助于数据的标签.

>   参考资料: [Lei Gao, Zhen-yun Jiang, Fan Min. First-arrival travel times picking through sliding windows and fuzzy c-means. Mathematics. 7(3)(2019)221.](http://www.fansmale.com/downloadRAR/publicationPdf/FPSF.pdf)

### 常见误区

*   认为性能评价指标是一成不变的, 实际上每个人都可以设计新的指标(或创造一种新的运动).
*   仅用一个指标来做实验, 一篇论文要写得丰富, 需要多个评价指标, 每个对应于一张图或一张表.