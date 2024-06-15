cmake_minimum_required(VERSION 3.10)

# 项目名称
project(SkipListProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 添加子目录
add_subdirectory(src)
add_subdirectory(test)

# 添加库目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

