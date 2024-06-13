cmake_minimum_required(VERSION 3.10)

#项目名称
project(Raft_SkipList_KV)

#设置CPP标准
set(CMAKE_CXX_STANDARD 20)

#设置头文件
include_directories(${PROJECT_SOURCE_DIR}/src/include)

#设置源文件
add_subdirectory(src)
add_subdirectory(test)
#
