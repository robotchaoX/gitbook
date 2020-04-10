cmake_minimum_required(VERSION 3.0.0)

project(test01)

# 设置 C语言标准
set(CMAKE_C_STANDARD 99)  # 90, 99, 11
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)  # 98, 11, 14, 17, 20.

# 添加头文件路径
include_directories(./ ./include ./src )

# 添加源文件路径 
aux_source_directory(./ SRC_DIR_CURT)
aux_source_directory(./src SRC_DIR_SRC)
set(SRC_FILES ${SRC_DIR_SRC} ${SRC_DIR_CURT} )

# 主函数生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_FILES}  )
 
# 链接pthread库
target_link_libraries(${PROJECT_NAME} -lpthread)
