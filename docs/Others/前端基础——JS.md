# 前端基础——JS

## JS基础

### 1 JS三种书写位置

1.1 行内

```html
<input type = "button" valyue = "点我试试" onclick = "alert('Hello World')" />
```

1.2 内嵌

```html
<script>
    alert('Hello World');
</script>
```

1.3 外部

`myhtml.html`

```html
<script src = "myjs .js"></script>
```

`myjs.js`

```
alert('Hello World');
```

### 2 JS注释

单行注释：`//`

多行注释：`/**/`

### 3 JS输入输出语句

```javascript
alert(msg);//浏览器弹出警示框
console.log(msg);//浏览器控制台打印输出信息
prompt(info);//浏览器弹出输入框，用户可以输入
```

### 4 变量

#### 4.1 声明变量

