#!/bin/bash

# 创建构建目录
if [ ! -d "build" ]; then
    mkdir -p build
fi

# 进入构建目录
cd build

# 运行CMake生成Makefile
cmake ..

# 构建项目
make

# 运行单元测试
if [ -f "unit_tests" ]; then
    echo "运行单元测试..."
    ./unit_tests
fi

# 运行基准测试
if [ -f "benchmark" ]; then
    echo "运行基准测试..."
    ./benchmark
fi

# 退出构建目录
cd ..

echo "构建完成！"
