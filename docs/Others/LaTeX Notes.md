# LaTeX Notes

## LaTeX 的基本概念

### Hello World

```latex
\documentclass{article}
\begin{document}
"Hello World!" from \LaTeX
\end{document}
```

将上述代码保存到 `helloworld.tex` 文件中.

### 在命令行中编译

```bash
pdflatex helloworld
```

或者

```bash
xelatex helloworld
```

### LaTeX 命令和代码结构

#### LaTeX 命令和环境

字母形式的 LaTeX 命令忽略其后的所有连续空格. 如果要人为引入空格, 需要在命令后面加上一对花括号阻止其忽略空格, 或者在命令后面加上命令 `\␣`(反斜杠加上空格)代表插入一个间距. 

```latex
\TeX users
\TeX{} users
\TeX\ users
```

一些 LaTeX 命令可以接收一些参数, 参数分为可选参数和必选参数. 可选参数以方括号 `[` 和 `]` 包裹; 必选参数一般以花括号 `{` 和 `}` 包裹. 还有些命令可以带一个星号 `*`, 带星号和不带星号的命令效果有一定差异. 初次接触这些概念时, 可以粗略地把星号看作一种特殊的可选参数.

LaTeX 中还包括环境, 用以令一些效果在局部生效, 或是生成特殊的文档元素. LaTeX 环境的用法为一对命令 `\begin` 和 `\end`.

```latex
\begin{<environment name>}[<optional arguments>]{<mandatory arguments>}
\end{<environment name>}
```

其中 ⟨environment name⟩ 为环境名, `\begin` 和 `\end` 中填写的环境名应当一致. 类似命令,  {⟨mandatory arguments⟩} 和 [⟨optional arguments⟩] 为环境所需的必选和可选参数.

有些命令(如 `\bfseries`)会对其后所有内容产生作用. 若要限制其作用范围, 则需要使用分组. LaTeX 使用一对花括号 `{` 和 `}` 作为分组, 在分组中使用的命令被限制在分组内, 不会影 响到分组外的内容. LaTeX 环境隐含了一个分组, 在环境中的命令被包裹在分组内.

#### LaTeX 源代码结构

```latex
\documentclass{...}  % ... 为某文档类
% 导言区, 使用 \usepackage 命令调用宏包, 还可以进行文档的全局设置
\begin{document}
% 正文内容
\end{document}
% 此后内容会被忽略
```

### LaTeX 宏包和文档类

#### 文档类

文档类规定了 LaTeX 源代码所要生成的文档的性质——普通文章、书籍、演示文稿、个人简历等等. LaTeX 源代码的开头需用 `\documentclass` 指定文档类: 

```latex
\documentclass[<options>]{<class-name>}
```

#### 宏包

在使用 LaTeX 时, 时常需要依赖一些扩展来增强或补充 LaTeX 的功能, 比如排版复杂的表 格、插入图片、增加颜色甚至超链接等等. 这些扩展称为宏包. 调用宏包的方法非常类似调用文 档类的方法: 

```latex
\usepackage[<options>]{<package-name>}
```

在命令行查看宏包的说明文档

```bash
texdoc <package-name>
```

### LaTeX 用到的文件一览

`.tex` 源代码文件.

`.sty` 宏包文件.

`.bib` bibTeX 参考文献数据库文件.

`.bst` bibTeX 用到的参考文献格式模板.

### 文件的组织方式

当编写长篇文档时, 例如当编写书籍、毕业论文时, 单个源文件会使修改、校对变得十分困难. 将源文件分割成若干个文件, 例如将每章内容单独写在一个文件中, 会大大简化修改和校对的工作.

LaTeX 中提供了 `\include` 命令用于在源代码中插入文件: 

```latex
\include{<filename>}
```

`\include` 命令在读入 <filename> 之前会另起一页. 有的时候我们并不需要这样, 而是用 `\input` 命令, 它纯粹是把文件里的内容插入: 

```latex
\input{<filename>}
```



## 用 LaTeX 排版文字

### UTF-8 编码

Unicode 是一个多国字符的集合, 覆盖了几乎全球范围内的语言文字. UTF-8 是 Unicode 的一套编码方案, 一个字符由一个到四个字节编码, 其中单字 节字符的编码与 ASCII 编码兼容. 现行版本的 LaTeX 使用 UTF-8 作为默认编码.

### 排版中文

