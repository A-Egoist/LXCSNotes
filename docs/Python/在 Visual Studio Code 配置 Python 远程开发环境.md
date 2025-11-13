# 在 Visual Studio Code 配置 Python 远程开发环境

## 1 安装 Visual Studio Code

## 2 添加拓展程序

*   本地笔记本安装拓展程序

    <img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/image-bed/202303061644528.png" alt="截屏2023-03-06 16.39.45" style="zoom:50%;" />



## 在 Visual Studio Code 调试和运行

## 设置用户代码片段

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/202303/202303061704378.png" alt="截屏2023-03-06 17.03.49" style="zoom:50%;" />

选择 `python.json`

将打开的文件中的内容修改为以下内容

```json
{
	// Place your snippets for python here. Each snippet is defined under a snippet name and has a prefix, body and 
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the 
	// same ids are connected.
	// Example:
	// "Print to console": {
	// 	"prefix": "log",
	// 	"body": [
	// 		"console.log('$1');",
	// 		"$2"
	// 	],
	// 	"description": "Log output to console"
	// }
	"HEADER": {
		"prefix": "header",
		"body": [
			"# -*- coding: utf-8 -*- ",
			"# @File : $TM_FILENAME",
        	"# @Time : $CURRENT_YEAR/$CURRENT_MONTH/$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE:$CURRENT_SECOND",
        	"# @Author : Amonologue ",
			"# @Software : Visual Studio Code",
		],
		"description": "header of python file"
	}
}
```

