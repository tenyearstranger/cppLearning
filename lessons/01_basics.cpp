#include <iostream>
#include <string>
using namespace std;

/**
 * 模块1：基础语法与变量类型
 * 若已有C基础，这部分可以快速过
 */

int main() {
    cout << "=== C++ 基础语法 ===" << endl;
    
    // 1. 基本数据类型（与C类似）
    int age = 25;
    double height = 1.75;
    char grade = 'A';
    bool is_active = true;
    
    cout << "Age: " << age << ", Height: " << height << endl;
    
    // 2. C++特有：string 类型（相比C的char[]更好用）
    string name = "Alice";
    cout << "Name: " << name << endl;
    
    // 3. 常量
    const int MAX_SIZE = 100;
    constexpr int COMPILE_TIME_CONST = 200;  // C++11: 编译期常量
    
    // 4. 类型别名（C++11推荐用using）
    using Age = int;
    Age my_age = 30;
    
    // 5. 自动类型推导（C++11）
    auto count = 42;           // int
    auto pi = 3.14159;         // double
    auto message = "Hello";    // const char*
    
    cout << "Auto types work correctly" << endl;
    
    // 6. 范围for循环（C++11）
    int arr[] = {1, 2, 3, 4, 5};
    cout << "Array elements: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}

/**
 * 编译与运行：
 * g++ -std=c++17 -o 01_basics 01_basics.cpp
 * ./01_basics
 */
