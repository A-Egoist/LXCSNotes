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

         