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

