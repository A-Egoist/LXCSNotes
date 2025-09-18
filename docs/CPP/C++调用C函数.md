# C++ 调用 C 函数

因为 C++ 的名称修饰机制，C 和 C++ 两种语言在编译链接阶段处理函数名的方式不同。所以想要在 C++ 中调用 C 的函数，需要使用 `extern "C"` 关键字。以如下项目为例。

项目结构：

```txt
.
├── CMakeLists.txt
├── build
├── include
│   ├── add.h
│   └── function.hpp
├── main.cpp
└── src
    ├── add.c
    └── function.cpp
```



main.cpp

```cpp
#include <iostream>
#include "function.hpp"

int main() {
    int a = 10, b = 20;
    std::cout << "a + b = " << test(a, b) << std::endl;

    return 0;
}
```



add.h

```cpp
#ifndef ADD_H
#define ADD_H

#ifdef __cplusplus
extern "C" {
#endif

    int add(int a, int b);

#ifdef __cplusplus
}
#endif

#endif
```

使用 `#ifdef __cplusplus` 和 `#endif` 以在 C 编译器处理时隐藏 `extern "C"`。



add.c

```cpp
#include "add.h"

int add(int a, int b) {
    return a + b;
}
```



function.hpp

```cpp
#ifndef FUNCTION_HPP
#define FUNCTION_HPP

int test(int a, int b);

#endif
```



function.cpp

```cpp
#include "function.hpp"
#include "add.h"

int test(int a, int b) {
    return add(a, b);
}
```



CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    ${PROJECT_NAME}
    main.cpp src/add.c src/function.cpp
)
```



最后在 `build` 文件夹运行如下代码即可编译并执行程序：

```bash
cd build
cmake ..
cmake --build .
./main
```





## 参考资料

[1] [c++代码调用c代码的函数](https://mp.weixin.qq.com/s/puMEPzfgsxYOCM1pP6Wzzg)

