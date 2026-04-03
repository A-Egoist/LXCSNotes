# Java 基础



## 基础知识

### JVM vs JDK vs JRE

*   JVM(Java Virtual Machine)
*   JDK(Java Development Kit)
*   JRE(Java Runtime Environment)

![jdk-include-jre](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202604031120149.png)



### Java 程序从源代码到运行过程

使用 `javac` 可以将 `.java` 源码编译成 `.class` 字节码；

使用 `java` 可以运行一个已编译的 Java 程序，参数是类名。

![Java 程序从源代码到运行过程示意图](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202604031128076.png)



### Java 命令行编译和运行

一个 Java 源码只能定义一个 `public` 类型的 class，并且 class 名称和 `.java` 文件名要完全一致；

Java 入口程序规定的方法必须是静态方法，方法名必须为 `main`，括号内的参数必须是 String 数组：

```java
public class Hello {
    public static void main(String[] args) {
        Systems.out.println("Hello, world!");
    }
}
```

这个命令行参数由 JVM 接收用户输入并传给 `main` 方法：

```java
public class Main {
    public static void main(String[] args) {
        for (String arg : args) {
            System.out.println(arg);
        }
    }
}
```

可以利用接收到的命令行参数，根据不同的参数执行不同的代码。例如，实现一个 `-version` 参数，打印程序版本号：

```java
public class Main {
    public static void main(String[] args) {
        for (String arg : args) {
            if ("-version".equals(arg)) {
                System.out.println("v 1.0");
                break;
            }
        }
    }
}
```

上面这个程序必须在命令行执行，先编译它：

```bash
javac Main.java
```

然后，执行的时候，传递一个 `-version` 参数：

```bash
java Main -version
```

这样，程序就可以根据传入的命令行参数，作出不同的响应。



### 注释

1.   单行注释
     ```java
     // 单行注释
     ```

     

2.   多行注释</br>
     以 `/*` 星号开头，以 `*/` 结束，可以有多行：

     ```java
     /*
     多行注释
     多行注释
     多行注释
     */
     ```

     

3.   文档注释（特殊的多行注释）</br>
     以 `/**` 开头，以 `*/` 结束，如果有多行，每行通常以星号开头：

     ```java
     /**
     * 可以用来自动创建文档的注释
     * @auther Amonologue
     */
     ```

     这种特殊的多行注释需要写在类和方法的定义处，可以用于自动创建文档。



### 基本数据类型

基本数据类型是 CPU 可以直接进行运算的类型。Java 定义了以下几种基本数据类型：

-   整数类型：byte，short，int，long
-   浮点数类型：float，double
-   字符类型：char
-   布尔类型：boolean

计算机内存的最小存储单元是字节（byte），一个字节就是一个 8 位二进制数，即 8 个 bit。它的二进制表示范围从 00000000 ~ 11111111，换算成十进制是 0 ~ 255，换算成十六进制是 00 ~ FF。

不同的数据类型占用的字节数不一样。我们看一下 Java 基本数据类型占用的字节数：

| 基本类型 | 字节 | 位数 | 默认值  | 取值范围                          |
| -------- | ---- | ---- | ------- | --------------------------------- |
| byte     | 1    | 8    | 0       | $-2^{7}$~ $2^{7}-1$               |
| short    | 2    | 16   | 0       | $-2^{15}$ ~ $2^{15} - 1$          |
| int      | 4    | 32   | 0       | $-2^{31}$ ~ $2^{31}-1$            |
| long     | 8    | 64   | 0L      | $-2^{63}$ ~ $2^{63}-1$            |
| float    | 4    | 32   | 0f      | 1.4E-45 ~ 3.4028235E38            |
| double   | 8    | 64   | 0d      | 4.9E-324 ~ 1.7976931348623157E308 |
| char     | 2    | 16   | 'u0000' | $0$ ~ $2^{16} - 1$                |
| boolean  |      |      | false   | true、false                       |

![8 种基本数据类型](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202604031417035.svg)



#### 整型（byte, short, int, long）

对于整型类型，Java 只定义了带符号的整型，因此，最高位的 bit 表示符号位（0 表示正数，1 表示负数）。各种整型能表示的最大范围如下：

-   byte：-128 ~ 127
-   short: -32768 ~ 32767
-   int: -2147483648 ~ 2147483647
-   long: -9223372036854775808 ~ 9223372036854775807

同一个数的不同进制的表示：例如 `15`=`0xf`＝`0b1111`，其中 `15` 表示十进制，`0xf` 表示十六进制，`0b` 表示二进制。

Java 里使用 `long` 类型的数据一定要在数值后面加上 **L**，否则将作为 `int` 类型解析。



#### 浮点型（float, double）

浮点类型的数就是小数，因为小数用科学计数法表示的时候，小数点是可以“浮动”的，如 $1234.5$ 可以表示成 $12.345\times10^2$，也可以表示成 $1.2345\times10^3$，所以称为浮点数。

下面是定义浮点数的例子：

```java
float f1 = 3.14f;
float f2 = 3.14e38f; // 科学计数法表示的3.14x10^38
float f3 = 1.0; // 错误：不带f结尾的是double类型，不能赋值给float

double d = 1.79e308;
double d2 = -1.79e308;
double d3 = 4.9e-324; // 科学计数法表示的4.9x10^-324
```

`float` 类型的数据一定要在数值后面加上 **f** 或 **F**，否则将无法通过编译。

浮点数可表示的范围非常大，`float` 类型可最大表示 $3.4\times10^{38}$，而 `double` 类型可最大表示$1.79\times10^{308}$。



#### 布尔类型（boolean）

布尔类型 `boolean` 只有 `true` 和 `false` 两个值，布尔类型总是关系运算的计算结果：

```java
boolean b1 = true;
boolean b2 = false;
boolean isGreater = 5 > 3; // 计算结果为true
int age = 12;
boolean isAdult = age >= 18; // 计算结果为false
```

Java 语言对布尔类型的存储并没有做规定，因为理论上存储布尔类型只需要 1 bit，但是通常 JVM 内部会把 `boolean` 表示为 <mark>4 字节整数</mark>。



#### 字符类型（char）

字符类型 `char` 表示一个字符，它是`character`的缩写。Java 的 `char` 类型除了可表示标准的 ASCII 外，还可以表示一个 Unicode 字符：

```java
// 字符类型
public class Main {
    public static void main(String[] args) {
        char a = 'A';
        char zh = '中';
        System.out.println(a);
        System.out.println(zh);
    }
}
```

因为 Java 在内存中总是使用 Unicode 表示字符，所以，一个英文字符和一个中文字符都用一个 `char` 类型表示，它们都占用 2 个字节。要显示一个字符的 Unicode 编码，只需将 `char` 类型直接赋值给 `int` 类型即可：

```java
int n1 = 'A'; // 字母“A”的Unicodde编码是65
int n2 = '中'; // 汉字“中”的Unicode编码是20013
```

