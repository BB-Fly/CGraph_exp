#!/bin/bash

# 运行demo
echo "Running pre-lock seats demo..."

# 检查构建目录是否存在
if [ ! -d "build" ]; then
    echo "Build directory not found. Please run build.sh first."
    exit 1
fi

# 检查demo可执行文件是否存在
if [ ! -f "build/exp_pre_lock_seat" ]; then
    echo "Demo executable not found. Please run build.sh first."
    exit 1
fi

# 运行demo
cd build && ./exp_pre_lock_seat

# 回到项目根目录
cd ..

echo "Demo run completed!"
