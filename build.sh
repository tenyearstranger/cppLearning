#!/bin/bash
# C++ 编译和运行脚本

COMPILER="g++"
STD_FLAG="-std=c++17"
WARNINGS="-Wall -Wextra -Werror=return-type"
OUTPUT_DIR="./build"

# 创建输出目录
mkdir -p $OUTPUT_DIR

# 编译函数
compile_file() {
    local file=$1
    local name=$(basename "$file" .cpp)
    local output="$OUTPUT_DIR/$name"
    
    echo "编译: $file"
    $COMPILER $STD_FLAG $WARNINGS -o "$output" "$file"
    
    if [ $? -eq 0 ]; then
        echo "✓ 编译成功: $output"
        return 0
    else
        echo "✗ 编译失败"
        return 1
    fi
}

# 运行函数
run_file() {
    local name=$1
    local output="$OUTPUT_DIR/$name"
    
    if [ -f "$output" ]; then
        echo ""
        echo "========== 运行: $name =========="
        "$output"
        echo "=================================="
        echo ""
    else
        echo "✗ 文件不存在: $output"
    fi
}

# 主程序
case $1 in
    compile)
        if [ -n "$2" ]; then
            compile_file "$2"
        else
            echo "用法: $0 compile <file.cpp>"
        fi
        ;;
    run)
        if [ -n "$2" ]; then
            run_file "$2"
        else
            echo "用法: $0 run <program_name>"
        fi
        ;;
    all)
        # 编译所有cpp文件
        for file in *.cpp; do
            compile_file "$file"
        done
        echo "所有文件编译完成！"
        ;;
    *)
        echo "用法:"
        echo "  $0 compile <file.cpp>  - 编译单个文件"
        echo "  $0 run <program_name>  - 运行编译后的程序"
        echo "  $0 all                 - 编译所有文件"
esac
