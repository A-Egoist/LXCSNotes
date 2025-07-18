# Python 命名规范

## 基本规范

| 类型               | 公有                    | 内部                                                       | 备注                |
| ------------------ | ----------------------- | ---------------------------------------------------------- | ------------------- |
| Package            | package_name            | none                                                       | 全小写+下划线式驼峰 |
| Module             | module_name             | _module_name                                               | 全小写+下划线式驼峰 |
| Class              | ClassName               | _ClassName                                                 | 首字母大写式驼峰    |
| Method             | method_name             | protected: _method_name private: __method_name             | 全小写+下划线式驼峰 |
| Exception          | ExceptionName           | none                                                       | 首字母大写式驼峰    |
| Function           | function_name           | none                                                       | 全小写+下划线式驼峰 |
| Global Constant    | GLOBAL_CONSTANT_NAME    | _GLOBAL_CONSTANT_NAME                                      | 全大写+下划线式驼峰 |
| Global Variable    | global_var_name         | _global_var_name                                           | 全小写+下划线式驼峰 |
| Local Variable     | local_var_name          | none                                                       | 全小写+下划线式驼峰 |
| Instance Variable  | instance_var_name       | protected: _instance_var_name private: __instance_var_name | 全小写+下划线式驼峰 |
| Function Parameter | function_parameter_name | none                                                       | 全小写+下划线式驼峰 |

函数名, 变量名和文件名应该是描述性的, 尽量避免缩写, 特别要避免使用非项目人员不清楚难以理解的缩写, 不要通过删除单词中的字母来进行缩写.
所谓”内部(Internal)”表示仅模块内可用, 或者, 在类内是保护或私有的。
用单下划线 `_` 开头表示模块变量或函数是 protected (使用from module import *时不会包含).
用双下划线 `__` 开头的实例变量或方法表示类内私有.

## 导包
每行只导入一个变量或者一个模块,避免一行导入多个模块：
```python
import os
import numpy as np
```

## 注释
短期注释TODO,需要注意三点

1.`#TODO`开头
2.在后面紧跟括号，注明名字和你的联系方式
3.写清楚这个todo要解决什么问题，在什么条件下解决（时间/其他工作完成条件）
```python
#TODO(hitrjj tom@tom.com): Test this module and add a function, when I have space time
#TODO(tom): Add data io modul untils I receive the data from boss...
```

## 参考资料
* [【Python命名规范】Python文件名、类、变量、函数方法等的命名规范](https://blog.csdn.net/chengyikang20/article/details/124706919)
* [【python命名规范】谷歌风格命名](https://blog.csdn.net/u014636245/article/details/89813732)
* [Google Style Guid](https://google.github.io/styleguide/pyguide.html)