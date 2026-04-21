# AI agent 入门笔记

Claude Code 官方文档：https://code.claude.com/docs/zh-CN/overview

Cursor 官方文档：https://cursor.com/cn/docs



中转站：https://www.packyapi.com/console



## 安装和配置

### Codex 安装

步骤1：

在 VS Code 扩展中安装 Codex 插件：

![image-20260419174740196](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604191747571.png)

步骤2：

安装 CC-Switch：https://github.com/farion1231/cc-switch/releases/tag/v3.13.0

在 CC-Switch 中配置 PackyCode，详见：https://docs.packyapi.com/docs/ccswitch/3-codex.html

![image-20260419195342821](C:\Users\Amonologue\AppData\Roaming\Typora\typora-user-images\image-20260419195342821.png)



### 在 WSL2 中安装 Codex

步骤1：

在 VS Code 扩展中安装 Codex 插件：

步骤2：

在 WSL2 中安装 CC-Switch CLI

```bash
# 下载
curl -LO https://github.com/saladday/cc-switch-cli/releases/latest/download/cc-switch-cli-linux-x64-musl.tar.gz

# 解压
tar -xzf cc-switch-cli-linux-x64-musl.tar.gz

# 添加执行权限
chmod +x cc-switch

# 移动到 PATH
sudo mv cc-switch /usr/local/bin/
```

在 CC-Switch CLI 中配置 Codex

```bash
# 启动 CC-Switch CLI
cc-switch
```

按下 `]` 切换到 Codex，选择 `Providers` ，回车选中，并按下 `a` 键，进入供应商添加页面

![image-20260421164505581](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604211645185.png)

在上方模板中选择 `PackyCode`

![image-20260421164550108](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604211645619.png)

在 `Api Key` 处填写你的 Apikey 回车，并按下 `Ctrl+S` 进行保存，`Api Key` 分组选择可用于 Codex 分组

![image-20260421164612531](C:\Users\Amonologue\AppData\Roaming\Typora\typora-user-images\image-20260421164612531.png)

确保此时选中的是刚才配置的 Provider，然后在左侧菜单中退出 CC Switch CLI

步骤3：

之后就可以通过在终端输入如下命令，然后在 Windows10 的 VS Code 中使用 Codex 了

```bash
code .
```





### Claude Code 安装

目标：将 Claude Code 安装到 Windows 10 的 WSL2 Ubuntu 系统中

步骤1：

使用如下命令直接安装 Claude Code，不用预先安装 node.js

```bash
curl -fsSL https://claude.ai/install.sh | bash
```

安装结果：

![QQ20260419-155708](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604191607109.png)

步骤2：

将如下内容写到 `~/.claude/settings.json` 最后

```
{
  "env": {
    "ANTHROPIC_BASE_URL": "https://www.packyapi.com",
    "ANTHROPIC_AUTH_TOKEN": "请输入密钥",
    "CLAUDE_CODE_ATTRIBUTION_HEADER": "0",
    "CLAUDE_CODE_DISABLE_NONESSENTIAL_TRAFFIC": "1",
    "CLAUDE_CODE_DISABLE_TERMINAL_TITLE": "1"
  }
}
```

步骤3：

在项目根目录中输入 `Claude` 指令

步骤4：

基本设置

![image-20260419163751992](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604191638869.png)

![image-20260419163810398](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604191638553.png)

![image-20260419163829275](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604191638156.png)

![image-20260419163855366](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604191638064.png)

步骤5：

连接测试

![image-20260419165609402](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604191656610.png)

安装完成



### 在 Claude Code 中使用 Codex 模型

同样使用 PackyAPI 进行中转

步骤1：

在 WSL2 中安装 CC-Switch CLI

```bash
# 下载
curl -LO https://github.com/saladday/cc-switch-cli/releases/latest/download/cc-switch-cli-linux-x64-musl.tar.gz

# 解压
tar -xzf cc-switch-cli-linux-x64-musl.tar.gz

# 添加执行权限
chmod +x cc-switch

# 移动到 PATH
sudo mv cc-switch /usr/local/bin/
```

步骤2：

在 CC-Switch CLI 中配置 Claude Code

```bash
# 启动 CC-Switch CLI
cc-switch
```

下拉在左侧选择 `Providers` ，回车选中，并按下 `a` 键，进入供应商添加页面

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604200925542.webp)

在上方模板中选择 `PackyCode`

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604200925238.webp)

在 `Api Key` 处填写你的 Apikey 回车，并按下 `Ctrl+S` 进行保存，`Api Key` 分组选择可用于 Claude Code 的 Codex 分组 (`cxtocc`)

![img](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604200925248.webp)

确保此时选中的是刚才配置的 Provider，然后在左侧菜单中退出 CC Switch CLI

步骤3：

查找 PackyAPI 中 `cxtocc` 分组中的模型，这里选择 `gpt-5.3-codex-medium`，通过如下方式在项目根目录中打开 Claude Code

```bash
claude --model gpt-5.3-codex-medium
```

![image-20260420093410807](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2026/202604200934069.png)

可以在 `.zshrc` 或 `.bashrc` 文件最后写入如下快捷命令

```bash
alias claude_codex='claude --model gpt-5.3-codex-medium'
```

之后就可以通过如下命令启动使用 `gpt-5.3-codex-medium` 模型的 Cluade Code 了
```bash
claude_codex
```



## VS Code + LaTeX + Cursor 的科研论文组合











## 参考资料

[1] [【AI编程工具】用国产替代模型入坑Claude Code吧】](https://www.bilibili.com/video/BV1FYvZBSEd9/)

[2] [【科研论文党王炸组合overleaf+Copilot】](https://www.bilibili.com/video/BV1RQALePEuu)

