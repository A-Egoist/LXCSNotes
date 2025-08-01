# 5 git

## github 工作流

```bash
# 复制 remote 仓库到本地
git clone https://github.com/A-Egoist/WebServer.git

# 建立新的 feature branch
git checkout -b my-feature

# 修改文件
git add <changed_files>
git commit -m "Comments"

# 将 local 的代码上传到 remote 的 my-feature 分支
git push origin my-feature
```

若在准备提交 `pull request` 的时候，发现 remote 的 main 分支存在新的提交，需要解决冲突：

>   若此时发现在 github 上的内容已经发生改变 (main 分支中增加了一个 update)，则不能直接提交 Pull Requests (PR)，而应该测试一下我们新提交的内容(new_branch 分支中的新增内容)在 github 上新增 update 的基础上还能否继续使用。

```bash
# 同步 remote(main) 的最新代码到 local(main)
git checkout main
git pull origin main

# 在 local 的 my-feature 分支解决冲突
git checkout my-feature
git rebase main
# 手动解决冲突文件

# 将解决冲突后的文件提交到 remote, 加上 -f 是因为我们在 push 之前已经 rebase 了
git push -f origin my-feature
```

若不需要解决冲突，可以直接提交 `pull request`：

1.   在 GitHub 上向 main 分支提交 `Pull request`
2.   使用 `Squash and merge`，将 commit 合并为一个 commit
3.   在 GitHub 上 `Delete branch`

在删除 remote 的 my-feature 分支后需要同步结果到 local：

```bash
# 在 local 删掉 my-feature 分支
git checkout main
git branch -D my-feature
```

最后，更新 local 的 main 分支：

```bash
# 拉取最新的更新
git pull origin main
```