ctex 宏包本身用于配合各种文档类排版中文, 而 ctex 文档类对 LaTeX 的标准文档类进行了封装, 对一些排版根据中文排版习惯做了调整, 包括 ctexart、ctexrep、 ctexbook 等. ctex 宏包和文档类能够识别操作系统和 TeX 发行版中安装的中文字体, 因此基本无需额外配置即可排版中文文档. 下面举一个使用 ctex 文档类排版中文的最简例子: 

```latex
\documentclass{ctexart}
\begin{document}
在\LaTeX{}中排版中文. 汉字和English单词混排, 通常不需要在中英文之间添加额外的空格. 
当然, 为了代码的可读性, 加上汉字和 English 之间的空格也无妨. 
汉字换行时不会引入多余的空格.
\end{document}
```

注意源代码须保存为 UTF-8 编码, 并使用 xelatex 或 lualatex 命令编译.

### 符号

文字在单词间的“空格”处断行时, “空格”生成的间距随之舍去. 我们可以使用字符 `~` 输入一个不会断行的空格(高德纳称之为 tie, “带子”), 通常用在英文人名、图表名称等上下文环境: 

```latex
Fig.~2a\\
Donald~E. Knuth
```



## 文档元素

### 章节和目录

#### 章节标题

article 文档类带编号的层级为 `\section`, `\subsection`, `\subsubsection` 三级. report 和 book 文档类带编号的层级为 `\chapter`, `\section`, `\subsection` 三级.

`\section[<short title>]{<title>}` 标题使用 <title> 参数, 在目录和页眉页脚中使用 <short title> 参数.

#### 目录

生成目录使用 `\tableofcontents` 命令, 要想正确的生成目录, 一般需要编译两次源代码.

### 标题页

标题: `\title{<title>}`

作者: `\author{<author>}`

目录: `\date{<date>}`

在正文部分使用 `\maketitle` 命令生成标题页

```latex
\title{Test title}
\author{ Mary\thanks{E-mail:*****@***.com}
  \and Ted\thanks{Corresponding author}
  \and Louis}
\date{\today}
```

### 交叉引用

在被引用的地方使用 `\label{<label-name>}`, 然后在引用的地方使用 `\ref{<label-name>}` 命令生成交叉引用的编号或者使用 `\pageref{<label-name>}` 命令生成交叉引用的页码. 为了生成正确的交叉引用, 一般也需要多次编译源代码.

`\label` 命令可用于记录各种类型的交叉引用, 使用位置分别为:

*   章节标题: 在章节标题命令 `\section` 等之后紧接着使用.
*   行间公式: 单行公式在公式内任意位置使用; 多行公式在每一行公式的任意位置使用.
*   有序列表: 在 enumerate 环境的每个 `\item` 命令之后、下一个 `\item` 命令之前任意位置使用.
*   图表标题: 在图表标题命令 `\caption` 之后紧接着使用.
*   定理环境: 在定理环境内部任意位置使用.

在使用不记编号的命令形式(`\section*`、`\caption*`、带可选参数的 `\item` 命令等)时不要使用 `\label` 命令，否则生成的引用编号不正确.

### 脚注

使用 `\footnote{<footnote>}` 命令可以在页面底部生成一个脚注: 

```latex
\footnote{<footnote>}
```

例如: 

```latex
"天地玄黄, 宇宙洪荒. 日月盈昃, 辰宿列张."\footnote{出自《千字文》.}
```

有些情况下(比如在表格环境、各种盒子内)使用 `\footnote` 并不能正确生成脚注. 我们可以分两步进行, 先使用 `\footnotemark` 为脚注计数, 再在合适的位置用 `\footnotetext` 生成脚注. 比如: 

```latex
\begin{tabular}{l}
\hline
"天地玄黄, 宇宙洪荒. 日月盈昃, 辰宿列张."\footnotemark \\ 
\hline
\end{tabular}
\footnotetext{表格里的名句出自《千字文》.}
```

### 特殊环境

#### 列表环境

*   有序列表环境: enumerate. 使用 `\item` 标明每个列表项.
    ```latex
    \begin{enumerate}
    \item ...
    \end{enumerate}
    ```

*   无需列表环境: itemize. 使用 `\item` 标明每个列表项.
    ```latex
    \begin{itemize}
    \item ...
    \end{itemize}
    ```

`\item` 可带一个可选参数, 将有序列表的计数或者无序列表的符号替换成自定义的符号. 列表可以嵌套使用, 最多嵌套四层.

