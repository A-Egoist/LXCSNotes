# 从零开始配置 Ubuntu 开发环境

在 WSL2 的 Ubuntu 系统中配置 C/C++ 和 Python 开发环境，请按以下步骤操作：

### 1. 更新系统包
```bash
sudo apt update && sudo apt upgrade -y
sudo apt autoremove
```

### 2. 安装 C/C++ 开发工具链
```bash
# 安装编译工具链（包括 gcc, g++, make 等）
sudo apt install build-essential -y

# 安装调试工具
sudo apt install gdb valgrind -y
```

### 3. 安装 Python 开发环境 (TODO)
**基础 Python 环境**

```bash
# 安装 Python 3 和 pip
sudo apt install python3 python3-pip python3-venv -y

# 更新 pip
python3 -m pip install --upgrade pip
```

**配置虚拟环境（推荐）**

```bash
# 创建项目目录
mkdir my_project && cd my_project

# 创建虚拟环境
python3 -m venv .venv

# 激活虚拟环境
source .venv/bin/activate  # 每次开发前运行
```

### 4. 安装常用开发工具
```bash
# 安装调试/构建工具
sudo apt install cmake clang lldb ninja-build -y

# 安装代码格式化工具
sudo apt install clang-format pylint -y

# 安装 Git
sudo apt install git -y
```

### 5. 配置开发环境（可选）
#### VS Code 集成
1. 在 Windows 安装 [VS Code](https://code.visualstudio.com/)
2. 安装扩展：
   - **Remote - WSL**（连接 WSL）
   - **C/C++**（Microsoft 官方扩展）
   - **Python**（Microsoft 官方扩展）
3. 在 WSL 终端输入 `code .` 启动 VS Code

#### 环境变量配置
编辑 `~/.bashrc` 添加常用别名：
```bash
# 快速激活虚拟环境
alias venv='source .venv/bin/activate'
```

### 6. 验证安装 (TODO)
#### C 程序测试
```bash
echo -e '#include <stdio.h>\nint main(){printf("Hello WSL!\\n");}' > test.c
gcc test.c -o test && ./test
```

#### C++ 程序测试
```bash
echo -e '#include <iostream>\nint main(){std::cout<<"Hello WSL!\\n";}' > test.cpp
g++ test.cpp -o test && ./test
```

#### Python 测试
```bash
python3 -c 'print("Hello WSL!")'
```



## 个性化操作

### WSL Ubuntu 美化

![image-20250616235628731](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506162357608.png)

![image-20250616235645418](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506162357868.png)

![image-20250616235700358](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506162357681.png)

![image-20250616235709628](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506162357789.png)

#### WSL Ubuntu 中安装 Zim

步骤1：安装前置依赖

```bash
sudo apt update
sudo apt install zsh neofetch fzf -y
```

步骤2：安装 Zim Framework

```bash
# 需要开启代理
curl -fsSL https://raw.githubusercontent.com/zimfw/install/master/install.zsh | zsh
```

步骤2.1：Clash 设置`允许局域网连接`：
![image-20250617193114333](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202506201615937.png)

步骤2.2：在 `~/.zshrc` 中添加：
```txt
alias PROXY_ON='export ALL_PROXY=[Windows_IP]:7890'
alias PROXY_OFF='unset ALL_PROXY'
```

其中 `[Windows_IP]` 使用如下命令获得：
```bash
cat /etc/resolv.conf
```

步骤2.3：在shell中使用 `PROXY_ON` 开启代理

步骤3：配置 `~/.zimrc` 文件：

```txt
zmodule completion
zmodule environment
zmodule git
zmodule input
zmodule termtitle
zmodule utility
zmodule duration-info
zmodule git-info
zmodule asciiship
zmodule zsh-users/zsh-completions --fpath src
zmodule zdharma-continuum/fast-syntax-highlighting
zmodule zsh-users/zsh-history-substring-search
zmodule zsh-users/zsh-autosuggestions
zmodule agkozak/zsh-z
zmodule hlissner/zsh-autopair
zmodule zsh-users/zsh-autosuggestions
zmodule Aloxaf/fzf-tab
zmodule romkatv/powerlevel10k --use degit
```

步骤4：安装配置的模块

```bash
zimfw install
```

步骤5：配置 Powerlevel10k 主题

```bash
p10k configure
```

步骤5.1：修改 `.p10k.zsh` 设置：

```txt
# 将
typeset -g POWERLEVEL9K_INSTANT_PROMPT=verbose
# 修改为
typeset -g POWERLEVEL9K_INSTANT_PROMPT=quiet
```

步骤6：在 `.bashrc` 的最后一行加上 `neofetch`

```bash
echo "neofetch" >> ~/.bashrc
```



#### 常见问题

1.   提示符显示异常：
     ```bash
     zimfw uninstall
     zimfw install
     exec zsh
     ```

2.   当出现 waring：
     ```txt
     warning: completion was already initialized before completion module. Will call compinit again. See https://github.com/zimfw/zimfw/wiki/Troubleshooting#completion-is-not-working
     ```

     参考 github 中的解决方法，将 `/etc/zsh/zshrc` 中的如下内容注释掉。
     即，将：
     
     ```txt
     if (( ${${(@f)"$(</etc/os-release)"}[(I)ID*=*ubuntu]} )) &&
        [[ -z "$skip_global_compinit" ]]; then
       autoload -U compinit
       compinit
     fi
     ```
     
     修改为：
     
     ```txt
     if (( ${${(@f)"$(</etc/os-release)"}[(I)ID*=*ubuntu]} )) &&
        [[ -z "$skip_global_compinit" ]]; then
     #   autoload -U compinit
     #   compinit
     fi
     ```
     
     如果提示权限不足，使用 `chmod` 修改权限：
     ```bash
     sudo chmod 0777 /etc/zsh/zshrc
     ```
     
     之后记得修改会原来的权限：
     ```bash
     sudo chmod 0644 /etc/zsh/zshrc
     ```



### tmux 改建

将 `.tmux.conf` 复制到新系统的用户目录下

```bash
cp /mnt/d/Projects/Notes/Linux/.tmux.conf .
```

