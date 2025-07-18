# ssh

## ssh登录

### 基本用法

登录远程服务器

```bash
ssh user@hostname
```

*   `user`: 用户名
*   `hostname`: IP地址或域名

已经登录过的服务器的信息将保存到`~/.ssh/known_hosts`

指定登录端口号为22

```bash
ssh user@hostname -p 22
```

### 配置文件

创建文件`~/.ssh/config`

在文件中写入:

```
Host myserver
	HostName IP地址或域名
	User 用户名
```

### 密钥登录

创建密钥

```bash
ssh-keygen
```

然后一直回车即可

执行结束后，`~/.ssh/`目录下会多出两个文件:

*   `id_rsa`: 私钥
*   `id_rsa.pub`: 公钥

将`id_ras.pub`上传到对应的服务器即可实现免密登录:

```bash
ssh-copy-id myserver
```

### 执行远程命令

命令格式:

```bash
ssh user@hostname command
```

例子1:

```bash
ssh user@hostname ls -a
```

例子2:

```bash
# 单引号中的$i可以求值
ssh myserver 'for ((i = 0; i < 10; i ++)) do echo $i; done'
```

例子3:

```bash
# 双引号中的$i不可以求值
ssh myserver "for ((i = 0; i < 10; i ++)) do echo $i; done"
```

例子4:

remote_mkdir.sh

```bash
#! /bin/bash

ssh myserver mkdir homework/lesson_4/homework_4/\"$1\"
```

remote_rmdir.sh

```bash
#! /bin/bash

ssh myserver rm -r homework/lesson_4/homework_4/\"$1\"
```

## scp传文件

### 基本用法

命令格式

```bash
scp source destination
```

将`source`路径下的文件复制到`destination`

一次复制多个文件：

```bash
scp source1 source2 destination
```

复制文件夹:

```bash
scp -r ~/tmp myserver:/home/acs/
```

将本地家目录中的`tmp`文件夹复制到``myserver`服务器中的`/home/acs/``目录下。

```bash
scp -r ~/tmp myserver:homework/
```

将本地家目录中的`tmp`文件夹复制到`myserver`服务器中的`~/homework/`目录下。

```bash
scp -r myserver:homework .
```

将`myserver`服务器中的`~/homework/`文件夹复制到本地的当前路径下。

指定服务器的端口号:

```bash
scp -P 22 source1 source2 destination
```

*   `-P`: P需要大写

### 使用`scp`配置其他服务器的`vim`和`tmux`

```bash
scp .bashrc .vimrc .tmux.conf myserver:
```
