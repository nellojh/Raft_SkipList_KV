# 查找测试源文件
file(GLOB TEST_SOURCES skiplist/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# 添加可执行文件
add_executable(skiplist_test ${TEST_SOURCES})

# 设置可执行文件输出位置
set_target_properties(skiplist_test PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# 链接库
target_link_libraries(skiplist_test PRIVATE skiplist)

