# Shell编程

----

[TOC]

<!-- toc -->

----

## shell简介

Shell的作用是解释执行用户的命令，用户输入一条命令，Shell就解释执行一条，这种方式称为**交互式**（Interactive），Shell还有一种执行命令的方式称为**批处理**（Batch），用户事先写一个Shell脚本（Script），其中有很多条命令，让Shell一次把这些命令执行完，而不必一条一条地敲命令。Shell脚本和编程语言很相似，也有变量和流程控制语句，但Shell脚本是**解释执行**的，不需要编译，Shell程序从脚本中一行一行读取并执行这些命令，相当于一个用户把脚本中的命令一行一行敲到Shell提示符下执行。

**什么是shell？**
Shell（外壳） 是一个用 C 语言编写的程序，它是用户使用 Linux 的桥梁。Shell 既是一种命令语言，又是一种程序设计语言。
Shell 是指一种应用程序，这个应用程序提供了一个界面，用户通过这个界面访问操作系统内核的服务。

**什么是脚本？**
脚本简单地说就是**一条条**的**文字命令**，这些文字命令是可以看到的（如可以用记事本打开查看、编辑）。
常见的脚本： JavaScript（JS，前端）， ASP，JSP，PHP（后端），SQL（数据库操作语言），Perl，Shell，python，Ruby，JavaFX，Lua等。

**为什么要学习和使用shell？**
Shell属于内置的脚本
程序开发的效率非常高，依赖于功能强大的命令可以迅速地完成开发任务（批处理）
语法简单，代码写起来比较轻松，简单易学

**常见的shell种类？**
在linux中有很多类型的shell，不同的shell具备不同的功能，shell还决定了脚本中函数的语法，Linux中默认的shell是`/bin/bash`（重点），流行的shell有ash、bash、ksh、csh、zsh等，不同的shell都有自己的特点以及用途。由于历史原因，UNIX系统上有很多种Shell：

- **sh**（Bourne Shell）：由Steve Bourne开发，各种UNIX系统都配有sh。
- **csh**（C Shell）：由Bill Joy开发，随BSD UNIX发布，它的流程控制语句很像C语言，支持很多Bourne Shell所不支持的功能：作业控制，命令历史，命令行编辑。
- **ksh**（Korn Shell）：由David Korn开发，向后兼容sh的功能，并且添加了csh引入的新功能，是目前很多UNIX系统标准配置的Shell，在这些系统上/bin/sh往往是指向/bin/ksh的符号链接。
- **tcsh**（TENEX C Shell）：是csh的增强版本，引入了命令补全等功能，在FreeBSD、MacOS X等系统上替代了csh。
- **bash**（Bourne Again Shell）：由GNU开发的Shell，主要目标是与POSIX标准保持一致，同时兼顾对sh的兼容，bash从csh和ksh借鉴了很多功能，大多数Linux系统默认使用的shell，在Linux系统上/bin/sh往往是指向/bin/bash的符号链接。虽然如此，bash和sh还是有很多不同的，一方面，bash扩展了一些命令和参数，另一方面，bash并不完全和sh兼容，有些行为并不一致，所以bash需要模拟sh的行为：当我们通过sh这个程序名启动bash时，bash可以假装自己是sh，不认扩展的命令，并且行为与sh保持一致。
- **dash**
- **zsh**

**内建命令**

用户在命令行输入命令后，一般情况下Shell会**fork并exec**该命令，但是Shell的**内建命令例外**，执行内建命令相当于调用Shell进程中的一个函数，并不创建新的进程。以前学过的cd、alias、umask、exit等命令即是内建命令，凡是用**which**命令**查不到**程序文件所在位置的命令都是内建命令，内建命令没有单独的man手册，要在man手册中查看内建命令，应该执行

```
man bash-builtins    # 查看内建命令
```

