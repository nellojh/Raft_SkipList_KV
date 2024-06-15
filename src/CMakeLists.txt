# 查找源文件
file(GLOB SKIPLIST_SOURCES skiplist/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# 添加静态库
add_library(skiplist STATIC ${SKIPLIST_SOURCES})

# 设置库文件输出目录
set_target_properties(skiplist PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)