#### 对齐环境

center、flushleft 和 flushright 环境分别用于生成居中、左对齐和右对齐的文本环境.

除此之外, 还可以用以下命令直接改变文字的对齐方式: `\centering`, `\raggedright`, `\raggedleft`.

上述三个环境和三个命令的区别在于: center 等环境会在上下文产生一个额外间距, 而 `\centering` 等命令不产生, 只是改变对齐方式. 比如在浮动体环境 table 或 figure 内实现居中对齐, 用 `\centering` 命令即可, 没必要再用 center 环境.

#### 引用环境

LaTeX 提供了两种引用环境: quote 用于引用较短的文字, 首行不缩进; quotation 用于引用若干段文字, 首行缩进. 引用环境较一般文字有额外的左右缩进.

#### 摘要环境

摘要环境 abstract 默认只在标准文档类中的 article 和 report 文档类可用, 一般用于紧跟 `\maketitle` 命令之后介绍文档的摘要. 如果文档类指定了 titlepage 选项, 则单独成页; 反之, 单栏排版时相当于一个居中的小标题加一个 quotation 环境, 双栏排版时相当于 `\section*` 定义的一节.

#### 代码环境

代码环境 verbatim

### 表格





### 图片

LaTeX 插入图片需要使用 graphicx 宏包支持, 使用 xelatex 编译, 支持的图片格式有: `.pdf`, `.eps`, `.jpg`, `.png`, `.bmp`.

使用 `\includegraphics` 命令加载图片:
```latex
\includegraphics[<options>]{<filename>}
```

### 盒子

### 浮动体

内容丰富的文章或者书籍往往包含许多图片和表格等内容. 这些内容的尺寸往往太大, 导致分页困难. LaTeX 为此引入了浮动体的机制, 令大块的内容可以脱离上下文, 放置在合适的位置. LaTeX 预定义了两类浮动体环境 figure 和 table. 习惯上 figure 里放图片, table 里放表格, 但并没有严格限制, 可以在任何一个浮动体里放置文字、公式、表格、图片等等任意内容.

```latex
\begin{table}[<placement>]
...
\end{table}
```

⟨placement⟩ 参数提供了一些符号用来表示浮动体允许排版的位置, 如 hbp 允许浮动体排版在当前位置、底部或者单独成页. table 和 figure 浮动体的默认设置为 tbp.

#### 浮动体的标题

图表等浮动体使用 `\caption` 命令添加标题, 并自动给浮动体编号.

## 排版数学公式

本章介绍的许多命令和环境依赖于 amsmath 宏包, 假定导言区都写有

```latex
\usepackage{amsmath}
```

### 公式排版基础

#### 行内公式和行间公式

行内公式使用一对 `$` 包裹. 单独成行的公式在 LaTeX 里由 equation 环境包裹. equation 环境为公式自动生成一个编号, 这个编号可以用 `\label` 和 `\ref` 生成交叉引用, amsmath 的 `\eqref` 命令甚至为引用自动加上圆括号; 还可以用 `\tag` 命令手动修改公式的编号, 或者用 `\notag` 命令取消为公式编号(与之基本等效的命令是 `\nonumber`).

如果需要直接使用不带编号的行间公式, 则将公式用命令 `\[` 和 `\]` 包裹(不推荐使用 `$$` 命令包裹), 与之等效的是 displaymath 环境. 有的人更喜欢 equation* 环境, 体现了带星号和不带星号的环境之间的区别.

### 数学符号

#### 一般符号

#### 指数、上下标和导数

#### 分式和根式

分式使用 `\frac{分子}{分母}` 来书写. 分式的大小在行间公式中是正常大小, 而在行内被极度压缩. amsmath 提供了方便的命令 `\dfrac` 和 `\tfrac`, 令用户能够在行内使用正常大小的分式, 或是反过来.

一般的根式使用 `\sqrt{...}`; 表示 n 次方根时写成 `\sqrt[n]{...}`.

### 多行公式

#### 长公式折行

amsmath 宏包的 multline 环境提供了书写折行长公式的方便环境. 它允许用 `\\` 折行, 将公式编号放在最后一行. 多行公式的首行左对齐, 末行右对齐, 其余行居中.

#### 多行公式

最常用的是 align 环境，它将公式用 `&` 隔为两部分并对齐. 分隔符通常放在等号左边. align 环境会给每行公式都编号. 我们仍然可以用 `\notag` 去掉某行的编号.