> bash defines the following built-in commands: 
>    : ,  . , [ , alias, bg, bind, break, builtin, case, cd, command, compgen, complete, continue, declare, dirs, disown, echo,  enable,  eval,  exec, exit, export, fc, fg, getopts, hash, help, history, if, jobs, kill, let, local, logout, popd, printf, pushd, pwd, read, readonly, return, set, shift, shopt, source, suspend, test,  times, trap, type, typeset, ulimit, umask, unalias, unset, until, wait, while.

如`export、shift、if、eval、[、for、while`等等。内建命令虽然不创建新的进程，但也会有Exit Status，通常也用0表示成功非零表示失败，虽然内建命令不创建新的进程，但执行结束后也会有一个**状态码**，也可以用特殊变量`$?`读出。

## 配置shell

### 系统可用的shell

```
cat /etc/shells
# /etc/shells: valid login shells
/bin/sh
/bin/dash
/bin/bash
/bin/rbash
```

### 查看系统当前shell

```
echo $SHELL    # 當前shell
# /bin/bash

ls -l /bin/sh
# lrwxrwxrwx 1 root root 4 Jan  2 12:55 /bin/sh -> dash
```

### 查看系统用户shell

```
cat /etc/passwd
```

> 其中最后一列显示了用户对应的shell类型
>
> root:x :0:0:root:/root:/bin/bash
> daemon:x :1:1:daemon:/usr/sbin:/usr/sbin/nologin
> bin:x :2:2:bin:/bin:/usr/sbin/nologin
> sys:x :3:3:sys:/dev:/usr/sbin/nologin
> chao:x :1000:1000::/home/chao:/bin/bash
> mongodb:x :119:127::/var/lib/mongodb:/bin/false

### 切换shell为zsh

```
chsh -s /bin/zsh     # 切換zsh
chsh -s /bin/bash    # 切換回bash
```

  `-s` ,  --shell SHELL       new login shell for the user account

### 配置dash让bash为默认shell

```
sudo dpkg-reconfigure dash
# 选择 <否> 取消默认配置dash，自动配置为bash
# lrwxrwxrwx 1 root root 4 May 17 21:59 /bin/sh -> bash
```

bash ： Bourne Again Shell

### 修改用户登录 Shell

```
sudo usermod -s /bin/bash 用户名  # 修改用户登录 Shell
```

  `-s` ,  --shell SHELL       new login shell for the user account

## shell脚本

### 编写规范

> **代码规范**：
>         ==#!/bin/bash==				# 首行#!(Shebang)指定执行当前脚本要使用的shell**解释器**
> 	Shell相关指令
> 	#表示注释

> **文件命名规范**：
> 	文件名==.sh==				# .sh是linux下bash shell 的默认后缀,可以不是sh

### 执行脚本

> ##### 使用流程
>
> 创建 **xx.sh** 文件
>
> 添加**可执行权限**,  **./ 可执行**的shell脚本必须得有**可执行权限**
> `chmod +x test.sh`
>
> **./运行**shell脚本
> ` ./test.sh`

创建 **xx.sh** 文件

> ``#! /bin/sh
> cd ..
> ls

添加**可执行权限**,  **./ 可执行**的shell脚本必须得有**可执行权限**

```
$ chmod a+x test.sh
```

**./ 运行**shell脚本（fork出子Shell执行）

```
$ ./test.sh    # ./ shell脚本必须得有可执行权限,fork子进程
```

Shell会**fork一个子进程并调用exec执行**`./test.sh`这个程序，exec系统调用应该把子进程的代码段替换成./test.sh程序的代码段，并从它的`_start`开始执行。然而test.sh是个文本文件，根本没有代码段和`_start`函数，怎么办呢？其实exec还有另外一种机制，如果要执行的是一个文本文件，并且第一行用Shebang指定了解释器，则用**解释器**程序的代码段替换当前进程，并且从解释器的`_start`开始执行，而这个**.sh文本文件**被当作**命令行参数**传给解释器。因此，执行上述脚本相当于执行程序。

```
$ /bin/sh ./test.sh    # 不需要shell脚本具有可执行权限,fork子shell进程
```

以这种方式执行不需要test.sh文件具有可执行权限。Shell会**fork一个子进程并调用exec**执行`test.sh`这个程序。

如果将命令行下输入的命令用**括号()**括起来，那么也会**fork**出一个**子Shell**执行小**括号**中的命令，一行中可以输入由**分号;隔开**的多个命令，比如：

```
$ (cd .. ; ls -l)    # fork一个子Shell执行
# drwxr-xr-x 50 chao chao 4096 Mar 21 10:04 chao
# chao@deepin:~$ 
```

和上面两种方法执行Shell脚本的效果是相同的，cd ..命令改变的是子Shell的pwd，而不会影响到交互式Shell。

然而不加()括号命令直接在当前交互式Shell下执行的，不会创建子Shell

```
$ cd .. ; ls -l    # 不会创建子Shell，当前shell执行
# drwxr-xr-x 50 chao chao 4096 Mar 21 10:04 chao
# chao@deepin:/home$ 
```

则有不同的效果，cd ..命令是直接在当前交互式Shell下执行的，改变当前交互式Shell的pwd，然而这种方式相当于这样执行Shell脚本：

```
$ source test.sh    # 不会创建子Shell，当前shell执行
$ source ./test.sh    # 不会创建子Shell，当前shell执行
$ . test.sh         # 不会创建子Shell，当前shell执行
$ . ./test.sh         # 不会创建子Shell，当前shell执行
```

==`source`==或者==`.`==命令是Shell的内建命令，这种方式也==**不会创建子Shell**==，而是直接在**当前交互式Shell**下逐行执行脚本中的命令。

## shell变量

### 环境变量/本地变量

有两种类型的Shell变量：

1. 环境变量

环境变量是**任何进程**都有的概念，环境变量可以从父进程传给子进程，因此Shell进程的环境变量可以从当前Shell进程传给fork出来的子进程。用`printenv`命令可以显示当前Shell进程的环境变量。

```
$ env         # 环境变量
$ printenv    # 环境变量
```

2. 本地变量

只存在于**当前Shell进程**，用set命令可以显示当前Shell进程中定义的所有变量（包括本地变量和环境变量）和函数。

```
$ set    # 所有变量（包括本地变量和环境变量）和函数
```

环境变量是任何进程都有的概念，而本地变量是Shell特有的概念。在Shell中，环境变量和本地变量的定义和用法相似。在Shell中定义或赋值一个变量：

```
# 变量名="变量值"  # 定义本地变量
$ VARNAME=value    # 定义本地变量
# echo $变量名  # 使用变量: $变量名
$ echo $VARNAME  # 使用变量: $变量名
```

**定义变量**：class_name====="yunwe "
**使用变量**：echo ==$==class_name

注意等号两边都不能有空格，否则会被Shell解释成命令和命令行参数。

一个变量定义后仅存在于当前Shell进程，它是**本地变量**，用==export==命令可以把本地变量导出为==环境变量==，定义和导出环境变量通常可以一步完成：

```
$ export VARNAME=value    # 把本地变量导出为环境变量
```

也可以分两步完成：

```
$ VARNAME=value    # 定义本地变量
$ export VARNAME    # 把本地变量导出为环境变量
```

> 示例
>
> ```
> #!/bin/bash
> mystr="hello world!"
> echo $mystr
> dt=`date + '%F %T'`
> echo dt
> ```

> 变量名规范：Shell变量通常由字母加下划线开头，由任意长度的字母、数字、下划线组成。
>
> 定义变量时等号==`=`==两边**不能有空格**
>
> 在使用shell变量的时候一定要在变量名前面添加一个==**`$`**==符号
>
> **关于单双引号的问题：**
> **双引号**能够识别变量，双引号能够实现转义（类似于“\”）
> **单引号**是不能识别变量，只会原样输出，单引号是不能转义的
>
> 注意：反引号==` ` `==（esc键下方的那个键），当在脚本中需要执行一些指令并且将执行的**结果赋给变量**的时候需要使用“反引号”。

注意，和C语言不同的是，Shell变量不需要明确定义类型，事实上**Shell变量**的值都是==字符串==，比如我们定义VAR=45，其实VAR的值是字符串45而非整数。Shell变量不需要先定义后使用，如果对一个没有定义的变量取值，则值为空字符串。

```
$ echo $?    # $?上一个进程退出的返回值
```

### 删除变量unset

**unset**命令可以**删除**已定义的**环境变量**或**本地变量**。

```
unset 变量名
$ unset VARNAME    # 删除已定义的变量
```

> ```
> #!/bin/bash
> b=20
> echo $b
> unset b    # 删除变量
> echo $b
> ```

### 只读变量readonly

```
readonly 变量名  # 定义只读变量
```

```
#!/bin/bash
a=10
readonly a
a=20    # 报错无法修改只读数据
echo $a
```

### 接收用户输入read

接受用户的输入并赋值给创建的变量

```
read  -p  '提示信息'  变量名valName
```

```
#!/bin/bash
read -p '请输入文件名' filepath    # 输入值给 filepath
touch $filepath
echo '文件创建成功'
```

### 通配符

这些用于匹配的字符称为通配符（Wildcard），如：* ? [ ] 具体如下：

```
*    匹配0个或多个任意字符(不同正则)
?    匹配一个任意字符(同正则)
[若干字符]    匹配方括号中任意一个字符的一次出现(同正则)
$ ls /dev/ttyS*
$ ls ch0?.doc
$ ls ch0[0-2].doc
$ ls ch[012][0-9].txt
```

注意，Globbing所匹配的文件名是由Shell展开的，也就是说在参数还没传给程序之前已经展开了，比如上述`ls ch0[012].txt`命令，如果当前目录下有ch00.txt和ch02.txt，则传给ls命令的参数实际上是这两个文件名，而不是一个匹配字符串。

### 命令代换`` $()

由`反引号括起来的也是一条命令，Shell先执行该命令，然后将输出结果立刻代换到当前命令行中。例如定义一个变量存放date命令的输出：

```
$ DATE=`date`    # 命令
$ echo $DATE    # 输出日期
```

命令代换也可以用$()表示：

```
$ DATE=$(date)    # 命令
$ echo $DATE    # 输出日期
```

### 算术代换 $(()) $[ ]

使用$(())，用于算术计算，(())中的Shell变量取值将转换成整数，同样含义的$[ ]等价例如：

```
$ VAR=45
$ echo $(($VAR+3))	# 等价于	
$ echo $[VAR+3]     # 等价于	
$ echo $[$VAR+3]    # 等价于	
```

$(())中只能用+-*/和()运算符，并且只能做**整数**运算。
$[base#n]，其中base表示**进制**，n按照base进制解释，后面再有运算数，按十进制解释。

```
echo $[2#10+11]    # 2进制
echo $[8#10+11]    # 8进制
echo $[16#10+11]   # 16进制
```

### 转义字符 \

和C语言类似，`\`在Shell中被用作转义字符，用于去除紧跟其后的单个字符的特殊意义（回车除外），换句话说，紧跟其后的字符取字面值。例如：

```
$ echo $SHELL
/bin/bash
$ echo \$SHELL    # \$ 转义$
# $SHELL
$ echo \\    # \\ 转义\
# \
```

比如创建一个文件名为“$ $.txt”的文件（$间含有空格）可以这样：

```
$ touch \$\ \$.txt    # 转义$和空格
```

还有一个字符虽然不具有特殊含义，但是要用它做文件名也很麻烦，就是-号。如果要创建一个文件名以-号开头的文件，加上`\-`转义也还是是不正确的.
因为各种UNIX命令都把-号开头的命令行参数当作命令的选项，而不会当作文件名。如果非要处理以-号开头的文件名，可以有两种办法：

```
$ touch ./-hello    # 或者
$ touch -- -hello
```

\还有一种用法，在`\`后敲回车表示**续行**，Shell并不会立刻执行命令，而是把光标移到下一行，给出一个续行提示符>，等待用户继续输入，最后把所有的续行接到一起当作一个命令执行。例如：

```
chao@deepin:~$  ls \    # \后回车表示续行
> -l                    # 就是 ls -l命令的输出
```

### 单引号

和C语言同，Shell脚本中的**单引号**和**双引号**一样都是**字符串的界定符**，而不是字符的界定符。**单引号**用于**保持**引号内所有**字符串的字面值**，即使引号内的\和回车也不例外，但是字符串中不能出现单引号。如果引号没有配对就输入回车，Shell会给出续行提示符，要求用户把引号配上对。例如：

```
$ echo '$SHELL'
SHELL
$ echo 'ABC\（回车）    # 引号没有配对
DE'（再按一次回车结束命令）
ABC\
DE
```

### 双引号

被**双引号**用括住的内容，将被视为单一字串。它防止通配符扩展，但**允许变量**扩展。这点与单引号的处理方式不同

```
$ DATE=$(date)    # 定义变量
$ echo "$DATE"    # 输出日期
Wed Dec 18 23:00:55 CST 2019
$ echo '$DATE'    # 输出字符的字面值
$DATE

再比如：
$ VAR=200
$ echo $VAR	   # 输出变量值
200
$ echo '$VAR'   # 输出字符的字面值
$VAR
$ echo "$VAR"   # 输出字符串变量值
200
```

### 位置参数和特殊符号

- ==`#`==    注释
- ==`;`==    暂不输出
- ==`\`==    续行符
- ==`:`==    空命令，该命令不做任何事，但Exit Status总是真
	 ==`$0`== 	当前命令,相当于C语言main函数的argv[0]
- ==`$1`==、==`$2`==...    第n个命令行参数，相当于C语言main函数的argv[1]、argv[2]...
	 ==`$# `==	传递到脚本的**参数个数**,相当于C语言argc - 1
	 ==`$@ `==	"$@"表示参数列表"$1" "$2" ... "$n" ， 可以用在for循环中的in后面
	 ==`$* `==	"$*"表示"$1 $2 … $n"，以一个单字符串显示所有向脚本传递的参数
	 ==`$? `==	上一条命令的Exit Status退出状态，0表示没有错误，其他任何值表明有错误
- ==` $-`==  显示Shell使用的当前选项，与[set命令](https://www.runoob.com/linux/linux-comm-set.html)功能相同。
	 ==`$$ `==	脚本运行的当前**进程号**
- $!  后台运行的最后一个进程的ID号

位置参数可以用shift命令左移。比如shift 3表示原来的$4现在变成$1，原来的$5现在变成$2等等，原来的$1、$2、$3丢弃，$0不移动。不带参数的shift命令相当于shift 1。例如：

```
#! /bin/sh
echo "The program $0 is now running"
echo "The first parameter is $1"
echo "The second parameter is $2"
echo "The parameter list is $@"
shift    # 相当于shift 1
echo "The first parameter is $1"
echo "The second parameter is $2"
echo "The parameter list is $@"
```

## 运算符

在shell中，运算符和其他编程脚本语言一样，常见的有算数运算符、关系运算符、\逻辑运算符、字符串运算符、文件测试运算符等

### 算数运算符

下表列出了常用的算术运算符，假定变量 a 为 10，变量 b 为 20：

| **运算符** | **说明**                                            | **举例**                        |
| ---------- | --------------------------------------------------- | ------------------------------- |
| +          | 加法                                                | `expr $a + $b` 结果为 30。      |
| -          | 减法                                                | `expr $a - $b` 结果为 -10。     |
| *          | 乘法                                                | `expr $a \* $b` 结果为  200。   |
| /          | 除法                                                | `expr $b / $a` 结果为 2。       |
| **%**      | **取余**                                            | `expr $b % $a` 结果为 0。       |
| =          | 赋值                                                | a=$b 将把变量 b 的值赋给 a。    |
| ==         | 相等。比较两个**数值相等**，相同则返回 true（真）。 | [ $a == $b ] 返回 false（假）。 |
| !=         | 不相等。比较两个数字，不相同则返回 true。           | [ $a != $b ] 返回 true。        |

原生bash**不支持**简单的**数学运算**，但是可以通过其他**命令**来实现，例如 `expr` 和`awk`，**expr** 最常用。

`expr`命令是一款表达式计算工具，使用它能完成表达式的求值操作。

表达式和运算符之间要有**空格**，例如 ~~2+2~~ 是不对的，必须写成`  2 + 2 `，这与我们熟悉的大多数编程语言不一样。

```
#！/bin/bash 
a=20
b=10
echo 'a+b=' `expr $a + $b`
echo 'a-b=' `expr $a - $b`
echo 'a*b=' `expr $a \* $b`    # 乘 * 需转义，与通配符*区分
echo 'a/b=' `expr $a / $b`
echo 'a%b=' `expr $a % $b`
```

> 原生bash**不支持**简单的**数学运算**，但是可以通过其他**命令**来实现，例如 `expr` 和`awk`，**expr** 最常用。
> expr 是一款表达式计算工具，使用它能完成表达式的求值操作。
> 例如，两个数相加(注意使用的是**反引号 `** 而不是单引号 ')：
> ``#!/bin/bash
> val=\`**expr** 2 + 2\`
> echo "两数之和为 : $val"
>
> 两点注意：
> 表达式和运算符之间要有**空格**，例如 ~~2+2~~ 是不对的，必须写成`  2 + 2 `，这与我们熟悉的大多数编程语言不一样。
> 完整的表达式要被 \`  \` 包含，注意这个字符不是常用的单引号，在 Esc 键下边。

```
#！/bin/bash
if [ $a == $b ]
then 
	echo 'a等于b'
else 
	echo 'a不等于b'
fi

if [ $a ！= $b ]
then 
	echo 'a等于b'
else 
	echo 'a不等于b'
fi
```

注意：条件表达式要放在方括号[]之间，并且要有空格，例如: ~~[\$a==\$b] 是错误的~~，必须写成 [\$a  ==  $b ]。

### 字符串运算符

下表列出了常用的字符串运算符，假定变量 a 为 "abc"，变量 b 为 "efg"：

| **运算符** | **说明**                                        | **举例**                 |
| ---------- | ----------------------------------------------- | ------------------------ |
| =          | 检测两个**字符串**是否**相等**，相等返回 true。 | [ $a = $b ] 返回 false。 |
| !=         | 检测两个字符串是否相等，不相等返回 true。       | [ $a != $b ] 返回 true。 |
| -z         | 检测字符串长度是否为0，为0返回 true。           | [ -z $a ] 返回 false。   |
| -n         | 检测字符串长度是否不为0，不为0返回 true。       | [ -n $a ] 返回 true。    |

> `-z`  zero 零
> `-n`  not zero 非零

```
#！/bin/bash
a='qbc'
b='def'
if [ $a = $b ]    # 字符串是否相等
then 
	echo 'true'
else 
	echo 'false'
fi
if [ $a != $b ]    # 字符串是否不相等
then 
	echo 'true'
else
	echo 'false'
fi
```

### 关系运算符

关系运算符只支持数字，不支持字符串，除非字符串的值是数字

下表列出了常用的**数值关系**运算符，假定变量 a 为 10，变量 b 为 20：

| **运算符** | **说明**                                                  | **举例**                   |
| ---------- | --------------------------------------------------------- | -------------------------- |
| -eq        | 检测**两个数是否相等**，相等返回 true。                   | [ $a -eq $b ] 返回false。  |
| -ne        | 检测**两个数是否相等**，不相等返回 true。                 | [ $a -ne $b ] 返回 true。  |
| -gt        | 检测左边的数**是否大于**右边的，如果是，则返回 true。     | [ $a -gt $b ] 返回 false。 |
| -lt        | 检测左边的数**是否小于**右边的，如果是，则返回 true。     | [ $a -lt $b ] 返回 true。  |
| -ge        | 检测左边的数**是否大于等于**右边的，如果是，则返回 true。 | [ $a -ge $b ] 返回 false。 |
| -le        | 检测左边的数**是否小于等于**右边的，如果是，则返回 true。 | [ $a -le $b ] 返回 true。  |

> -eq：equal
> -ne：not equal
> -gt：great than
> -lt：less than
> -ge：great than or equal
> -le：less than or equal

```
#!/bin/bash 
a=10
b=20
echo "a = $a"
echo "b = $b"
if [ $a -eq $b ]    # -eq 等于 等价于 ==
then 
	echo 'a 等于 b'
else 
	echo 'a 不等于 b'
fi

if [ $a -gt $b ]    # -gt 大于
then 
	echo 'a 大于 b'
else 
	echo 'a 不大于 b'
fi
```

### 逻辑运算符

下表列出了常用的布尔运算符，假定变量 a 为 10，变量 b 为 20：

| **运算符** | **说明**                                                | **举例**                                   |
| ---------- | ------------------------------------------------------- | ------------------------------------------ |
| !          | 非运算，表达式为 true 则返回 false，否则返回 true。     | [ ! false ] 返回 true。                    |
| -o         | **或(**或者)运算，**有一个表达式为 true 则返回 true**。 | [ \$a -lt 20 -o \$b -gt 100 ] 返回 true。  |
| -a         | **与**(并且)运算，**两个表达式都为 true** 才返回 true。 | [ \$a -lt 20 -a \$b -gt 100 ] 返回 false。 |

> `！`    非
> `-o`    or 或
> `-a`    and 与

```
#！/bin/bash
a=10
b=20
if [ $a -lt 20 -o $b -gt 100 ]  # -o 或
then 
	echo '真'
fi
```

### && || 语句选择

==`&&`==相当于“if…then…”,只有当前一条语句为真执行**成功**才执行后一条,失败了则跳过后面的语句

==`||`==相当于“if not…then…”,只有当前一条语句为真执行**失败**才执行后一条,成功了则跳过后面的语句&&和||用于连接两个命令，而上面讲的-a和-o仅用于在测试表达式中连接两个测试条件，和C语言类似，&&和||具有Short-circuit特性

```
test "$(whoami)" != 'root' && (echo you are using a non-privileged account; exit 1)     # && 前一句为真才执行后一句,否则跳过后一句
test "$(whoami)" != 'root' || (echo you are using a root account; exit 1)      #  || 前一句为假才执行后一句,否则跳过后一句
```

**&&和||**用于**连接两个命令**，而上面讲的**-a和-o**仅用于在测试表达式中**连接两个测试条件**，要注意它们的区别，例如：

```
test "$VAR" -gt 12 -a "$VAR" -lt 33
```

和以下写法是等价的

```
test "$VAR" -gt 12 && test "$VAR" -lt 33
```

### 文件测试运算符

文件测试运算符用于检测 Unix/Linux 文件的各种属性。
属性检测描述如下：

| **操作符**  | **说明**                                                    | **举例**                   |
| ----------- | ----------------------------------------------------------- | -------------------------- |
| -b file     | 检测文件是否是块设备文件，如果是，则返回 true。             | [ -b \$file ] 返回 false。 |
| -c file     | 检测文件是否是字符设备文件，如果是，则返回 true。           | [ -c \$file ] 返回 false。 |
| -p file     | 检测文件是否是**有名管道**，如果是，则返回 true。           | [ -p \$file ] 返回 false。 |
| ==-d== file | 检测文件**是否是目录**，如果是，则返回 true。               | [ -d \$file ] 返回 false。 |
| ==-f== file | 检测文件**是否是普通文件**（既不是目录，也不是设备文件）    | [ -f $file ] 返回 true。   |
| -g file     | 检测文件是否设置了 SGID 位，如果是，则返回 true。           | [ -g \$file ] 返回 false。 |
| -u file     | 检测文件是否设置了 SUID 位，如果是，则返回 true。           | [ -u \$file ] 返回 false。 |
| -k file     | 检测文件是否设置了粘着位(Sticky Bit)，如果是，则返回 true。 | [ -k \$file ] 返回 false。 |
| ==-r== file | 检测文件是否**可读**，如果是，则返回 true。                 | [ -r $file ] 返回 true。   |
| ==-w== file | 检测文件是否**可写**，如果是，则返回 true。                 | [ -w $file ] 返回 true。   |
| ==-x== file | 检测文件是否**可执行**，如果是，则返回 true。               | [ -x \$file ] 返回 true。  |
| ==-s== file | 检测文件是否**非空**（文件大小是否大于0），非空返回 true。  | [ -s \$file ] 返回 true。  |
| ==-e== file | 检测**文件（包括目录）是否存在**，如果是，则返回 true。     | [ -e \$file ] 返回 true。  |

```
#!/bin/bash
file="test.sh"
if [ -f $file ]
then
   echo "文件为普通文件"
else
   echo "文件为特殊文件"
fi
if [ -d $file ]
then
   echo "文件是个目录"
else
   echo "文件不是个目录"
fi
if [ -s $file ]
then
   echo "文件不为空"
else
   echo "文件为空"
fi
if [ -e $file ]
then
   echo "文件存在"
else
   echo "文件不存在"
fi
if [ -r $file ]
then
   echo "文件可读"
else
   echo "文件不可读"
fi
if [ -w $file ]
then
   echo "文件可写"
else
   echo "文件不可写"
fi
if [ -x $file ]
then
   echo "文件可执行"
else
   echo "文件不可执行"
fi
```

## 输入输出

### echo

显示文本行或变量，或者把字符串输入到文件。

```
echo [option] string
```

```
echo "hello\n\n"
echo -e "hello\n\n"
echo "hello"
echo -n "hello"
```

- ==-e== 解析**转义字符**
- -n 不回车换行。默认情况echo回显的内容后面跟一个回车换行。

### 管道 |

可以通过 `|` 把一个命令的输出传递给另一个命令做输入。

```
cat myfile | more
ls -l | grep "myfile"
df -k | awk '{print $1}' | grep -v "Filesystem"
# df -k 查看磁盘空间，找到第一列，去除“Filesystem”，并输出
```

### tee

tee命令把结果输出到标准**输出**，另一个**副本**输出到相应**文件**。

```
df -k | awk '{print $1}' | grep -v "Filesystem" | tee a.txt    # 输出并写到文件
```

```
df -k | awk '{print $1}' | grep -v "Filesystem" | tee -a a.txt   # 输出并追加到文件
```

`tee -a a.txt `表示**追加**操作。

- ==-a== 追加到文件

### 文件重定向

```
cmd > file 		# >把标准输出重定向到新文件中
ls > a.txt
cmd >> file 	# >>追加
ls >> a.txt
```

```
cmd > file 2>&1 		标准出错也重定向到1所指向的file里
cmd >> file 2>&1        追加
cmd < file1 > file2 	输入输出都定向到文件里
cmd < &fd 				把文件描述符fd作为标准输入
cmd > &fd 				把文件描述符fd作为标准输出
cmd < &- 				关闭标准输入
```

## 分支

### if/then/elif/else/fi

和C语言类似，在Shell中用if、then、elif、else、fi这几条命令实现分支控制。这种流程控制语句本质上也是由若干条Shell命令组成的

单行写法：

```
if [condition]; then command; fi
```

多行写法：

```
if [ condition1 ]
then
    command1
elif [ condition2 ]
then 
    command2
else
    commandN
fi
```

示例

```
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi
```

其实是三条命令，`if [ -f ∼/.bashrc ]`是第一条，`then . ∼/.bashrc`是第二条，`fi`是第三条。如果两条命令写在同一行则需要用;号隔开，一行只写一条命令就不需要写;号了，另外，then后面有换行，但这条命令没写完，Shell会自动续行，把下一行接在then后面当作一条命令处理。和[命令一样，要注意命令和各参数之间必须用空格隔开。if命令的参数组成一条子命令，如果该子命令的Exit Status为0（表示真），则执行then后面的子命令，如果Exit Status非0（表示假），则执行elif、else或者fi后面的子命令。if后面的子命令通常是测试命令，但也可以是其它命令。Shell脚本没有{}括号，所以用fi表示if语句块的结束。 

```
#! /bin/sh
if [ -f /bin/bash ]
then 
	echo "/bin/bash is a file"
else 
	echo "/bin/bash is NOT a file"
fi
if :; then echo "always true"; fi
```

==`:`==是一个特殊的命令，称为**空命令**，该命令不做任何事，但Exit Status总是真。此外，也可以执行/bin/true或/bin/false得到真或假的Exit Status。再看一个例子：

```
#! /bin/sh
echo "Is it morning? Please answer yes or no."
read YES_OR_NO
if [ "$YES_OR_NO" = "yes" ]; then
	echo "Good morning!"
elif [ "$YES_OR_NO" = "no" ]; then
	echo "Good afternoon!"
else
	echo "Sorry, $YES_OR_NO not recognized. Enter yes or no."
	exit 1
fi
exit 0
```

上例中的read命令的作用是等待用户输入一行字符串，将该字符串存到一个Shell变量中。

### case/esac

case命令可类比C语言的switch/case语句，esac表示case语句块的结束。C语言的case只能匹配整型或字符型常量表达式，而Shell脚本的case可以匹配**字符串**和**Wildcard**，**每个匹配分支可以有若干条命令，末尾必须以==`;;`==结束**，执行时找到第一个匹配的分支并执行相应的命令，然后直接跳到esac之后，~~不需要像C语言一样用break跳出~~。

```
echo "Is it morning? Please answer yes or no."
read YES_OR_NO
case "$YES_OR_NO" in
    yes|y|Yes|YES)       # 条件1
        echo "Good Morning!"
        ;;              # 分支必须以;;结束
    [nN]*)              # 条件2 
        echo "Good Afternoon!"
        ;;
    *)                  # 其他
        echo "Sorry, $YES_OR_NO not recognized. Enter yes or no."
        exit 1
        ;;
esac
exit 0
```

使用case语句的例子可以在系统服务的脚本目录`/etc/init.d`中找到。这个目录下的脚本大多具有这种形式（以/etc/init.d/nfs-kernel-server为例）：

```
case "$1" in        # case  xxx in
	start)          # xxx)条件
		...
	;;              # 分支必须以;;结束， ;; 等价C break
	stop)
		...
		;;
	reload | force-reload)
		...
	;;
	restart)
		...
	*)              # *)其他条件
	    log_success_msg"Usage: nfs-kernel-server \	
        {start|stop|status|reload|force-reload|restart}"
	    exit 1
	;;
