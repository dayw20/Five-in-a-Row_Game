#!/bin/bash

echo "Building Five-in-a-Row Game..."

# 检查是否安装了CMake
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake not found. Please install CMake first."
    echo "Ubuntu/Debian: sudo apt-get install cmake"
    echo "CentOS/RHEL: sudo yum install cmake"
    echo "macOS: brew install cmake"
    exit 1
fi

# 创建构建目录
mkdir -p build
cd build

# 配置项目
echo "Configuring project..."
cmake ..
if [ $? -ne 0 ]; then
    echo "Error: CMake configuration failed."
    exit 1
fi

# 构建项目
echo "Building project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
if [ $? -ne 0 ]; then
    echo "Error: Build failed."
    exit 1
fi

echo "Build completed successfully!"
echo "Executable location: build/bin/gobang"

# 设置执行权限
chmod +x bin/gobang
