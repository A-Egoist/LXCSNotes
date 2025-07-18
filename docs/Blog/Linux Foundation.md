## Linux 基础
### 关机和重启
1. 关机

    ```bash
    sudo shutdown -h now
    ```

2. 重启

    ```bash
    sudo shutdown -r now
    ```

### 常用文件管理及系统命令



#### 用户组管理



#### 用户管理

1. 添加用户

```bash
adduser username
```

2. 修改密码

```bash
passwd username
```



## tmux

功能: 

1.   分屏.
2.   允许断开 Terminal 连接后, 继续运行进程.

结构: 

*   一个 tmux 可以包含多个 session, 一个 session 可以包含多个 window, 一个 window 可以包含多个 pane.

*   实例:

    >   tmux: 
    >
    >   ​	session 0:
    >
    >   ​		window 0:
    >
    >   ​			pane 0
    >
    >   ​			pane 1
    >
    >   ​			pane 2
    >
    >   ​			...
    >
    >   ​		window 1
    >
    >   ​		window 2
    >
    >   ​	session 1

*   操作

    1.   tmux: 新建一个 session, 其中包含一个 window, window 中包含一个 pane, pane 里打开了一个 shell 对话框
    2.   按下 `Ctrl + b` 后手指松开, 然后按 `%`: 将当前 pane 左右平分成两个 pane.
    3.   按下 `Ctrl + b` 后手指松开, 然后按 `"`: 将当前 pane 上下平分成两个 pane.
    4.   `Ctrl + d`: 关闭当前 pane (如果当前window的所有pane均已关闭, 则自动关闭window; 如果当前session的所有window均已关闭, 则自动关闭session).
    5.   鼠标点击可以选 pane.
    6.   按下`ctrl + b` 后手指松开, 然后按方向键: 选择相邻的 pane.
    7.   鼠标拖动 pane 之间的分割线, 可以调整分割线的位置.
    8.   按住 `ctrl + b` 的同时按方向键, 可以调整 pane 之间分割线的位置.
    9.   按下 `ctrl + b` 后手指松开, 然后按 z: 将当前 pane 全屏/取消全屏.
    10.   按下 `ctrl + b` 后手指松开, 然后按 d: 挂起当前 session.
    11.   tmux a: 打开之前挂起的 session.
    12.   按下 `ctrl + b` 后手指松开, 然后按 s: 选择其它 session
          *    方向键上: 选择上一项 session/window/pane
          *    方向键下: 选择下一项 session/window/pane
          *    方向键左: 展开当前项 session/window
          *    方向键右: 闭合当前项 session/window
    13.   按下 `Ctrl + b` 后手指松开, 然后按 `c`: 在当前 session 中创建一个新的 window.
    14.   按下 `Ctrl + b` 后手指松开, 然后按 `w`: 选择其他 window, 操作方法与(12) 完全相同.
    15.   按下 `Ctrl + b` 后手指松开, 然后按 `PageUp`: 翻阅当前 pane 内的内容.
    16.   鼠标滚轮: 翻阅当前 pane 内的内容.
    17.   在 tmux 中选中文本时, 需要按住 `shift` 键。(仅支持Windows和Linux, 不支持Mac, 不过该操作并不是必须的, 因此影响不大).
    18.   tmux 中复制/粘贴文本的通用方式: 
          *   按下 `Ctrl + b` 后松开手指, 然后按 `[`.
          *   用鼠标选中文本, 被选中的文本会被自动复制到 tmux 的剪贴板.
          *   按下 `Ctrl + b` 后松开手指, 然后按 `]`, 会将剪贴板中的内容粘贴到光标处.

### 参考资料

[tmux常用命令](https://www.cnblogs.com/lizhang4/p/7325086.html)

## vim


## 解压文件
![[Ubuntu 中解压文件]]
## wget
![[wget]]