esac
```

启动nfs-kernel-server服务的命令是

```
sudo /etc/init.d/nfs-kernel-server start
```

`$1`是一个特殊变量，在执行脚本时自动取值为第一个命令行参数，也就是start，所以进入start)分支执行相关的命令。同理，命令行参数指定为stop、reload或restart可以进入其它分支执行停止服务、重新加载配置文件或重新启动服务的相关命令。

## 循环

### for/do/done

Shell脚本的for循环结构和C语言很不一样，它类似于某些编程语言的foreach循环。例如：

```
#! /bin/sh
for FRUIT in apple banana pear     # 循环条件
do
	echo "I like $FRUIT"
done
```

FRUIT是一个循环变量，第一次循环$FRUIT的取值是apple，第二次取值是banana，第三次取值是pear。再比如，要将当前目录下的chap0、chap1、chap2等文件名改为chap0~、chap1~、chap2~等（按惯例，末尾有~字符的文件名表示临时文件），这个命令可以这样写：

```
# 批量重命名
for FILENAME in chap?
do 
	mv $FILENAME $FILENAME~
done
```

也可以这样写：

```
$ for FILENAME in `ls chap?`; do mv $FILENAME $FILENAME~; done
```

### while/do/done

while的用法和C语言类似。比如一个验证密码的脚本：

```
#! /bin/sh
echo "Enter password:"
read TRY
while [ "$TRY" != "secret" ]     # 循环条件
do
	echo "Sorry, try again"
	read TRY
