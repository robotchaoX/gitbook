## Valgrind

### valgrind简介

Valgrind是一款用于内存调试、内存泄漏检测以及性能分析的软件开发工具。

Valgrind是用于调试和分析Linux程序的GPL系统。使用Valgrind的 工具套件，您可以自动检测许多内存管理和线程错误。您还可以执行详细的性能分析，以帮助加快程序速度。

Valgrind可使用任何语言编写的程序。因为Valgrind直接与程序二进制文件一起使用，所以它可以与以任何编程语言编写的程序一起使用，无论它们是编译的，即时编译的还是解释的。Valgrind工具主要针对用C和C ++编写的程序，因为用这些语言编写的程序往往有最多的错误！但是，例如，它可以用于调试和分析以多种语言编写的系统。Valgrind已用于部分或全部用C，C ++，Java，Perl，Python，汇编代码，Fortran，Ada等编写的程序上。

Valgrind是一套Linux下，开放源代码（GPL V2）的仿真调试工具的集合。Valgrind由内核（core）以及基于内核的其他调试工具组成。内核类似于一个框架（framework），它模拟了一个CPU环境，并提供服务给其他工具；而其他工具则类似于插件 (plug-in)，利用内核提供的服务完成各种特定的内存调试任务。Valgrind的体系结构如下图所示：

![img](assets/1783214-cef417fe58980365.jpg)

#### valgrind工具

1. **Memcheck**：

   **内存错误**检测器，能够发现开发中绝大多数内存错误使用情况。它可以帮助您使程序，尤其是C和C ++的程序更加正确。

   Memcheck 工具主要检查下面的程序错误：

   - 使用未初始化的内存 (Use of uninitialised memory)
   - 读/写已经被释放的内存 (Reading/writing memory after it has been free’d)
   - 读/写内存越界 (Reading/writing off the end of malloc’d blocks)
   - 读/写不恰当的内存栈空间 (Reading/writing inappropriate areas on the stack)
   - 内存泄漏 (Memory leaks – where pointers to malloc’d blocks are lost forever)
   - malloc/new/new[]和free/delete/delete[]不匹配 (Mismatched use of malloc/new/new [] vs free/delete/delete [])
   - src和dst的重叠 (Overlapping src and dst pointers in memcpy() and related functions)

2. **Callgrind**：

   生成调用图的缓存分析器，它主要用来检查程序中**函数调用**过程中出现的问题。
   Callgrind收集程序运行时的一些数据，函数调用关系等信息，还可以有选择地进行cache 模拟。在运行结束时，它会把分析数据写入一个文件。callgrind_annotate可以把这个文件的内容转化成可读的形式。

3. **Cachegrind**：

   缓存和分支预测探查器，它主要用来检查程序中**缓存使用**出现的问题。它可以帮助您使程序运行更快。
   它模拟 CPU中的一级缓存I1,D1和L2二级缓存，能够精确地指出程序中 cache的丢失和命中。如果需要，它还能够为我们提供cache丢失次数，内存引用次数，以及每行代码，每个函数，每个模块，整个程序产生的指令数。这对优化程序有很大的帮助。

4. **Helgrind**：

   线程错误检测器，它主要用来检查**多线程程**序中出现的**竞争**问题。
   Helgrind 寻找内存中被多个线程访问，而又没有一贯加锁的区域，这些区域往往是线程之间失去同步的地方，而且会导致难以发掘的错误。Helgrind实现了名为” Eraser” 的竞争检测算法，并做了进一步改进，减少了报告错误的次数。

5. DRD：还是线程错误检测器。它类似于Helgrind，但是使用不同的分析技术，因此可能会发现不同的问题。

6. **Massif**：

   堆分析器，它主要用来检查程序中**堆栈使用**中出现的问题。
   堆栈分析器，它能测量程序在堆栈中使用了多少内存，告诉我们堆块，堆管理块和栈的大小。Massif能帮助我们减少内存的使用，在带有虚拟内存的现代系统中，它还能够加速我们程序的运行，减少程序停留在交换区中的几率。

