# TeX Live + CTeX + Visual Studio Code 配置

如果 TeX Live 的路径在**用户变量**中，而不是**系统变量**，这说明该路径的作用范围仅限于当前用户，而不是整个系统。虽然这通常不会影响 VSCode 的使用，但当系统中有多个 LaTeX 环境时（如 CTeX 和 TeX Live 并存），可能会导致优先级冲突。

### 解决方案

为了确保 TeX Live 被正确调用，你可以选择以下操作：

------

#### 1. 将 TeX Live 路径移到系统变量中

1.  打开“系统属性”：

    -   搜索“环境变量”并打开。
    -   在弹出的“环境变量”窗口中，找到“系统变量”下的 `Path`，点击“编辑”。

2.  添加 TeX Live 路径：

    -   点击“新建”，添加：

        ```
        D:\Program Files\texlive\2023\bin\windows
        ```

    -   确保该路径位于 CTeX 的路径之前。

3.  保存并退出。

4.  重启电脑，确保设置生效。

------

#### 2. 直接修改用户变量的顺序

如果你不想修改系统变量，可以调整用户变量的优先级：

1.  在“用户变量”中找到 `Path`，点击“编辑”。

2.  确认是否包含 TeX Live 的路径：

    ```
    D:\Program Files\texlive\2023\bin\windows
    ```

3.  确保它位于 CTeX 路径之前。

4.  保存后，重启 VSCode。

------

#### 3. 在 VSCode 中明确指定 TeX Live 的路径

即使用户变量中配置了 TeX Live 的路径，仍建议在 VSCode 中手动指定 TeX Live 的工具路径：

1.  打开 VSCode 的设置（`Ctrl + ,`），搜索 `LaTeX Workshop`。

2.  配置 `latex-workshop.latex.toolchain`，确保路径指向 TeX Live：

    ```json
    "latex-workshop.latex.toolchain": [
        {
            "name": "pdflatex",
            "command": "D:\\Program Files\\texlive\\2023\\bin\\windows\\pdflatex.exe",
            "args": [
                "-synctex=1",
                "-interaction=nonstopmode",
                "-file-line-error",
                "%DOC%"
            ]
        }
    ]
    ```

3.  保存后，在 VSCode 中测试编译。

------

#### 4. 验证最终配置

在终端中运行以下命令，确认 `pdflatex` 正确指向 TeX Live：

```bash
where pdflatex
```

理想结果应为：

```
D:\Program Files\texlive\2023\bin\windows\pdflatex.exe
```

如果仍然显示 CTeX 优先，可能需要彻底检查环境变量配置，或者清理终端缓存（执行 `refreshenv`）。

------

### 总结

-   **推荐方式**：将 TeX Live 的路径移动到系统变量，确保系统范围内的优先级。
-   如果不想修改系统变量，可以调整用户变量的顺序，并在 VSCode 中明确指定 TeX Live 的路径。
-   验证 `pdflatex` 路径是否正确是最终排查的关键步骤。



参考资料：

*   [用于 Visual Studio Code 的 LaTeX Workshop](https://blog.csdn.net/qq_23599965/article/details/103022215)
*   [Visual Studio Code (vscode)配置LaTeX](https://zhuanlan.zhihu.com/p/166523064)
*   

