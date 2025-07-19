

# 8 docker

## 从零开始配置服务器

以 `ubuntu server 20.04 LTS` 为例

新安装的 ubuntu server 默认只有 root 用户

1.   以 root 的身份登录服务器
     ```bash
     ssh root@hostname
     ```

2.   添加非 root 用户，并赋予 `sudo` 权限
     ```bash
     # apt install sudo
     adduser amonologue
     usermod -aG sudo amonologue
     ```

3.   配置文件
     创建文件 `~/.ssh/config`，并在文件中输入如下内容，若使用 22 号端口登录不需要指定 `Port`

     ```
     Host myserver1
     	HostName IP地址或域名
     	User 用户名
     
     Host myserver2
     	HostName IP地址或域名
     	User 用户名
     	Port
     ```

4.   密钥登录

     1.   创建密钥
          ```bash
          ssh-keygen
          ```

     2.   添加密钥到服务器
          ```bash
          ssh-copy-id myserver
          ```

          或者将`id_rsa.pub`复制到`~/.ssh/authorized_keys`中的单独一行。因为还没有试过用`ssh-copy-id`将多台电脑的公钥复制到同一个服务器上是否可行。

5.   配置服务器的工作环境（初恋？）
     ```bash
     scp .bashrc .vimrc .tmux.conf myserver:
     ```

6.   安装常用的软件
     ```bash
     sudo apt update
     sudo apt install tmux
     sudo apt install tree
     sudo apt install 
     ```

## 安装 docker

*   [官方教程](https://docs.docker.com/engine/install/ubuntu/)

*   [Ubuntu 22.04下Docker安装（最全指引）](https://blog.csdn.net/u011278722/article/details/137673353)

## docker 创建服务器

1.   添加`docker`用户组（可选）
     ```bash
     sudo groupadd docker
     ```

2.   将当前用户添加到用户组
     ```bash
     sudo usermod -aG docker $USER
     ```

3.   使权限生效
     ```bash
     newgrp docker
     ```

4.   更新`.bashrc`文件，以避免每一次打开新的终端都需要执行`newgrp docker`
     ```bash
     # 在文件末尾增加如下命令
     groupadd -f docker
     ```

5.   执行如下命令
     ```bash
     scp /var/lib/acwing/docker/images/docker_lesson_1_0.tar server_name:  # 将镜像上传到自己租的云端服务器
     ssh server_name  # 登录自己的云端服务器
     
     docker load -i docker_lesson_1_0.tar  # 将镜像加载到本地
     docker run -p 20000:22 --name my_docker_server -itd docker_lesson:1.0  # 创建并运行docker_lesson:1.0镜像
     
     docker attach my_docker_server  # 进入创建的docker容器
     passwd  # 设置root密码
     ```

6.   开放云平台的`20000`端口

## 配置 docker 服务器

参考 “从零开始配置服务器”，指定端口为`20000`



## docker 常用命令

https://www.acwing.com/blog/content/10878/

参考 “docker 创建服务器” 给省去`docker`命令的`sudo`权限

### 镜像（images）

1.   `docker pull ubuntu:20.04`: 拉取一个镜像
2.   `docker images`: 列出本地所有镜像
3.   `docker image rm ubuntu:20.04` 或 `docker rmi ubuntu:20.04`: 删除镜像`ubuntu:20.04`
4.   `docker [container] commit CONTAINER IMAGE_NAME:TAG`: 创建某个`container`的镜像
5.   `docker save -o ubuntu_20_04.tar ubuntu:20.04`: 将镜像`ubuntu:20.04`导出到本地文件`ubuntu_20_04.tar`中
6.   `docker load -i ubuntu_20_04.tar`: 将镜像`ubuntu:20.04`从本地文件`ubuntu_20_04.tar`中加载出来

### 容器（container）

1.   `docker [container] create -it ubuntu:20.04`: 利用镜像`ubuntu:20.04`创建一个容器。
2.   `docker ps -a`: 查看本地的所有容器
3.   `docker [container] start CONTAINER`: 启动容器
4.   `docker [container] stop CONTAINER`: 停止容器
5.   `docker [container] restart CONTAINER`: 重启容器
6.   `docker [contaienr] run -itd ubuntu:20.04`: 创建并启动一个容器
7.   `docker [container] attach CONTAINER`: 进入容器
     -   先按`Ctrl-p`，再按`Ctrl-q`可以挂起容器
8.   `docker [container] exec CONTAINER COMMAND`: 在容器中执行命令
9.   `docker [container] rm CONTAINER`: 删除容器
10.   `docker container prune`: 删除所有已停止的容器
11.   `docker export -o xxx.tar CONTAINER`: 将容器`CONTAINER`导出到本地文件`xxx.tar`中
12.   `docker import xxx.tar image_name:tag`: 将本地文件`xxx.tar`导入成镜像，并将镜像命名为`image_name:tag`
13.   `docker export/import`与`docker save/load`的区别: 
      -   `export/import`会丢弃历史记录和元数据信息，仅保存容器当时的快照状态
      -   `save/load`会保存完整记录，体积更大
14.   `docker top CONTAINER`: 查看某个容器内的所有进程
15.   `docker stats`: 查看所有容器的统计信息，包括CPU、内存、存储、网络等信息
16.   `docker cp xxx CONTAINER:xxx` 或 `docker cp CONTAINER:xxx xxx`: 在本地和容器间复制文件
17.   `docker rename CONTAINER1 CONTAINER2`: 重命名容器
18.   `docker update CONTAINER --memory 500MB`: 修改容器限制