done
```

下面的例子通过算术运算控制循环的次数：

```
#! /bin/sh
COUNTER=1
while [ "$COUNTER" -lt 10 ]
do
	echo "Here we go again"
	COUNTER=$(($COUNTER+1))
done
```

另，Shell还有until循环，类似C语言的do…while。

### break和continue

break跳出循环，continue跳过本次循环。

```
break[n]    # 可以指定跳出n层循环
```

```
continue    # 跳过本次循环，但不会跳出循环
```

## 函数

### 函数定义

和C语言类似，Shell中也有**函数**的概念，但是函数**定义**中**没有返回值**也**没有参数列表**。例如：

```
#! /bin/sh
myfuc(){ echo "Function foo is called";}  # 定义函数写一行
echo "-=start=-"
myfuc   			 # 调用
echo "-=end=-"

foo(){ 
	echo "Function foo is called"
}
echo "-=start=-"
foo
echo "-=end=-"
```

注意函数体的左花括号 { 和后面的命令之间必须有**空格**或换行，如果将最后一条命令和右花括号 } 写在同一行，命令末尾必须有**分号;**。但，不建议将函数定义写至一行上，不利于脚本阅读。
在定义foo()函数时并不执行函数体中的命令，就像定义变量一样，只是给foo这个名一个定义，到后面调用foo函数的时候（注意Shell中的函数调用不写括号）才执行函数体中的命令。Shell脚本中的函数必须先定义后调用，一般把函数定义语句写在脚本的前面，把函数调用和其它命令写在脚本的最后（类似C语言中的main函数，这才是整个脚本实际开始执行命令的地方）。
Shell函数**没有参数列表**并不表示不能传参数，事实上，函数就像是迷你脚本，调用函数时可以传任意个参数，在函数内同样是用**$0、$1、$2**等变量来**提取参数**，函数中的位置参数相当于函数的**局部变量**，改变这些变量并不会影响函数外面的$0、$1、$2等变量。函数中可以用return命令返回，如果return后面跟一个数字则表示函数的Exit Status。
下面这个脚本可以一次创建多个目录，各目录名通过命令行参数传入，脚本逐个测试各目录是否存在，如果目录不存在，首先打印信息然后试着创建该目录。

```
#! /bin/sh
is_directory()           # 定义函数
{
	DIR_NAME=$1
	if [ ! -d $DIR_NAME ]; then
		return 1
	else
		return 0
	fi
}
for DIR in "$@"; 
do
	if is_directory "$DIR"      # 调用函数，参数$1
	then 
		:    # 文件夹存在，啥也不干
	else
		echo "$DIR doesn't exist. Creating it now..."
		mkdir $DIR > /dev/null 2>&1    # 若mkdir错误信息重定向
		if [ $? -ne 0 ]; then   # $?上一条命令的Exit Status
			echo "Cannot create directory $DIR"
			exit 1
		fi
	fi
