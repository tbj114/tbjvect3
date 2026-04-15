@echo off

rem 创建构建目录
if not exist "build" mkdir build

rem 进入构建目录
cd build

rem 尝试使用不同的Visual Studio版本
set VS_FOUND=0

rem 尝试Visual Studio 2022
cmake .. -G "Visual Studio 17 2022" -A x64
if %errorlevel% equ 0 (
    set VS_FOUND=1
    goto build
)

rem 尝试Visual Studio 2019
cmake .. -G "Visual Studio 16 2019" -A x64
if %errorlevel% equ 0 (
    set VS_FOUND=1
    goto build
)

rem 尝试Visual Studio 2017
cmake .. -G "Visual Studio 15 2017" -A x64
if %errorlevel% equ 0 (
    set VS_FOUND=1
    goto build
)

rem 尝试使用MinGW生成器
if %VS_FOUND% equ 0 (
    echo 未找到Visual Studio，尝试使用MinGW生成器...
    cmake .. -G "MinGW Makefiles"
    if %errorlevel% equ 0 (
        set VS_FOUND=1
        goto build_mingw
    )
)

if %VS_FOUND% equ 0 (
    echo 错误：未找到可用的CMake生成器！
    pause
    exit /b 1
)

build:
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
goto end

build_mingw:
rem 使用MinGW构建
mingw32-make

rem 运行单元测试
if exist "unit_tests.exe" (
    echo 运行单元测试...
    unit_tests.exe
)

rem 运行基准测试
if exist "benchmark.exe" (
    echo 运行基准测试...
    benchmark.exe
)

rem 退出构建目录
cd ..

echo 构建完成！
pause

:end
