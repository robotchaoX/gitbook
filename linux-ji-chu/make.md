# make

------

[TOC]

<!-- toc -->

------



### CMake编译

[cmake官方教程](https://cmake.org/cmake-tutorial/)

[cmake官方帮助手册](https://cmake.org/cmake/help/latest/)

[cmake使用教程](https://juejin.im/post/5a6f32e86fb9a01ca6031230)

CMake是一种跨平台编译工具，是一个集软件构建、测试、打包于一身的软件，比make更为高级。它可以根据不同平台、不同的编译器，生成相应的Makefile。CMake主要是编写CMakeLists.txt文件，然后用cmake命令将CMakeLists.txt文件转化为make所需要的makefile文件，最后用make命令编译源码生成可执行程序或共享库（so(shared object)）。

cmake  指向CMakeLists.txt所在的目录，例如cmake .. 表示CMakeLists.txt在当前目录的上一级目录。cmake后会生成很多编译的中间文件以及makefile文件，所以一般建议新建一个新的目录，专门用来编译。

CMake自动生成的Makefile不仅可以通过make命令构建项目生成目标文件，还支持安装（make install）、测试安装的程序是否能正确执行（make test，或者ctest）、生成当前平台的安装包（make package）、生成源码包（make package_source）、产生Dashboard显示数据并上传等高级功能，只要在CMakeLists.txt中简单配置，就可以完成很多复杂的功能，包括写测试用例。

make根据生成makefile文件，编译程序。

> 在 linux 平台下使用 CMake 生成 Makefile 并编译的流程如下：
>
> 1. 编写 cmake 配置文件 **CMakeLists.txt** 
>
> 2. 执行命令 `cmake PATH` 或者 `ccmake PATH` 生成 **Makefile** ,其中，`PATH` 是 CMakeLists.txt 所在的目录。
>
> 3. 使用 `make` 命令进行编译。
>
>    `ccmake` 和 `cmake` 的区别在于ccmake提供了一个交互式的界面。

```
mkdir build
cd build
cmake ..    # 指向CMakeLists.txt所在的目录,生成的makefile文件
# 编译
make    # 编译,指向makefile文件,生成执行程序
# 安装
make install  
# 测试安装的程序是否能正确执行
make test
# 将程序和相关的档案包装成一个压缩文件以供发布
make dist
# 生成当前平台的安装包
make package  
# 生成源码包
make package_source  
# 清除编译产生的可执行文件及目标文件(object file，*.o)
make clean
```

CMakeLists.txt 的语法比较简单，由命令、注释和空格组成，其中命令是不区分大小写的。符号 # 后面的内容被认为是注释。命令由命令名称、小括号和参数组成，参数之间使用空格进行间隔。

#### CMakeLists.txt文件格式

1. #设置最低版本的cmake要求
   cmake_minimum_required(VERSION 2.8)

2. #设置项目信息，一般和项目的文件夹名称对应
   project(demo_main_project)

3. #设置编译器版本
   set(CMAKE_CXX_STANDARD 14)

4. #添加头文件
   include_directories(./include)  # 把当前目录(CMakeLists.txt所在目录)下的include文件夹加入到包含路径
   include_directories(
     ${CMAKE_CURRENT_SOURCE_DIR}
     ${CMAKE_CURRENT_BINARY_DIR}
     ${CMAKE_CURRENT_LIST_DIR}/include)

5. #添加源文件
   5.2 搜索指定目录下的所有的 cpp 文件,并将结果存储在指定变量名中
   aux_source_directory(<dir> <variable>)  # 查找dir路径下的所有源文件(不会递归包含子目录)，保存到variable变量中

   ​    aux_source_directory(./src SRC_DIR)   # 搜索**./src目录**下的所有的.cpp源文件,并将结果存在**变量 SRC_DIR**中
   ​    add_executable(demo_main ${SRC_DIR})  # 给demo添加包含的源文件   

   也可以这样 add_library(demo_main ${SRC_DIR})  # 给demo添加包含的源文件

   #注意${SRC_DIR}变量**定义**一定要在**使用前**，否则会报错`No SOURCES given to target: `

     5.1 添加包含的所有源文件(数量少)
     add_library(demo demo.cpp test.cpp util.cpp)  # 给demo添加包含的源文件

6. #添加链接库文件搜索目录
   link_directories(directory1 directory2 ...)  # 添加了库包含路径directory1 directory2 ...
   link_directories( ${CMAKE_CURRENT_LIST_DIR}/lib )  # 添加./lib下的链接库

7. #设置编译类型,主函数生成可执行文件
   add_executable(demo_main demo_main.cpp)     # 生成可执行文件

8. #添加可执行文件 target 需要链接的库文件,等效与g++ -l库文件名
   target_link_libraries(<name> lib1 lib2 lib3)  # 将lib1, lib2, lib3链接到<name>上
   target_link_libraries(demo_main util)  
   #字叫demo_main这个target需要链接util这个库，会优先搜索libutil.a， 如果没有就搜索libutil.so
    8.1 #指定链接动态库或静态库
     target_link_libraries(demo libface.a) # 链接libface.a
     target_link_libraries(demo libface.so) # 链接libface.so
     8.2 #指定全路径
     target_link_libraries(demo ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
     8.3 #指定链接多个库
     target_link_libraries(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a
        boost_system.a
        boost_thread
        pthread)

   

#查找指定的库文件？？
find_package(OpenCV 2.4.3 REQUIRED)
  find_library()
  类似的命令还有 find_file()、find_path()、find_program()、find_package()。

3.add_library 添加库？？
3.1 添加一个库

```
add_library(<name> [STATIC | SHARED | MODULE] [EXCLUDE_FROM_ALL] source1 source2 ... sourceN)
```

添加一个名为<name>的库文件
指定STATIC, SHARED, MODULE参数来指定要创建的库的类型, 
STATIC对应的静态库 .a
SHARED对应共享动态库.so
[EXCLUDE_FROM_ALL], 如果指定了这一属性，对应的一些属性会在目标被创建时被设置(指明此目录和子目录中所有的目标，是否应当从默认构建中排除, 子目录的IDE工程文件/Makefile将从顶级IDE工程文件/Makefile中排除)
source1 source2 ... sourceN用来指定源文件
3.2 导入已有的库
add_library(<name> [STATIC | SHARED | MODULE | UNKNOWN] IMPORTED)
导入了一个已存在的<name>库文件，导入库一般配合set_target_properties使用，这个命令用来指定导入库的路径,比如：

> add_library(test SHARED IMPORTED)
> set_target_properties(  test #指定目标库名称
>                         PROPERTIES IMPORTED_LOCATION #指明要设置的参数
>                         libs/src/${ANDROID_ABI}/libtest.so #设定导入库的路径)

add_library(common STATIC util.cpp)     # 生成静态库 .a
add_library(common SHARED util.cpp)     # 生成动态共享库 .so

1. add_subdirectory 如果当前目录下还有子目录时可以使用add_subdirectory，子目录中也需要包含有CMakeLists.txt
2. file文件操作命令

三、常用变量

1. 预定义变量
   PROJECT_NAME：项目名称
   PROJECT_SOURCE_DIR：工程的根目录
   CMAKE_CURRENT_LIST_DIR：CMakeLists.txt 的完整路径
   CMAKE_CURRENT_SOURCE_DIR：当前处理的 CMakeLists.txt 所在的路径
   PROJECT_BINARY_DIR：运行 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}/build
   CMAKE_CURRENT_BINARY_DIR：target 编译目录
   CMAKE_CURRENT_LIST_LINE：当前所在的行
   CMAKE_MODULE_PATH：定义自己的 cmake 模块所在的路径，SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)，然后可以用INCLUDE命令来调用自己的模块
   EXECUTABLE_OUTPUT_PATH：重新定义可执行文件的输出路径
   LIBRARY_OUTPUT_PATH：重新定义目标链接库文件的输出路径
2. 环境变量
   env
3. 系统信息
   CMAKE_MAJOR_VERSION：cmake 主版本号，比如 3.4.1 中的 3
   CMAKE_MINOR_VERSION：cmake 次版本号，比如 3.4.1 中的 4
   CMAKE_PATCH_VERSION：cmake 补丁等级，比如 3.4.1 中的 1
   CMAKE_SYSTEM：系统名称，比如 Linux-­2.6.22
   CMAKE_SYSTEM_NAME：不包含版本的系统名，比如 Linux
   CMAKE_SYSTEM_VERSION：系统版本，比如 2.6.22
   CMAKE_SYSTEM_PROCESSOR：处理器名称，比如 i686
   UNIX：在所有的类 UNIX 平台下该值为 TRUE，包括 OS X 和 cygwin
   WIN32：在所有的 win32 平台下该值为 TRUE，包括 cygwin
4. 主要开关选项
   BUILD_SHARED_LIBS：这个开关用来控制默认的库编译方式，如果不进行设置，使用 add_library 又没有指定库类型的情况下，默认编译生成的库都是静态库。如果 set(BUILD_SHARED_LIBS ON) 后，默认生成的为动态库
   CMAKE_CXX_FLAGS：设置 C++ 编译选项

#设置可执行文件的输出路径(EXCUTABLE_OUTPUT_PATH是全局变量)
set(EXECUTABLE_OUTPUT_PATH [output_path])
如set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#设置库文件的输出路径(LIBRARY_OUTPUT_PATH是全局变量)
set(LIBRARY_OUTPUT_PATH [output_path])

#设置编译模式
set( CMAKE_BUILD_TYPE "Debug" )
#set( CMAKE_BUILD_TYPE "Release" )

#设置C++编译参数(CMAKE_CXX_FLAGS是全局变量)
set(CMAKE_CXX_FLAGS   "-std=c++11")             # c++11
set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告

#9. 设置变量
#9.1 set 直接设置变量的值
set(SRC_LIST main.cpp test.cpp)
add_executable(demo ${SRC_LIST})
#9.2 set 追加设置变量的值
set(SRC_LIST main.cpp)
set(SRC_LIST ${SRC_LIST} test.cpp)
add_executable(demo ${SRC_LIST})
#9.3 list 追加或者删除变量的值
set(SRC_LIST main.cpp)
list(APPEND SRC_LIST test.cpp)
list(REMOVE_ITEM SRC_LIST main.cpp)
add_executable(demo ${SRC_LIST})



#### install 安装规则

[install 指定在安装时要运行的规则](https://www.cnblogs.com/coderfenghc/archive/2012/08/12/2627561.html)





报错： undefined reference to ......

[C++程序报错undefined reference to](https://www.cnblogs.com/herenzhiming/articles/5067879.html)

在C++代码中调用C的库文件，需加上extern "C"，用来告知编译器：这是一个用C写成的库文件，请用C的方式连接他们。

Undefined reference to 错误:这类错误是在连接过程中出现的，可能有两种原因∶

一是使用者自己定义的函数或者全局变量所在源代码文件，没有被编译、连接，或者干脆还没有定义，这 需要使用者根据实际情况修改源程序，给出全局变量或者函数的定义体；

二是未定义的符号是一个标准的库函数，在源程序中使用了该库函数，而连接过程中还没有 给定相应的函数库的名称，或者是该档案库的目录名称有问题.



### makefile

[Make 命令教程](http://www.ruanyifeng.com/blog/2015/02/make.html)

Makefile文件的格式

Makefile文件由一系列规则（rules）构成。每条规则的形式如下。

```
<target> : <prerequisites> 
[tab]  <commands>
```

上面第一行冒号前面的部分，叫做"目标"（target），冒号后面的部分叫做"前置条件"（prerequisites）；第二行必须由一个tab键起首，后面跟着"命令"（commands）。

"目标"是必需的，不可省略；"前置条件"和"命令"都是可选的，但是两者之中必须至少存在一个。

每条规则就明确两件事：构建目标的前置条件是什么，以及如何构建。下面就详细讲解，每条规则的这三个组成部分。









### CLion

> Ctrl + / 添加或删除注释
> Ctrl + Alt + L 格式化代码
> Alt + Enter 智能提示
> Ctrl + R 替换
> Ctrl + Shift + R 全局替换
> Ctrl + F 搜索
> Ctrl + Shift + F 全局搜索
> Ctrl + B 在定义和申明之间跳转
> Ctrl + Shift + Backspace 回到最后编辑的地方
> Alt + 鼠标选择  多行编辑
> Shift + Enter 在下面新开一行
> Ctrl + Alt + -/+ 展开折叠当前函数、类
> Ctrl + Shift + -/+ 展开折叠所有函数、类Ctrl + N 查找类
> Ctrl + Q 快速查看文档
> Ctrl + P 提示参数信息
> Ctrl + H 查看继承树
> Ctrl + Shift + N 找文件
> Shift + Shift 全局搜索

在keymap快捷键找到 related symbol :  .h 和.CPPcpp切换



### VS Code

ctrl+shift+n   打开新窗口









