done
```

注意：is_directory()返回0表示真返回1表示假。

### Shell 传递参数

我们可以在执行 Shell 脚本时，向脚本传递参数，脚本内获取参数的格式为：**$n**。**n** 代表一个数字，1 为执行脚本的第一个参数`$1`，2 为执行脚本的第二个参数`$2`，以此类推……

| 参数处理 | 说明                                                         |
| :------- | :----------------------------------------------------------- |
| $0       | 当前命令                                                     |
| $1       | 传递到脚本的第一个参数                                       |
| $2       | 传递到脚本的第2个参数                                        |
| $#       | 传递到脚本的**参数个数**                                     |
| $*       | 以一个单字符串显示所有向脚本传递的参数。 如"$*"用「"」括起来的情况、以"$1 $2 … $n"的形式输出所有参数。 |
| $@       | 与$*相同，但是使用时加引号，并在引号中返回每个参数。 如"$@"用「"」括起来的情况、以"$1" "$2" … "$n" 的形式输出所有参数。 |
| $$       | 脚本运行的当前**进程ID号**                                   |
| $!       | 后台运行的最后一个进程的ID号                                 |
| $-       | 显示Shell使用的当前选项，与[set命令](https://www.runoob.com/linux/linux-comm-set.html)功能相同。 |
| $?       | 显示 上一条命令的**退出状态**。0表示没有错误，其他任何值表明有错误。 |

```
#!/bin/bash
echo "Shell 传递参数实例！";
echo "执行的文件名：$0";
echo "第一个参数为：$1";
echo "第二个参数为：$2";
echo "第三个参数为：$3";
echo "参数个数为：$#";
echo "传递的参数作为一个字符串显示：$*";
```

## Shell脚本调试方法

Shell提供了一些用于调试脚本的选项，如：

- `-n`	  读一遍脚本中的命令但不执行，用于**检查**脚本中的**语法**错误。
	 `-v`	  一边执行脚本，一边将执行过的脚本命令打印到标准错误输出。
	 `-x`	  提供**跟踪**执行信息，将执行的每一条命令和结果依次打印出来。

这些选项有三种常见的使用方法：

1. 在命令行提供参数。如：

```
$ sh -x ./script.sh    # 调试脚本
```

2. 在脚本开头提供参数。如：

```
#! /bin/sh -x      # 调试脚本
  ......
```

3. 在脚本中用set命令启用或禁用参数。如：

```
#! /bin/sh
if [ -z "$1" ]; then
	set -x              # 启用调试
	echo "ERROR: Insufficient Args."
	exit 1
	set +x              # 结束调试
fi
```

set -x和set +x分别表示启用和禁用-x参数，这样可以只对脚本中的某一段进行跟踪调试。