7. DHAT：是另一种堆分析器。它可以帮助您了解模块寿命，模块利用率和布局效率低下的问题。

8. BBV：是一个实验性的SimPoint基本块矢量生成器。这对从事计算机体系结构研究和开发的人员很有用。



#### 内存检查原理

**Memcheck**检测内存问题的原理如下图所示：

![内存检查原理](assets/image003.jpg)

Memcheck 能够检测出内存问题，关键在于其建立了两个全局表。

- Valid-Value 表：
  对于进程的整个地址空间中的每一个字节(byte)，都有与之对应的 8 个 bits；对于 CPU 的每个寄存器，也有一个与之对应的 bit 向量。这些 bits 负责记录该字节或者寄存器值是否具有有效的、已初始化的值。
- Valid-Address 表
  对于进程整个地址空间中的每一个字节(byte)，还有与之对应的 1 个 bit，负责记录该地址是否能够被读写。

**检测原理**：

- 当要读写内存中某个字节时，首先检查这个字节对应的 A bit。如果该A bit显示该位置是无效位置，memcheck 则报告读写错误。
- 内核（core）类似于一个虚拟的 CPU 环境，这样当内存中的某个字节被加载到真实的 CPU 中时，该字节对应的 V bit 也被加载到虚拟的 CPU 环境中。一旦寄存器中的值，被用来产生内存地址，或者该值能够影响程序输出，则 memcheck 会检查对应的V bits，如果该值尚未初始化，则会报告使用未初始化内存错误。



### valgrind的使用

#### 编译准备

建议在编译时加上`-g`参数启用了调试信息，可以使valgrind发现的错误更精确，如能够定位到源代码行。

编译优化选项请选择`-O0`，虽然这会降低程序的执行效率。因为在极少数情况下，`-O2` 会`-O1`观察到编译器的优化，从而生成使Memcheck误报未初始化值错误或丢失未初始化值错误的代码。除了Memcheck所有其他工具不受优化级别的影响，对于Cachegrind之类的性能分析工具，最好以其常规优化级别编译程序。

建议使用`-Wall`开启所有警告，因为它可以识别Valgrind在较高的优化级别上可能会遗漏的部分或全部问题。

```
#include <stdlib.h>
void f(void) {
  int *x = malloc(10 * sizeof(int));
  x[10] = 0; // problem 1: heap block overrun
  // problem 2: memory leak -- x not freed
} 

int main(void) {
  f();
  return 0;
}
```

编译程序时，需要加上-g选项：

```
$ gcc -g -o main main.c
```

#### valgrind调试

Valgrind被设计为尽可能非侵入性的。利用valgrind调试内存问题，不需要重新编译源，重新链接或以其他方式修改要检查的程序，它的输入就是二进制的可执行程序。

调用Valgrind的通用格式是：

```
valgrind [valgrind-options] your-prog-name [your-prog-options]

valgrind --tool=memcheck --leak-check=full ./main
```

`--tool=memcheck`选择valgrind工具，默认是memcheck。`--leak-check=full` 选项打开详细的内存泄漏检测器。

您的程序将比正常运行慢得多（例如20到30倍），并且使用更多的内存。memcheck将发出有关内存错误和它检测到的泄漏的消息。

如果您使用的是C ++，则可能要考虑的另一种选择是`-fno-inline`。这样可以更轻松地查看函数调用链，这有助于减少在大型C ++应用程序中导航时的混乱。或者，Valgrind选项 `--read-inline-info=yes`指示Valgrind读取描述内联信息的调试信息。这样，即使使用内联编译应用程序时，函数调用链也会正确显示。

#### 选项参数

Valgrind 的参数分为两类，一类是 Valgrind核心的参数选项，它对所有的工具都适用；另外一类就是具体某个工具如 memcheck 的参数选项。

