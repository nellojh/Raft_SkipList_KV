cmake_minimum_required(VERSION 3.10)
project(SkipListProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# 添加子目录
add_subdirectory(src)
add_subdirectory(test)
# 添加库
