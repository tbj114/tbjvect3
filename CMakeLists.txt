cmake_minimum_required(VERSION 3.10)
project(geometry_library)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 跨平台支持
if(WIN32)
    # Windows特定设置
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0600 -DGEOMETRY_EXPORTS)
elseif(UNIX)
    # Linux/macOS特定设置
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# 创建动态链接库
add_library(geometry SHARED
    src/core/geometry.cpp
    src/core/matrix.cpp
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
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
)

# 安装头文件
install(FILES src/core/geometry.h src/core/matrix.h DESTINATION include/geometry)
install(FILES src/c_interface/geometry_c.h DESTINATION include/geometry)

# 构建单元测试
add_executable(unit_tests src/tests/unit_tests.cpp)
target_link_libraries(unit_tests geometry)
target_include_directories(unit_tests PRIVATE src/core)

# 构建基准测试
add_executable(benchmark src/tests/benchmark.cpp)
target_link_libraries(benchmark geometry)
target_include_directories(benchmark PRIVATE src/core)
