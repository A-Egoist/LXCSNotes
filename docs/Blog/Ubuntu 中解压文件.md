## 解压 zip 文件

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



## 参考资料

*   [ubuntu下如何解压zip文件（超详细）](https://www.cnblogs.com/cy0628/p/13903990.html)
