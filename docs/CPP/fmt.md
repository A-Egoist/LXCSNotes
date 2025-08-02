# fmt

## 安装

### 包管理安装

```bash
# Ubuntu/Debian
sudo apt update && sudo apt install libfmt-dev
```

-   适合大多数用户
-   自动处理依赖和更新
-   与系统其他组件兼容性好

### 源码安装

```bash
git clone https://github.com/fmtlib/fmt.git
cd fmt
cmake -B build -DCMAKE_INSTALL_PREFIX=$HOME/.local -DFMT_TEST=OFF
cmake --build build --parallel
cmake --install build
```

-   需要最新版本时
-   需要自定义编译选项时
-   没有 root 权限时 (安装到用户目录)
-   需要特定版本时 (通过 `git checkout v10.0.0`)

## 项目中使用

```cmake
find_pacakge(fmt REQUIRED)
target_link_libraries(project_name PRIVATE fmt::fmt)
```

也可以指定最低版本：
```cmake
find_package(fmt 9.0 REQUIRED)  # 要求 ≥9.0
```

