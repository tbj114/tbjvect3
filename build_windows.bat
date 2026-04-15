@echo off

rem 创建构建目录
if not exist "build" mkdir build

rem 进入构建目录
cd build

rem 运行CMake生成解决方案
cmake .. -G "Visual Studio 16 2019" -A x64

rem 构建项目
cmake --build . --config Release

rem 运行单元测试
if exist "Release\unit_tests.exe" (
    echo 运行单元测试...
    Release\unit_tests.exe
)

rem 运行基准测试
if exist "Release\benchmark.exe" (
    echo 运行基准测试...
    Release\benchmark.exe
)

rem 退出构建目录
cd ..

echo 构建完成！
pause
