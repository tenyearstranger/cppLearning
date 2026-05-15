#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

/**
 * 模块15：移动语义 ⭐
 * C++11最重要的特性之一
 */

// ============ 问题：深拷贝的低效 ============
class String {
private:
    char* data;
    int size;
    
public:
    // 构造函数
    String(const char* s = "") {
        size = strlen(s);
        data = new char[size + 1];
        strcpy(data, s);
        cout << "Constructor called for: " << s << endl;
    }
    
    // 拷贝构造（深拷贝）
    String(const String& other) {
        size = other.size;
        data = new char[size + 1];
        strcpy(data, other.data);
        cout << "Copy constructor called for: " << data << endl;
    }
    
    // 移动构造（C++11）- 窃取资源
    String(String&& other) noexcept {
        data = other.data;
        size = other.size;
        
        other.data = nullptr;  // 清空原对象
        other.size = 0;
        
        cout << "Move constructor called for: " << data << endl;
    }
    
    // 拷贝赋值
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            
            size = other.size;
            data = new char[size + 1];
            strcpy(data, other.data);
            
            cout << "Copy assignment for: " << data << endl;
        }
        return *this;
    }
    
    // 移动赋值（C++11）
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            data = other.data;
            size = other.size;
            
            other.data = nullptr;
            other.size = 0;
            
            cout << "Move assignment for: " << data << endl;
        }
        return *this;
    }
    
    ~String() {
        delete[] data;
        cout << "Destructor called" << endl;
    }
    
    void display() const {
        if (data) {
            cout << "String: " << data << endl;
        }
    }
};

// ============ 左值与右值 ============
/**
 * 左值 (lvalue): 有地址的值，可以在赋值号左边
 * - 变量、数组元素等
 * - 可以取地址
 * 
 * 右值 (rvalue): 临时值，不能在赋值号左边
 * - 字面值、函数返回值、表达式结果
 * - 不能取地址
 * 
 * 右值引用 (rvalue reference): T&&
 * - 只能绑定右值
 * - 目的是窃取资源
 */

void demonstrate_lvalue_rvalue() {
    cout << "\n--- 左值与右值 ---" << endl;
    
    String s1("Hello");      // 左值
    String s2 = s1;          // 调用拷贝构造
    String s3 = String("World");  // 右值，调用移动构造
    
    // String s4 = s1 + s2;   // 如果+返回右值，调用移动构造
}

// ============ std::move 强制转换为右值 ============
void move_example() {
    cout << "\n--- std::move 示例 ---" << endl;
    
    String s1("Original");
    String s2 = move(s1);  // 强制调用移动构造
    
    cout << "After move:" << endl;
    s2.display();
    // s1现在是空的！
}

// ============ 完美转发 ============
template<typename T>
void relay(T&& arg) {
    // forward保留参数的值类别
    process(forward<T>(arg));
}

void process(const String& s) {
    cout << "Processing lvalue reference" << endl;
    s.display();
}

void process(String&& s) {
    cout << "Processing rvalue reference" << endl;
    s.display();
}

// ============ 返回值优化(RVO) ============
String create_string() {
    String temp("RVO_String");
    return temp;  // 编译器优化：调用移动构造而不是拷贝
}

// ============ 容器中的移动 ============
void container_move_demo() {
    cout << "\n--- 容器中的移动语义 ---" << endl;
    
    vector<String> strings;
    
    strings.push_back(String("Item1"));  // 移动构造
    strings.push_back(String("Item2"));  // 移动构造
    
    String s = create_string();  // 移动构造
    strings.push_back(move(s));   // 移动
}

// ============ 移动迭代器 ============
void move_iterator_demo() {
    cout << "\n--- 移动迭代器 ---" << endl;
    
    vector<String> v1;
    v1.push_back(String("A"));
    v1.push_back(String("B"));
    
    vector<String> v2;
    // 从v1移动元素到v2
    copy(make_move_iterator(v1.begin()),
         make_move_iterator(v1.end()),
         back_inserter(v2));
}

// ============ noexcept与移动 ============
/**
 * 移动操作通常标记为 noexcept
 * 原因：
 * - 如果移动构造抛异常，容器可能处于不一致状态
 * - 标记noexcept让编译器进行更多优化
 * - 确保强异常安全
 */

// ============ 返回多个值（C++17）============
#include <tuple>

tuple<int, string, double> get_data() {
    return make_tuple(42, "answer", 3.14);
}

void structured_binding_demo() {
    cout << "\n--- 结构化绑定(C++17) ---" << endl;
    
    auto [number, text, pi] = get_data();
    cout << "Number: " << number << ", Text: " << text << ", Pi: " << pi << endl;
}

// ============ 通用引用（转发引用） ============
template<typename T>
void handle(T&& param) {
    // T&&在模板中是转发引用，可以绑定左值也可以绑定右值
    forward_impl(forward<T>(param));
}

void forward_impl(const String& s) {
    cout << "Got lvalue reference" << endl;
}

void forward_impl(String&& s) {
    cout << "Got rvalue reference" << endl;
}

int main() {
    cout << "=== 移动语义 ===" << endl;
    
    // ============ 基本示例 ============
    cout << "\n--- 基本移动示例 ---" << endl;
    {
        String original("Important Data");
        String moved = move(original);  // 移动而不是拷贝
    }
    
    // ============ 左值与右值 ============
    demonstrate_lvalue_rvalue();
    
    // ============ std::move ============
    move_example();
    
    // ============ 返回值优化 ============
    cout << "\n--- 返回值优化 ---" << endl;
    String s = create_string();
    
    // ============ 容器 ============
    container_move_demo();
    
    // ============ 移动迭代器 ============
    move_iterator_demo();
    
    // ============ 结构化绑定 ============
    structured_binding_demo();
    
    // ============ 转发引用 ============
    cout << "\n--- 转发引用 ---" << endl;
    String lval("LeftValue");
    handle(lval);                      // 左值
    handle(String("RightValue"));      // 右值
    
    cout << "\n=== 移动语义总结 ===" << endl;
    cout << "1. 右值引用T&&允许转移资源所有权" << endl;
    cout << "2. std::move将左值转换为右值引用" << endl;
    cout << "3. 标记移动操作为noexcept" << endl;
    cout << "4. 使用std::forward进行完美转发" << endl;
    cout << "5. 避免不必要的拷贝，提高性能" << endl;
    
    return 0;
}

/**
 * 移动语义的好处：
 * 1. 性能提升：避免深拷贝开销
 * 2. 资源管理：自然的所有权转移
 * 3. 容器效率：push_back/emplace_back更快
 * 4. 写时复制(COW)等技术的基础
 * 
 * 与其他语言对比：
 * - Java/Python: 垃圾回收，自动内存管理
 * - C#: 类是引用类型，值类型没有移动
 * - C++: 值语义，支持零成本抽象
 */
