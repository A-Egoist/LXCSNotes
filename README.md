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

