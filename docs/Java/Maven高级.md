# Maven高级

## 分模块设计与开发

![image-20251101084713282](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010847087.png)

![image-20251101085142634](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010851527.png)

![image-20251101085318140](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010853919.png)

![image-20251101085437873](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010854929.png)

![image-20251101085543390](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010855287.png)



## 继承与聚合

### 继承

#### 继承关系

![image-20251101093959368](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010940281.png)

![image-20251101094153725](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010941614.png)

项目的打包方式：

*   jar：普通模块打包，SpringBoot 项目基本都是 jar 包（内嵌 tomcat 运行）
*   war：普通 web 程序打包，需要部署在外部的 tomcat 服务其中运行
*   pom：父工程或聚合工程，该模块不写代码，仅进行依赖管理

:warning: Maven 中不支持多继承，但是支持多重继承​

![image-20251101094624011](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010946880.png)

![image-20251101095629120](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511010956091.png)



#### 版本锁定

![image-20251101101118330](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011011104.png)

![image-20251101101915419](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011019523.png)

![image-20251101101958097](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011019055.png)



### 聚合

![image-20251101104504515](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011045380.png)

![image-20251101110604453](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011106710.png)



## 私服

### 介绍

![image-20251101111248967](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011112823.png)



### 资源上传和下载

![image-20251101111649674](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011116659.png)

![image-20251101111731511](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011117588.png)

![image-20251101111813084](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011118848.png)

![image-20251101111853760](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011118619.png)

![image-20251101111956503](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011119403.png)

![image-20251101112034587](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011120351.png)

Maven 私服配置文档：https://heuqqdmbyk.feishu.cn/wiki/BPzFwIajLi8GXyk3JXmcLRYVn5c

