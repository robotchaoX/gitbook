# gdb调试

---

[TOC]

<!-- toc -->

----

### 1 简介

GDB（GNU Debugger）是GCC的调试工具。其功能强大，现描述如下：     
GDB主要帮忙你完成下面四个方面的功能：     
1.启动你的程序，可以按照你的自定义的要求随心所欲的运行程序。     
2.可让被调试的程序在你所指定的调置的断点处停住。（断点可以是条件表达式）     
3.当程序被停住时，可以检查此时你的程序中所发生的事。     
4.动态的改变你程序的执行环境。

使用文字终端（shell），实现一个单步调试的功能

### 2 生成调试信息

​     一般来说GDB主要调试的是C/C++的程序。要调试C/C++的程序，首先在编译时，我们必须要把调试信息加到可执行文件中。使用编译器（cc/gcc/g++）的 -g 参数可以做到这一点。如：

```
gcc -g hello.c -o hello
g++ -g hello.cpp -o hello
```

`-g` gdb调试

如果没有`-g`，你将看不见程序的函数名、变量名，所代替的全是运行时的内存地址。当你用-g把调试信息加入之后，并成功编译目标代码以后，让我们来看看如何用gdb来调试他。

### 3 启动GDB

gdb + 可执行文件 （如：gdb hello）

```
gdb hello    # 启动gdb调试
quit    # 退出gdb
```

### 4 程序运行上下文

##### 4.1 运行程序

```
run
r    # 启动程序
start    # 单步执行，运行程序，停在第一行执行语句
```

##### 4.2 程序运行参数

```
set args aa bb    # 指定运行时参数aa bb
```

指定运行时参数,int main(int *argc,char **argv)。（如：set args 10 20 30 40 50 ）

```
show args    # 查看设置好的运行参数
```

##### 4.3 工作目录

```
cd    # 相当于shell的cd命令
pwd    # 显示当前的所在目录
```

### 5 设置断点

##### 5.1 简单断点

`break` 设置断点，可以简写为b

```
# break
b 行号12    # 在第12行设置断点
b func    # 设置断点，在func函数入口处
```

##### 5.2 多文件设置断点

在进入指定函数时停住:
C++中可以使用class::function或function(type,type)格式来指定函数名。
如果有名称空间，可以使用namespace::class::function或者function(type,type)格式来指定函数名。

```
break filename:linenum    # 在源文件filename的linenum行处停住
break filename:function    # 在源文件filename的function函数的入口处停住
break class::function或function(type,type)    # 在类class的function函数的入口处停住
break namespace::class::function    # 在名称空间为namespace的类class的function函数的入口处停住
```

##### 5.3 查询所有断点

```
info b    # 查询所有断点
# info break    # 查看断点信息
```

### 6 条件断点

​     一般来说，为断点设置一个条件，我们使用if关键词，后面跟其断点条件

```
b test.c:8 if intValue = 5    # 设置一个条件断点
# b 行号（2） 条件（if i=5） --> 在第2行设置断点，只有i等于5时生效
```

### 7 维护断点

##### 删除断点

d（delete）+ 断点号 --> 删除指定断点号对应的断点

```
# delete
d    # 删除所有的断点
delete [range...]    # 删除指定的断点
```

delete [range...] 删除指定的断点，如果不指定断点号，则表示删除所有的断点。range 表示断点号的范围（如：3-7）。其简写命令为`d`

比删除更好的一种方法是disable停止点，disable了的停止点，GDB不会删除，当你还需要时，enable即可 

##### enable/disable 断点

disable/enable + 断点号 --> 设置断点是否有效

```
# disable
dis    # disable所有的停止点
disable  [range...]    # disable所指定的停止点
```

disable所指定的停止点，如果什么都不指定，表示disable所有的停止点。简写命令是`dis`

```
# enable
ena    # enable所有的停止点
enable [range...]    # enable所指定的停止点
```

enable所指定的停止点，如果什么都不指定，表示enable所有的停止点。简写命令是`ena`

### 8 调试代码

##### 可视化调试

```
wi    # 可视化调试
```

```
run    # 运行程序，可简写为r
next    # 单步跟踪，下一行（不会进入到函数体内部），可简写为n
step    # 单步跟踪，下一步（会进入到函数体内部），可简写为s
skip fuction getVal    # step单步时跳过getVal函数
finish    # 结束当前函数，返回到函数调用点，简写fin
return -1    # 在当前位置直接return -1返回
continue    # 继续运行程序，直到下一个端点，可简写为c
until 5    # 向下运行5行后暂停
until    # 在一个循环体内单步跟踪时，这个命令可以运行程序直到退出循环体,可简写为u
```