还可以直接用转义字符 `\u` + Unicode 编码来表示一个字符：

```java
// 注意是十六进制:
char c3 = '\u0041'; // 'A'，因为十六进制0041 = 十进制65
char c4 = '\u4e2d'; // '中'，因为十六进制4e2d = 十进制20013
```

>   :bulb: Java 中的 `char` 与 CPP 中的 `char` 的内存占用不同，Java 中的 `char` 是两个字节，而 CPP 中的 `char` 只有一个字节。

>   :bulb: ​`char` 类型使用单引号 `'`，且仅有一个字符，要和双引号 `"` 的字符串类型区分开。
>
>   `char a = 'h'`，使用单引号；`String a = "hello"` ，使用双引号。



### 数组类型

int 类型数组代码如下所示：

```java
public class Main {
    public static void main(String[] args) {
        // 5位同学的成绩:
        int[] ns = new int[5];
        ns[0] = 68;
        ns[1] = 79;
        ns[2] = 91;
        ns[3] = 85;
        ns[4] = 62;
    }
}
```

定义一个数组类型的变量，使用数组类型 `类型[]`，例如 `int[]`。和单个基本类型变量不同，数组变量初始化必须使用 `new int[5]` 表示创建一个可容纳 5 个 `int` 元素的数组。

Java 的数组有几个特点：

-   数组所有元素初始化为默认值，整型都是 `0`，浮点型是 `0.0`，布尔型是 `false`；
-   数组一旦创建后，大小就不可改变。

可以用 `数组变量.length` 获取数组大小：

```java
// 数组
public class Main {
    public static void main(String[] args) {
        // 5位同学的成绩:
        int[] ns = new int[5];
        System.out.println(ns.length); // 5
    }
}
```

数组是引用类型，在使用索引访问数组元素时，如果索引超出范围，运行时将报错：

```java
// 数组
public class Main {
    public static void main(String[] args) {
        // 5位同学的成绩:
        int[] ns = new int[5];
        int n = 5;
        System.out.println(ns[n]); // 索引n不能超出范围
    }
}
```

也可以在定义数组时直接指定初始化的元素，这样就不必写出数组大小，而是由编译器自动推算数组大小。例如：

```java
// 数组
public class Main {
    public static void main(String[] args) {
        // 5位同学的成绩:
        int[] ns = new int[] { 68, 79, 91, 85, 62 };
        System.out.println(ns.length); // 编译器自动推算数组大小为5
    }
}
```

还可以进一步简写为：

```java
int[] ns = { 68, 79, 91, 85, 62 };
```

注意数组是引用类型，并且数组大小不可变。我们观察下面的代码：

```java
// 数组
public class Main {
    public static void main(String[] args) {
        // 5位同学的成绩:
        int[] ns;
        ns = new int[] { 68, 79, 91, 85, 62 };
        System.out.println(ns.length); // 5
        ns = new int[] { 1, 2, 3 };
        System.out.println(ns.length); // 3
    }
}
```

数组大小变了吗？看上去好像是变了，但其实根本没变。

对于数组 `ns` 来说，执行 `ns = new int[] { 68, 79, 91, 85, 62 };` 时，它指向一个包含 5 个元素的数组。

执行 `ns = new int[] { 1, 2, 3 };` 时，它指向一个新的包含 3 个元素的数组。

但是，原有的 5 个元素的数组并没有改变，只是无法通过变量 `ns` 引用到它们而已。



使用 Java 标准库提供的 `Arrays.toString()` 快速打印数组内容：

```java
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int[] ns = { 1, 1, 2, 3, 5, 8 };
        System.out.println(Arrays.toString(ns));
    }
}
```



#### 二维数组

二维数组就是数组的数组。定义一个二维数组如下：

```java
// 二维数组
public class Main {
    public static void main(String[] args) {
        int[][] ns = {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 }
        };
        System.out.println(ns.length); // 3
    }
}
```



### 包装类型

