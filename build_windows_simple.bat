@echo off

REM Simple build script for Windows
REM This script builds the geometry library using CMake

ECHO Starting build process...
ECHO Current directory: %CD%

REM Check if CMake is available
cmake --version >nul 2>&1
if %errorlevel% neq 0 (
    ECHO Error: CMake not found! Please make sure CMake is installed and added to system PATH.
    PAUSE
    exit /b 1
)

REM Create build directory if it doesn't exist
if not exist "build" (
    ECHO Creating build directory...
    mkdir build
)

REM Change to build directory
cd build
ECHO Changed to build directory: %CD%

REM Try to generate build files with CMake
ECHO Generating build files with CMake...
cmake ..

if %errorlevel% neq 0 (
    ECHO Error: Failed to generate build files!
    ECHO Please check if you have a C++ compiler installed.
    PAUSE
    exit /b 1
)

REM Build the project
ECHO Building the project...
cmake --build . --config Release

if %errorlevel% neq 0 (
    ECHO Error: Build failed!
    PAUSE
    exit /b 1
)

REM Check if the library was built successfully
if exist "Release\geometry.dll" (
    ECHO Success: Geometry library built successfully!
    ECHO Library location: %CD%\Release\geometry.dll
) else (
    ECHO Warning: Geometry library not found!
)

REM Check if unit tests were built
if exist "Release\unit_tests.exe" (
    ECHO Success: Unit tests built successfully!
    ECHO Running unit tests...
    Release\unit_tests.exe
) else (
    ECHO Warning: Unit tests not found!
)

REM Check if benchmark was built
if exist "Release\benchmark.exe" (
    ECHO Success: Benchmark built successfully!
    ECHO Running benchmark...
    Release\benchmark.exe
) else (
    ECHO Warning: Benchmark not found!
)

REM Change back to original directory
cd ..

ECHO Build process completed!
ECHO Please check the output above for any errors.
PAUSE
