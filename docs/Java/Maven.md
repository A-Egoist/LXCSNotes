# Maven

## Maven 基础

### 什么是 Maven？

[Maven](https://maven.apache.org/) 是一款用于管理和构建 Java 项目的工具，是 Apache 旗下的一个开源项目。

### Maven 的作用

![image-20251007221917770](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072222882.png)

![image-20251007222251046](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072222946.png)

![image-20251007222532662](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072225672.png)

![image-20251007222902219](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072229330.png)

![image-20251007222929929](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072229292.png)

![image-20251007223026784](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072230090.png)



## Maven 概述

### 介绍

![image-20251007225826555](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072258606.png)

![image-20251007230240036](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072302126.png)

Maven 中的仓库用来存储和管理 jar 包

Maven 中三类仓库，查找优先级为：本地仓库 > 远程仓库 > 中央仓库



### 安装

![image-20251007230626375](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072306773.png)

![image-20251008091134238](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510080911447.png)

阿里云私服：

```xml
<mirror>
  <id>alimaven</id>
  <name>aliyun maven</name>
  <url>http://maven.aliyun.com/nexus/content/groups/public/</url>
  <blocked>central</blocked>
</mirror>
```

环境变量：

*   系统环境变量：`MAVEN_HOME`，路径为 Maven 安装路径，比如：`D:\Program Files\apache-maven-3.9.11`
*   在 Path 中添加 `%MAVEN_HOME%/bin`

验证：

```bash
mvn -v
```

![image-20251008092239480](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510080922938.png)

## IDEA 集成 Maven

### 创建 Maven 项目

1、设置 Maven

![image-20251008100217583](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081002213.png)

2、修改 Runner

![image-20251008101042346](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081010741.png)

3、修改 Compiler

![image-20251008101149977](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081011430.png)

4、创建项目

![image-20251008102447416](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081024073.png)

5、创建模块

![image-20251008102546815](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081025873.png)

![image-20251008102828680](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081028069.png)

6、创建结果

![image-20251008103700919](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081037851.png)

默认创建的 Maven 项目在 test 目录下并没有 resources 目录，可以通过手动创建 `Directory` 的方式来创建：

![image-20251008103936387](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081039321.png)

7、创建并运行

![image-20251008110841346](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081108911.png)



### Maven 坐标

![image-20251008143547176](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081435411.png)



### 导入 Maven 项目

![image-20251008143716544](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081439133.png)

![image-20251008143740250](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081439266.png)

:bulb: 建议将要导入的 Maven 项目复制到你的项目目录下，然后再选择 Maven 项目的 `pom.xml` 进行导入。



## 依赖管理

### 依赖配置

![image-20251008144413797](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081444402.png)

https://mvnrepository.com/



### 排除依赖

![image-20251008150159165](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081502411.png)



### 生命周期

![image-20251008175740695](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081757986.png)

![image-20251008175831710](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081758871.png)

![image-20251008180035542](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081800424.png)

:bulb: 是同一套生命周期，即运行 `instal` 的时候并不会运行 `clean​`，但是会运行 `compile`、`test`、`package`。

:bulb: `install​` 会将项目安装到 Maven 的本地仓库中，具体的本地仓库设置可以查看 `maven/conf/settings.xml` 文件

:bulb: ​

![image-20251008180756719](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081807849.png)

![image-20251008182826572](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081828737.png)



## 单元测试

![image-20251008183249997](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081833468.png)

![](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081833449.png)

![image-20251008183334183](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081833183.png)



### 快速入门

使用 JUnit 进行单元测试

![image-20251008183605459](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081836676.png)

![image-20251008183733078](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081837138.png)

![image-20251008185123801](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081851426.png)

![image-20251008185224560](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081852403.png)





### 断言

单元测试运行不报错，不能保证代码没有逻辑问题。

![image-20251008185735866](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510081857887.png)

在 JUnit 单元测试中，为什么要使用断言？

*   单元测试方法运行不报错，不代表业务方法没有问题。
*   通过断言可以检测方法运行结果是否和预期一致，从而判断业务方法的正确性。
*   `Assertions.assertXxxx(...)`



### 常见注解

![image-20251008212159048](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082122965.png)

![image-20251008212232180](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082122074.png)

### 企业开发规范

![image-20251008213140290](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082131469.png)

:bulb: ​IDEA 可以查看单元测试覆盖率。

![image-20251008213611868](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082136860.png)



### 依赖范围

![image-20251008214401176](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082144314.png)



![image-20251008214921728](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082149742.png)

## 常见问题

![image-20251008215944454](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510082159001.png)

:bulb: 可以把 `del /s *.lastUpdated` 指令写成批处理文件，放到 Maven 的安装目录中，从而方便之后删除 `*.lastUpdated` 文件。​