>   [java 包装类](https://developer.aliyun.com/article/1191099)
>   基本数据类型不是对象，不能使用类的方法；因此，java针对基本类型提供了它们对应的包装类，八大基本数据类型，对应了八种包装类，以对象的形式来调用。包装类有了类的特点，使我们可以调用包装类中的方法。

![image.png](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202604030025061.png)



### 引用类型

除了上述基本类型的变量，剩下的都是引用类型。例如，引用类型最常用的就是 `String` 字符串：

```java
String s = "hello";
```

引用类型的变量类似于 C 语言的指针，它内部存储一个“地址”，指向某个对象在内存的位置，后续我们介绍类的概念时会详细讨论。



### 常量

定义变量的时候，如果加上 `final` 修饰符，这个变量就变成了常量：

```java
final double PI = 3.14; // PI是一个常量
double r = 5.0;
double area = PI * r * r;
PI = 300; // compile error!
```

常量在定义时进行初始化后就不可再次赋值，再次赋值会导致编译错误。

常量的作用是用有意义的变量名来避免魔术数字（Magic number），例如，不要在代码中到处写 `3.14`，而是定义一个常量。如果将来需要提高计算精度，我们只需要在常量的定义处修改，例如，改成 `3.1416`，而不必在所有地方替换 `3.14`。

为了和变量区分开来，根据习惯，<mark>常量名通常**全部大写**</mark>。

>   类似与 CPP 中的 const 关键字



### var 关键字

有些时候，类型的名字太长，写起来比较麻烦。例如：

```java
StringBuilder sb = new StringBuilder();
```

这个时候，如果想省略变量类型，可以使用 `var` 关键字：

```java
var sb = new StringBuilder();
```

编译器会根据赋值语句自动推断出变量 `sb` 的类型是 `StringBuilder`。对编译器来说，语句：

```java
var sb = new StringBuilder();
```

实际上会自动变成：

```java
StringBuilder sb = new StringBuilder();
```

因此，使用 `var` 定义变量，仅仅是少写了变量类型而已。

>   类似与 CPP 中的 auto 关键字



### 移位运算

在计算机中，整数总是以二进制的形式表示。例如，`int`类型的整数`7`使用4字节表示的二进制如下：

```
00000000 0000000 0000000 00000111
```

可以对整数进行移位运算。对整数`7`左移1位将得到整数`14`，左移两位将得到整数`28`：

```java
int n = 7;       // 00000000 00000000 00000000 00000111 = 7
int a = n << 1;  // 00000000 00000000 00000000 00001110 = 14
int b = n << 2;  // 00000000 00000000 00000000 00011100 = 28
int c = n << 28; // 01110000 00000000 00000000 00000000 = 1879048192
int d = n << 29; // 11100000 00000000 00000000 00000000 = -536870912
```

左移29位时，由于最高位变成`1`，因此结果变成了负数。

类似的，对整数28进行右移，结果如下：

```java
int n = 7;       // 00000000 00000000 00000000 00000111 = 7
int a = n >> 1;  // 00000000 00000000 00000000 00000011 = 3
int b = n >> 2;  // 00000000 00000000 00000000 00000001 = 1
int c = n >> 3;  // 00000000 00000000 00000000 00000000 = 0
```

如果对一个负数进行右移，最高位的`1`不动，结果仍然是一个负数：

```java
int n = -536870912;
int a = n >> 1;  // 11110000 00000000 00000000 00000000 = -268435456
int b = n >> 2;  // 11111000 00000000 00000000 00000000 = -134217728
int c = n >> 28; // 11111111 11111111 11111111 11111110 = -2
int d = n >> 29; // 11111111 11111111 11111111 11111111 = -1
```

还有一种无符号的右移运算，使用`>>>`，它的特点是不管符号位，右移后高位总是补`0`，因此，对一个负数进行`>>>`右移，它会变成正数，原因是最高位的`1`变成了`0`：

```java
int n = -536870912;
int a = n >>> 1;  // 01110000 00000000 00000000 00000000 = 1879048192
int b = n >>> 2;  // 00111000 00000000 00000000 00000000 = 939524096
int c = n >>> 29; // 00000000 00000000 00000000 00000111 = 7
int d = n >>> 31; // 00000000 00000000 00000000 00000001 = 1
```

对`byte`和`short`类型进行移位时，会首先转换为`int`再进行位移。

仔细观察可发现，左移实际上就是不断地×2，右移实际上就是不断地÷2。



### 自动类型转换与强制类型转换

在运算过程中，如果参与运算的两个数类型不一致，那么计算结果为较大类型的整型。例如，`short` 和 `int` 计算，结果总是 `int`，原因是 `short` 首先自动被转型为 `int`：

```java
// 类型自动提升与强制转型
public class Main {
    public static void main(String[] args) {
        short s = 1234;
        int i = 123456;
        int x = s + i; // s自动转型为int
        short y = s + i; // 编译错误!
    }
}
```

也可以将结果强制转型，即将大范围的整数转型为小范围的整数。强制转型使用`(类型)`，例如，将 `int` 强制转型为 `short`：

```java
int i = 12345;
short s = (short) i; // 12345
```

要注意，超出范围的强制转型会得到错误的结果，原因是转型时，`int` 的两个高位字节直接被扔掉，仅保留了低位的两个字节：

```java
// 强制转型
public class Main {
    public static void main(String[] args) {
        int i1 = 1234567;
        short s1 = (short) i1; // -10617
        System.out.println(s1);
        int i2 = 12345678;
        short s2 = (short) i2; // 24910
        System.out.println(s2);
    }
}
```

因此，强制转型的结果很可能是错的。



### 字符串类型

字符类型（`char`）不同，字符串类型 `String` 是引用类型，使用双引号 `"..."` 表示字符串。一个字符串可以存储 0 个到任意个字符：

```java
String s = ""; // 空字符串，包含0个字符
String s1 = "A"; // 包含一个字符
String s2 = "ABC"; // 包含3个字符
String s3 = "中文 ABC"; // 包含6个字符，其中有一个空格
```

因为字符串使用双引号 `"..."` 表示开始和结束，那如果字符串本身恰好包含一个`"`字符怎么表示？例如 `"abc"xyz"`，编译器就无法判断中间的引号究竟是字符串的一部分还是表示字符串结束。这个时候，我们需要借助转义字符 `\`：

```java
String s = "abc\"xyz"; // 包含7个字符: a, b, c, ", x, y, z
```

因为 `\` 是转义字符，所以，两个 `\\` 表示一个 `\` 字符：

```java
String s = "abc\\xyz"; // 包含7个字符: a, b, c, \, x, y, z
```

常见的转义字符包括：

-   `\"` 表示字符 `"`
-   `\'` 表示字符 `'`
-   `\\` 表示字符 `\`
-   `\n` 表示换行符
-   `\r` 表示回车符
-   `\t` 表示Tab
-   `\u####` 表示一个Unicode编码的字符

例如：

```java
String s = "ABC\n\u4e2d\u6587"; // 包含6个字符: A, B, C, 换行符, 中, 文
```



### 字符串连接

Java 的编译器对字符串做了特殊照顾，可以使用 `+` 连接任意字符串和其他数据类型，这样极大地方便了字符串的处理。例如：

```java
// 字符串连接，连接两个 String
public class Main {
    public static void main(String[] args) {
        String s1 = "Hello";
        String s2 = "world";
        String s = s1 + " " + s2 + "!";
        System.out.println(s); // Hello world!
    }
}
```

如果用 `+` 连接字符串和其他数据类型，会<mark>将其他数据类型先自动转型为字符串</mark>，再连接：

```java
// 字符串连接，连接 int 和 String
public class Main {
    public static void main(String[] args) {
        int age = 25;
        String s = "age is " + age;
        System.out.println(s); // age is 25
    }
}
```



## 面向对象编程

### classpath

在 Java 中，我们经常听到 `classpath` 这个东西。网上有很多关于“如何设置 classpath ”的文章，但大部分设置都不靠谱。

到底什么是 `classpath`？

`classpath` 是 JVM 用到的一个环境变量，它用来指示 JVM 如何搜索 `class`。

更好的做法是，不要设置 `classpath`！默认的当前目录 `.` 对于绝大多数情况都够用了。

假设我们有一个编译后的 `Hello.class`，它的包名是 `com.example`，当前目录是 `C:\work`，那么，目录结构必须如下：

```
C:\work
└─ com
   └─ example
      └─ Hello.class
```

运行这个 `Hello.class` 必须在当前目录下使用如下命令：

```plain
C:\work> java -cp . com.example.Hello
```

JVM 根据 classpath 设置的 `.` 在当前目录下查找 `com.example.Hello`，即实际搜索文件必须位于 `com/example/Hello.class`。如果指定的 `.class` 文件不存在，或者目录结构和包名对不上，均会报错。

### jar包

如果有很多 `.class` 文件，散落在各层目录中，肯定不便于管理。如果能把目录打一个包，变成一个文件，就方便多了。

jar 包就是用来干这个事的，它可以把 `package` 组织的目录层级，以及各个目录下的所有文件（包括 `.class` 文件和其他文件）都打成一个 jar 文件，这样一来，无论是备份，还是发给客户，就简单多了。

jar 包实际上就是一个 zip 格式的压缩文件，而 jar 包相当于目录。如果我们要执行一个 jar 包的 `class`，就可以把 jar 包放到 `classpath` 的位置：

```plain
java -cp ./hello.jar abc.xyz.Hello
```

这样 JVM 会自动在 `hello.jar` 文件里去搜索某个类。

那么问题来了：如何创建 jar 包？

因为 jar 包就是 zip 包，所以直接在资源管理器中，找到正确的目录，点击右键，在弹出的快捷菜单中选择“发送到”，“压缩(zipped)文件夹”，就制作了一个 zip 文件。然后，把后缀从 `.zip` 改为 `.jar`，一个 jar 包就创建成功。

假设编译输出的目录结构是这样：

```
package_sample
└─ bin
   ├─ hong
   │  └─ Person.class
   │  ming
   │  └─ Person.class
   └─ mr
      └─ jun
         └─ Arrays.class
```

这里需要特别注意的是，jar 包里的第一层目录，不能是 `bin`，而应该是 `hong`、`ming`、`mr`。



### 字符编码

在早期的计算机系统中，为了给字符编码，美国国家标准学会（American National Standard Institute：ANSI）制定了一套英文字母、数字和常用符号的编码，它占用一个字节，编码范围从 `0` 到 `127`，最高位始终为 `0`，称为 `ASCII` 编码。例如，字符 `'A'` 的编码是 `0x41`，字符 `'1'` 的编码是 `0x31`。

如果要把汉字也纳入计算机编码，很显然一个字节是不够的。`GB2312` 标准使用两个字节表示一个汉字，其中第一个字节的最高位始终为 `1`，以便和 `ASCII` 编码区分开。例如，汉字 `'中'` 的 `GB2312` 编码是 `0xd6d0`。

类似的，日文有 `Shift_JIS` 编码，韩文有 `EUC-KR` 编码，这些编码因为标准不统一，同时使用，就会产生冲突。

为了统一全球所有语言的编码，全球统一码联盟发布了 `Unicode` 编码，它把世界上主要语言都纳入同一个编码，这样，中文、日文、韩文和其他语言就不会冲突。

`Unicode` 编码需要两个或者更多字节表示，我们可以比较中英文字符在 `ASCII`、`GB2312` 和 `Unicode` 的编码：

英文字符 `'A'` 的 `ASCII` 编码和 `Unicode` 编码：

```
         ┌────┐
ASCII:   │ 41 │
         └────┘
         ┌────┬────┐
Unicode: │ 00 │ 41 │
         └────┴────┘
```

英文字符的 `Unicode` 编码就是简单地在前面添加一个 `00` 字节。

中文字符 `'中'` 的 `GB2312` 编码和 `Unicode` 编码：

```
         ┌────┬────┐
GB2312:  │ d6 │ d0 │
         └────┴────┘
         ┌────┬────┐
Unicode: │ 4e │ 2d │
         └────┴────┘
```

那我们经常使用的 `UTF-8` 又是什么编码呢？因为英文字符的 `Unicode` 编码高字节总是 `00`，包含大量英文的文本会浪费空间，所以，出现了 `UTF-8` 编码，它是一种变长编码，用来把固定长度的 `Unicode` 编码变成 1～4 字节的变长编码。通过 `UTF-8` 编码，英文字符 `'A'` 的 `UTF-8` 编码变为 `0x41`，正好和 `ASCII` 码一致，而中文 `'中'` 的 `UTF-8` 编码为 3 字节 `0xe4b8ad`。

`UTF-8` 编码的另一个好处是容错能力强。如果传输过程中某些字符出错，不会影响后续字符，因为`UTF-8` 编码依靠高字节位来确定一个字符究竟是几个字节，它经常用来作为传输编码。

在 Java 中，`char` 类型实际上就是两个字节的 `Unicode` 编码。如果我们要手动把字符串转换成其他编码，可以这样做：

```java
byte[] b1 = "Hello".getBytes(); // 按系统默认编码转换，不推荐
byte[] b2 = "Hello".getBytes("UTF-8"); // 按UTF-8编码转换
byte[] b2 = "Hello".getBytes("GBK"); // 按GBK编码转换
byte[] b3 = "Hello".getBytes(StandardCharsets.UTF_8); // 按UTF-8编码转换
```

:bulb: 转换编码后，就不再是 `char` 类型，而是 `byte` 类型表示的数组。

如果要把已知编码的 `byte[]` 转换为 `String`，可以这样做：

```java
byte[] b = ...
String s1 = new String(b, "GBK"); // 按GBK转换
String s2 = new String(b, StandardCharsets.UTF_8); // 按UTF-8转换
```

始终牢记：Java 的 `String` 和 `char` **在内存中总是以 Unicode 编码表示**。

:bulb: ​Java 使用 Unicode 编码表示 `String` 和 `char`；

:bulb: 转换编码就是将 `String` 和 `byte[]` 转换，需要指定编码；

:bulb: 转换为 `byte[]` 时，始终优先考虑 `UTF-8` 编码。



### 自动装箱与自动拆箱

因为 `int` 和 `Integer` 可以互相转换：

```java
int i = 100;
Integer n = Integer.valueOf(i);
int x = n.intValue();
```

所以，Java 编译器可以帮助我们自动在 `int` 和 `Integer` 之间转型：

```java
Integer n = 100; // 编译器自动使用Integer.valueOf(int)
int x = n; // 编译器自动使用Integer.intValue()
```

这种直接把 `int` 变为 `Integer` 的赋值写法，称为**自动装箱（Auto Boxing）**，反过来，把 `Integer` 变为 `int` 的赋值写法，称为**自动拆箱（Auto Unboxing）**。

:bulb: ​装箱和拆箱会影响代码的执行效率，因为编译后的 `class` 代码是严格区分基本类型和引用类型的。并且自动拆箱执行时可能会报 `NullPointerException`：

```java
// NullPointerException
public class Main {
    public static void main(String[] args) {
        Integer n = null;
        int i = n;
    }
}
```



### JavaBean

在 Java 中，有很多 `class` 的定义都符合这样的规范：

-   若干 `private` 实例字段；
-   通过 `public` 方法来读写实例字段。

例如：

```java
public class Person {
    private String name;
    private int age;

    public String getName() { return this.name; }
    public void setName(String name) { this.name = name; }

    public int getAge() { return this.age; }
    public void setAge(int age) { this.age = age; }
}
```

如果读写方法符合以下这种命名规范：

```java
// 读方法:
public Type getXyz()
// 写方法:
public void setXyz(Type value)
```

那么这种 `class` 被称为 `JavaBean`。

JavaBean 主要用来传递数据，即把一组数据组合成一个 JavaBean 便于传输。此外，JavaBean 可以方便地被 IDE 工具分析，生成读写属性的代码，主要用在图形界面的可视化设计中。



### 枚举类

为了让编译器能自动检查某个值在枚举的集合内，并且不同用途的枚举需要不同的类型来标记，不能混用，我们可以使用 `enum` 来定义枚举类：

```java
public class Main {
    public static void main(String[] args) {
        Weekday day = Weekday.SUN;
        if (day == Weekday.SAT || day == Weekday.SUN) {
            System.out.println("Work at home!");
        } else {
            System.out.println("Work at office!");
        }
    }
}

// 枚举类
enum Weekday {
    SUN, MON, TUE, WED, THU, FRI, SAT;
}
```

注意到定义枚举类是通过关键字 `enum` 实现的，我们只需依次列出枚举的常量名。

和 `int` 定义的常量相比，使用 `enum` 定义枚举有如下好处：

首先，`enum` 常量本身带有类型信息，即 `Weekday.SUN` 的数据类型是 `Weekday`，编译器会自动检查出类型错误。例如，下面的语句不可能编译通过：

```java
int day = 1;
if (day == Weekday.SUN) { // Compile error: bad operand types for binary operator '=='
}
```

其次，不可能引用到非枚举的值，因为无法通过编译。

最后，不同类型的枚举不能互相比较或者赋值，因为类型不符。例如，不能给一个 `Weekday` 枚举类型的变量赋值为 `Color` 枚举类型的值：

```java
Weekday x = Weekday.SUN; // ok!
Weekday y = Color.RED; // Compile error: incompatible types
```

这就使得编译器可以在编译期自动检查出所有可能的潜在错误。



### 记录类



### BigInteger



### BigDecimal



### 常用工具类



### 构造方法

创建实例的时候，实际上是通过构造方法来初始化实例的。我们先来定义一个构造方法，能在创建`Person`实例的时候，一次性传入`name`和`age`，完成初始化：

```java
// 构造方法
public class Main {
    public static void main(String[] args) {
        Person p = new Person("Xiao Ming", 15);
        System.out.println(p.getName());
        System.out.println(p.getAge());
    }
}

class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
    
    public String getName() {
        return this.name;
    }

    public int getAge() {
        return this.age;
    }
}
```

由于构造方法是如此特殊，所以构造方法的名称就是类名。构造方法的参数没有限制，在方法内部，也可以编写任意语句。但是，和普通方法相比，构造方法没有返回值（也没有 `void`），调用构造方法，必须用 `new` 操作符。

#### 默认构造方法

如果一个类没有定义构造方法，编译器会自动生成一个默认构造方法，它没有参数也没有执行语句，类似这样：

```java
class Person {
    public Person() {
    }
}
```

要特别注意的是，如果我们自定义了一个构造方法，那么，编译器就不再自动创建默认构造方法。

如果既要能使用带参数的构造方法，又想保留不带参数的构造方法，那么只能把两个构造方法都定义出来。

#### 多个构造方法

可以定义多个构造方法，在通过 `new` 操作符调用的时候，编译器通过构造方法的参数数量、位置和类型自动区分：

```java
class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public Person(String name) {
        this.name = name;
        this.age = 12;
    }

    public Person() {
    }
}
```

如果调用 `new Person("Xiao Ming", 20);`，会自动匹配到构造方法 `public Person(String, int)`；
如果调用 `new Person("Xiao Ming");`，会自动匹配到构造方法 `public Person(String)`；
如果调用 `new Person();`，会自动匹配到构造方法 `public Person()`。

一个构造方法可以调用其他构造方法，这样做的目的是便于代码复用。调用其他构造方法的语法是 `this(…)`：

```java
class Person {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public Person(String name) {
        this(name, 18); // 调用另一个构造方法Person(String, int)
    }

    public Person() {
        this("Unnamed"); // 调用另一个构造方法Person(String)
    }
}

```



### 方法重载

方法重载必须满足：

-   方法名相同
-   参数列表不同
    -   参数个数不同
    -   参数类型不同
    -   参数顺序不同（类型不同时）

返回值、访问修饰符、异常抛出 都不影响重载判定。



### 继承

基类 `Person`：

```java
class Person {
    private String name;
    private int age;

    public String getName() {...}
    public void setName(String name) {...}
    public int getAge() {...}
    public void setAge(int age) {...}
}
```

子类 `Student`：

```java
class Student extends Person {
    // 不要重复name和age字段/方法,
    // 只需要定义新增score字段/方法:
    private int score;

    public int getScore() { … }
    public void setScore(int score) { … }
}
```

Java 使用 `extends` 关键字来实现继承。

>   在 OOP 的术语中，把 `Person` 称为超类（super class），父类（parent class），基类（base class），把 `Student` 称为子类（subclass），扩展类（extended class）。



#### 继承树

注意到在定义 `Person` 的时候，没有写 `extends`。在 Java 中，没有明确写 `extends` 的类，编译器会自动加上 `extends Object`。所以任何类，除了 `Object`，都会继承自某个类。下图是 `Person`、`Student` 的继承树：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202604031539455.png" alt="image-20260403153950286" style="zoom: 67%;" />

Java 只允许一个 class 继承自一个类，因此一个类有且仅有一个父类。只有 `Object` 特殊，它没有父类。

类似的，如果我们定义一个继承自 `Person` 的 `Teacher`，它们的继承树关系如下：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202604031541243.png" alt="image-20260403154112185" style="zoom:67%;" />



#### protected

继承有个特点，就是子类无法访问父类的 `private` 字段或者 `private` 方法。例如，`Student` 类就无法访问 `Person` 类的 `name` 和 `age` 字段：

```java
class Person {
    private String name;
    private int age;
}

class Student extends Person {
    public String hello() {
        return "Hello, " + name; // 编译错误：无法访问name字段
    }
}
```

这使得继承的作用被削弱了。为了让子类可以访问父类的字段，我们需要把 `private` 改为 `protected`。用 `protected` 修饰的字段可以被子类访问：

```java
class Person {
    protected String name;
    protected int age;
}

class Student extends Person {
    public String hello() {
        return "Hello, " + name; // OK!
    }
}
```

因此，`protected` 关键字可以把字段和方法的访问权限控制在继承树内部，一个 `protected` 字段和方法可以被其子类，以及子类的子类所访问。



#### super

`super` 关键字表示父类（超类）。子类引用父类的字段时，可以用 `super.fieldName`。例如：

```java
// super
public class Main {
    public static void main(String[] args) {
        Student s = new Student("Xiao Ming", 12, 89);
    }
}

class Person {
    protected String name;
    protected int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

class Student extends Person {
    protected int score;

    public Student(String name, int age, int score) {
        this.score = score;
    }
}
```

运行上面的代码，会得到一个编译错误，大意是在 `Student` 的构造方法中，无法调用 `Person` 的构造方法。

这是因为在 Java 中，任何 `class` 的构造方法，第一行语句必须是调用父类的构造方法。如果没有明确地调用父类的构造方法，编译器会帮我们自动加一句 `super();`，所以，`Student` 类的构造方法实际上是这样：

```java
class Student extends Person {
    protected int score;

    public Student(String name, int age, int score) {
        super(); // 自动调用父类的构造方法
        this.score = score;
    }
}
```

但是，`Person` 类并没有无参数的构造方法，因此，编译失败。

解决方法是调用 `Person` 类存在的某个构造方法。例如：

```java
class Student extends Person {
    protected int score;

    public Student(String name, int age, int score) {
        super(name, age); // 调用父类的构造方法Person(String, int)
        this.score = score;
    }
}
```

这样就可以正常编译了！

因此我们得出结论：如果父类没有默认的构造方法，子类就必须显式调用`super()`并给出参数以便让编译器定位到父类的一个合适的构造方法。

这里还顺带引出了另一个问题：即子类不会继承任何父类的构造方法。子类默认的构造方法是编译器自动生成的，不是继承的。



#### 阻止继承

正常情况下，只要某个 class 没有 `final` 修饰符，那么任何类都可以从该 class 继承。

从 Java 15 开始，允许使用 `sealed` 修饰 class，并通过 `permits` 明确写出能够从该 class 继承的子类名称。

例如，定义一个`Shape`类：

```java
public sealed class Shape permits Rect, Circle, Triangle {
    ...
}
```

上述 `Shape` 类就是一个 `sealed` 类，它只允许指定的 3 个类继承它。如果写：

```java
public final class Rect extends Shape {...}
```

是没问题的，因为 `Rect` 出现在 `Shape` 的 `permits` 列表中。但是，如果定义一个 `Ellipse` 就会报错：

```java
public final class Ellipse extends Shape {...}
// Compile error: class is not allowed to extend sealed class: Shape
```

原因是 `Ellipse` 并未出现在 `Shape` 的 `permits` 列表中。这种 `sealed` 类主要用于一些框架，防止继承被滥用。



#### 向上转型

如果一个引用变量的类型是 `Student`，那么它可以指向一个 `Student` 类型的实例：

```java
Student s = new Student();
```

如果一个引用类型的变量是 `Person`，那么它可以指向一个 `Person` 类型的实例：

```java
Person p = new Person();
```

现在问题来了：如果 `Student` 是从 `Person` 继承下来的，那么，一个引用类型为 `Person` 的变量，能否指向 `Student` 类型的实例？

```java
Person p = new Student(); // ???
```

测试一下就可以发现，这种指向是允许的！

这是因为 `Student` 继承自 `Person`，因此，它拥有 `Person` 的全部功能。`Person` 类型的变量，如果指向 `Student` 类型的实例，对它进行操作，是没有问题的！

这种把一个子类类型安全地变为父类类型的赋值，被称为向上转型（upcasting）。

向上转型实际上是把一个子类型安全地变为更加抽象的父类型：

```java
Student s = new Student();
Person p = s; // upcasting, ok
Object o1 = p; // upcasting, ok
Object o2 = s; // upcasting, ok
```

注意到继承树是 `Student > Person > Object`，所以，可以把 `Student` 类型转型为 `Person`，或者更高层次的 `Object`。



#### 向下转型

和向上转型相反，如果把一个父类类型强制转型为子类类型，就是向下转型（downcasting）。例如：

```java
Person p1 = new Student(); // upcasting, ok
Person p2 = new Person();
Student s1 = (Student) p1; // ok
Student s2 = (Student) p2; // runtime error! ClassCastException!
```

如果测试上面的代码，可以发现：

`Person` 类型 `p1` 实际指向 `Student` 实例，`Person` 类型变量 `p2` 实际指向 `Person` 实例。在向下转型的时候，把 `p1` 转型为 `Student` 会成功，因为 `p1` 确实指向 `Student` 实例，把 `p2` 转型为 `Student` 会失败，因为 `p2` 的实际类型是 `Person`，不能把父类变为子类，因为子类功能比父类多，多的功能无法凭空变出来。

因此，向下转型很可能会失败。失败的时候，Java虚拟机会报 `ClassCastException`。

为了避免向下转型出错，Java 提供了 `instanceof` 操作符，可以先判断一个实例究竟是不是某种类型：

```java
Person p = new Person();
System.out.println(p instanceof Person); // true
System.out.println(p instanceof Student); // false

Student s = new Student();
System.out.println(s instanceof Person); // true
System.out.println(s instanceof Student); // true

Student n = null;
System.out.println(n instanceof Student); // false
```

`instanceof` 实际上判断一个变量所指向的实例是否是指定类型，或者这个类型的子类。如果一个引用变量为 `null`，那么对任何 `instanceof` 的判断都为 `false`。

利用 `instanceof`，在向下转型前可以先判断：

```java
Person p = new Student();
if (p instanceof Student) {
    // 只有判断成功才会向下转型:
    Student s = (Student) p; // 一定会成功
}
```



#### 区分继承和组合

在使用继承时，我们要注意逻辑一致性。

考察下面的 `Book` 类：

```java
class Book {
    protected String name;
    public String getName() {...}
    public void setName(String name) {...}
}
```

这个 `Book` 类也有 `name` 字段，那么，我们能不能让 `Student` 继承自 `Book` 呢？

```java
class Student extends Book {
    protected int score;
}
```

显然，从逻辑上讲，这是不合理的，`Student` 不应该从 `Book` 继承，而应该从 `Person` 继承。

究其原因，是因为 `Student` 是 `Person` 的一种，它们是 is 关系，而 `Student` 并不是 `Book`。实际上 `Student` 和 `Book` 的关系是 has 关系。

具有 has 关系不应该使用继承，而是使用组合，即 `Student` 可以持有一个 `Book` 实例：

```java
class Student extends Person {
    protected Book book;
    protected int score;
}
```

因此，继承是 is 关系，组合是 has 关系。



### 多态

在继承关系中，子类如果定义了一个与父类方法签名完全相同的方法，被称为覆写（Override）。

加上`@Override`可以让编译器帮助检查是否进行了正确的覆写。希望进行覆写，但是不小心写错了方法签名，编译器会报错。

```java
// override
public class Main {
    public static void main(String[] args) {
    }
}

class Person {
    public void run() {}
}

public class Student extends Person {
    @Override // Compile error!
    public void run(String s) {}
}
```



现在，我们考虑一种情况，如果子类覆写了父类的方法：

```java
// override
public class Main {
    public static void main(String[] args) {
        Person p = new Student();
        p.run(); // 应该打印Person.run还是Student.run?
    }
}

class Person {
    public void run() {
        System.out.println("Person.run");
    }
}

class Student extends Person {
    @Override
    public void run() {
        System.out.println("Student.run");
    }
}
```

那么，一个实际类型为 `Student`，引用类型为 `Person` 的变量，调用其 `run()` 方法，调用的是 `Person` 还是 `Student` 的 `run()` 方法？
运行一下上面的代码就可以知道，实际上调用的方法是 `Student` 的 `run()` 方法。因此可得出结论：Java 的实例方法调用是基于运行时的实际类型的动态调用，而非变量的声明类型。

这个非常重要的特性在面向对象编程中称之为**多态（Polymorphic）**。

多态是指，针对某个类型的方法调用，其真正执行的方法取决于运行时期实际类型的方法。

假设编写这样一个方法：

```java
public void runTwice(Person p) {
    p.run();
    p.run();
}
```

它传入的参数类型是 `Person`，我们是无法知道传入的参数实际类型究竟是 `Person`，还是 `Student`，还是 `Person` 的其他子类例如 `Teacher`，因此，也无法确定调用的是不是 `Person` 类定义的 `run()` 方法。

所以，多态的特性就是，运行期才能动态决定调用的子类方法。对某个类型调用某个方法，执行的实际方法可能是某个子类的覆写方法。这种不确定性的方法调用，究竟有什么作用？



#### 覆写 Object 方法

因为所有的 `class` 最终都继承自 `Object`，而 `Object` 定义了几个重要的方法：

-   `toString()`：把 instance 输出为 `String`；
-   `equals()`：判断两个 instance 是否逻辑相等；
-   `hashCode()`：计算一个 instance 的哈希值。

在必要的情况下，我们可以覆写 `Object` 的这几个方法。例如：

```java
class Person {
    ...
    // 显示更有意义的字符串:
    @Override
    public String toString() {
        return "Person:name=" + name;
    }

    // 比较是否相等:
    @Override
    public boolean equals(Object o) {
        // 当且仅当o为Person类型:
        if (o instanceof Person) {
            Person p = (Person) o;
            // 并且name字段相同时，返回true:
            return this.name.equals(p.name);
        }
        return false;
    }

    // 计算hash:
    @Override
    public int hashCode() {
        return this.name.hashCode();
    }
}
```



#### 调用super

在子类的覆写方法中，如果要调用父类的被覆写的方法，可以通过 `super` 来调用。例如：

```java
class Person {
    protected String name;
    public String hello() {
        return "Hello, " + name;
    }
}

class Student extends Person {
    @Override
    public String hello() {
        // 调用父类的hello()方法:
        return super.hello() + "!";
    }
}
```



### final

`final` 修饰符有多种作用：

-   `final` 修饰的方法可以阻止被覆写；
-   `final` 修饰的 class 可以阻止被继承；
-   `final` 修饰的 field 必须在创建对象时初始化，随后不可修改。

具体来说，继承可以允许子类覆写父类的方法。如果一个父类不允许子类对它的某个方法进行覆写，可以把该方法标记为 `final`。用 `final` 修饰的方法不能被 `Override`：

```java
class Person {
    protected String name;
    public final String hello() {
        return "Hello, " + name;
    }
}

class Student extends Person {
    // compile error: 不允许覆写
    @Override
    public String hello() {
    }
}
```

如果一个类不希望任何其他类继承自它，那么可以把这个类本身标记为 `final`。用 `final` 修饰的类不能被继承：

```java
final class Person {
    protected String name;
}

// compile error: 不允许继承自Person
class Student extends Person {
}
```

对于一个类的实例字段，同样可以用 `final` 修饰。用 `final` 修饰的字段在初始化后不能被修改。例如：

```java
class Person {
    public final String name = "Unamed";
}
```

对 `final` 字段重新赋值会报错：

```java
Person p = new Person();
p.name = "New Name"; // compile error!
```

可以在构造方法中初始化 final 字段：

```java
class Person {
    public final String name;
    public Person(String name) {
        this.name = name;
    }
}
```

这种方法更为常用，因为可以保证实例一旦创建，其 `final` 字段就不可修改。



### 抽象类

如果父类的方法本身不需要实现任何功能，仅仅是为了定义方法签名，目的是让子类去覆写它，那么，可以把父类的方法声明为抽象方法：

```java
class Person {
    public abstract void run();
}
```

把一个方法声明为 `abstract`，表示它是一个抽象方法，本身没有实现任何方法语句。因为这个抽象方法本身是无法执行的，所以，`Person` 类也无法被实例化。必须把 `Person` 类本身也声明为 `abstract`，才能正确编译它：

```java
abstract class Person {
    public abstract void run();
}
```

因为抽象类本身被设计成只能用于被继承，因此，抽象类可以强迫子类实现其定义的抽象方法，否则编译会报错。因此，抽象方法实际上相当于定义了“规范”。

例如，`Person` 类定义了抽象方法 `run()`，那么，在实现子类 `Student` 的时候，就必须覆写 `run()` 方法：

```java
// abstract class
public class Main {
    public static void main(String[] args) {
        Person p = new Student();
        p.run();
    }
}

abstract class Person {
    public abstract void run();
}

class Student extends Person {
    @Override
    public void run() {
        System.out.println("Student.run");
    }
}
```



### 接口

如果一个抽象类没有字段，所有方法全部都是抽象方法：

```java
abstract class Person {
    public abstract void run();
    public abstract String getName();
}
```

就可以把该抽象类改写为接口：`interface`。

在 Java 中，使用 `interface` 可以声明一个接口：

```java
interface Person {
    void run();
    String getName();
}
```

所谓 `interface`，就是比抽象类还要抽象的纯抽象接口，因为它连字段都不能有。因为接口定义的所有方法默认都是 `public abstract` 的，所以这两个修饰符不需要写出来（写不写效果都一样）。

当一个具体的 `class` 去实现一个 `interface` 时，需要使用 `implements` 关键字。举个例子：

```java
class Student implements Person {
    private String name;

    public Student(String name) {
        this.name = name;
    }

    @Override
    public void run() {
        System.out.println(this.name + " run");
    }

    @Override
    public String getName() {
        return this.name;
    }
}
```

在 Java 中，一个类只能继承自另一个类，不能从多个类继承。但是，一个类可以实现多个 `interface`，例如：

```java
class Student implements Person, Hello { // 实现了两个interface
    ...
}
```



#### 接口继承

一个 `interface` 可以继承自另一个 `interface`。`interface` 继承自 `interface` 使用 `extends`，它相当于扩展了接口的方法。例如：

```java
interface Hello {
    void hello();
}

interface Person extends Hello {
    void run();
    String getName();
}
```

此时，`Person` 接口继承自 `Hello` 接口，因此，`Person` 接口现在实际上有 3 个抽象方法签名，其中一个来自继承的 `Hello` 接口。

#### 

#### default 方法

在接口中，可以定义 `default` 方法。例如，把 `Person` 接口的 `run()` 方法改为 `default` 方法：

```java
// interface
public class Main {
    public static void main(String[] args) {
        Person p = new Student("Xiao Ming");
        p.run();
    }
}

interface Person {
    String getName();
    default void run() {
        System.out.println(getName() + " run");
    }
}

class Student implements Person {
    private String name;

    public Student(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }
}
```

实现类可以不必覆写 `default` 方法。`default` 方法的目的是，当我们需要**给接口新增一个方法时**，会涉及到修改全部子类。如果新增的是 `default` 方法，那么子类就不必全部修改，只需要在需要覆写的地方去覆写新增方法。

`default` 方法和抽象类的普通方法是有所不同的。因为 `interface` 没有字段，`default` 方法无法访问字段，而抽象类的普通方法可以访问实例字段。



### 继承关系

合理设计 `interface` 和 `abstract class` 的继承关系，可以充分复用代码。一般来说，公共逻辑适合放在 `abstract class` 中，具体逻辑放到各个子类，而接口层次代表抽象程度。可以参考 Java 的集合类定义的一组接口、抽象类以及具体子类的继承关系：

<img src="https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202604031646680.png" alt="image-20260403164600658" style="zoom:67%;" />

在使用的时候，实例化的对象永远只能是某个具体的子类，但总是通过接口去引用它，因为接口比抽象类更抽象：

```java
List list = new ArrayList(); // 用List接口引用具体子类的实例
Collection coll = list; // 向上转型为Collection接口
Iterable it = coll; // 向上转型为Iterable接口
```



### 静态字段和静态方法

用 `static` 修饰的字段，称为静态字段：`static field`。例如：

```java
class Person {
    public String name;
    public int age;
    // 定义静态字段number:
    public static int number;
}
```

推荐用类名来访问静态字段。可以把静态字段理解为描述`class`本身的字段。



用`static`修饰的方法称为静态方法。例如：

```java
// static method
public class Main {
    public static void main(String[] args) {
        Person.setNumber(99);
        System.out.println(Person.number);
    }
}

class Person {
    public static int number;

    public static void setNumber(int value) {
        number = value;
    }
}
```

因为静态方法属于 `class` 而不属于实例，因此，静态方法内部，无法访问 `this` 变量，也无法访问实例字段，它只能访问静态字段。

通过实例变量也可以调用静态方法，但这只是编译器自动帮我们把实例改写成类名而已。通常情况下，通过实例变量访问静态字段和静态方法，会得到一个编译警告。



#### 接口的静态字段

因为 `interface` 是一个纯抽象类，所以它不能定义实例字段。但是，`interface` 是可以有静态字段的，并且静态字段必须为 `final` 类型：

```java
public interface Person {
    public static final int MALE = 1;
    public static final int FEMALE = 2;
}
```

实际上，因为 `interface` 的字段只能是 `public static final` 类型，所以我们可以把这些修饰符都去掉，上述代码可以简写为：

```java
public interface Person {
    // 编译器会自动加上public static final:
    int MALE = 1;
    int FEMALE = 2;
}
```

编译器会自动把该字段变为 `public static final` 类型。



### 包

为了避免名字冲突，我们需要确定唯一的包名。推荐的做法是使用倒置的域名来确保唯一性。例如：

-   org.apache
-   org.apache.commons.log
-   com.liaoxuefeng.sample

要注意不要和`java.lang`包的类重名，即自己的类不要使用这些名字：

-   String
-   System
-   Runtime
-   ...

要注意也不要和JDK常用类重名：

-   java.util.List
-   java.text.Format
-   java.math.BigInteger
-   ...



### 作用域

*   public：全项目可见
*   package(default)：同包可见
*   protected：同包 + 子类可见
*   private：只有自己类可见



#### public



#### private

`private` 访问权限被限定在 `class` 的内部，而且与方法声明顺序无关。推荐把 `private` 方法放到后面，因为 `public` 方法定义了类对外提供的功能，阅读代码的时候，应该先关注 `public` 方法。

由于 Java 支持嵌套类，如果一个类内部还定义了嵌套类，那么，嵌套类拥有访问 `private` 的权限。



#### protected



#### package

包作用域是指一个类允许访问同一个 `package` 的没有 `public`、`private` 修饰的 `class`，以及没有 `public`、`protected`、`private` 修饰的字段和方法。

只要在同一个包，就可以访问 `package` 权限的 `class`、`field` 和 `method`。

```java
package abc;

class Main {
    void foo() {
        // 可以访问package权限的类:
        Hello h = new Hello();
        // 可以调用package权限的方法:
        h.hi();
    }
}
```

注意，包名必须完全一致，包没有父子关系，`com.apache` 和 `com.apache.abc` 是不同的包。



## 异常处理



![image-20251005231941005](https://amonologue-image-bed.oss-cn-chengdu.aliyuncs.com/2025/202510052319714.png)



### 捕获异常

捕获异常使用 `try...catch` 语句，把可能发生异常的代码放到 `try {...}` 中，然后使用 `catch` 捕获对应的 `Exception` 及其子类。

所有异常都可以调用 `printStackTrace()` 方法打印异常栈，这是一个简单有用的快速打印异常的方法。

Java 使用异常来表示错误，并通过 `try ... catch` 捕获异常；

Java 的异常是 `class`，并且从 `Throwable` 继承；

`Error` 是无需捕获的严重错误，`Exception` 是应该捕获的可处理的错误；

`RuntimeException` 无需强制捕获，非 `RuntimeException`（Checked Exception）需强制捕获，或者用 `throws` 声明；

不推荐捕获了异常但不进行任何处理。



### finally语句

无论是否有异常发生，如果我们都希望执行一些语句，Java 的 `try ... catch` 机制提供了`finally`语句，`finally` 语句块保证有无错误都会执行：

```java
public static void main(String[] args) {
    try {
        process1();
        process2();
        process3();
    } catch (UnsupportedEncodingException e) {
        System.out.println("Bad encoding");
    } catch (IOException e) {
        System.out.println("IO error");
    } finally {
        System.out.println("END");
    }
}
```

注意 `finally` 有几个特点：

1.  `finally` 语句不是必须的，可写可不写；
2.  `finally` 总是最后执行。

如果没有发生异常，就正常执行 `try { ... }` 语句块，然后执行 `finally`。如果发生了异常，就中断执行 `try { ... }` 语句块，然后跳转执行匹配的 `catch` 语句块，最后执行 `finally`。

可见，`finally` 是用来保证一些代码必须执行的。

某些情况下，可以没有 `catch`，只使用 `try ... finally` 结构。例如：

```java
void process(String file) throws IOException {
    try {
        ...
    } finally {
        System.out.println("END");
    }
}
```

因为方法声明了可能抛出的异常，所以可以不写 `catch`。



### 抛出异常



### 自定义异常



### 断言



### JDK Logging

### Commons Logging

Commons Logging是使用最广泛的日志模块；

Commons Logging的API非常简单；

Commons Logging可以自动检测并使用其他日志模块。



### Log4j

前面介绍了Commons Logging，可以作为“日志接口”来使用。而真正的“日志实现”可以使用Log4j。

在开发阶段，始终使用Commons Logging接口来写入日志，并且开发阶段无需引入Log4j。如果需要把日志写入文件，只需要把正确的配置文件和Log4j相关的jar包放入`classpath`，就可以自动把日志切换成使用Log4j写入，无需修改任何代码。



## 反射

### 反射的作用

1、保存任意对象数据

2、利用反射动态的创建对象和运行方法



## 注解



## 泛型



## 动态代理

### 为什么需要代理？

代理可以无侵入式的给对象增加其他的功能



## 集合

>   类似于 `std::vector`，也支持泛型编程

### ArrayList





