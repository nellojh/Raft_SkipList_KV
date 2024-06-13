# FIND ALL SOURCE 
file(GLOB SKIPLIST_SOURCES ${PROJECT_SOURCE_DIR}/src/skiplist/*.cpp)

# add static
add_library(skiplist STATIC ${SKIPLIST_SOURCES})

# output
set_target_properties(skiplist PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
)
