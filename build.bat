@echo off
echo Building Five-in-a-Row Game...

REM 检查是否安装了CMake
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: CMake not found. Please install CMake first.
    echo Download from: https://cmake.org/download/
    pause
    exit /b 1
)

REM 创建构建目录
if not exist build mkdir build
cd build

REM 配置项目
echo Configuring project...
cmake .. -G "Visual Studio 16 2019" -A x64
if %errorlevel% neq 0 (
    echo Error: CMake configuration failed.
    pause
    exit /b 1
)

REM 构建项目
echo Building project...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Error: Build failed.
    pause
    exit /b 1
)

echo Build completed successfully!
echo Executable location: build\bin\Release\gobang.exe
pause
