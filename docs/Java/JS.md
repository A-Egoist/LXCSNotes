# JS

![image-20251006210147438](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510062101218.png)

![image-20251006210429835](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510062104449.png)

## JS核心语法

### JS引入方式

1、内部脚本

将 JS 代码定义在 HTML 页面中

*   JavaScript 代码必须位于 `<script></script>` 标签之间
*   在 HTML 文件中，可以在任意地方，防止任意数量的 `<script></script>`
*   一般会把脚本置于 `<body>` 元素的底部，可改善显示速度

```html
<body>
    <!-- 页面内容 -->
    <script>
        alert("Hello World");
    </script>
</body>
```



2、外部脚本

将 JS 代码定义在外部 JS 文件中，然后引入到 HTML 页面中

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510062110443.png" alt="image-20251006211020473" style="zoom:67%;" />



### 基础语法

#### 变量

JS 中使用 `let` 关键字来声明变量（弱类型语言，变量可以存放不同类型的值）。

```js
let a = 20;
a = "Hello";
alert(a);  // 弹出框
```

变量名规则：

*   只能用 字母、数字、下划线、美元符号组成，且数字不能开头
*   变量名严格区分大小写
*   不能使用关键字



JS 中使用 `const` 关键字来声明常量，声明之后不可以重新赋值。

```js
const PI = 3.14;
// PI = 5.0;
console.log(PI);  // 输出到控制台
document.write(PI);  // 直接输出到 body 区域，不常用
```



#### 数据类型

JavaScript 中的数据类型分为：基本数据类型和引用数据类型（对象）。

基本数据类型：

*   number：数字（整数、小数、NaN(Not a Number)）
*   boolean
*   null：对象为空。因为 JavaScript 中是大小写敏感的，因此 null、Null、NULL 是完全不同的。
*   undefined：当声明的变量未初始化的时候，该变量的默认值是 undefined
*   string：字符串，单引号、双引号、反引号都可以，推荐使用<mark>单引号</mark>



通过 `typeof` 运算符获取数据类型：

```js
let a = 20;
alert(typeof a);

alert(typeof null);  // null -> object
```



模板字符串：

*   使用反引号 \`\` 拼接
*   内容拼接变量时，使用 `${}` 包住变量

```js
let name = 'Tom';
let age = 18;
console.log('大家好，我是新入职的' + name + '，今年' + age + '岁了，请多指教');
console.log(`大家好，我是新入职的${name}，今年${age}岁了，请多指教`);
```



#### 函数

JavaScript 中通过 `function` 关键字定义：
```js
// 具名函数
function add(a, b) {
    return a + b;
}
```



匿名函数

```js
// 函数表达式
let add = function(a, b) {
    return a + b;
}
```

```js
// 箭头函数
let add = (a, b) => {
    return a + b;
}
```



#### 自定义对象

定义格式：

```js
let 对象名 = {
    属性名1: 属性值1,
    属性名2: 属性值2,
    属性名3: 属性值3,
    方法名: function () {}
}
```

具体实现：

```js
let user = {
    name: 'Tom',
    age: 20,
    gender: '男',
    sing: function () {
        alert(this.name + '唱着最炫的民族风')
    }
}
```

或

```js
let user = {
    name: 'Tom',
    age: 20,
    gender: '男',
    sing() {
        alert(this.name + '唱着最炫的民族风')
    }
}
```

调用格式：

```js
对象名.属性名;
对象名.方法名();
```

具体实现：

```js
console.log(user.name);
user.sing();
```

:bulb: 在定义对象中的方法时，尽量不使用箭头函数（this）。



**JSON (JavaScript Object Notation)**

JSON 的本质是一个字符串，多用于作为<font color='red'>数据载体</font>。

```json
{
    "name": "Tom",
    "age": 20,
    "gender": "男"
}
```

:bulb: JSON 格式的文本中，所有的 key 必须使用双引号引起来。

JSON 对象的两个方法：

*   JSON.parse: 将 JSON 字符串转为 JS 对象
*   JSON.stringify: 将 JS 对象转为 JSON 字符串

![image-20251006230344836](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510062303429.png)

```js
let person = {
    name: 'itcast',
    age: 18,
    gender: '男'
}
alert(JSON.stringify(person));  // JS对象 --> JSON字符串

let personJson = '{"name": 'heima', "age": 18}';
alert(JSON.parse(personJson).name);
```



### DOM

概念：Document Object Model，文档对象模型。

将标记语言的各个组成部分封装为对应的对象：

*   Document：整个文档对象
*   Element：元素对象
*   Attribute：属性对象
*   Text：文本对象
*   Comment：注释对象

#### DOM 树

![image-20251006231502049](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510062315597.png)

JavaScript 通过 DOM，就能够对 HTML 进行操作：

*   改变 HTML 元素的内容
*   改变 HTML 元素的样式（CSS）
*   对 HTML DOM 事件做出反应
*   添加和删除 HTML 元素



#### DOM操作

DOM 操作核心思想：将网页中所有的元素当做对象来处理。（标签的所有属性在该对象上都可以找到）

操作步骤：

*   获取要操作的 DOM 元素对象
*   操作 DOM 对象的属性或方法（查文档或 AI）

获取 DOM 对象

*   根据 CSS 选择器来获取 DOM 元素，获取匹配到的第一个元素：`document.querySelector('选择器')`
*   根据 CSS 选择器来获取 DOM 元素，获取匹配到的所有元素：`document.querySelectorAll('选择器')`
    注意：得到的是一个 NodeList 节点集合，是一个伪数组（有长度、有索引的数组）



:bulb: ​具体的操作可以在 [W3School](https://www.w3school.com.cn/) 中查表。



## JS事件监听







## 参考资料

[1] [MDN](https://developer.mozilla.org/zh-CN/)

[2] [W3School](https://www.w3school.com.cn/)