### 9 查看运行时数据

p(print) + 变量名 --> 打印变量值

`print` 打印变量、字符串、表达式等的值，可简写为`p`

```
print aaaa    # 打印 aaaa 的值
```

### 10 追踪变量

display + 变量名 --> 追踪变量，之后每执行一步，该变量值都会被打印出来

undisplay + 变量名编号 --> 取消跟踪

你可以设置一些自动显示的变量，当程序停住时，或是在你单步跟踪时，这些变量会自动显示。相关的GDB命令是display。

```
display 变量名    # 设置自定显示变量
undisplay 变量名编号    # 取消自动显示
info display    # 查看display设置的自动显示的信息
delete display dnums…    # 删除自动显示
disable display dnums…
enable display dnums…
```

dnums意为所设置好了的自动显式的编号。如果要同时删除几个，编号可以用空格分隔，如果要删除一个范围内的编号，可以用减号表示（如：2-5）

disable和enalbe不删除自动显示的设置，而只是让其失效和恢复。

### 11  查看修改变量的值

```
ptype width    # 查看变量width的类型
```

```
p width    # 打印变量width 的值
```

 你可以使用set var命令来告诉GDB，width不是你GDB的参数，而是程序的变量名，如：

set --> 设置变量的值 set var n=100

```
set var width=47
```

在你改变程序变量取值时，最好都使用set var格式的GDB命令。

### 12 显示源代码

​     GDB 可以打印出所调试程序的源代码，当然，在程序编译时一定要加上 -g 的参数，把源程序信息编译到执行文件中。不然就看不到源程序了。当程序停下来以后，

​     GDB会报告程序停在了那个文件的第几行上。你可以用list命令来打印程序的源代码。默认打印10行，还是来看一看查看源代码的GDB命令吧。

`list`  简写`l` 列出文件的代码清单

```
l
list    # 显示当前行后面的源程序
list -    # 显示当前行前面的源程序
list 行号32    # 代码从第32行开始显示
list function    # 显示函数名为function的函数的源程序
```

一般是打印当前行的上5行和下5行，如果显示函数是是上2行下8行，默认是10行，当然，你也可以定制显示的范围，使用下面命令可以设置一次显示源程序的行数。

```
set listsize count    # 设置一次显示源代码的行数
show listsize    # 查看当前listsize的设置
```

### 退出gdb

```
quit
q    # 退出gdb
```



### gdb调试core文件

什么是coredump

  Coredump叫做核心转储，它是进程运行时在突然崩溃的那一刻的一个内存快照。操作系统在程序发生异常而异常在进程内部又没有被捕获的情况下，会把进程此刻内存、寄存器状态、运行堆栈等信息转储保存在一个文件里。

core文件

当程序运行过程中出现段错误（Segmentation Fault），程序将停止运行，由操作系统把程序当前的内存状况存储在一个 core 文件中，即核心转储文件（Coredump File），core 文件是程序运行状态的内存映象。

通常情况下，core文件会包含了程序运行时的内存，寄存器状态，堆栈指针，内存管理信息还有各种函数调用堆栈信息等，我们可以理解为是程序工作当前状态存储生成第一个文件，许多的程序出错的时候都会产生一个core文件，通过工具分析这个文件，我们可以定位到程序异常退出的时候对应的堆栈调用等信息，找出问题所在并进行及时解决。

使用 gdb 调试 core 文件，可以帮助我们快速定位程序出现段错误的位置。当然，可执行程序编译时应加上 -g 编译选项，生成调试信息。

coredump文件的存储位置

   core文件默认的存储位置与对应的可执行程序在同一目录下，文件名是core，大家可以通过下面的命令看到core文件的存在位置：`cat  /proc/sys/kernel/core_pattern`

缺省值是core

通过下面的命令可以更改coredump文件的存储位置，若你希望把core文件生成到/data/coredump/core目录下：

   echo “/data/coredump/core”> /proc/sys/kernel/core_pattern

注意，这里当前用户必须具有对/proc/sys/kernel/core_pattern的写权限。

缺省情况下，内核在coredump时所产生的core文件放在与该程序相同的目录中，并且文件名固定为*core*。很显然，如果有多个程序产生core文件，或者同一个程序多次崩溃，就会重复覆盖同一个core文件，因此我们有必要对不同程序生成的core文件进行分别命名。

我们通过修改kernel的参数，可以指定内核所生成的coredump文件的文件名。例如，使用下面的命令使kernel生成名字为*core.filename.pid*格式的core dump文件：

