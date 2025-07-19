## 1 虚拟环境
1.   查看安装的虚拟环境

     ```bash
     conda info -e
     ```

2.   创建

     ```bash
     conda create -n env-name python=3.8
     ```

3.   激活

     ```bash
     conda activate env-name
     ```

4.   退出

     ```bash
     conda deactivate
     ```

5.   删除

     ```bash
     conda remove -n env-name --all
     ```

6.   导出虚拟环境

     ```bash
     conda env export > ./environment.yaml
     ```

7.   利用导出的虚拟环境配置新的虚拟环境

     ```bash
     conda env create -f ./environment.yaml
     ```
## 2 源
1. 查看源

    ```bash
    conda config --show channels
    ```

    or

    ```bash
    conda info
    ```

2. 添加清华源
    在 home 目录下执行一下命令

    ```bash
    vi ./.condarc
    ```

    将打开的文件中的内容替换为如下的内容

    ```bash
    channels:
      - defaults
    show_channel_urls: true
    default_channels:
      - http://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
      - http://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r
      - http://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/msys2
    custom_channels:
      conda-forge: http://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
      msys2: http://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
      bioconda: http://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
      menpo: http://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
      pytorch: http://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
      pytorch-lts: http://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
      simpleitk: http://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
    ```

3. 恢复默认源

    执行如下命令

    ```bash
    vi ~/.condarc
    ```

    将打开的文件的内容清空
