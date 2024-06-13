# 查找所有源文件
file(GLOB SKIPLIST_SOURCES ${PROJECT_SOURCE_DIR}/src/skiplist/*.cpp)

# 编译静态库
add_library(skiplist STATIC ${SKIPLIST_SOURCES})

# 设置库的输出目录
set_target_properties(skiplist PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

