project(test_delete)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 设置Debug模式
SET(CMAKE_BUILD_TYPE "Debug")

# 设置要编译的头文件
set(HEADER_FILES 
    ../../include/include.h
    )

# 设置要编译的源文件
set(SOURCE_FILES 
    ./delete_test.cpp
    ../../skiplist/skiplist.cpp
    )

# 生成可执行文件
add_executable(test_delete ${SOURCE_FILES} ${HEADER_FILES})