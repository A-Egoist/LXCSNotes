# extern 的作用

## 重定义问题

### 产生原因

假设我们在`global.hpp`中定义了两个变量

```cpp title="global.hpp"
#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>

int globalAge = 24;
std::string globalName = "Amonologue";

#endif
```

然后我们创建`global.cpp`包含`global.hpp`

```cpp title="global.cpp"
#include "global.hpp"
```

然后我们在`main.cpp`中包含`global.hpp`

```cpp title="main.cpp"
#include <iostream>
#include "global.hpp"

int main() {
    std::cout << "Hello, World!\n";
    std::cout << "Global age is " << globalAge << '\n';
    std::cout << "Global name is " << globalName << std::endl;
    
    return 0;
}
```

我们运行上述代码, 程序编译并未产生问题,但是链接产生问题了

```bash
duplicate symbol '_globalName' in:
    /var/folders/7f/3vdsv1x51gz3ccmrf8zv32c80000gn/T/main-beaf8a.o
    /var/folders/7f/3vdsv1x51gz3ccmrf8zv32c80000gn/T/global-d201e4.o
duplicate symbol '_globalAge' in:
    /var/folders/7f/3vdsv1x51gz3ccmrf8zv32c80000gn/T/main-beaf8a.o
    /var/folders/7f/3vdsv1x51gz3ccmrf8zv32c80000gn/T/global-d201e4.o
ld: 2 duplicate symbols for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

上述报错的意思是在链接`main.cpp.obj`时发现`global_age`重定义，第一次定义在`global.hpp`这里。

同样链接`mian.cpp.obj`时发现global_name重定义，第一次定义在`global.hpp`。

因为`global.hpp`中定义了`global_age`，根据我们之前学习的预编译知识，只要是包含`global.hpp`的文件都会展开`global.hpp`，`main.cpp`展开了一次，`global.cpp`展开了一次

### 解决办法

在C++中，`extern` 关键字用于声明一个变量或函数是在另一个文件或同一个文件的其他位置定义的。这主要用于处理全局变量或函数声明，确保在多个源文件中能够正确地链接到这些全局变量或函数的定义。

在`global.hpp`中用extern声明两个变量

```cpp title="global.hpp"
#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>

extern int globalAge;
extern std::string globalName;

#endif
```

在`global.cpp`中定义这些变量

```cpp title="global.cpp"
#include "global.hpp"

int globalAge = 24;
std::string globalName = "Amonologue";
```

在`main.cpp`中包含`global.hpp`

```cpp title="main.cpp"
#include <iostream>
#include "global.hpp"

int main() {
    std::cout << "Hello, World!\n";
    std::cout << "Global age is " << globalAge << '\n';
    std::cout << "Global name is " << globalName << std::endl;
    
    return 0;
}
```

再次编译，运行成功

```bash
Hello, World!
Global age is 24
Global name is Amonologue
```



### 总结

*   头文件只做变量的声明，不能做变量的定义
*   头文件声明变量可以采用extern的方式