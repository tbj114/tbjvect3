cmake_minimum_required(VERSION 3.10)
project(geometry_library)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建动态链接库
add_library(geometry SHARED
    src/core/geometry.cpp
    src/c_interface/geometry_c.cpp
)

# 包含头文件目录
target_include_directories(geometry PRIVATE
    src/core
    src/c_interface
)

# 安装库
install(TARGETS geometry
    LIBRARY DESTINATION lib
)

# 安装头文件
install(FILES src/core/geometry.h DESTINATION include/geometry)
install(FILES src/c_interface/geometry_c.h DESTINATION include/geometry)
