#!/bin/bash

# 创建构建目录
mkdir -p build

# 检查是否安装了cmake
if command -v cmake &> /dev/null; then
    echo "Using cmake to build..."
    # 进入构建目录
    cd build
    
    # 运行cmake配置
    cmake ..
    
    # 编译项目
    cmake --build .
    
    # 复制数据文件到构建目录
    mkdir -p src/data
    cp -r ../src/data/* src/data/
    
    # 回到项目根目录
    cd ..
else
    echo "cmake not found, using g++/clang++ to build..."
    # 检查是否安装了g++
    if command -v g++ &> /dev/null; then
        COMPILER=g++
    # 检查是否安装了clang++
    elif command -v clang++ &> /dev/null; then
        COMPILER=clang++
    else
        echo "Error: Neither g++, clang++, nor cmake found."
        exit 1
    fi
    
    # 编译项目
    $COMPILER -std=c++11 -Ithirdparty -Ithirdparty/CGraph -Isrc/include src/src/main.cpp $(find thirdparty/CGraph -name "*.cpp") -o build/CGraph_exp
    
    # 复制数据文件到构建目录
    mkdir -p build/src/data
    cp -r src/data/* build/src/data/
fi

echo "Build completed successfully!"