Valgrind 默认的工具就是 memcheck，也可以通过“--tool=tool name”指定其他的工具。Valgrind 提供了大量的参数满足你特定的调试需求，具体可参考其用户手册，[Valgrind核心命令行参数选项](https://www.valgrind.org/docs/manual/manual-core.html)。

常用选项，适用于所有Valgrind工具：

1. --tool=<name> 运行 valgrind中名为toolname的工具。例如memcheck（默认），cachegrind，callgrind，helgrind，drd，massif，dhat，bouchey，none，exp-bbv等。
2. -h --help 显示帮助信息。
3. --version 显示valgrind内核的版本，每个工具都有各自的版本。
4. -q --quiet 安静地运行，只打印错误信息。
5. -v --verbose 更详细的信息, 增加错误数统计。
6. --trace-children=no|yes 跟踪子线程? [no]
7. --track-fds=no|yes 跟踪打开的文件描述？[no]
8. --time-stamp=no|yes 增加时间戳到LOG信息? [no]
9. --log-fd=<number> 输出LOG到描述符文件 [2=stderr]
10. --log-file=<file> 将输出LOG信息写入到指定文件里
11. --log-file-exactly=<file> 输出LOG信息到 file
12. --log-file-qualifier=<VAR> 取得环境变量的值来做为输出信息的文件名。 [none]
13. --log-socket=<ip-address:port-number> 输出LOG信息到指定IP地址的指定端口

LOG信息输出

1. -xml=yes 将信息以xml格式输出，只有memcheck可用
2. -num-callers=<number> show <number> callers in stack traces [12]
3. -error-limit=no|yes 如果太多错误，则停止显示新错误? [yes]
4. -error-exitcode=<number> 如果发现错误则返回错误代码 [0=disable]
5. -db-attach=no|yes 当出现错误，valgrind会自动启动调试器gdb。[no]
6. -db-command=<command> 启动调试器的命令行选项[gdb -nw %f %p]

适用于Memcheck工具的相关选项：

1. -leak-check=no|summary|full 要求对leak给出详细信息
2. -leak-resolution=low|med|high how much bt merging in leak check
3. -show-reachable=no|yes show reachable blocks in leak check

#### 输出信息

```

```

`==19182==`进程ID19182 ，通常不重要。

`HEAP SUMMARY`，它表示程序在堆上分配内存的情况。程序报错的具体位置。

`LEAK SUMMARY`，它表示程序内存泄露的情况，其中对内存泄露进行了分类，总共有五类：

- **definitely lost** 意味着你的程序一定存在内存泄露；
- **indirectly lost** 意味着你的程序一定存在内存泄露，并且泄露情况和指针结构相关。
- **possibly lost** 意味着你的程序一定存在内存泄露，除非你是故意进行着不符合常规的操作，例如将指针指向某个已分配内存块的中间位置。
- **still reachable** 意味着你的程序可能是没问题的，但确实没有释放掉一些本可以释放的内存。这种情况是很常见的，并且通常基于合理的理由。
- **suppressed** 意味着有些泄露信息被压制了。在默认的 suppression 文件中可以看到一些 suppression 相关设置。



#### Valgrind的局限？？

1. Valgrind不对静态数组(分配在栈上)进行边界检查。

   如果在程序中声明了一个数组:

   ```
   int main() {
     char x[10];
     x[11] = 'a';
   }
   ```

   Valgrind则不会警告你，你可以把数组改为动态在堆上分配的数组，这样就可能进行边界检查了。这个方法好像有点得不偿失的感觉。

2. Valgrind占用了更多的内存，可达两倍于你程序的正常使用量。

   如果你用Valgrind来检测使用大量内存的程序就会遇到问题，它可能会用很长的时间来运行测试。大多数情况下，这都不是问题，即使速度慢也仅是检测时速度慢，如果你用Valgrind来检测一个正常运行时速度就很慢的程序，这下问题就大了。 Valgrind不可能检测出你在程序中犯下的所有错误--如果你不检查缓冲区溢出，Valgrind也不会告诉你代码写了它不应该写的内存。



### valgrind例子

#### 使用未初始化的内存

```
#include <iostream>
int main() {
  int x;
  if (x == 0) {
    std::cout << "X is zero" << std::endl;
  }
  return 0;
}
```

使用 Valgrind 检测内存使用情况：

```
$ g++ -std=c++11 -g -o main_cpp main.cpp
$ valgrind --tool=memcheck --leak-check=full ./main_cpp
```

```
==31554== Memcheck, a memory error detector
==31554== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31554== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31554== Command: ./main_cpp
==31554==
==31554== Conditional jump or move depends on uninitialised value(s)
==31554==    at 0x400852: main (main.cpp:6)
```



#### 内存泄漏/未释放内存

##### C语言

Valgrind 可以用来检测程序在哪个位置发生内存泄漏，例如下面的C语言程序：

```
#include <stdlib.h>
int main() {
  int *array = malloc(sizeof(int));
  return 0;
}
```

编译程序时，需要加上-g选项：

```
$ gcc -g -o main_c main.c
```

使用 Valgrind 检测内存使用情况：

```
$ valgrind --tool=memcheck --leak-check=full  ./main_c
```

```
==31416== Memcheck, a memory error detector
==31416== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31416== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31416== Command: ./main_c
==31416==
==31416==
==31416== HEAP SUMMARY:
==31416==     in use at exit: 4 bytes in 1 blocks
==31416==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==31416==
==31416== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==31416==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==31416==     by 0x400537: main (main.c:5)
==31416==
==31416== LEAK SUMMARY:
==31416==    definitely lost: 4 bytes in 1 blocks
==31416==    indirectly lost: 0 bytes in 0 blocks
==31416==      possibly lost: 0 bytes in 0 blocks
==31416==    still reachable: 0 bytes in 0 blocks
==31416==         suppressed: 0 bytes in 0 blocks
==31416==
==31416== For counts of detected and suppressed errors, rerun with: -v
==31416== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

先看看输出信息中的`HEAP SUMMARY`，它表示程序在堆上分配内存的情况，其中的`1 allocs`表示程序分配了 1 次内存，`0 frees`表示程序释放了 0 次内存，`4 bytes allocated`表示分配了 4 个字节的内存。

另外，Valgrind 也会报告程序是在哪个位置发生内存泄漏。`by 0x400537: main (main.c:5)`从上面的信息可以看到，程序发生了一次内存泄漏，位置是`main.c`文件的第 5 行。

`LEAK SUMMARY`，它表示程序内存泄露的情况。`definitely lost: 4 bytes in 1 blocks`程序一定存在内存泄露。

#####  C++ 程序reachable原因

下面是一个正常的 C++ 程序，没有发生内存泄漏：

```
#include <string>
int main() {
  auto ptr = new std::string("Hello, World!");
  delete ptr;
  return 0;
}
```

使用 Valgrind 分析这段程序：

```
$ valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./main_cpp
```

```
==31438== Memcheck, a memory error detector
==31438== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31438== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31438== Command: ./main_cpp
==31438==
==31438==
==31438== HEAP SUMMARY:
==31438==     in use at exit: 72,704 bytes in 1 blocks
==31438==   total heap usage: 2 allocs, 1 frees, 72,736 bytes allocated
==31438==
==31438== 72,704 bytes in 1 blocks are still reachable in loss record 1 of 1
==31438==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==31438==    by 0x4EC3EFF: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
==31438==    by 0x40104E9: call_init.part.0 (dl-init.c:72)
==31438==    by 0x40105FA: call_init (dl-init.c:30)
==31438==    by 0x40105FA: _dl_init (dl-init.c:120)
==31438==    by 0x4000CF9: ??? (in /lib/x86_64-linux-gnu/ld-2.23.so)
==31438==
==31438== LEAK SUMMARY:
==31438==    definitely lost: 0 bytes in 0 blocks
==31438==    indirectly lost: 0 bytes in 0 blocks
==31438==      possibly lost: 0 bytes in 0 blocks
==31438==    still reachable: 72,704 bytes in 1 blocks
==31438==         suppressed: 0 bytes in 0 blocks
==31438==
==31438== For counts of detected and suppressed errors, rerun with: -v
==31438== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

使用 Valgrind 分析 C++ 程序时，有一些问题需要留意。

例如，这个程序并没有发生内存泄漏，但是从`HEAP SUMMARY`可以看到，程序分配了 2 次内存，但却只释放了 1 次内存，为什么会这样呢？
实际上这是**由于C++ 在分配内存时，为了提高效率，使用了它自己的内存池。当程序终止时，内存池的内存才会被操作系统回收**，所以 Valgrind 会将这部分内存报告为 reachable 的，需要注意，**reachable 的内存不代表内存泄漏**。例如，从上面的输出中可以看到，有 72704 个字节是 reachable 的，但没有报告内存泄漏。



#### 内存读写越界

C++ 程序经常出现的 Bug 就是数组越界访问，例如下面的程序出现了越界访问：

```
#include <iostream>
#include <vector>
int main() {
  std::vector<int> v(10, 0);
  std::cout << v[10] << std::endl;
  return 0;
}
```

使用 Valgrind 分析这段程序，Valgrind 会提示越界访问：

```
$ g++ -std=c++11 -g -o main_cpp main.cpp
$ valgrind --tool=memcheck --leak-check=full ./main_cpp
```

```
==31523== Memcheck, a memory error detector
==31523== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31523== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31523== Command: ./main_cpp
==31523==
==31523== Invalid read of size 4
==31523==    at 0x400AD7: main (main.cpp:5)
==31523==  Address 0x5ab5ca8 is 0 bytes after a block of size 40 alloc'd
==31523==    at 0x4C2E216: operator new(unsigned long) (vg_replace_malloc.c:334)
==31523==    by 0x4010D3: __gnu_cxx::new_allocator<int>::allocate(unsigned long, void const*) (new_allocator.h:104)
==31523==    by 0x401040: std::allocator_traits<std::allocator<int> >::allocate(std::allocator<int>&, unsigned long) (alloc_traits.h:491)
==31523==    by 0x400F91: std::_Vector_base<int, std::allocator<int> >::_M_allocate(unsigned long) (stl_vector.h:170)
==31523==    by 0x400E7E: std::_Vector_base<int, std::allocator<int> >::_M_create_storage(unsigned long) (stl_vector.h:185)
==31523==    by 0x400D1E: std::_Vector_base<int, std::allocator<int> >::_Vector_base(unsigned long, std::allocator<int> const&) (stl_vector.h:136)
==31523==    by 0x400C11: std::vector<int, std::allocator<int> >::vector(unsigned long, int const&, std::allocator<int> const&) (stl_vector.h:291)
==31523==    by 0x400AB9: main (main.cpp:4)
```

`Invalid read of size 4`表示越界读取 4 个字节，这个操作出现在`main.cpp`文件的第 5 行。另外可以看到，`vector`分配了一块 40 字节的内存，程序越界访问紧接着这块内存之后的 4 个字节。

#### 非法读写

```
int main() {
  int i, *x;
  x = (int *)malloc(10 * sizeof(int));
  for (i = 0; i < 11; i++)
    x[i] = i;
  free(x);
}
```

> `==21483== Invalid write of size 4
> ==21483== at 0x4004EA: main (sample6.c:6)
> ==21483== Address 0x4C2E058 is 0 bytes after a block of size 40 alloc'd
> ==21483== at 0x4A05809: malloc (vg_replace_malloc.c:149)
> ==21483== by 0x4004C9: main (sample6.c:4)
> ==21483==
> ==21483== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 5 from 1)
> ==21483== malloc/free: in use at exit: 0 bytes in 0 blocks.
> ==21483== malloc/free: 1 allocs, 1 frees, 40 bytes allocated.
> ==21483== For counts of detected errors, rerun with: -v
> ==21483== All heap blocks were freed -- no leaks are possible.`

#### 无效指针

```
#include <stdlib.h>
int main() {
  char *x = malloc(10);
  x[10] = 'a';
  free(x);
  return 0;
}
```

> `==15262== Invalid write of size 1
> ==15262== at 0x4004D6: main (sample7.c:5)
> ==15262== Address 0x4C2E03A is 0 bytes after a block of size 10 alloc'd
> ==15262== at 0x4A05809: malloc (vg_replace_malloc.c:149)
> ==15262== by 0x4004C9: main (sample7.c:4)
> ==15262==
> ==15262== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 5 from 1)
> ==15262== malloc/free: in use at exit: 0 bytes in 0 blocks.
> ==15262== malloc/free: 1 allocs, 1 frees, 10 bytes allocated.
> ==15262== For counts of detected errors, rerun with: -v
> ==15262== All heap blocks were freed -- no leaks are possible.`

#### 重复释放

```
#include <stdlib.h>
int main() {
  char *x = malloc(10);
  free(x);
  free(x);
  return 0;
}
```

> `==15005== Invalid free() / delete / delete[]
> ==15005== at 0x4A0541E: free (vg_replace_malloc.c:233)
> ==15005== by 0x4004DF: main (sample8.c:6)
> ==15005== Address 0x4C2E030 is 0 bytes inside a block of size 10 free'd
> ==15005== at 0x4A0541E: free (vg_replace_malloc.c:233)
> ==15005== by 0x4004D6: main (sample8.c:5)
> ==15005==
> ==15005== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 5 from 1)
> ==15005== malloc/free: in use at exit: 0 bytes in 0 blocks.
> ==15005== malloc/free: 1 allocs, 2 frees, 10 bytes allocated.
> ==15005== For counts of detected errors, rerun with: -v
> ==15005== All heap blocks were freed -- no leaks are possible.`

#### 动态内存管理错误

常见的内存分配方式分三种：静态存储，栈上分配，堆上分配。全局变量属于静态存储，它们是在编译时就被分配了存储空间，函数内的局部变量属于栈上分配，而最灵活的内存使用方式当属堆上分配，也叫做内存动态分配了。常用的内存动态分配函数包括：malloc, alloc, realloc, new等，动态释放函数包括free, delete。

一旦成功申请了动态内存，我们就需要自己对其进行内存管理，而这又是最容易犯错误的。常见的内存动态管理错误包括：

##### 申请和释放不一致

由于 C++ 兼容 C，而 C 与 C++ 的内存申请和释放函数是不同的，因此在 C++ 程序中，就有两套动态内存管理函数。一条不变的规则就是采用 C 方式申请的内存就用 C 方式释放；用 C++ 方式申请的内存，用 C++ 方式释放。也就是用 malloc/alloc/realloc 方式申请的内存，用 free 释放；用 new 方式申请的内存用 delete 释放。在上述程序中，用 malloc 方式申请了内存却用 delete 来释放，虽然这在很多情况下不会有问题，但这绝对是潜在的问题。

##### 申请和释放不匹配

申请了多少内存，在使用完成后就要释放多少。如果没有释放，或者少释放了就是内存泄露；多释放了也会产生问题。上述程序中，指针p和pt指向的是同一块内存，却被先后释放两次。

##### 释放后仍然读写

本质上说，系统会在堆上维护一个动态内存链表，如果被释放，就意味着该块内存可以继续被分配给其他部分，如果内存被释放后再访问，就可能覆盖其他部分的信息，这是一种严重的错误，上述程序第16行中就在释放后仍然写这块内存。

下面的一段程序，就包括了内存动态管理中常见的错误。

```
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  char *p = (char *)malloc(10);
  char *pt = p;
  int i;
  for (i = 0; i < 10; i++) {
    p[i] = 'z';
  }
  delete p;
  p[1] = 'a';
  free(pt);
  return 0;
}
```

> `Valgrind提示如下
> ==25811== Mismatched free() / delete / delete []
> ==25811== at 0x4A05130: operator delete(void*) (vg_replace_malloc.c:244)
> ==25811== by 0x400654: main (sample4.c:9)
> ==25811== Address 0x4C2F030 is 0 bytes inside a block of size 10 alloc'd
> ==25811== at 0x4A05809: malloc (vg_replace_malloc.c:149)
> ==25811== by 0x400620: main (sample4.c:4)
> ==25811==
> ==25811== Invalid write of size 1
> ==25811== at 0x40065D: main (sample4.c:10)
> ==25811== Address 0x4C2F031 is 1 bytes inside a block of size 10 free'd
> ==25811== at 0x4A05130: operator delete(void*) (vg_replace_malloc.c:244)
> ==25811== by 0x400654: main (sample4.c:9)
> ==25811==
> ==25811== Invalid free() / delete / delete[]
> ==25811== at 0x4A0541E: free (vg_replace_malloc.c:233)
> ==25811== by 0x400668: main (sample4.c:11)
> ==25811== Address 0x4C2F030 is 0 bytes inside a block of size 10 free'd
> ==25811== at 0x4A05130: operator delete(void*) (vg_replace_malloc.c:244)
> ==25811== by 0x400654: main (sample4.c:9)
> ==25811==
> ==25811== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 5 from 1)
> ==25811== malloc/free: in use at exit: 0 bytes in 0 blocks.
> ==25811== malloc/free: 1 allocs, 2 frees, 10 bytes allocated.
> ==25811== For counts of detected errors, rerun with: -v
> ==25811== All heap blocks were freed -- no leaks are possible.`



#### src和dst内存覆盖

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  char x[50];
  int i;
  for (i = 0; i < 50; i++) {
    x[i] = i;
  }
  strncpy(x + 20, x, 20); // Good
  strncpy(x + 20, x, 21); // Overlap
  x[39] = '\0';
  strcpy(x, x + 20); // Good
  x[39] = 40;
  x[40] = '\0';
  strcpy(x, x + 20); // Overlap

  return 0;
}
```

> `Valgrind提示如下
> ==24139== Source and destination overlap in strncpy(0x7FEFFFC09, 0x7FEFFFBF5, 21)
> ==24139== at 0x4A0724F: strncpy (mc_replace_strmem.c:116)
> ==24139== by 0x400527: main (sample3.c:10)
> ==24139==
> ==24139== Source and destination overlap in strcpy(0x7FEFFFBE0, 0x7FEFFFBF4)
> ==24139== at 0x4A06E47: strcpy (mc_replace_strmem.c:106)
> ==24139== by 0x400555: main (sample3.c:15)
> ==24139==
> ==24139== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 5 from 1)
> ==24139== malloc/free: in use at exit: 0 bytes in 0 blocks.
> ==24139== malloc/free: 0 allocs, 0 frees, 0 bytes allocated.
> ==24139== For counts of detected errors, rerun with: -v
> ==24139== All heap blocks were freed -- no leaks are possible.`



### reference

[Valgrind Documentation](https://www.valgrind.org/docs/)

[valgrind 详细说明](https://www.cnblogs.com/wangkangluo1/archive/2011/07/20/2111273.html)

[使用 Valgrind 检测 C++ 内存泄漏](http://senlinzhan.github.io/2017/12/31/valgrind/)

[内存泄漏检查工具valgrind使用方法](https://blog.csdn.net/caohao2008/article/details/5682291)