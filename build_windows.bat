@echo off

rem 显示详细信息
echo 开始构建几何库...
echo 当前目录: %CD%

rem 检查CMake是否可用
cmake --version >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误：未找到CMake！请确保CMake已安装并添加到系统路径中。
    pause
    exit /b 1
)

rem 创建构建目录
if not exist "build" (
    echo 创建构建目录...
    mkdir build
)

rem 进入构建目录
cd build
echo 进入构建目录: %CD%

rem 尝试使用不同的Visual Studio版本
set VS_FOUND=0

rem 尝试Visual Studio 2022
echo 尝试使用Visual Studio 2022...
cmake .. -G "Visual Studio 17 2022" -A x64
if %errorlevel% equ 0 (
    echo 成功找到Visual Studio 2022
    set VS_FOUND=1
    goto build
)

rem 尝试Visual Studio 2019
echo 尝试使用Visual Studio 2019...
cmake .. -G "Visual Studio 16 2019" -A x64
if %errorlevel% equ 0 (
    echo 成功找到Visual Studio 2019
    set VS_FOUND=1
    goto build
)

rem 尝试Visual Studio 2017
echo 尝试使用Visual Studio 2017...
cmake .. -G "Visual Studio 15 2017" -A x64
if %errorlevel% equ 0 (
    echo 成功找到Visual Studio 2017
    set VS_FOUND=1
    goto build
)

rem 尝试使用MinGW生成器
if %VS_FOUND% equ 0 (
    echo 未找到Visual Studio，尝试使用MinGW生成器...
    cmake .. -G "MinGW Makefiles"
    if %errorlevel% equ 0 (
        echo 成功找到MinGW生成器
        set VS_FOUND=1
        goto build_mingw
    )
)

if %VS_FOUND% equ 0 (
    echo 错误：未找到可用的CMake生成器！
    echo 请尝试以下解决方案：
    echo 1. 安装Visual Studio 2017或更高版本
    echo 2. 安装MinGW并添加到系统路径中
    echo 3. 确保CMake已正确安装
    pause
    exit /b 1
)

build:
echo 开始构建项目...
rem 构建项目
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo 错误：构建失败！
    pause
    exit /b 1
)

rem 运行单元测试
echo 检查单元测试可执行文件...
if exist "Release\unit_tests.exe" (
    echo 运行单元测试...
    Release\unit_tests.exe
) else (
    echo 警告：未找到单元测试可执行文件！
)

rem 运行基准测试
echo 检查基准测试可执行文件...
if exist "Release\benchmark.exe" (
    echo 运行基准测试...
    Release\benchmark.exe
) else (
    echo 警告：未找到基准测试可执行文件！
)

rem 检查库文件
echo 检查库文件...
if exist "Release\geometry.dll" (
    echo 成功生成几何库：Release\geometry.dll
) else (
    echo 警告：未找到几何库文件！
)

rem 退出构建目录
cd ..

echo 构建完成！
echo 请检查上面的输出信息，确保构建成功。
pause
goto end

build_mingw:
echo 开始使用MinGW构建项目...
rem 使用MinGW构建
mingw32-make

if %errorlevel% neq 0 (
    echo 错误：构建失败！
    pause
    exit /b 1
)

rem 运行单元测试
echo 检查单元测试可执行文件...
if exist "unit_tests.exe" (
    echo 运行单元测试...
    unit_tests.exe
) else (
    echo 警告：未找到单元测试可执行文件！
)

rem 运行基准测试
echo 检查基准测试可执行文件...
if exist "benchmark.exe" (
    echo 运行基准测试...
    benchmark.exe
) else (
    echo 警告：未找到基准测试可执行文件！
)

rem 检查库文件
echo 检查库文件...
if exist "libgeometry.dll" (
    echo 成功生成几何库：libgeometry.dll
) else (
    echo 警告：未找到几何库文件！
)

rem 退出构建目录
cd ..

echo 构建完成！
echo 请检查上面的输出信息，确保构建成功。
pause

:end
