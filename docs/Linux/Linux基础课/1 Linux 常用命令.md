# 1 Linux 常用命令


##### 1. ctrl c: 取消命令，并且换行

##### 2. ctrl u: 清空本行命令

##### 3. tab键：可以补全命令和文件名，如果补全不了快速按两下tab键，可以显示备选选项

##### 4. ls: 列出当前目录下所有文件，蓝色的是文件夹，白色的是普通文件，绿色的是可执行文件

1. ls -a
2. ls -h
3. ls -ah

##### 5. pwd: 显示当前路径

##### 6. cd XXX: 进入XXX目录下, cd .. 返回上层目录

##### 7. cp 复制文件或文件夹

cp XXX YYY: 将XXX文件复制成YYY，XXX和YYY可以是一个路径，比如../dir_c/a.txt，表示上层目录下的dir_c文件夹下的文件a.txt

cp -r XXX YYY: 将指定目录下的所有文件和子目录一并处理。

##### 8. mkdir XXX: 创建目录XXX

mkdir -p

##### 9. history

##### 10. rm 删除文件或文件夹

rm XXX: 删除普通文件
rm XXX -r: 删除文件夹
rm *.txt

##### 11. mv 移动文件或文件夹

mv XXX YYY: 将XXX文件移动到YYY，和cp命令一样，XXX和YYY可以是一个路径；重命名也是用这个命令

##### 12. find

##### 13. touch XXX: 创建一个文件

##### 14. cat XXX: 展示文件XXX中的内容

##### 15. chmod 修改文件权限

在 Linux 中，`chmod` 命令用于修改文件或目录的权限，文件权限可以使用 `ls -l` 命令查看。示例权限 `drwxrwxr-x@` 的分解如下：

```
d rwx rwx r-x @
│  │   │   │  │
│  │   │   │  └─ 扩展属性（macOS的扩展文件属性）
│  │   │   └─── 其他用户（others）的权限：r-x（读+执行）
│  │   └─────── 所属组（group）的权限：rwx（读+写+执行）
│  └─────────── 所有者（user）的权限：rwx（读+写+执行）
└────────────── 文件类型（d表示目录）
```

Linux 权限分为 **3 类用户**，每类用 **3 个字符**表示：
| 用户类别           | 符号表示 | 权限位             |
| ------------------ | -------- | ------------------ |
| 所有者（User）     | `u`      | 前 3 位（`rwx`）   |
| 所属组（Group）    | `g`      | 中间 3 位（`rwx`） |
| 其他用户（Others） | `o`      | 后 3 位（`r-x`）   |
| 所有用户（All）    | `a`      | `u+g+o`            |

权限字符：
- `r` = 读（4）
- `w` = 写（2）
- `x` = 执行（1）
- `-` = 无权限（0）

通过数字模式修改权限，用 3 位八进制数表示权限，每位对应 `u`、`g`、`o` 的权限和：
- `r` = 4
- `w` = 2
- `x` = 1 

组合方式：`rwx` = 4+2+1 = 7，`r-x` = 4+0+1 = 5

示例：

```bash
chmod 755 file      # u=rwx (7), g=rx (5), o=rx (5)
chmod 644 file      # u=rw (6), g=r (4), o=r (4)
```

加上 `-R`，递归的修改目录内的所有文件

```bash
chmod -R 755 目录名
```



##### 16. grep 命令



## 解压文件

1.   安装解压软件

     ```bash
     sudo apt install unzip
     ```

2.   解压文件

     *   将文件解压到当前目录

         ```bash
         unzip filename.zip
         ```

     *   将文件解压到指定目录

         ```bash
         unzip filename.zip -d save_path
         ```

     *   解压文件, 同时不覆盖已经存在的文件

         ```bash
         unzip filename.zip -n
         ```

     *   解压文件, 覆盖已经存在的文件

         ```bash
         unzip filename.zip -o
         ```

3.   查看压缩包中的文件

     ```bash
     unzip filename.zip -l
     ```



## wget

GNU Wget (简称: wget) 是一个用于下载的软件

1.   安装

     ```bash
     sudo apt install wget
     ```

2.   使用

     *   下载单个文件

         ```bash
         wget url
         ```

     *   下载文件并以不同的文件名保存

         ```bash
         wget -o filename url
         ```

     *   限定下载速度

         ```bash
         wget -limit-rate=1024k url
         ```

     *   断续下载

         ```bash
         wget -c url
         ```

     *   后台下载

         ```bash
         wget -b url
         ```

     *   下载多个文件

         首先将需要下载的多个 url 保存到 url_list 中, 然后再使用如下命令

         ```bash
         wget -i url_list.txt
         ```



## tmux

详见：[2 tmux和vim.md](./2 tmux和vim.md)



## vim

详见：[2 tmux和vim.md](./2 tmux和vim.md)



## 用户管理

添加用户：

```bash
adduser username
```

修改密码：

```bash
passwd username
```



## 关机和重启

关机：

```bash
sudo shutdown -h now
```

重启：

```bash
sudo shutdown -r now
```



## 参考资料

[1] [ubuntu下如何解压zip文件（超详细）](https://www.cnblogs.com/cy0628/p/13903990.html)

