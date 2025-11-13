# LXCSNotes



## 快速开始

### 克隆仓库

```bash
git clone https://github.com/A-Egoist/LXCSNotes.git --depth=1
cd LXCSNotes
```

### 环境配置

```bash
conda create -n MkDocs python=3.9
conda activate MkDocs
pip install -r requirements.txt
```

### MkDocs

```bash
# 本地预览
mkdocs serve
# 构建(如果是推送到 github pages，可以直接省略)
mkdocs build
# 推送到 github pages
mkdocs gh-deploy
```



## 仓库结构

博客的所有源文件都放在 `/docs` 目录下，`/site` 目录下是编译好的网页。

在 `/docs` 目录下，有三个目录属于页面设置相关：`/assets`、`/javascripts`、`stylesheets`。

