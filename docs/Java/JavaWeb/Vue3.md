# Vue3

## 什么是 Vue

Vue 是一款用于<font color='red'>构建用户界面</font>的<font color='red'>渐进式</font>的 JavaScript <font color='red'>框架</font>。（官网：https://cn.vuejs.org/）

构建用户界面：

![image-20251007170154193](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071704677.png)

渐进式：

![image-20251007170410482](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071704622.png)

框架：

![image-20251007170558669](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071706778.png)

## Vue 快速入门

>   基于数据渲染出用户看到的页面 --> 数据驱动视图

准备工作

*   引入 Vue 模块（官方提供）
*   创建 Vue 程序的应用实例，控制视图的元素
*   准备元素（div），被 Vue 控制

数据驱动视图

*   准备数据
*   通过插值表达式渲染页面

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Vue-快速入门</title>
</head>
<body>
    <div id="app">
        <h1>{{message}}</h1>
        <h1>{{count}}</h1>
    </div>

    <script type="module">
        import { createApp, ref } from 'https://unpkg.com/vue@3/dist/vue.esm-browser.js';

        createApp({
            data() {
                return {
                    message: 'Hello Vue',
                    count: 100
                }
            }
        }).mount('#app');
    </script>
</body>
</html>
```

更多的例子可以参考官方文档：https://cn.vuejs.org/guide/quick-start.html



## Vue 常用指令

![image-20251007172813997](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071728464.png)

### v-for

![image-20251007173223588](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071732260.png)

### v-bind

![image-20251007180914606](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071809241.png)

### v-if & v-show

![image-20251007181352712](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071813835.png)

:bulb: v-if 适用于不频繁切换的场景

:bulb: v-show适用于频繁切换的场景



### v-model

![image-20251007182316559](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071823814.png)



### v-on

![image-20251007184010230](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510071840564.png)



### Vue 生命周期

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072142125.png)

![image-20251007214347649](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510072143682.png)

:bulb: 重点掌握 `mounted()`



## Vue 工程化

![image-20251101181405693](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011814661.png)

![image-20251101181506240](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011815250.png)

![image-20251101181835055](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011818912.png)

![image-20251101181955526](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011819431.png)

![image-20251101182040814](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011820614.png)



### 环境准备

![image-20251101182241153](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011822224.png)

![image-20251101182604413](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011826566.png)

1、安装 NodeJS，高于 18 版本

2、通过 `node -v` 命令和 `npm -v` 验证安装

![image-20251101182712789](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011827555.png)

3、配置 npm 的全局安装路径

4、切换镜像，加速包下载



### Vue 项目简介

![image-20251101183037126](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011830044.png)

:bulb: 不加 `@3.3.4`，默认安装最新版本

![image-20251101183110387](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511011831263.png)

![image-20251101224513648](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511012245653.png)

![image-20251101224616192](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511012246015.png)



### Vue 项目开发流程

![image-20251102124911064](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511021249956.png)

![image-20251102124952756](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511021249684.png)

![image-20251102125024194](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202511021250847.png)



### API 风格

**选项式 API** 和**组合式 API**





### 案例
