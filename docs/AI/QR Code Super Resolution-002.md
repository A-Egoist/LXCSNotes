# QR Code Super Resolution

Author：隆兴

## 1 Introduction

在此之前，我已经基于 SRGAN 模型和 WeChat AI 开源的超分辨技术构建了一个基础的模型。经过一个比较简短的训练之后，在 [数据集(yxuw)](https://pan.baidu.com/s/1dt6kNWN4L27o9Xm1Trp5tQ) 文件夹中的 `BaseDataSet.rar` 数据集上的超分效果很好。

为了提高模型的泛化性，我在已有模型的基础上，根据 ESRGAN[^2] 和 Real-ESRGAN[^4] 这两个模型的亮点对模型进行优化，主要对这几个方向进行改进：网络结构、对抗损失、感知损失、二值模式限制。同时本文的结构也参照论文[^2]的格式。

**网络结构**：总体上参照 SRGAN[^3]中的网络结构，但是去掉了其中的 BN 层，并根据任务需要对网络的输入输出做了修改。

**对抗损失**：利用 Relativistic GAN[^1]中提出的方法，让生成图像 SR 和原始图像 HR 之间的距离保持尽可能大，而不是 SRGAN[^3] 中的恒量和 0 或 1 间的绝对距离。

**感知损失**：利用预训练好的 VGG19 网络提取生成图像 SR 和原始图像 HR 的 feature map 计算两者的均方误差。

**二值模式限制**：采用二值模式限制损失函数加大对错误计算的灰色像素的惩罚。

## 2 Related Work

论文[^2]在该部分提出到了当时的一些 tricks，我选取了其中能够用于当前任务的 tricks

**整体网络**：扩展模型尺寸；使用高效残差密集块、使用 channel attention 机制加深网络、强化学习、无监督学习。

**深度网络的稳定训练**：残差通道、残差因子、网络(无 BN)参数初始化的方法、RRDB(residual-in-residual dense block) 替换残差块。

**感知损失**：目标是最小化特征空间的误差而不是像素空间的误差。

**判别损失**：用相关性判别器作为优化目标，不仅增加了生成数据为真的概率，也减小了真实数据为真的概率。

**评价标准**：否定了 PSNR 和 SSIM 这两种评价指标。肯定了基于人类感知的无线照评价方法 Ma's score 和 NIQE，并根据这种评价标准创建了 PI(perceptual index) 评价方法。

## 3 Proposed Methods

### 3.1 Network Architecture

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062348643.png" alt="image-20211119231948411" style="zoom:67%;" />

网络的整体结构如上图所示。

Generator 部分较 SRGAN 论文[^3]，移除了 BN 层。因为 BN 层会将一个 batch 的特征进行归一化处理，从在像素级生成任务的效果上来看，BN 层会使得生成的图像出现伪影和模糊。而且由于不同网络的不同参数设置，BN 层的引入有时还能造成网络不稳定，所以为了稳定的训练和一致的性能，论文[^2]的作者去掉了 BN 层。

### 3.2 Relativistic Discriminator

根据 Standard GAN 的缺点，论文[^1]提出了一种新的优化方案 Relativistic GAN，在此基础上论文[^2]给出了如下式子：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062348364.png" alt="image-20211119231922230" style="zoom:80%;" />

首先给出 sigmoid 函数的图像：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062348407.png" alt="image-20211119232005625" style="zoom:80%;" />

**Standard GAN** 中的 Discriminator 的表达式为：
$$
D(I^{HR})=\sigma(C(I^{HR}))\to1\\
D(I^{SR})=\sigma(C(I^{SR}))\to0\tag{1}
$$
根据上图的 sigmoid 函数图像可知，Standard GAN 的目的是为了让 Discriminator 对原始图像 HR 的判别结果更趋进于 1，对生成图像 SR 的判别结果更趋近于 0，从而达到区分二者的目的。

**Relativistic GAN** 中的 Discriminator 的表达式为：
$$
D_{Ra}(I^{HR},I^{SR})=\sigma(C(I^{HR})-\mathbb{E}\left[C(I^{SR})\right])\to1\\
D_{Ra}(I^{SR},I^{HR})=\sigma(C(I^{SR})-\mathbb{E}\left[C(I^{HR})\right])\to0\tag{2}
$$
其中，$C(\cdot)$ 表示的判别器的原始输出，$D_{Ra}$ 表示 Relativistic average Discriminator，$\sigma(\cdot)$ 表示 sigmoid 函数。

**Relativistic average Discriminator** 的解释如下：

首先需要明确的是判别器对真实数据判决的原始值大于对生成数据判决的原始值。因此考虑第一个等式左侧，有 $C(I^{HR})-\mathbb{E}\left[C(I^{SR})\right]>0$，且差值越大，表明二者距离越远，该差值经过 sigmoid 后的值越接近于 1。因此 D 的目的是使得该 sigmoid 值尽可能接近于 1，这就将真实图片和生成图片很好的区分开来；考虑第二个等式左侧，有 $C(I^{SR})-\mathbb{E}\left[C(I^{HR})\right]<0$，且差值越小，表明二者距离越远，该差值经过 sigmoid 后的值越接近于 0。因此 D 的目的是使得该 sigmoid 值尽可能接近于 0，这就将真实图片和生成图片很好的区分开来。

那么根据上面的两个式子，文章[^2]提出了新的 Discriminator 损失函数：
$$
L_{Discriminator}=-\mathbb E_{I^{HR}}\left[\log\left(D_{Ra}\left(I^{HR},I^{SR}\right)\right)\right]-\mathbb E_{I^{SR}}\left[\log\left(1-D_{Ra}\left(I^{SR},I^{HR}\right)\right)\right]\tag{3}
$$
与此对应 Generator 的对抗损失为：
$$
L_{adversarial}=-\mathbb E_{I^{HR}}\left[\log\left(1-D_{Ra}\left(I^{HR},I^{SR}\right)\right)\right]-\mathbb E_{I^{SR}}\left[\log\left(D_{Ra}\left(I^{SR},I^{HR}\right)\right)\right]\tag{4}
$$
从直观的角度上解释：因为 Discriminator 是为了更好的区分真实和生成，而 Generator 是为了更难区分真实和生成。因为 Generator 的对抗损失中同时涉及生成图像 $I^{SR}$ 和真实图像 $I^{HR}$，所以更有利于梯度的生成，可以更有利于生成图像中的边缘和细节信息。

### 3.3 Perceptual Loss

论文[^2]提出了一种在 VGG 激活层前计算感知损失 $L_{perceptual}$ 的方法，而不是与 SRGAN 一样在激活层后计算感知损失。在激活层后计算感知损失有两个缺点：

1. 激活层后的特征是已经稀疏化了的，越深的网络越明显。稀疏的特征会导致更弱的监督，从而网络性能变差。

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062348009.png" alt="image-20211119231906934" style="zoom:80%;" />

2. 使用激活层后的特征图计算感知损失会使得生成图像 SR 的亮度和目标图像 HR 不一致。

参考 SRGAN 的论文[^3]，现给出在我的模型中 $L_{perceptual}$ 的计算式子：
$$
L_{perceptual}=\frac{1}{KWH}\sum_{k=1}^K\sum_{i=1}^W\sum_{j=1}^H\left(\phi_{ij}^k\left(I^{HR}\right)-\phi_{ij}^k\left(G\left(I^{LR}\right)\right)\right)^2\tag{5}
$$
其中 K 表示 feature map 的数量，W 表示一个 feature map 的宽度，H 表示一个 feature map 的高度，$\phi_{ij}^k\left(\cdot\right)$ 表示对应第 k 个 feature map 的坐标为 $(i, j)$ 的像素点的值，$G(\cdot)$ 表示 Generator 的输出，$I^{HR}$ 对应原始图像，$I^{LR}$ 对应原始图像经过处理得到的低分辨率图像。



### 3.4 Binary Pattern Constraint

文章[^5]指出，根据二维码图像是二值图像，仅由黑白两种颜色组成，但退化后的图像会产生灰色像素这一特点。可以采用二值模式限制损失函数加大对错误计算的灰色像素的惩罚。在 L2 Loss 的基础上，使用 Sigmoid 函数的一阶导数作为权重：
$$
w(x)=\frac{4e^{-\alpha{(x-128)}}}{(1+e^{-\alpha{(x-128)}})^2}\tag{6}
$$
函数图像如图所示：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062348140.png" alt="image-20211119232025891" style="zoom:80%;" />

该函数对落在中间灰色区间的灰度值施以更大的惩罚，从而促使网络输出更符合二维码特性的重建结果。

根据式子$(6)$可以将 Generator 中的 $L_{content}$ 表示如下：
$$
L_{content}=\frac{1}{WH}\sum_{i=1}^W\sum_{j=1}^H\frac{4\cdot e^{-\alpha\left(I^{SR}-128\right)}}{\left(1+e^{-\alpha\left(I^{SR}-128\right)}\right)^2}\tag{7}
$$

### 3.5 Generator Loss

由式子 $(4)(5)(7)$ 可得 Generator 的 loss 为：
$$
L_{Generator}=\alpha\cdot L_{adversarial}+\beta\cdot L_{perceptual}+\gamma\cdot L_{content}\tag{8}
$$
其中 $\alpha,\beta,\gamma$ 是平衡三种 loss 的系数。

### 3.6 Network Interpolation

此部分是论文[^2]中提出的方法，其目的是为了平衡感知质量和 PSNR 等评价指标。具体而言，作者首先基于 PSNR 方法训练的得到网络 G_PSNR，然后再用基于 GAN 的网络 G_GAN 进行 fine tuning。然后，对这两个网络相应的网络参数进行插值得到一个插值后的网络 G_INTERP：

$$
\theta_G^{INTERP}=(1-\alpha)\cdot\theta_G^{PSNR}+\alpha\cdot\theta_G^{GAN}
$$
通过调整 $\alpha$ 来调节两个模型的比重，从而使得生成的图像在 PSNR 和感知质量上都有一个不错的效果。

### 3.7 DataSet

文章[^4]指出，之前的 SR 模型所使用的 LR 图像都是从 HR 图像通过 Bicubic 进行下采样得到的，但是这种退化方式和真实世界的退化方式不一致，且模式单一。为此，文章[^4]提出了一种引入多重退化类型的输入数据模拟方式(sinc 滤波，模拟振铃效应、传感器过冲退化)。

### 3.8 Tricks

文章[^2]和文章[^4]提出提出了一些模型训练中的 tricks：

* 在训练时对 ground truth 进行 unsharp mask 锐化后再计算 loss，可以引导网络生成更加清晰的结果。
* 将 VGG 判别器替换为 U-net，对输出进行“像素级”的监督训练。
* 引入 spectral normalization 使得 GAN 训练更稳定，同时输出的结果也更少 artifact 了。
* 引入 exponential moving average，维护模型的一个影子权重，计算移动均值，减少训练的抖动。

## 4 Experiments

### 4.1 Training Details

放大倍数：x4

**数据集**：

LR：

* size = (128, 128)
* num = 1000
* 使用 OpenCV 按照 JPEG 压缩方法从 HR 获得，质量为 10

HR：

* size = (512, 512)
* num = 1000

**训练过程**：

部分训练过程如下所示：

![Generator and Discriminator loss](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062349916.png)

**训练结果**：

训练完成之后，对 `lr_img` 文件夹进行超分，然后使用 OpenCV 识别，得到 `lr_img`，`sr_img`，`hr_img` 的识别率：

|         | Bicubic | WeChat API | **Ours** |
| ------- | ------- | ---------- | -------- |
| lr_imgs | 0.2278  | 0.6871     | 0.5366   |
| hr_imgs |         | 0.8599     |          |

>  注：因为模型分成了两次训练，所以计算了一下中间的到模型的训练效果

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062349998.png" alt="image-20211119232148168" style="zoom: 50%;" />

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062349945.png" alt="image-20211119232200617" style="zoom: 50%;" />

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062349973.jpeg" alt="2021-10-20_13_56_02" style="zoom: 50%;" />

![3_src](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062349623.png)

![2021-10-20_13_55_41](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2024/202410062349414.png)

### 4.2 Qualitative Results

### 4.3 Ablation Study

### 4.4 Network Interpolation

## 5 Conclusion



## 6 TODO Work



## 7 Reference

[^1]: The relativistic discriminator: a key element missing from standard GAN
[^2]: ESRGAN: Enhanced Super-Resolution Generative Adversarial Networks
[^3]: Photo-Realistic Single Image Super-Resolution Using a Generative Adversarial
[^4]: Real-ESRGAN: Training Real-World Blind Super-Resolution with Pure Synthetic Data
[^5]: 微信AI设计了一种超分辨率技术，让扫二维码更方便