```latex
\begin{align}
a & = b + c \\
  & = d + e 
\end{align}
```

align 还能够对齐多组公式, 除等号前的 `&` 之外, 公式之间也用 `&` 分隔.

```latex
\begin{align}
a &= 1  & b &= 2  & c &= 3 \\
d &= -1 & e &= -2 & f &= -5 
\end{align}
```

如果我们不需要按等号对齐, 只需罗列数个公式, gather 将是一个很好用的环境. align 和 gather 有对应的不带编号的版本 align* 和 gather*.

#### 公用编号的多行公式

另一个常见的需求是将多个公式组在一起公用一个编号, 编号位于公式的居中位置. 为此, amsmath 宏包提供了诸如 aligned、gathered 等环境, 与 equation 环境套用. 以 -ed 结尾的环境用法与前一节不以 -ed 结尾的环境用法一一对应. 我们仅以 aligned 举例: 

```latex
\begin{equation}
  \begin{aligned}
  a &= b + c \\
  d &= e + f + g \\
  h + i &= j + k \\
  l + m &= n
  \end{aligned}
\end{equation}
```

$$
\begin{equation}
  \begin{aligned}
  a &= b + c \\
  d &= e + f + g \\
  h + i &= j + k \\
  l + m &= n
  \end{aligned}
\end{equation}
$$



### 数组和矩阵

数组可作为一个公式块, 在外套用 `\left`、`\right` 等定界符.

```latex
\[
\mathbf{X} =
\left(
  \begin{array}{cccc}
  x_{11} & x_{12} & \ldots & x_{1n}\\
  x_{21} & x_{22} & \ldots & x_{2n}\\
  \vdots & \vdots & \ddots & \vdots\\
  x_{n1} & x_{n2} & \ldots & x_{nn}\\
  \end{array}
\right) 
\]
```

$$
\mathbf{X} =
\left(
  \begin{array}{cccc}
  x_{11} & x_{12} & \ldots & x_{1n}\\
  x_{21} & x_{22} & \ldots & x_{2n}\\
  \vdots & \vdots & \ddots & \vdots\\
  x_{n1} & x_{n2} & \ldots & x_{nn}\\
  \end{array}
\right)
$$

值得注意的是, 上一节末尾介绍的 aligned 等环境也可以用定界符包裹. 我们还可以利用空的定界符排版出这样的效果: 

```latex
\[
|x| = 
\left\{
\begin{array}{rl}
-x & \text{if } x < 0,\\
0 & \text{if } x = 0,\\
x & \text{if } x > 0.
\end{array} 
\right. 
\]
```

$$
|x| = 
\left\{
\begin{array}{rl}
-x & \text{if } x < 0,\\
0 & \text{if } x = 0,\\
x & \text{if } x > 0.
\end{array} 
\right.
$$

不过上述例子可以用 amsmath 提供的 cases 环境更轻松地完成: 

```latex
\[
|x| =
\begin{cases}
-x & \text{if } x < 0,\\
0 & \text{if } x = 0,\\
x & \text{if } x > 0.
\end{cases} 
\]
```

$$
|x| =
\begin{cases}
-x & \text{if } x < 0,\\
0 & \text{if } x = 0,\\
x & \text{if } x > 0.
\end{cases}
$$

## 排版样式设定

## 特色工具和功能

### 参考文献和 bibTeX

### 索引和 makeindex 工具

### 使用颜色

### 使用超链接



## 其他

### 使用 LaTeX/XeLaTeX 编辑中文

#### method 1: 使用 ctexart 文档类型

```latex
\documentclass{ctexart}
\begin{document}
	你好！
\end{document}
```



#### method 2: 使用 ctex 宏包

```latex
\documentclass{article}
\usepackage[UTF8]{ctex}
\begin{document}
    你好！
\end{document}
```



## 参考资料

[1] [如何使用 LaTeX/XeLaTeX 编辑中文？](https://zhuanlan.zhihu.com/p/27739925)

[2] [TeX 家族（TeX, XeTeX, LuaTeX,XeLaTeX …看完这篇就懂了）](https://zhuanlan.zhihu.com/p/248669482)

[3] [一份（不太）简短的 LaTeX2ε 介绍](https://mirrors.sustech.edu.cn/CTAN/info/lshort/chinese/lshort-zh-cn.pdf)