[【十分钟学会正确的github工作流，和开源作者们使用同一套流程】](https://www.bilibili.com/video/BV19e4y1q7JJ/?share_source=copy_web&vd_source=b5ed364998fc1b958c57abd6dbda38e3)

```mermaid
graph TD
    A[从 main 创建新分支] --> B[进行开发工作]
    B --> C[推送分支到 GitHub]
    C --> D[创建 Pull Request]
    D --> E[代码审查和讨论]
    E --> F[通过 CI/CD 测试]
    F --> G[合并到 main]
    G --> H[立即部署到生产环境]
    H --> I[删除功能分支]
```

## git常用命令

**全局设置**

`git config --global user.name xxx`: 设置全局用户名，信息记录在`~/.gitconfig`文件中
`git config --global user.email xxx@xxx.com`: 设置全局邮箱地址，信息记录在`~/.gitconfig`文件中
`git init`: 将当前目录配置成git仓库，信息记录在隐藏的.git文件夹中

**常用命令**

`git add XX` : 将XX文件添加到暂存区
`git add .`: 将所有待加入暂存区的文件放入暂存区
`git commit -m "给自己看的备注信息"`: 将暂存区的内容提交到当前分支
`git status`: 查看仓库状态
`git log`: 查看当前分支的所有版本
`git push -u (第一次需要-u以后不需要) `: 将当前分支推送到远程仓库
`git clone git@git.acwing.com:xxx/XXX.git`: 将远程仓库XXX下载到当前目录下
`git branch`: 查看所有分支和当前所处分支

**查看命令**

`git diff XX`: 查看XX文件相对于暂存区修改了哪些内容
`git status`: 查看仓库状态
`git log`: 查看当前分支的所有版本
`git log --pretty=oneline`: 用一行来显示
`git reflog`: 查看HEAD指针的移动历史（包括被回滚的版本）
`git branch`: 查看所有分支和当前所处分支
`git pull`: 将远程仓库的当前分支与本地仓库的当前分支合并

**删除命令**

`git rm --cached XX`: 将文件从仓库索引目录中删掉，==不希望管理这个文件==
`git restore --staged xx`: ==将xx从暂存区里移除==
`git checkout — XX`或``git restore XX`: ==将XX文件尚未加入暂存区的修改全部撤销==

**代码回滚**

`git reset --hard HEAD^` 或`git reset --hard HEAD~`: 将代码库回滚到上一个版本
*   `git reset --hard HEAD^^`: 往上回滚两次，以此类推
*   `git reset --hard HEAD~100`: 往上回滚100个版本
*   `git reset --hard 版本号`: 回滚到某一特定版本

**远程仓库**

`git remote add origin git@git.acwing.com:xxx/XXX.git`: 将本地仓库关联到远程仓库
`git push -u` (第一次需要-u以后不需要) : 将当前分支推送到远程仓库
`git push origin branch_name`: 将本地的某个分支推送到远程仓库
`git clone git@git.acwing.com:xxx/XXX.git`: 将远程仓库XXX下载到当前目录下
`git push --set-upstream origin branch_name`: 设置本地的`branch_name`分支对应远程仓库的`branch_name`分支
`git push -d origin branch_name`: 删除远程仓库的`branch_name`分支
`git checkout -t origin/branch_name`: 将远程的`branch_name`分支拉取到本地
`git pull` : 将远程仓库的当前分支与本地仓库的当前分支合并
`git pull origin branch_name`: 将远程仓库的`branch_name`分支与本地仓库的当前分支合并
`git branch --set-upstream-to=origin/branch_name1 branch_name2`: 将远程的`branch_name1`分支与本地的`branch_name2`分支对应

**分支命令**

`git branch`: 查看所有分支和当前所处分支
`git branch branch_name`: 创建新分支
`git checkout -b branch_name`: 创建并切换到`branch_name`这个分支
`git checkout branch_name`: 切换到`branch_name`这个分支
`git merge branch_name`: 将分支`branch_name`合并到当前分支上
`git branch -d branch_name`: 删除本地仓库的`branch_name`分支
`git push --set-upstream origin branch_name`: 设置本地的`branch_name`分支对应远程仓库的`branch_name`分支
`git push -d origin branch_name`: 删除远程仓库的`branch_name`分支
`git checkout -t origin/branch_name`: 将远程的`branch_name`分支拉取到本地
`git pull`: 将远程仓库的当前分支与本地仓库的当前分支合并
`git pull origin branch_name`: 将远程仓库的`branch_name`分支与本地仓库的当前分支合并
`git branch --set-upstream-to=origin/branch_name1 branch_name2`: 将远程的`branch_name1`分支与本地的`branch_name2`分支对应

**stash暂存**

`git stash`: 将工作区和暂存区中尚未提交的修改存入栈中
`git stash apply`: 将栈顶存储的修改恢复到当前分支，但不删除栈顶元素
`git stash drop`: 删除栈顶存储的修改
`git stash pop`: 将栈顶存储的修改恢复到当前分支，同时删除栈顶元素
`git stash list`: 查看栈中所有元素



## 其他常见问题

### 1. 将本地git仓库绑定的HTTP连接切换为ssh连接

1.   检查当前远程仓库地址
     ```bash
     git remote -v
     ```

2.   替换为ssh地址
     ```bash
     git remote set-url origin 新的ssh地址
     ```

3.   验证是否切换成功
     ```bash
     git remote -v
     ```

### 2. 配置ssh密钥

1.   生成ssh密钥
     ```bash
     ssh-keygen -t ed25519 -C "your_email@example.com"
     ```

2.   将公钥添加到github
     ```bash
     cat ~/.ssh/id_ed25519.pub | clip   # PowerShell
     ```

     将 `id_ed25519.pub` 复制到 GitHub $\to$ Settings $\to$ SSH and GPG keys $\to$ New SSH key。

## 参考资料

* [十分钟学会正确的github工作流，和开源作者们使用同一套流程](https://www.bilibili.com/video/BV19e4y1q7JJ/)

* [GitHub 流](https://docs.github.com/zh/get-started/quickstart/github-flow)

* [一文弄懂 Gitflow、Github flow、Gitlab flow 的工作流](https://cloud.tencent.com/developer/article/1646937)
* [PyCharm中使用Git/GitHub详细步骤（图文详解）](https://blog.csdn.net/Q0717168/article/details/108719275)