echo “/data/coredump/core.%e.%p” >/proc/sys/kernel/core_pattern

这样配置后，产生的core文件中将带有崩溃的程序名、以及它的进程ID。上面的%e和%p会被替换成程序文件名以及进程ID。

如果在上述文件名中包含目录分隔符“/”，那么所生成的core文件将会被放到指定的目录中。 需要说明的是，在内核中还有一个与coredump相关的设置，就是/proc/sys/kernel/core_uses_pid。如果这个文件的内容被配置成1，那么即使core_pattern中没有设置%p，最后生成的core dump文件名仍会加上进程ID。

##### coredump产生的原因

造成程序coredump的原因有很多，这里总结一些比较常用的经验吧：

 1，内存访问越界

  a) 由于使用错误的下标，导致数组访问越界。

  b) 搜索字符串时，依靠字符串结束符来判断字符串是否结束，但是字符串没有正常的使用结束符。

  c) 使用strcpy, strcat, sprintf, strcmp,strcasecmp等字符串操作函数，将目标字符串读/写爆。应该使用strncpy, strlcpy, strncat, strlcat, snprintf, strncmp, strncasecmp等函数防止读写越界。

 2，多线程程序使用了线程不安全的函数。

应该使用下面这些可重入的函数，它们很容易被用错：

asctime_r(3c) gethostbyname_r(3n) getservbyname_r(3n)ctermid_r(3s) gethostent_r(3n) getservbyport_r(3n) ctime_r(3c) getlogin_r(3c)getservent_r(3n) fgetgrent_r(3c) getnetbyaddr_r(3n) getspent_r(3c)fgetpwent_r(3c) getnetbyname_r(3n) getspnam_r(3c) fgetspent_r(3c)getnetent_r(3n) gmtime_r(3c) gamma_r(3m) getnetgrent_r(3n) lgamma_r(3m) getauclassent_r(3)getprotobyname_r(3n) localtime_r(3c) getauclassnam_r(3) etprotobynumber_r(3n)nis_sperror_r(3n) getauevent_r(3) getprotoent_r(3n) rand_r(3c) getauevnam_r(3)getpwent_r(3c) readdir_r(3c) getauevnum_r(3) getpwnam_r(3c) strtok_r(3c) getgrent_r(3c)getpwuid_r(3c) tmpnam_r(3s) getgrgid_r(3c) getrpcbyname_r(3n) ttyname_r(3c)getgrnam_r(3c) getrpcbynumber_r(3n) gethostbyaddr_r(3n) getrpcent_r(3n)

 3，多线程读写的数据未加锁保护。

对于会被多个线程同时访问的全局数据，应该注意加锁保护，否则很容易造成coredump

 4，非法指针

  a) 使用空指针

  b) 随意使用指针转换。一个指向一段内存的指针，除非确定这段内存原先就分配为某种结构或类型，或者这种结构或类型的数组，否则不要将它转换为这种结构或类型的指针，而应该将这段内存拷贝到一个这种结构或类型中，再访问这个结构或类型。这是因为如果这段内存的开始地址不是按照这种结构或类型对齐的，那么访问它时就很容易因为bus error而core dump。

 5，堆栈溢出

不要使用大的局部变量（因为局部变量都分配在栈上），这样容易造成堆栈溢出，破坏系统的栈和堆结构，导致出现莫名其妙的错误。  



##### 1 配置产生core文件

查看ulimit设置

```
ulimit -c
ulimit -a    # 查看core file大小的配置情况
```

如果core file size为0，则表示系统关闭了dump core。可以通过ulimit -c unlimited来打开。若发生了段错误，但没有core dump，是由于系统禁止core文件的生成。

设置ulimit

```
ulimit -c unlimited    # 配置产生core文件，临时修改，重启后无效
```

修改当前用户的`~/.bashrc`文件，添加 `ulimit -c unlimited` （一劳永逸）

或者
（1）在/etc/rc.local 中增加一行 `ulimit -c unlimited`
（2）在/etc/profile 中增加一行 `ulimit -c unlimited`



##### 2 用gdb调试core文件

发生core dump之后, 用gdb进行查看core文件的内容, 以定位文件中引发core dump的行

```
gdb 可执行文件 core文件    # gdb查看core文件
gdb test core
```

启动调试可以使用where或者bt（breaktrace）来查看错误发生的位置和堆栈。

在进入gdb后，查找段错误位置：**where或者bt(backtrace)**

查找段错误位置

```
where    # 查看调用栈信息
bt    # 查看调用栈信息
```

