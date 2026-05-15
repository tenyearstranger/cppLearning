#include <iostream>
#include <string>
using namespace std;

/**
 * 模块3：函数与作用域
 */

// ============ 基本函数定义 ============
int add(int a, int b) {
    return a + b;
}

// ============ 函数声明（前向声明） ============
void greet(const string& name);

// ============ 默认参数 ============
void print_with_prefix(const string& text, const string& prefix = ">> ") {
    cout << prefix << text << endl;
}

// ============ 函数重载 ============
void print(int x) {
    cout << "Integer: " << x << endl;
}

void print(double x) {
    cout << "Double: " << x << endl;
}

void print(const string& s) {
    cout << "String: " << s << endl;
}

// ============ 变长参数（C风格）============
#include <cstdarg>

double average(int count, ...) {
    double sum = 0;
    va_list args;
    va_start(args, count);
    
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }
    
    va_end(args);
    return sum / count;
}

// ============ 变长参数（现代C++风格）============
template<typename... Args>
int sum_variadic(Args... args) {
    return (args + ... + 0);
}

// ============ 返回引用 ============
int global_var = 42;

int& get_reference() {
    return global_var;  // 返回引用
}

// ============ 指向函数的指针 ============
typedef int (*MathFunc)(int, int);

int multiply(int a, int b) {
    return a * b;
}

// ============ lambda与std::function ============
#include <functional>

void apply_operation(int a, int b, function<void(int, int)> op) {
    op(a, b);
}

// ============ 作用域示例 ============
int global_x = 100;  // 全局作用域

class MyClass {
public:
    static int static_x;  // 类作用域的静态变量
    
    void member_function() {
        int local_x = 1;  // 局部作用域
    }
};

int MyClass::static_x = 200;

// ============ 命名空间 ============
namespace MyNamespace {
    int value = 42;
    
    void function() {
        cout << "MyNamespace::function()" << endl;
    }
}

namespace {  // 匿名命名空间（内部链接）
    void private_function() {
        cout << "Private to this file" << endl;
    }
}

// ============ 函数对象 ============
class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    int operator()(int x) const {
        return x * factor;
    }
};

int main() {
    cout << "=== 函数与作用域 ===" << endl;
    
    // ============ 基本函数调用 ============
    cout << "\n--- 基本函数 ---" << endl;
    cout << "5 + 3 = " << add(5, 3) << endl;
    
    // ============ 函数声明的使用 ============
    greet("Alice");
    
    // ============ 默认参数 ============
    cout << "\n--- 默认参数 ---" << endl;
    print_with_prefix("Hello");
    print_with_prefix("World", ">>> ");
    
    // ============ 函数重载 ============
    cout << "\n--- 函数重载 ---" << endl;
    print(42);
    print(3.14);
    print("C++");
    
    // ============ 变长参数 ============
    cout << "\n--- 变长参数 ---" << endl;
    cout << "Average (C风格): " << average(3, 10, 20, 30) << endl;
    cout << "Sum (现代C++): " << sum_variadic(1, 2, 3, 4, 5) << endl;
    
    // ============ 返回引用 ============
    cout << "\n--- 返回引用 ---" << endl;
    int& ref = get_reference();
    cout << "Reference value: " << ref << endl;
    ref = 99;
    cout << "After modification: " << global_var << endl;
    
    // ============ 函数指针 ============
    cout << "\n--- 函数指针 ---" << endl;
    MathFunc func = multiply;
    cout << "4 * 5 = " << func(4, 5) << endl;
    
    // ============ lambda函数 ============
    cout << "\n--- Lambda函数 ---" << endl;
    auto subtract = [](int a, int b) { return a - b; };
    cout << "10 - 3 = " << subtract(10, 3) << endl;
    
    apply_operation(5, 3, [](int a, int b) {
        cout << a << " + " << b << " = " << (a + b) << endl;
    });
    
    // ============ 函数对象 ============
    cout << "\n--- 函数对象 ---" << endl;
    Multiplier times_three(3);
    cout << "5 * 3 = " << times_three(5) << endl;
    
    // ============ 作用域演示 ============
    cout << "\n--- 作用域 ---" << endl;
    
    int local_var = 1;
    cout << "Local variable: " << local_var << endl;
    
    {
        int local_var = 2;  // 新的作用域，遮蔽外层变量
        cout << "Inside block: " << local_var << endl;
    }
    
    cout << "After block: " << local_var << endl;
    
    // ============ 全局变量 ============
    cout << "\n--- 全局变量 ---" << endl;
    cout << "Global x: " << global_x << endl;
    
    // ============ 命名空间 ============
    cout << "\n--- 命名空间 ---" << endl;
    cout << "MyNamespace::value = " << MyNamespace::value << endl;
    MyNamespace::function();
    
    using namespace MyNamespace;  // 引入命名空间
    cout << "Direct access: " << value << endl;
    function();
    
    // ============ 静态变量 ============
    cout << "\n--- 静态变量 ---" << endl;
    
    auto count_calls = []() {
        static int call_count = 0;  // 只初始化一次
        call_count++;
        cout << "Call count: " << call_count << endl;
    };
    
    count_calls();
    count_calls();
    count_calls();
    
    // ============ 局部类 ============
    cout << "\n--- 局部类（C++11） ---" << endl;
    
    class LocalClass {
    public:
        void display() {
            cout << "Local class method" << endl;
        }
    };
    
    LocalClass obj;
    obj.display();
    
    return 0;
}

// ============ 函数定义（放在main之后） ============
void greet(const string& name) {
    cout << "Hello, " << name << "!" << endl;
}

/**
 * 作用域与生命周期：
 * 
 * 全局作用域：
 * - 程序开始到结束
 * - 命名空间、文件级作用域
 * 
 * 函数作用域：
 * - 从函数开始到结束
 * - 局部变量
 * 
 * 块作用域：
 * - 从声明到块结束
 * - 可以嵌套（内层遮蔽外层）
 * 
 * 类作用域：
 * - 成员变量和方法
 * - public/private/protected
 * 
 * 函数名称改写：
 * - 函数重载基于参数类型
 * - 编译器内部生成唯一的符号名
 */
