# GitHub Workflow

## 基本流程

1. 把远程仓库克隆到本地

   ```bash
   git clone xxxx.git
   ```

2. 在本地切换至新的分支

   ```bash
   git checkout -b new_branch
   ```

3. 修改本地仓库的文件

4. 项目修改完成后，查看修改的内容

   ```bash
   git diff
   ```

5. 上传修改之后的内容到本地暂存区

   ```bash
   git add modified_files
   ```

6. 将本地暂存区的代码更新到本地 git

   ```bash
   git commit -m [message]
   ```

   [message] 是一些备注信息

7. 将本地 git 的内容更新到 github 上

   ```bash
   git push origin new_branch
   ```

   执行之后，github 上多了 new_branch 这个分支

8. 若此时发现在 github 上的内容已经发生改变 (main 分支中增加了一个 update)，则不能直接提交 Pull Requests (PR)，而应该测试一下我们新提交的内容(new_branch 分支中的新增内容)在 github 上新增 update 的基础上还能否继续使用。

9. 将 github 中 main 分支中的 update 同步到本地

   ```bash
   git checkout main
   git pull origin main
   ```

10. 回到 new_branch 分支，并比较 update 的内容和 new_branch 中的内容差别

    ```bash
    git checkout new_branch
    git rebase main
    ```

    `git rebase main` 表示把 update 的内容放进项目中，然后再把 new_branch 中新修改的内容添加进去。

    在这个过程中可能会出现 rebase conflict，若出现这个冲突，则需要我们手动的去选择需要保留哪些内容

11. 合并完成之后，再将 new_branch 的内容上传

    ```bash
    git push -f origin main
    ```

    加上 `-f` 是因为我们在 push 之前已经 rebase 了

12. 然后再 github 上 `Pull Requests`

13. 项目的主人在收到 `Pull Requests` 之后，会 `Squash and merge` 不同的 commit，然后删除远端的 new_branch 分支

    `squash and merge` 表示将 new_branch 分支上的所有改变合并成一个改变，然后把这个 commit 放到 main 分支上

14. 远端更新完成后，就可以删除本地的分支，并把最新的内容拉取到本地

    ```bash
    git branch -d new_branch
    git pull origin main
    ```

    





## 参考资料

* [十分钟学会正确的github工作流，和开源作者们使用同一套流程](https://www.bilibili.com/video/BV19e4y1q7JJ/)

* [GitHub 流](https://docs.github.com/zh/get-started/quickstart/github-flow)

* [一文弄懂 Gitflow、Github flow、Gitlab flow 的工作流](https://cloud.tencent.com/developer/article/1646937)
* [PyCharm中使用Git/GitHub详细步骤（图文详解）](https://blog.csdn.net/Q0717168/article/details/108719275)