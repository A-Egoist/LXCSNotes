# CMake

## CMake 快速入门：一个简单示例

### 项目结构

```
.
├── src/
│   ├── main.cpp
│   ├── greet.cpp
│   └── greet.h
└── CMakeLists.txt
```



### 编写 `CMakeLists.txt` 文件

```cmake
# 指定项目所需的 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(MyHelloProject VERSION 1.0)

# 添加 C++ 可执行文件，它的源文件是 'src/main.cpp' 和 'src/greet.cpp'
add_executable(hello src/main.cpp src/greet.cpp)
```



### 编写源代码

`src/main.cpp`：

```cpp
#include <iostream>
#include "greet.h"

int main() {
    std::cout << getGreeting() << std::endl;
    return 0;
}
```

`src/greet.h`：

```cpp
#ifndef GREET_H
#define GREET_H

#include <string>

std::string getGreeting();

#endif
```

`stc/greet.cpp`：

```cpp
#include "greet.h"

std::string getGreeting() {
    return "Hello, CMake!";
}
```



### 创建构建目录并生成构建文件

```bash
mkdir build
cd build
```

在 `build` 目录下，运行 `cmake ..` （注意，`..` 表示父目录，即你的项目根目录，里面有 `CMakeLists.txt`）：

```bash
cmake ..
```

运行这个命令后，CMake 会根据 `CMakeLists.txt` 的内容，在 `build` 目录中生成 `Makefile`（在 Linux 上）或其它相应的构建文件。



### 编译项目

在 `build` 目录中，运行 `cmake --build .` 命令来编译项目：

```bash
cmake --build .
```

这个命令会调用底层的构建工具（比如 `make` 或 `ninja`）来编译你的代码。



### 运行可执行程序

```bash
./hello
```

你会看到输出：`Hello, CMake!`



### 常用的 CMake 命令

| 命令                     | 功能                                                         |
| ------------------------ | ------------------------------------------------------------ |
| `cmake_minimum_required` | 指定项目所需的 CMake 最低版本，这是每个 `CMakeLists.txt` 文件的第一行。 |
| `project`                | 定义项目名称，并可以指定版本、语言等。                       |
| `add_executable`         | 添加一个可执行文件目标。指定目标名称和所有源文件。           |
| `add_library`            | 添加一个库目标。可以指定为 `STATIC`（静态库）或 `SHARED`（动态库）。 |
| `target_link_libraries`  | 将一个目标（例如可执行文件）与所需的库链接起来。             |
| `set`                    | 设置一个变量。                                               |
| `include_directories`    | 为编译过程添加头文件搜索路径。                               |
| `add_subdirectory`       | 包含子目录中的 `CMakeLists.txt` 文件。这是组织大型项目的重要方式。 |



## 更复杂的项目示例

### 项目场景

我们来创建一个简单的数学计算库 `math_lib` 和一个使用该库的可执行程序 `calculator`。

-   **`math_lib` 库**：提供一个 `add` 函数。
-   **`calculator` 程序**：调用 `math_lib` 中的 `add` 函数。

我们将项目分解成两个子目录：`src` 和 `lib`。

### 项目结构

```
.
├── CMakeLists.txt              # 根目录的 CMakeLists.txt
├── src/                        # 存放可执行程序的源代码
│   ├── CMakeLists.txt
│   └── main.cpp
└── lib/                        # 存放库的源代码
    ├── CMakeLists.txt
    ├── include/
    │   └── math_functions.h
    └── math_functions.cpp
```

### 编写 `CMakeLists.txt` 文件

根目录的 `CMakeLists.txt`

```cmake
# 根目录 CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(CalculatorApp VERSION 1.0)

# 添加 lib 子目录，CMake 会进入该目录并处理其 CMakeLists.txt
add_subdirectory(lib)

# 添加 src 子目录，CMake 会进入该目录并处理其 CMakeLists.txt
add_subdirectory(src)
```

`lib/CMakeLists.txt`

```cmake
# lib/CMakeLists.txt

# 添加一个静态库目标，名为 'math_lib'
# 它的源文件是 'math_functions.cpp'
add_library(math_lib STATIC math_functions.cpp)

# 指定头文件的搜索路径
# 这里告诉 CMake，'math_lib' 的头文件在 'include' 目录下
target_include_directories(math_lib PUBLIC include)
```

`src/CMakeLists.txt`

```cmake
# 添加一个可执行文件目标，名为 'calculator'
# 它的源文件是 'main.cpp'
add_executable(calculator main.cpp)

# 将 'calculator' 目标链接到 'math_lib'
# 这样 'calculator' 就可以使用 'math_lib' 中的函数了
target_link_libraries(calculator PRIVATE math_lib)
```



### 编写源代码

`lib/include/math_functions.h`：

```cpp
#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

int add(int a, int b);

#endif
```

`lib/math_functions.cpp`

```cpp
#include "math_functions.h"

int add(int a, int b) {
    return a + b;
}
```

`src/main.cpp`

```cpp
#include <iostream>
#include "math_functions.h"

int main() {
    int sum = add(5, 7);
    std::cout << "The sum of 5 and 7 is: " << sum << std::endl;
    return 0;
}
```



### 构建和运行

```bash
mkdir build
cd build

cmake ..

cmake --build .

./src/calculator
```

输出

```bash
The sum of 5 and 7 is: 12
```



### 总结

通过这个例子，我们展示了 CMake 中最常用的三个核心命令：

-   **`add_subdirectory()`**：将大型项目分解成更小的、可管理的单元。
-   **`add_library()` / `add_executable()`**：定义构建目标。
-   **`target_include_directories()` / `target_link_libraries()`**：管理目标的依赖关系（头文件和库）。

这些命令构成了大多数 CMake 项目的基础，熟练掌握它们将大大简化你的项目管理工作。



## CMake 参数

### 指定生成版本

```bash
cd build

# 生成 Debug 版本的 Makefile
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

这里的 `-D` 选项用来定义一个 CMake 变量。`CMAKE_BUILD_TYPE` 是一个内置变量，可以设置以下几个常见的值：

*   `Debug`：生成带调试信息的代码（等同于 `g++ -g`），通常不会开启代码优化，适合 GDB 调试。
*   `Release`：生成优化过的代码（等同于 `g++ -O3`），不包含调试信息，适合最终发布给用户的版本。
*   `RelWithDebInfo`：生成优化过的代码，但保留调试信息，用于需要调试 Release 版本性能问题。
*   `MinSizeRel`：生成为减少代码体积而优化的代码。



### 指定编译器

使用 `-DCMAKE_CXX_COMPILER` 变量来指定 C++ 编译器

```bash
# 使用 g++
cmake .. -DCMAKE_CXX_COMPILER=g++

# 使用 clang++
cmake .. -DCMAKE_CXX_COMPILER=clang++
```



## CMake 如何打包并发布程序

### Windows



### Linux



## 参考资料

[1] [CMake菜谱（CMake Cookbook中文版）](https://www.bookstack.cn/books/CMake-Cookbook)

[2] [CMake 官方文档](https://cmake.org/cmake/help/latest/)